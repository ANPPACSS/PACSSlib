#include "../COINCEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcT90Offset(string inFileName, string outFileName, int nBL);

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

  CalcT90Offset(inFileName, outFileName, nBL);

  return 0;
}

void CalcT90Offset(string inFileName, string outFileName, int nBL)
{
	int t90Ge, t50LYSO, deltaT;
	// ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("T90Samples", "T90Samples");

	string bName = "t90Ge";
	tAnalysis->Branch(bName.c_str(), &t90Ge);
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
		t90Ge = PACSSAnalysis::CalcTXSample(event->GetWFRaw(), 0.90, nBL);
		t50LYSO = PACSSAnalysis::CalcTXSample(event->GetWFLYSO(), 0.50, nBL);
		deltaT = 10.0*(t90Ge - t50LYSO);

    if(i % 10000 == 0)
      cout << "Calculating T90 for event " << i << endl;
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated values written to T90Samples tree in " << outFileName << endl;
  delete event;
	return;
}
