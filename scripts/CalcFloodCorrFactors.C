{
	int x, y;

	// File and event stuff
	TFile *f = new TFile("flood.root", "READ");
	TTree *t = (TTree*)f->Get("LYSOEvents");
	LYSOEvent *e = new LYSOEvent();
	t->SetBranchAddress("event", &e);

	// Create histograms to plot as sanity check
	TH2D *hCharge = new TH2D("hCharge", "Charge Map", 8, 0.0, 49.0, 8, 0.0, 49.0);
	TH2D *hChargeGC = new TH2D("hChargeGC", "Charge Map GC", 8, 0.0, 49.0, 8, 0.0, 49.0);
	//TH2D *hChargeFC = new TH2D("hChargeFC", "Charge Map FC", 8, 0.0, 49.0, 8, 0.0, 49.0);

	// Create the summed charge vector - 64 pixels, start at 0.0
	vector<double> *sumCharge = new vector<double(64, 0.0);

	// Loop over all events and fill sumCharge
	vector<double> charge, chargeGC;
	for (int i=0;i < t->GetEntries();i++) {
		if (i % 10000 == 0) {
			cout << "Processing event " << i << ": ";
		}
		
		t->GetEntry(i);
		charge = e->GetCharge();
		chargeGC = e->GetChargeGC();

		for (int k=0;k < 64;k++) {
			sumCharge->at(k) += charge.at(k);
			PACSSAnalysis::ChanNumToXYPos(k, x, y);
			hCharge->Fill(x, y, charge.at(k));
			hChargeGC->Fill(x, y, chargeGC.at(k));
			cout << "(" << charge.at(k) << "," << chargeGC.at(k) << "," << sumCharge.at(k) << ") ";
		}
		cout << endl;
	}

	TCanvas *cC = new TCanvas("cCharge", "Charge", 800, 800);
	hCharge->Draw("colz");
	TCanvas *cCGC = new TCanvas("cChargeGC", "Charge GC", 800, 800);
	hChargeGC->Draw("colz");
}
