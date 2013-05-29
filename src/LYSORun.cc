#include "LYSORun.hh"

ClassImp(LYSORun)

LYSORun::LYSORun()
{
	event = new LYSOEvent();
}

LYSORun::LYSORun(string newFileName): PACSSRun(newFileName)
{
	// Open the ROOT file
	rootFile = new TFile(fileName.c_str(), "READ");
	cout << "LYSO data file " << fileName << " loaded." << endl;
  // Get the event tree
	eventTree = (TTree*)rootFile->Get("LYSOEvents");
  // Attach an event object
  event = new LYSOEvent();
  eventTree->SetBranchAddress("event", &event);

	// Open the analysis file (hardcoded for now)
	string aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_980pos.root";
	aFile = new TFile(aName.c_str(), "READ");
	aTree = (TTree*)aFile->Get("Analysis");
	rootFile->cd();
	eventTree->AddFriend(aTree);
	aTree->AddFriend(eventTree);

  // How many events? iEvent = 0 from PACSSRun initialization
  numEvents = eventTree->GetEntries();
  cout << numEvents << " events in data file." << endl;
  eventTree->GetEntry(iEvent);
}

LYSORun::~LYSORun()
{
	// Clean up
	delete event;

	aFile->cd();
	aFile->Close();
	rootFile->cd();
	rootFile->Close();
}

LYSOEvent* LYSORun::GetEvent()
{
	return event;
}

LYSOEvent* LYSORun::GetEvent(int nEvent)
{
	// If the number is out of range, just return the current event
	if((nEvent > numEvents-1) || (nEvent < 0))
	{
  	cout << "Event index out of range. Returning current event (";
	  cout << iEvent << ")." << endl;
	  return event;
  }

  rootFile->cd();
  eventTree->GetEntry(nEvent);
  iEvent = nEvent;
  return event;
}

LYSOEvent* LYSORun::GetNextEvent()
{
  if(iEvent == (numEvents - 1))
  {
	  cout << "Already at last event. Returning last event..." << endl;
    return event;
  }

  rootFile->cd();
	eventTree->GetEntry(++iEvent);
  return event;
}

// Return a generic TObject pointer so we can get any type of hist (or really any object) from gDirectory
TObject* LYSORun::GetHistogram(string histName)
{
	// Return the histogram
	return (TObject*)gDirectory->FindObject(histName.c_str());
}

TCanvas* LYSORun::GetCanvas(string canvName)
{
	// return the canvas
	return (TCanvas*)gROOT->GetListOfCanvases()->FindObject(canvName.c_str());
}

void LYSORun::SaveHistogram(string histName, string hFileName)
{
	if((hFileName == fileName) || (hFileName.c_str() == aFile->GetName()))
	{
		cout << "Input file name the same as data file name. You definitely don't want to do that!" << endl;
		return;
	}
	TFile *f = new TFile(hFileName.c_str(), "RECREATE");
	TObject *o = gDirectory->FindObject(histName.c_str());
	if(o)
	{
		o->Write();
		cout << "Histogram written to file " << hFileName << endl;
	}
	else
		cout << "Histogram not found in gDirectory." << endl;
	f->Close();
	rootFile->cd();
	return;
}

