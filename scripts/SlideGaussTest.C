#define NUM_LYSO_PIXELS 64
{
	const int NUM_POS = 100;

	COINCRun *run = new COINCRun("paired_events.root");
	COINCEvent *event = run->GetEvent(1043);

	TCanvas *c1 = new TCanvas();
	TCanvas *c2 = new TCanvas();
	TCanvas *c3 = new TCanvas();

	TH1D *hProjX = new TH1D("hProjX", "", 8, 0, 8);
	TH1D *hProjY = new TH1D("hProjY", "", 8, 0, 8);
	TF1 *fGauss = new TF1("fGauss", "gaus");
	TH1I *hChi2 = new TH1I("hChi2", "Chi2 in X", NUM_POS+2, 0, NUM_POS+1);

	LYSOEvent *temp = new LYSOEvent();
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		int x, y;
		temp->ChanNumToXYPos(i, x, y);
		hProjX.Fill(x, event->GetCharge().at(i));
		hProjY.Fill(y, event->GetCharge().at(i));
	}
	delete temp;

	fGauss->FixParameter(0, 47.0);
	fGauss->FixParameter(2, 0.65);
	double slidePosition = 0.0;
	double minChi2X = 10000.0;
	double minChi2Y = 10000.0;
	double posX = 0.0;
	double posY = 0.0;
	for(int i=0;i < NUM_POS+1;i++)
	{
		c1->cd();
		cout << i << "; " << "Slide position: " << slidePosition << endl;
		fGauss->FixParameter(1, slidePosition);
		hProjX->Fit("fGauss", "BQ");
		c1->Update();
		double tempChi2 = (double)fGauss.GetChisquare();
		if(tempChi2 < minChi2X)
		{
			minChi2X = tempChi2;
			posX = 8.0*(double)i/(double)NUM_POS;
		}
		cout << "Chi2X: " << tempChi2 << endl;
		hChi2->Fill(i, tempChi2);
		c2->cd();
		hProjY->Fit("fGauss", "BQ");
		tempChi2 = (double)fGauss.GetChisquare();
		if(tempChi2 < minChi2Y)
		{
			minChi2Y = tempChi2;
			posY = 8.0*(double)i/(double)NUM_POS;
		}
		cout << "Chi2Y: " << tempChi2 << endl;
		cout << "Pos: " << 8.0*(double)i/(double)NUM_POS << endl;
		c2->Update();
		gSystem->Sleep(100); //ms
		slidePosition += 8.0/(double)NUM_POS;
	}
	c3->cd();
	hChi2->Draw();
	cout << "Finished. Mins: " << minChi2X << ", " << minChi2Y << endl;
	cout << "At (" << posX << "," << posY << ")" << endl;
	fGauss->FixParameter(1, posX);
	c1->cd();
	hProjX->Fit("fGauss", "BQ");
	fGauss->FixParameter(1, posY);
	c2->cd();
	hProjY->Fit("fGauss", "BQ");
}
