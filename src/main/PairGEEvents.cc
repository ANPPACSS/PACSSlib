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

  int nFilled = 0;
	int nSkipped = 0;
	int iGE1 = 0;
	int iGE2 = 0;
  for(int i=0;i < numEvents;i++)
  {
		event->ClearEvent();
		// Grab this event
		runGE1->GetEvent(iGE1);
		runGE2->GetEvent(iGE2);

		// Equal timestamps? -> copy!
		if(eventGE1->GetTimestampGE(false) == eventGE2->GetTimestampGE(false))
		{
			*event = *eventGE1;
			// Copy the LYSO waveform only from the second channel
			vector<double> wf = eventGE2->GetWFRaw();
			event->SetWFLYSO(wf);
			nFilled++;
			iGE1++;
			iGE2++;
			eventTree->Fill();
		}
		// Check next two events
		else if(runGE1->GetEvent(iGE1+1)->GetTimestampGE(false) == runGE2->GetEvent(iGE2)->GetTimestampGE(false))
			iGE1++;
		else if(runGE1->GetEvent(iGE1+2)->GetTimestampGE(false) == runGE2->GetEvent(iGE2)->GetTimestampGE(false))
			iGE1 += 2;
		else if(runGE2->GetEvent(iGE2+1)->GetTimestampGE(false) == runGE1->GetEvent(iGE1)->GetTimestampGE(false))
			iGE2++;
		else if(runGE2->GetEvent(iGE2+2)->GetTimestampGE(false) == runGE1->GetEvent(iGE1)->GetTimestampGE(false))
			iGE2 += 2;
		else
		{
			cout << "Pair not found. Skipping " << iGE1 << ", " << iGE2 << endl;
			nSkipped++;
			cout << eventGE1->GetTimestampGE(false) << ", " << eventGE2->GetTimestampGE(false) << endl;
			iGE1++;
			iGE2++;
		}

    if(i % 10000 == 0)
    {
      cout << "Attempting to pair GE event " << i << "." << endl;
    }
  }
  
  cout << nFilled << " events successfully paired." << endl;

  rootFile->cd();
  eventTree->Write();
  rootFile->Close();
	delete event;
	delete runGE1;
	delete runGE2;
  cout << "Paired events written to " << fileNameOut << endl;
	cout << nSkipped << " events skipped." << endl;
  return;
}
