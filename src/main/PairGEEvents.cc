#include "../GERun.hh"

void PairGEEvents(string fileNameGE1, string fileNameGE2, string fileNameOut);

int main(int argc, char *argv[])
{
  string fileNameGE1;
  string fileNameGE2;
	string fileNameOut;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
      fileNameGE1 = (string)argv[1];
      fileNameGE2 = (string)argv[2];
			fileNameOut = (string)argv[3];
      cout << "Beginning event pairing of GE events." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [GE (CH1) ROOT file] ";
      cout << "[GE (CH2) ROOT file] [GE OUTPUT ROOT file]" << endl;
      return 1;
  }

  PairGEEvents(fileNameGE1, fileNameGE2, fileNameOut);

  return 0;
}

void PairGEEvents(string fileNameGE1, string fileNameGE2, string fileNameOut)
{
  // ROOT stuff
  TFile *rootFile = new TFile(fileNameOut.c_str(), "RECREATE");
  TTree *eventTree = new TTree("GEEvents", "GEEvents");
  GEEvent *event = new GEEvent();
  eventTree->Branch("event", &event);
  cout << "ROOT file loaded, tree created." << endl;

  // Make the run objects
  GERun *runGE1 = new GERun(fileNameGE1);
	GEEvent *eventGE1 = runGE1->GetEvent(0);
	cout << "GE1: " << runGE1->GetNumEvents() << " entries." << endl;
  GERun *runGE2 = new GERun(fileNameGE2);
	GEEvent *eventGE2 = runGE2->GetEvent(0);
	cout << "GE2: " << runGE2->GetNumEvents() << " entries." << endl;

	// Both channels should have the same number of events
  int numEvents = runGE1->GetNumEvents();
	if(runGE2->GetNumEvents() != runGE1->GetNumEvents())
	{
		cout << "Unequal number of events - exiting." << endl;
		return;
	}

  int iGE2 = 0;
  int iGE1 = 0;
  int nFilled = 0;
  for(int i=0;i < numEvents;i++)
  {
		event->ClearEvent();
		// Grab this event
		runGE1->GetEvent(iGE1);
		runGE2->GetEvent(iGE2);

		if(eventGE1->GetTimestampGE(false) == eventGE2->GetTimestampGE(false))
		{
			// Copy the CH1 stuff - primary event information
			*event = *eventGE1;
			// Copy the LYSO waveform only from the second channel
			event->SetWFLYSO(eventGE2->GetWFLYSO());
			iGE1++;
			iGE2++;
			nFilled++;
			eventTree->Fill();
		}

    if(iGE1 % 10000 == 0)
    {
      cout << "Attempting to pair GE1 event " << iGE1 << "." << endl;
    }
  }
  
  cout << nFilled << " events successfully paired." << endl;

  rootFile->cd();
  rootFile->Write();
  rootFile->Close();
	delete event;
	delete runGE1;
	delete runGE2;
  cout << "Paired events written to " << fileNameOut << endl;
  return;
}
