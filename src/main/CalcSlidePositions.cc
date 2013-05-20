#include "../COINCEvent.hh"
#include "../LYSORun.hh"
#include "../GERun.hh"

void CalcSlidePos(string fileName, int nSlidePos);

int main(int argc, char *argv[])
{
	string fileName;
  int nSlidePos;

  // Handle the command line arguments
  switch(argc)
  {
    case 3:
			fileName = (string)argv[1];
      nSlidePos = atoi(argv[2]);
      cout << "Calculating Gauss & Lerche slide positions with " << nSlidePos << " positions." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [COINC or LYSO ROOT file] [n positions]" << endl;
      return 1;
  }

  CalcSlidePos(fileName, nSlidePos);

  return 0;
}

void CalcSlidePos(string fileName, int nSlidePos)
{
	double lercheXPos, lercheYPos, gaussXPos, gaussYPos;
	vector<double> chi2LX, chi2LY, chi2GX, chi2GY;
  // ROOT stuff
  TFile *rootFile = new TFile(fileName.c_str(), "UPDATE");
	// Determine if it's an LYSO file or coincident file
	bool coinc = false;
	TTree *eventTree;
	COINCEvent *cEvent = new COINCEvent();
	LYSOEvent *lEvent= new LYSOEvent();
	// find() returns string::npos if the argument is not found (COINC file)
	if(fileName.find("lyso") == string::npos)
	{
  	eventTree = (TTree*)rootFile->Get("COINCEvents");
  	eventTree->SetBranchAddress("event", &cEvent);
		coinc = true;
	}
	else
	{
		eventTree = (TTree*)rootFile->Get("LYSOEvents");
  	eventTree->SetBranchAddress("event", &lEvent);
	}

	// Set the branch name depending on the number of sliding positions for clarity
	string NPos = to_string(nSlidePos) + "Pos";
	string tName = to_string(nSlidePos) + "Positions";
	TTree *posTree = new TTree(tName.c_str(), tName.c_str());
	string bName = "lercheX" + NPos;
	posTree->Branch(bName.c_str(), &lercheXPos);
	bName = "lercheY" + NPos;
	posTree->Branch(bName.c_str(), &lercheYPos);
	bName = "gaussX" + NPos;
	posTree->Branch(bName.c_str(), &gaussXPos);
	bName = "gaussY" + NPos;
	posTree->Branch(bName.c_str(), &gaussYPos);
	bName = "chi2LX" + NPos;
	posTree->Branch(bName.c_str(), &chi2LX);
	bName = "chi2LY" + NPos;
	posTree->Branch(bName.c_str(), &chi2LY);
	bName = "chi2GX" + NPos;
	posTree->Branch(bName.c_str(), &chi2GX);
	bName = "chi2GY" + NPos;
	posTree->Branch(bName.c_str(), &chi2GY);
  cout << "ROOT file loaded, tree created." << endl;
	
	// Fitting functions
	TF1 fitGauss("fitGauss", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]");
	// Lerche distribution
	string temp = "(sqrt(((x-[2])**2)+2.25))";
	string ex = "(exp((-1.0)*[1]*"+temp+"))";
  string sLerche = "[0]*[1]*"+ex+"/"+temp+"*(atan((25.0-[3])/"+temp+")-atan((-25.0-[3])/"+temp+"))";
  sLerche += "+[4]";
	TF1 fitLerche("lerche", sLerche.c_str());


	TH1D hx("hx", "X Projection", 8, 0.0, 49.0);
	TH1D hy("hy", "Y Projection", 8, 0.0, 49.0);
	LYSOEvent *ev = new LYSOEvent();
	int x, y;
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);
		hx.Reset();
		hy.Reset();

		// Project the charge
		for(int k=0;k < 64;k++)
		{
			ev->ChanNumToXYPos(k, x, y);
			if(coinc)
			{
				hx.Fill(x, cEvent->GetChargeGC().at(k));
				hy.Fill(y, cEvent->GetChargeGC().at(k));
			}
			else
			{
				hx.Fill(x, lEvent->GetChargeGC().at(k));
				hy.Fill(y, lEvent->GetChargeGC().at(k));
			}

		}

		// Slide
		// Gauss parameters and value trackers
		double slidePosition = 0.0;
		double minChi2X = 50000000.0;			// something big
		double posMinX = 0.0;
		double minChi2Y = 50000000.0;
		double posMinY = 0.0;
		double ampX = hx.GetBinContent(hx.GetMaximumBin());
		double TX = hx.GetBinContent(hx.GetMinimumBin());
		double ampY = hy.GetBinContent(hy.GetMaximumBin());
		double TY = hy.GetBinContent(hy.GetMinimumBin());
		// Lerche parameters and value trackers
		double minChi2LX = 50000000.0;			// something big
		double posMinLX = 0.0;
		double minChi2LY = 50000000.0;
		double posMinLY = 0.0;
		double ampLX = hx.GetBinContent(hx.GetMaximumBin());
		double TLX = hx.GetBinContent(hx.GetMinimumBin());
		double ampLY = hy.GetBinContent(hy.GetMaximumBin());
		double TLY = hy.GetBinContent(hy.GetMinimumBin());
		chi2LX.clear();
		chi2LY.clear();
		chi2GX.clear();
		chi2GY.clear();
		for(int i=0;i < nSlidePos;i++)
		{
			double tempChi2;
			// Gauss calculation
			fitGauss.FixParameter(0, ampX);
			fitGauss.FixParameter(1, slidePosition);
	  	fitGauss.FixParameter(2, 5.09); // sigma in mm
			fitGauss.SetParameter(3, TX);
			hx.Fit("fitGauss", "NBQ");
			tempChi2 = (double)fitGauss.GetChisquare();
			if(tempChi2 < minChi2X)
			{
				minChi2X = tempChi2;
				posMinX = slidePosition;
			}
			chi2GX.push_back(tempChi2);
			fitGauss.FixParameter(0, ampY);
			fitGauss.FixParameter(2, 5.06);
			fitGauss.SetParameter(3, TY);
			hy.Fit("fitGauss", "NBQ");
			tempChi2 = (double)fitGauss.GetChisquare();
			if(tempChi2 < minChi2Y)
			{
				minChi2Y = tempChi2;
				posMinY = slidePosition;
			}
			chi2GY.push_back(tempChi2);

			// Lerche calculation
			fitLerche.SetParameter(0, ampLX*3.0);
	  	fitLerche.FixParameter(1, 0.2071);//alpha
			fitLerche.FixParameter(2, slidePosition);
	  	fitLerche.FixParameter(3, 36.4);//yo
			fitLerche.SetParameter(4, TLX);
			hx.Fit("lerche", "NBQ");
			tempChi2 = (double)fitLerche.GetChisquare();
			if(tempChi2 < minChi2LX)
			{
				minChi2LX = tempChi2;
				posMinLX = slidePosition;
			}
			chi2LX.push_back(tempChi2);
			fitLerche.SetParameter(0, ampLY*3.0);
			fitLerche.FixParameter(1, 0.2004);
			fitLerche.FixParameter(3, 35.8);
			fitLerche.SetParameter(4, TLY);
			hy.Fit("lerche", "NBQ");
			tempChi2 = (double)fitLerche.GetChisquare();
			if(tempChi2 < minChi2LY)
			{
				minChi2LY = tempChi2;
				posMinLY = slidePosition;
			}
			chi2LY.push_back(tempChi2);
			slidePosition += 49.0/(double)nSlidePos;
		}
		lercheXPos = posMinLX;
		lercheYPos = posMinLY;
		gaussXPos = posMinX;
		gaussYPos = posMinY;

    if(i % 1000 == 0)
    {
      cout << "Calculating positions for event " << i << ": " << "SG(" << gaussXPos << ", " << gaussYPos << ")";
			cout << ", SL(" << lercheXPos << ", " << lercheYPos << ")" << endl;
    }
		posTree->Fill();
  }
  

  rootFile->Write();
  rootFile->Close();
  cout << "Calculated positions written to " << tName << " in " << fileName << endl;
  return;
}
