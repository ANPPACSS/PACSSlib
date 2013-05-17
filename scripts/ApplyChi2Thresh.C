// Apply a chi2 upper limit to the 511 subrun
{
  TFile *runOrig = new TFile("paired_186_511.root", "READ");
	TTree *treeOrig = (TTree*)runOrig->Get("COINCEvents");
  COINCEvent *event = new COINCEvent();
  treeOrig->SetBranchAddress("event", &event);

  TFile *runSub = new TFile("paired_186_511_16chi2thresh.root", "RECREATE");
  TTree *treeSub = new TTree("COINCEvents", "COINCEvents");
  treeSub->Branch("event", &event);

  int iSubrun = 0;
  for(int i=0;i < treeOrig->GetEntries();i++)
  {
    runOrig->cd();
    treeOrig->GetEntry(i);

		vector<double> chi2X = event->GetEventLYSO()->GetChi2XPos();
		vector<double> chi2Y = event->GetEventLYSO()->GetChi2YPos();

		double minX = 500000.0;
		double minY = 500000.0;
		for(size_t k=0;k < chi2X.size();k++)
		{
			if(chi2X.at(k) < minX)
				minX = chi2X.at(k);
			if(chi2Y.at(k) < minY)
				minY = chi2Y.at(k);
		}
		if((minX < 16.0) && (minY < 16.0))
			treeSub->Fill();
		if(i % 10000 == 0)
     	cout << "Processing event " << i << "." << endl;
  }

  runSub->cd();
  runSub->Write();
  runSub->Close();
  runOrig->cd();
  runOrig->Close();
}
