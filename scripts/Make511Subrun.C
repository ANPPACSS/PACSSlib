// Take a paired_events file, window on the energies, and output a new file
{
	TFile *runOrig = new TFile("paired_events_186pos_varamp.root", "READ");
	TTree *treeOrig = (TTree*)runOrig->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	treeOrig->SetBranchAddress("event", &event);

	TFile *runSub = new TFile("paired_186_511.root", "RECREATE");
	TTree *treeSub = new TTree("COINCEvents", "COINCEvents");
	treeSub->Branch("event", &event);

	int iSubrun = 0;
	for(int i=0;i < treeOrig->GetEntries();i++)
	{
		runOrig->cd();
		treeOrig->GetEntry(i);
		// Apply GE energy window (511 keV)
		if((event->GetEnergyGE()>5100.0) && (event->GetEnergyGE()<5250.0))
		{
			// Apply LYSO energy window
			if((event->GetEnergyLYSO()> 50.0) && (event->GetEnergyLYSO()< 160.0))
			{
				runSub->cd();
				treeSub->Fill();
				iSubrun++;
			}
		}
		if(i % 10000 == 0)
			cout << "Processing event " << i << "." << endl;
	}

	runSub->cd();
	runSub->Write();
	runSub->Close();
	runOrig->cd();
	runOrig->Close();
}
