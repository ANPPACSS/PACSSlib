#include "../LYSOEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcSlidePosFC(string inFileName, string outFileName, int nSlidePos);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
  int nSlidePos;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
      nSlidePos = atoi(argv[3]);
      cout << "Calculating Gauss & Lerche slide positions with " << nSlidePos << " positions." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [LYSO ROOT file] [analysis output ROOT file] [n positions]" << endl;
      return 1;
  }

  CalcSlidePosFC(inFileName, outFileName, nSlidePos);

  return 0;
}

void CalcSlidePosFC(string inFileName, string outFileName, int nSlidePos)
{
	double gaussXPos, gaussYPos, lercheXPos, lercheYPos;
	vector<double> chi2GX, chi2GY, chi2LX, chi2LY;
  // ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("LYSOEvents");
	LYSOEvent *event = new LYSOEvent();
	eventTree->SetBranchAddress("event", &event);
	cout << eventTree->GetEntries() << " events in raw data file." << endl;

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("98PosFC511", "98PosFC511");

	// Get the flood correction tree
	string aName = inFileName;
	aName.erase(aName.size()-5, 5);
	aName += "_floodcorrect511.root";
	TFile *fFC = new TFile(aName.c_str(), "READ");
	TTree *tFC = (TTree*)fFC->Get("FloodCorrect");
	vector<double> *chargeFC = new vector<double>();
	tFC->SetBranchAddress("chargeFC511", &chargeFC);

	eventTree->AddFriend(tFC);

	// Set the branch name depending on the number of sliding positions for clarity
	string NPos = to_string(nSlidePos) + "Pos";
	// Check if the branch for this analysis exists. If so, overwrite it, if not, make it
	// Not found
	string bName = "gaussX" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &gaussXPos);
	bName = "gaussY" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &gaussYPos);
	bName = "lercheX" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &lercheXPos);	
	bName = "lercheY" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &lercheYPos);	
	bName = "chi2GX" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &chi2GX);
	bName = "chi2GY" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &chi2GY);
	bName = "chi2LX" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &chi2LX);	
	bName = "chi2LY" + NPos + "FC511";
	tAnalysis->Branch(bName.c_str(), &chi2LY);	
 	cout << "ROOT file loaded, tree created." << endl;
	
	int nFilled = 0;
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		event->SetChargeGC(*chargeFC);

		// Do analysis
		PACSSAnalysis::CalcSlidingGaussXYPosition(event, gaussXPos, chi2GX, gaussYPos, chi2GY, nSlidePos);
		PACSSAnalysis::CalcSlidingLercheXYPosition(event, lercheXPos, chi2LX, lercheYPos, chi2LY, nSlidePos);

    if(i % 1000 == 0)
      cout << "Calculating positions for event " << i << ": " << "(" << gaussXPos << ", " << gaussYPos << ")" << endl;
		tAnalysis->Fill();
		nFilled++;
  }

	fOut->cd();
	tAnalysis->Write();
	fOut->Write();
	fOut->Close();
	fFC->Close();
  rootFile->Close();
  cout << nFilled << " calculated positions written to 98PosFC tree in " << inFileName << endl;
  delete event;
	return;
}
