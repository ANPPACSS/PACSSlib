#include "../LYSOEvent.hh"

void ShortenRun(string inFileName, string outFileName, int nEvents);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
  int nEvents;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
      nEvents = atoi(argv[3]);
      cout << "Shortening data file " << inFileName << " to " << nEvents << " events and outputting to ";
			cout << outFileName << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [LYSO ROOT file] [output LYSO ROOT file] [n events to copy]" << endl;
      return 1;
  }

  ShortenRun(inFileName, outFileName, nEvents);

  return 0;
}

void ShortenRun(string inFileName, string outFileName, int nEvents)
{
  // ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("LYSOEvents");
	LYSOEvent *event = new LYSOEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	TTree *tOut = new TTree("LYSOEvents", "LYSOEvents");
	tOut->Branch("event", &event);
	
	// Loop over nEvents
  for(int i=0;i < nEvents;i++)
  {
		// Grab this event
		eventTree->GetEntry(i);
		// Fill the new tree
		tOut->Fill();

    if(i % 10000 == 0)
      cout << "Copying event " << i << endl;
  }
  
	tOut->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated positions written to Analysis tree  in " << inFileName << endl;
  delete event;
	return;
}
