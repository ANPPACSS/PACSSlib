#include "../COINCEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcT50Offset(string inFileName, string outFileName, int preTrigDelay);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
  int preTrigDelay;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
      preTrigDelay = atoi(argv[3]);
      cout << "Calculating T50 offset (samples between Ttrig and T50) assuming " << preTrigDelay;
			cout << " samples of pre-trigger delay." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [COINC ROOT file] [analysis output ROOT file] [pre-trigger delay (samples)]";
			cout << endl;
      return 1;
  }

  CalcT50Offset(inFileName, outFileName, preTrigDelay);

  return 0;
}

void CalcT50Offset(string inFileName, string outFileName, int preTrigDelay)
{
	int T50Offset;
	double corrTimestamp, corrTimestampNS, deltaT;
	// ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("T50Offset", "T50Offset");

	string bName = "T50Offset";
	tAnalysis->Branch(bName.c_str(), &T50Offset);
	bName = "corrTimestamp";
	tAnalysis->Branch(bName.c_str(), &corrTimestamp);
	bName = "corrTimestampNS";
	tAnalysis->Branch(bName.c_str(), &corrTimestampNS);
	bName = "deltaT";
	tAnalysis->Branch(bName.c_str(), &deltaT);
 	cout << "ROOT file loaded, tree created." << endl;
	
	// Get the timestamp offset
	eventTree->GetEntry(0);
	double sLYSO = event->GetTimestampLYSO(true);
	T50Offset = PACSSAnalysis::CalcT50Offset(event->GetWFRaw(), preTrigDelay);
	corrTimestampNS = event->GetTimestampGE(true) + T50Offset*(1000.0/event->GetClockFreq());
	double sGE = corrTimestampNS;
	
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		// Do analysis
		T50Offset = PACSSAnalysis::CalcT50Offset(event->GetWFRaw(), preTrigDelay);
		// Create a new, corrected timestamp
		corrTimestamp = event->GetTimestampGE(false) + T50Offset;
		corrTimestampNS = corrTimestamp*(1000.0/event->GetClockFreq());
		deltaT = (corrTimestampNS - sGE) - (event->GetTimestampLYSO(true) - sLYSO);

    if(i % 10000 == 0)
		{
      cout << "Calculating T50 offset for event " << i << "(= " << T50Offset << ", ";
			cout << corrTimestamp << "), deltaT = " << deltaT << "." << endl;
		}
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated values written to T50Offset tree in " << inFileName << endl;
  delete event;
	return;
}
