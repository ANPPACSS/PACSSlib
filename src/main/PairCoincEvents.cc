#include "../COINCEvent.hh"
#include "../LYSORun.hh"
#include "../GERun.hh"

void PairEvents(double dtWindow, string fileNameLYSO, string fileNameGE, string fileNameCOINC);

int main(int argc, char *argv[])
{
  string fileNameLYSO;
  string fileNameGE;
	string fileNameCOINC;
  double dtWindow;

  // Handle the command line arguments
  switch(argc)
  {
    case 5:
      fileNameLYSO = (string)argv[1];
      fileNameGE = (string)argv[2];
			fileNameCOINC = (string)argv[3];
      dtWindow = (double)atoi(argv[4]);
      cout << "Beginning event pairing with a window of " << dtWindow;
      cout << " nanoseconds." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [LYSO ROOT file] ";
      cout << "[GE ROOT file] [COINC ROOT file] [dT window, ns]" << endl;
      return 1;
  }

  PairEvents(dtWindow, fileNameLYSO, fileNameGE, fileNameCOINC);

  return 0;
}

void PairEvents(double dtWindow, string fileNameLYSO, string fileNameGE, string fileNameCOINC)
{
  double startLYSO = 0;
  double startGE = 0;

  // ROOT stuff
  TFile *rootFile = new TFile(fileNameCOINC.c_str(), "RECREATE");
  TTree *eventTree = new TTree("COINCEvents", "COINCEvents");
  COINCEvent *event = new COINCEvent();
  eventTree->Branch("event", &event);
  cout << "ROOT file loaded, tree created." << endl;

  // Make the run objects
  GERun *runGE = new GERun(fileNameGE);
	GEEvent *eventGE = runGE->GetEvent(0);
  LYSORun *runLYSO = new LYSORun(fileNameLYSO);
	LYSOEvent *eventLYSO = runLYSO->GetEvent(0);

	// Number of loop iterations should be # of events in the run with the lower
	// number of events
  int numEvents = 0;
	if(runLYSO->GetNumEvents() > runGE->GetNumEvents())
		numEvents = runGE->GetNumEvents();
	else
		numEvents = runLYSO->GetNumEvents();

  // Get the offset for subtraction, in ns
  startLYSO = eventLYSO->GetTimestampLYSO(true);
  startGE = eventGE->GetTimestampGE(true);

  cout << "First timestamps: " << startLYSO << " " << startGE << endl;

  int iLYSO = 0;
  int iGE = 0;
  int nFilled = 0;
  for(int i=0;i < numEvents;i++)
  {
		// Grab this event
		runLYSO->GetEvent(iLYSO);
		runGE->GetEvent(iGE);

		// Skip this event if IE or OOR
		bool fIE = eventLYSO->ErrInput();
		bool fOOR = eventLYSO->ErrOutOfRange();
		if(fIE || fOOR)
		{
			iGE++;
			iLYSO++;
			continue;
		}

    // Get a set of timestamps, convert to ns and subtract offset
    double timeLYSO = eventLYSO->GetTimestampLYSO(true)-startLYSO;
    double timeGE = eventGE->GetTimestampGE(true)-startGE;
		//cout << "Attempting to pair :: iLYSO=" << iLYSO << ", t=" << timeLYSO;
		//cout << "; iGE=" << iGE << ", t=" << timeGE << endl;

    // Clear out the event object
    rootFile->cd();
    event->Clear();

    // Check if in window
    if(fabs(timeLYSO - timeGE) < dtWindow)
    {
      rootFile->cd();
      // Coincidence
			event->CopyEvents(*eventLYSO, *eventGE);

      // Increment counters since we found coincidence
      rootFile->cd();
      eventTree->Fill();
			iGE++;
      iLYSO++;
      nFilled++;
    }
		// Try the next LYSO event
		else if(fabs((runLYSO->GetEvent(iLYSO+1)->GetTimestampLYSO(true)-startLYSO)-timeGE) < dtWindow)
			iLYSO++;
		// Try 2 LYSO events from here
		else if(fabs((runLYSO->GetEvent(iLYSO+2)->GetTimestampLYSO(true)-startLYSO)-timeGE) < dtWindow)
			iLYSO += 2;
		// Try the next GE event
		else if(fabs((runGE->GetEvent(iGE+1)->GetTimestampGE(true)-startGE)-timeLYSO) < dtWindow)
			iGE++;
		// Try 2 GE events from here
		else if(fabs((runGE->GetEvent(iGE+2)->GetTimestampGE(true)-startGE)-timeLYSO) < dtWindow)
			iGE += 2;
		// Can't find a pair, skip em both
		else
		{
			cout << "Pair not found. Skipping " << i << "." << endl;
			iGE++;
			iLYSO++;
		}

    if(iGE % 10000 == 0)
    {
      cout << "Attempting to pair GE event " << iGE << ". deltaT: ";
      cout << (event->GetTimestampLYSO(true)-startLYSO) - (event->GetTimestampGE(true)-startGE) << "." << endl;
    }
    // No coincidence, only iLYSO gets incremented
  }
  
  cout << nFilled << " events successfully paired." << endl;

  rootFile->cd();
  rootFile->Write();
  rootFile->Close();
	delete event;
	delete runGE;
	delete runLYSO;
  cout << "Paired events written to " << fileNameCOINC << endl;
  return;
}