TH2D* LYSORun::PlotChargeMap(TCut inCut, bool gc)
{
	TCanvas *cChargeMap;
	TH2D *hCharge;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cChargeMap" + cutName + (gc ? "gc" : "");
	cDesc = "Charge Map" + (string)(gc ? " (Gain Corrected) " : "") + ", Event ";
	histName = hPrefix + "hChargeMap" + cutName + (gc ? "gc" : "");

	if((cChargeMap = GetCanvas(cName.c_str())) == 0)
		cChargeMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hCharge = (TH2D*)GetHistogram(histName)) == 0)
		hCharge = new TH2D(histName.c_str(), "Charge Map", 8, 0.0, 49.0, 8, 0.0, 49.0);
	else
	{
		cout << "Histogram found in gDirectory. Delete it or change the name to redraw." << endl;
		cChargeMap->cd();
		hCharge->Draw();
		return hCharge;
	}

	// Make a copy of the tree with the selection
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotchargemap_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events in temp tree based on your selection." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		int x, y;
		vector<double> cgc;
		tSelection->GetEntry(i);
		if(gc)
			cgc = event->GetChargeGC();
		else
			cgc = event->GetCharge();
		for(int i=0;i < NUM_LYSO_PIXELS;i++)
		{
			event->ChanNumToXYPos(i, x, y);
			hCharge->Fill(x, y, cgc[i]);
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	hCharge->Draw("colz");
	hCharge->GetXaxis()->SetTitle("X Pixel (mm)");
	hCharge->GetYaxis()->SetTitle("Y Pixel (mm)");
	cout << "Charge map for event " << tSelection->GetEntries() << " plotted." << endl;
	delete tSelection;
	fTemp->Close();
	rootFile->cd();
	return hCharge;
}

// Arguments: energy window
TObjArray* LYSORun::PlotChargeProj(TCut inCut, bool gc)
{
	TCanvas *cChargeProj;
	TH1D *hX;
	TH1D *hY;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName() + (string)(gc ? "gc" : "");
	cName = cPrefix + "cChargeProj" + cutName;
	cDesc = "Charge Projections";
	histName[0] = hPrefix + "hChargeXProj" + cutName;
	histName[1] = hPrefix + "hChargeYProj" + cutName;

	if((cChargeProj = GetCanvas(cName.c_str())) == 0)
	{
		cChargeProj = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cChargeProj->Divide(1,2);
	}
	if((hX = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hX = new TH1D(histName[0].c_str(), "Charge X Projection", 8, 0.0, 49.0);
		hY = new TH1D(histName[1].c_str(), "Charge Y Projection", 8, 0.0, 49.0);
	}
	else
	{
		cout << "Histograms found in gDirectory. Provide a different cut name or delete/rename the histograms."<< endl;
		cChargeProj->cd(1);
		hX->Draw();
		hY = (TH1D*)GetHistogram(histName[1]);
		cChargeProj->cd(2);
		hY->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hX);
		ret->Add(hY);
		return ret;
	}

	// Make a temp tree to hold the selection
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotchargeproj_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	int x, y;
	vector<double> charge;
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		eventTree->GetEntry(i);
		if(gc)
			charge = event->GetChargeGC();
		else
			charge = event->GetCharge();
		for(int k=0;k < NUM_LYSO_PIXELS;k++)
		{
			event->ChanNumToXYPos(k, x, y);
			hX->Fill(x, charge[k]);
			hY->Fill(y, charge[k]);
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << "." << endl;
	}

	cChargeProj->cd(1);
	hX->GetXaxis()->SetTitle("X Pixel (mm)");
	hX->GetYaxis()->SetTitle("Proj. Charge (pC)");
	hX->Draw();
	cChargeProj->cd(2);
	hY->GetXaxis()->SetTitle("Y Pixel (mm)");
	hY->GetYaxis()->SetTitle("Proj. Charge (pC)");
	hY->Draw();
	cout << tSelection->GetEntries() << " events plotted." << endl;
	delete tSelection;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hX);
	ret->Add(hY);
	return ret;
}

TH2D* LYSORun::PlotSGPosMap(TCut inCut, string plotArgs)
{	
	TCanvas *cSGPosMap;
	TH2D *hSGPos;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSGPosMap" + cutName;
	cDesc = "Sliding Gauss Position";
	histName = hPrefix + "hSGPosMap" + cutName;

	if((cSGPosMap = GetCanvas(cName.c_str())) == 0)
		cSGPosMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if(!(hSGPos = (TH2D*)GetHistogram(histName)) == 0)
	{
		cout << "Histogram found in gDirectory." << endl;
		cSGPosMap->cd();
		hSGPos->Draw("colz");
		return hSGPos;
	}
	string toDraw = "gaussY980Pos:gaussX980Pos >> " + histName + plotArgs;
	int nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hSGPos = (TH2D*)GetHistogram(histName);
	hSGPos->SetTitle("Sliding Gauss Position Map");
	hSGPos->GetXaxis()->SetTitle("SGX Position (mm)");
	hSGPos->GetYaxis()->SetTitle("SGY Position (mm)");
	hSGPos->Draw("colz");
	cout << nPlotted << " events plotted based on cut." << endl;
	return hSGPos;
}

