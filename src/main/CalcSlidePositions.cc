#include "../COINCEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcSlidePos(string inFileName, string outFileName, int nSlidePos);

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
      cout << "Usage: " << argv[0] << " [COINC ROOT file] [analysis output ROOT file] [n positions]" << endl;
      return 1;
  }

  CalcSlidePos(inFileName, outFileName, nSlidePos);

  return 0;
}

void CalcSlidePos(string inFileName, string outFileName, int nSlidePos)
{
	double lercheXPos, lercheYPos;
	vector<double> chi2LX, chi2LY;
  // ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	string NPos = to_string(nSlidePos) + "Pos";
	TTree *tAnalysis = new TTree(NPos.c_str(), NPos.c_str());

	// Set the branch name depending on the number of sliding positions for clarity
	// Check if the branch for this analysis exists. If so, overwrite it, if not, make it
	// Not found
	string bName = "lercheX" + NPos;
	tAnalysis->Branch(bName.c_str(), &lercheXPos);	
	bName = "lercheY" + NPos;
	tAnalysis->Branch(bName.c_str(), &lercheYPos);	
	bName = "chi2LX" + NPos;
	tAnalysis->Branch(bName.c_str(), &chi2LX);	
	bName = "chi2LY" + NPos;
	tAnalysis->Branch(bName.c_str(), &chi2LY);	
 	cout << "ROOT file loaded, tree created." << endl;
	
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		// Do analysis
		//PACSSAnalysis::CalcSlidingGaussXYPosition(event, gaussXPos, chi2GX, gaussYPos, chi2GY, nSlidePos);
		PACSSAnalysis::CalcSlidingLercheXYPosition(event->GetChargeGC(), lercheXPos, chi2LX, lercheYPos, chi2LY, nSlidePos);

    if(i % 1000 == 0)
      cout << "Calculating positions for event " << i << ": " << "(" << lercheXPos << ", " << lercheYPos << ")" << endl;
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated positions written to " << NPos << " tree in " << outFileName << endl;
  delete event;
	return;
}
