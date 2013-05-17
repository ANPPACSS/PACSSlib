/* This file reads in a COINCEvent run and generates another .root file with another tree containing
	 the calculated values */
{
	cout << "Updating file with T1ToT2Times tree with: " << endl;
	cout << "T2, T5, T10 -> T90 and T2, T5, T10 -> T50 in nanoseconds." << endl;

	// Times to calculate, in ns
	double t2t90, t5t90, t10t90, t2t50, t5t50, t10t50;
	COINCEvent *event = new COINCEvent();

	cout << "Opening ROOT file." << endl;
	TFile *f = new TFile("bege_coinc.root", "UPDATE");
	TTree *tTimes = new TTree("T1ToT2Times", "T1ToT2Times");
	TTree *tEvents = (TTree*)f->Get("COINCEvents");
	tTimes->Branch("t2t90", &t2t90);
	tTimes->Branch("t5t90", &t5t90);
	tTimes->Branch("t10t90", &t10t90);
	tTimes->Branch("t2t50", &t2t50);
	tTimes->Branch("t5t50", &t5t50);
	tTimes->Branch("t10t50", &t10t50);
	tEvents->SetBranchAddress("event", &event);

	for(int i=0;i < tEvents->GetEntries();i++)
	{
		tEvents->GetEntry(i);
		// Calculate the times
		event->CalcT1ToT2TimeNS(0.02, 0.90, t2t90);
		event->CalcT1ToT2TimeNS(0.05, 0.90, t5t90);
		event->CalcT1ToT2TimeNS(0.10, 0.90, t10t90);
		event->CalcT1ToT2TimeNS(0.02, 0.50, t2t50);
		event->CalcT1ToT2TimeNS(0.05, 0.50, t5t50);
		event->CalcT1ToT2TimeNS(0.10, 0.50, t10t50);

		tTimes->Fill();
		if(i % 10000 == 0)
			cout << "Processing event " << i << "." << endl;
	}

	f->Write();
	return;
}
