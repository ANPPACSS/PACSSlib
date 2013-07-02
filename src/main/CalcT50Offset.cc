#include "../COINCEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcT50Offset(string inFileName, string outFileName, int nBL);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
	int nBL;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
			nBL = atoi(argv[3]);
      cout << "Calculating T50 sample numbers for both waveforms with " << nBL << " samples BL subtract." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [COINC ROOT file] [analysis output ROOT file] [n sample bl subtract]";
			cout << endl;
      return 1;
  }

  CalcT50Offset(inFileName, outFileName, nBL);

  return 0;
}

void CalcT50Offset(string inFileName, string outFileName, int nBL)
{
	int t50Ge, t50LYSO, deltaT;
	// ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("T50Samples", "T50Samples");

	string bName = "t50Ge";
	tAnalysis->Branch(bName.c_str(), &t50Ge);
	bName = "t50LYSO";
	tAnalysis->Branch(bName.c_str(), &t50LYSO);
	bName = "deltaT";
	tAnalysis->Branch(bName.c_str(), &deltaT);
 	cout << "ROOT file loaded, tree created." << endl;
	
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		// Do analysis
		t50Ge = PACSSAnalysis::CalcT50Offset(event->GetWFRaw(), nBL);
		t50LYSO = PACSSAnalysis::CalcT50Offset(event->GetWFLYSO(), nBL);
		deltaT = 10.0*(t50Ge - t50LYSO);

    if(i % 10000 == 0)
      cout << "Calculating T50 for event " << i << endl;
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated values written to T50Samples tree in " << outFileName << endl;
  delete event;
	return;
}