TObjArray* LYSORun::PlotSGChi2ByPos(TCut inCut)
{
	TCanvas *cSGChi2;
	TH1D *hSGChi2X;
	TH1D *hSGChi2Y;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSGChi2" + cutName;
	cDesc = "Sliding Gauss #Chi^{2}";
	histName[0] = hPrefix + "hSGChi2XPos" + cutName;
	histName[1] = hPrefix + "hSGChi2YPos" + cutName;
	
	if((cSGChi2 = GetCanvas(cName.c_str())) == 0)
	{
		cSGChi2 = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGChi2->Divide(1,2);
	}
	if((hSGChi2X = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hSGChi2X = new TH1D(histName[0].c_str(), "Gauss X #Chi^{2}", 490, 0.0, 490.0);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Gauss Y #Chi^{2}", 490, 0.0, 490.0);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hSGChi2Y = (TH1D*)GetHistogram(histName[1]);
		cSGChi2->cd(1);
		hSGChi2X->Draw();
		cSGChi2->cd(2);
		hSGChi2Y->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hSGChi2X);
		ret->Add(hSGChi2Y);
		return ret;
	}
	// Make a temp tree to hold the selection
	vector<double> *chi2X = new vector<double>();
	vector<double> *chi2Y = new vector<double>();
	aTree->SetBranchAddress("chi2GX980Pos", &chi2X);
	aTree->SetBranchAddress("chi2GY980Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotsgchi2pos_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	TTree *tSelection2 = aTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		tSelection2->GetEntry(i);
		for(size_t k=0;k < chi2X->size();k++)
		{
			hSGChi2X->Fill(k, chi2X->at(k));
			hSGChi2Y->Fill(k, chi2Y->at(k));
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	cSGChi2->cd(1);
	hSGChi2X->GetXaxis()->SetTitle("Slide Pos #");
	hSGChi2X->GetYaxis()->SetTitle("X #Chi^{2}");
	hSGChi2X->Draw();
	cSGChi2->cd(2);
	hSGChi2Y->GetXaxis()->SetTitle("Slide Pos #");
	hSGChi2Y->GetYaxis()->SetTitle("Y #Chi^{2}");
	hSGChi2Y->Draw();
	delete tSelection;
	delete chi2X;
	delete chi2Y;
	delete tSelection2;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* LYSORun::PlotSGChi2(TCut inCut, int nBin, double xMin, double xMax)
{
	TCanvas *cSGChi2;
	TH1D *hSGChi2X;
	TH1D *hSGChi2Y;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSGChi2" + cutName;
	cDesc = "Sliding Gauss #Chi^{2}";
	histName[0] = hPrefix + "hSGChi2X" + cutName;
	histName[1] = hPrefix + "hSGChi2Y" + cutName;
	
	if((cSGChi2 = GetCanvas(cName.c_str())) == 0)
	{
		cSGChi2 = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGChi2->Divide(1,2);
	}
	if((hSGChi2X = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hSGChi2X = new TH1D(histName[0].c_str(), "X #Chi^{2}", nBin, xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y #Chi^{2}", nBin, xMin, xMax);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hSGChi2Y = (TH1D*)GetHistogram(histName[1]);
		cSGChi2->cd(1);
		hSGChi2X->Draw();
		cSGChi2->cd(2);
		hSGChi2Y->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hSGChi2X);
		ret->Add(hSGChi2Y);
		return ret;
	}
	// Make a temp tree to hold the selection
	vector<double> *chi2X = new vector<double>();
	vector<double> *chi2Y = new vector<double>();
	aTree->SetBranchAddress("chi2GX980Pos", &chi2X);
	aTree->SetBranchAddress("chi2GY980Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotsgchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	TTree *tSelection2 = aTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		tSelection2->GetEntry(i);
		for(size_t k=0;k < chi2X->size();k++)
		{
			hSGChi2X->Fill(chi2X->at(k));
			hSGChi2Y->Fill(chi2Y->at(k));
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	cSGChi2->cd(1);
	hSGChi2X->GetXaxis()->SetTitle("X #Chi^{2}");
	hSGChi2X->GetYaxis()->SetTitle("Counts");
	hSGChi2X->Draw();
	cSGChi2->cd(2);
	hSGChi2Y->GetXaxis()->SetTitle("Y #Chi^{2}");
	hSGChi2Y->GetYaxis()->SetTitle("Counts");
	hSGChi2Y->Draw();
	delete tSelection;
	delete chi2X;
	delete chi2Y;
	delete tSelection2;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* LYSORun::PlotSGMinChi2(TCut inCut, int nBin, double xMin, double xMax)
{
	TCanvas *cSGChi2;
	TH1D *hSGChi2X;
	TH1D *hSGChi2Y;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSGMinChi2" + cutName;
	cDesc = "Sliding Gauss Min #Chi^{2}";
	histName[0] = hPrefix + "hSGMinChi2X" + cutName;
	histName[1] = hPrefix + "hSGMinChi2Y" + cutName;
	
	if((cSGChi2 = GetCanvas(cName.c_str())) == 0)
	{
		cSGChi2 = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGChi2->Divide(1,2);
	}
	if((hSGChi2X = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hSGChi2X = new TH1D(histName[0].c_str(), "X Min #Chi^{2}", nBin, xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y Min #Chi^{2}", nBin, xMin, xMax);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hSGChi2Y = (TH1D*)GetHistogram(histName[1]);
		cSGChi2->cd(1);
		hSGChi2X->Draw();
		cSGChi2->cd(2);
		hSGChi2Y->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hSGChi2X);
		ret->Add(hSGChi2Y);
		return ret;
	}
	// Make a temp tree to hold the selection
	vector<double> *chi2X = new vector<double>();
	vector<double> *chi2Y = new vector<double>();
	aTree->SetBranchAddress("chi2GX980Pos", &chi2X);
	aTree->SetBranchAddress("chi2GY980Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotsgminchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	TTree *tSelection2 = aTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		double minX = 5e10;
		double minY = 5e10;
		tSelection->GetEntry(i);
		tSelection2->GetEntry(i);
		for(size_t k=0;k < chi2X->size();k++)
		{
			if(chi2X->at(k) < minX)
				minX = chi2X->at(k);
			if(chi2Y->at(k) < minY)
				minY = chi2Y->at(k);
		}
		hSGChi2X->Fill(minX);
		hSGChi2Y->Fill(minY);
		if(i % reportFreq == 0)
			cout << "Processing event " << i << ":"<<minX<<","<<minY<<endl;
	}

	cSGChi2->cd(1);
	hSGChi2X->GetXaxis()->SetTitle("X Min #Chi^{2}");
	hSGChi2X->GetYaxis()->SetTitle("Counts");
	hSGChi2X->Draw();
	cSGChi2->cd(2);
	hSGChi2Y->GetXaxis()->SetTitle("Y Min #Chi^{2}");
	hSGChi2Y->GetYaxis()->SetTitle("Counts");
	hSGChi2Y->Draw();
	delete tSelection;
	delete chi2X;
	delete chi2Y;
	delete tSelection2;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* LYSORun::PlotSGPosProj(TCut inCut, string plotArgsX, string plotArgsY)
{
	TCanvas *cSGPosProj;
	TH1D *hX;
	TH1D *hY;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cPlotSGPosProj" + cutName;
	cDesc = "Sliding Gauss Projections";
	histName[0] = hPrefix + "hSGPosProjX" + cutName;
	histName[1] = hPrefix + "hSGPosProjY" + cutName;

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cSGPosProj = GetCanvas(cName.c_str())) == 0)
	{
		cSGPosProj = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGPosProj->Divide(1, 2);
	}

	// Make sure we don't have the histograms already available to us. Closing the canvas window
	// does not delete the histograms, no need to recreate them if they exist
	// found - will need to process
	if(!(hX = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		cout << "Histograms found in gDirectory. Delete them or change the names to redraw." << endl;
		hY = (TH1D*)GetHistogram(histName[1]);
		cSGPosProj->cd(1);
		hX->Draw();
		cSGPosProj->cd(2);
		hY->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hX);
		ret->Add(hY);
  	return ret;
	}

	// Fill the histograms
	int nPlotted = 0;
	cSGPosProj->cd(1);
	// Scale GE energy
	string toDraw = "gaussX980Pos >> " + histName[0] + plotArgsX;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hX = (TH1D*)GetHistogram(histName[0]);
	hX->SetTitle("SG X Projection");
  hX->GetXaxis()->SetTitle("SGX Position (mm)");
  hX->GetYaxis()->SetTitle("Counts");
	hX->Draw();
	cout << nPlotted << " drawn to X projection." << endl;
	cSGPosProj->cd(2);
	toDraw = "gaussY980Pos >> " + histName[1] + plotArgsY;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hY = (TH1D*)GetHistogram(histName[1]);
	hY->SetTitle("SG Y Projection");
	hY->GetXaxis()->SetTitle("SGY Position (mm)");
	hY->GetYaxis()->SetTitle("Counts");
	hY->Draw();
	cout << nPlotted << " drawn to LYSO histogram." << endl;
	TObjArray *ret = new TObjArray();
	ret->Add(hX);
	ret->Add(hY);
  return ret;
}

TH2D* LYSORun::PlotSLPosMap(TCut inCut, string plotArgs)
{	
	TCanvas *cSLPosMap;
	TH2D *hSLPos;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSLPosMap" + cutName;
	cDesc = "Sliding Lerche Position";
	histName = hPrefix + "hSLPosMap" + cutName;

	if((cSLPosMap = GetCanvas(cName.c_str())) == 0)
		cSLPosMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if(!(hSLPos = (TH2D*)GetHistogram(histName)) == 0)
	{
		cout << "Histogram found in gDirectory." << endl;
		cSLPosMap->cd();
		hSLPos->Draw("colz");
		return hSLPos;
	}
	string toDraw = "lercheY980Pos:lercheX980Pos >> " + histName + plotArgs;
	int nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hSLPos = (TH2D*)GetHistogram(histName);
	hSLPos->SetTitle("Sliding Lerche Position Map");
	hSLPos->GetXaxis()->SetTitle("SLX Position (mm)");
	hSLPos->GetYaxis()->SetTitle("SLY Position (mm)");
	hSLPos->Draw("colz");
	cout << nPlotted << " events plotted based on cut." << endl;
	return hSLPos;
}

TObjArray* LYSORun::PlotSLChi2ByPos(TCut inCut)
{
	TCanvas *cSGChi2;
	TH1D *hSGChi2X;
	TH1D *hSGChi2Y;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSLChi2Pos" + cutName;
	cDesc = "Sliding Lerche #Chi^{2}";
	histName[0] = hPrefix + "hSLChi2XPos" + cutName;
	histName[1] = hPrefix + "hSLChi2YPos" + cutName;
	
	if((cSGChi2 = GetCanvas(cName.c_str())) == 0)
	{
		cSGChi2 = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGChi2->Divide(1,2);
	}
	if((hSGChi2X = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hSGChi2X = new TH1D(histName[0].c_str(), "Lerche X #Chi^{2}", 490, 0.0, 490.0);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Lerche Y #Chi^{2}", 490, 0.0, 490.0);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hSGChi2Y = (TH1D*)GetHistogram(histName[1]);
		cSGChi2->cd(1);
		hSGChi2X->Draw();
		cSGChi2->cd(2);
		hSGChi2Y->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hSGChi2X);
		ret->Add(hSGChi2Y);
		return ret;
	}
	// Make a temp tree to hold the selection
	vector<double> *chi2X = new vector<double>();
	vector<double> *chi2Y = new vector<double>();
	aTree->SetBranchAddress("chi2LX980Pos", &chi2X);
	aTree->SetBranchAddress("chi2LY980Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotslchi2pos_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	TTree *tSelection2 = aTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		tSelection2->GetEntry(i);
		for(size_t k=0;k < chi2X->size();k++)
		{
			hSGChi2X->Fill(k, chi2X->at(k));
			hSGChi2Y->Fill(k, chi2Y->at(k));
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	cSGChi2->cd(1);
	hSGChi2X->GetXaxis()->SetTitle("Slide Pos #");
	hSGChi2X->GetYaxis()->SetTitle("X #Chi^{2}");
	hSGChi2X->Draw();
	cSGChi2->cd(2);
	hSGChi2Y->GetXaxis()->SetTitle("Slide Pos #");
	hSGChi2Y->GetYaxis()->SetTitle("Y #Chi^{2}");
	hSGChi2Y->Draw();
	delete tSelection;
	delete chi2X;
	delete chi2Y;
	delete tSelection2;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* LYSORun::PlotSLChi2(TCut inCut, int nBin, double xMin, double xMax)
{
	TCanvas *cSGChi2;
	TH1D *hSGChi2X;
	TH1D *hSGChi2Y;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSLChi2" + cutName;
	cDesc = "Sliding Lerche #Chi^{2}";
	histName[0] = hPrefix + "hSLChi2X" + cutName;
	histName[1] = hPrefix + "hSLChi2Y" + cutName;
	
	if((cSGChi2 = GetCanvas(cName.c_str())) == 0)
	{
		cSGChi2 = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGChi2->Divide(1,2);
	}
	if((hSGChi2X = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hSGChi2X = new TH1D(histName[0].c_str(), "Lerche X #Chi^{2}", nBin, xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Lerche Y #Chi^{2}", nBin, xMin, xMax);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hSGChi2Y = (TH1D*)GetHistogram(histName[1]);
		cSGChi2->cd(1);
		hSGChi2X->Draw();
		cSGChi2->cd(2);
		hSGChi2Y->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hSGChi2X);
		ret->Add(hSGChi2Y);
		return ret;
	}
	// Make a temp tree to hold the selection
	vector<double> *chi2X = new vector<double>();
	vector<double> *chi2Y = new vector<double>();
	aTree->SetBranchAddress("chi2LX980Pos", &chi2X);
	aTree->SetBranchAddress("chi2LY980Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotslchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	TTree *tSelection2 = aTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		tSelection2->GetEntry(i);
		for(size_t k=0;k < chi2X->size();k++)
		{
			hSGChi2X->Fill(chi2X->at(k));
			hSGChi2Y->Fill(chi2Y->at(k));
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	cSGChi2->cd(1);
	hSGChi2X->GetXaxis()->SetTitle("X #Chi^{2}");
	hSGChi2X->GetYaxis()->SetTitle("Counts");
	hSGChi2X->Draw();
	cSGChi2->cd(2);
	hSGChi2Y->GetXaxis()->SetTitle("Y #Chi^{2}");
	hSGChi2Y->GetYaxis()->SetTitle("Counts");
	hSGChi2Y->Draw();
	delete tSelection;
	delete chi2X;
	delete chi2Y;
	delete tSelection2;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* LYSORun::PlotSLMinChi2(TCut inCut, int nBin, double xMin, double xMax)
{
	TCanvas *cSGChi2;
	TH1D *hSGChi2X;
	TH1D *hSGChi2Y;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cSLMinChi2" + cutName;
	cDesc = "Sliding Lerche Min #Chi^{2}";
	histName[0] = hPrefix + "hSLMinChi2X" + cutName;
	histName[1] = hPrefix + "hSLMinChi2Y" + cutName;
	
	if((cSGChi2 = GetCanvas(cName.c_str())) == 0)
	{
		cSGChi2 = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGChi2->Divide(1,2);
	}
	if((hSGChi2X = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hSGChi2X = new TH1D(histName[0].c_str(), "X Min #Chi^{2}", nBin, xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y Min #Chi^{2}", nBin, xMin, xMax);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hSGChi2Y = (TH1D*)GetHistogram(histName[1]);
		cSGChi2->cd(1);
		hSGChi2X->Draw();
		cSGChi2->cd(2);
		hSGChi2Y->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hSGChi2X);
		ret->Add(hSGChi2Y);
		return ret;
	}
	// Make a temp tree to hold the selection
	vector<double> *chi2X = new vector<double>();
	vector<double> *chi2Y = new vector<double>();
	aTree->SetBranchAddress("chi2LX980Pos", &chi2X);
	aTree->SetBranchAddress("chi2LY980Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotslminchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	TTree *tSelection2 = aTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		double minX = 5e10;
		double minY = 5e10;
		tSelection->GetEntry(i);
		tSelection2->GetEntry(i);
		for(size_t k=0;k < chi2X->size();k++)
		{
			if(chi2X->at(k) < minX)
				minX = chi2X->at(k);
			if(chi2Y->at(k) < minY)
				minY = chi2Y->at(k);
		}
		hSGChi2X->Fill(minX);
		hSGChi2Y->Fill(minY);
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	cSGChi2->cd(1);
	hSGChi2X->GetXaxis()->SetTitle("X Min #Chi^{2}");
	hSGChi2X->GetYaxis()->SetTitle("Counts");
	hSGChi2X->Draw();
	cSGChi2->cd(2);
	hSGChi2Y->GetXaxis()->SetTitle("Y Min #Chi^{2}");
	hSGChi2Y->GetYaxis()->SetTitle("Counts");
	hSGChi2Y->Draw();
	delete tSelection;
	delete chi2X;
	delete chi2Y;
	delete tSelection2;
	fTemp->Close();
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* LYSORun::PlotSLPosProj(TCut inCut, string plotArgsX, string plotArgsY)
{
	TCanvas *cSGPosProj;
	TH1D *hX;
	TH1D *hY;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cPlotSLPosProj" + cutName;
	cDesc = "Sliding Lerche Projections";
	histName[0] = hPrefix + "hSLPosProjX" + cutName;
	histName[1] = hPrefix + "hSLPosProjY" + cutName;

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cSGPosProj = GetCanvas(cName.c_str())) == 0)
	{
		cSGPosProj = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cSGPosProj->Divide(1, 2);
	}

	// Make sure we don't have the histograms already available to us. Closing the canvas window
	// does not delete the histograms, no need to recreate them if they exist
	// found - will need to process
	if(!(hX = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		cout << "Histograms found in gDirectory. Delete them or change the names to redraw." << endl;
		hY = (TH1D*)GetHistogram(histName[1]);
		cSGPosProj->cd(1);
		hX->Draw();
		cSGPosProj->cd(2);
		hY->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hX);
		ret->Add(hY);
  	return ret;
	}

	// Fill the histograms
	int nPlotted = 0;
	cSGPosProj->cd(1);
	// Scale GE energy
	string toDraw = "lercheX980Pos >> " + histName[0] + plotArgsX;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hX = (TH1D*)GetHistogram(histName[0]);
	hX->SetTitle("SL X Projection");
  hX->GetXaxis()->SetTitle("SLX Position (mm)");
  hX->GetYaxis()->SetTitle("Counts");
	hX->Draw();
	cout << nPlotted << " drawn to X projection." << endl;
	cSGPosProj->cd(2);
	toDraw = "lercheY980Pos >> " + histName[1] + plotArgsY;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hY = (TH1D*)GetHistogram(histName[1]);
	hY->SetTitle("SL Y Projection");
	hY->GetXaxis()->SetTitle("SLY Position (mm)");
	hY->GetYaxis()->SetTitle("Counts");
	hY->Draw();
	cout << nPlotted << " drawn to Y projection." << endl;
	TObjArray *ret = new TObjArray();
	ret->Add(hX);
	ret->Add(hY);
  return ret;
}
