#include "COINCRun.hh"

ClassImp(COINCRun)

COINCRun::COINCRun()
{
	event = new COINCEvent();
}

COINCRun::COINCRun(string newFileName): PACSSRun(newFileName)
{
	// Open the ROOT file
	rootFile = new TFile(fileName.c_str(), "READ");
	cout << "COINC data file " << fileName << " loaded." << endl;
  // Get the event tree
	eventTree = (TTree*)rootFile->Get("COINCEvents");
  // Attach an event object
  event = new COINCEvent();
  eventTree->SetBranchAddress("event", &event);

	// Open the analysis file (hardcoded for now)
	string aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_98pos.root";
	aFile = new TFile(aName.c_str(), "READ");
	aTree = (TTree*)aFile->Get("Analysis");
	rootFile->cd();
	eventTree->AddFriend(aTree);

  // How many events? iEvent = 0 from PACSSRun initialization
  numEvents = eventTree->GetEntries();
  cout << numEvents << " events in data file." << endl;
  eventTree->GetEntry(iEvent);
}

COINCRun::~COINCRun()
{
	// Clean up
	delete event;

	aFile->cd();
	aFile->Close();
	rootFile->cd();
	rootFile->Close();
}

COINCEvent* COINCRun::GetEvent()
{
	return event;
}

COINCEvent* COINCRun::GetEvent(int nEvent)
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

COINCEvent* COINCRun::GetNextEvent()
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
TObject* COINCRun::GetHistogram(string histName)
{
	// Return the histogram
	return (TObject*)gDirectory->FindObject(histName.c_str());
}

TCanvas* COINCRun::GetCanvas(string canvName)
{
	// return the canvas
	return (TCanvas*)gROOT->GetListOfCanvases()->FindObject(canvName.c_str());
}

void COINCRun::SaveHistogram(string histName, string hFileName)
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

// Plot energy histograms from both detectors on one canvas
TObjArray* COINCRun::PlotEnergyHist(TCut inCut, string plotArgsGE, string plotArgsLYSO)
{
	TCanvas *cEnergyHist;
	TH1D *hLYSO;
	TH1D *hGE;
	string cName, cDesc, histName[2];
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "PlotEnergyHist" + cutName;
	cDesc = "Energy Spectra";
	histName[0] = hPrefix + "PlotEnergyHistLYSO" + cutName;
	histName[1] = hPrefix + "PlotEnergyHistGE" + cutName;

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cEnergyHist = GetCanvas(cName.c_str())) == 0)
	{
		cEnergyHist = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cEnergyHist->Divide(1, 2);
	}

	// Make sure we don't have the histograms already available to us. Closing the canvas window
	// does not delete the histograms, no need to recreate them if they exist
	// found - will need to process
	if(!(hLYSO = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		cout << "Histograms found in gDirectory. Delete them or change the names to redraw." << endl;
		hGE = (TH1D*)GetHistogram(histName[1]);
		cEnergyHist->cd(1);
		hGE->Draw();
		cEnergyHist->cd(2);
		hLYSO->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hGE);
		ret->Add(hLYSO);
  	return ret;
	}

	// Fill the histograms
	int nPlotted = 0;
	cEnergyHist->cd(1);
	// Scale GE energy
	string toDraw = "energyGE >> " + histName[1] + plotArgsGE;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hGE = (TH1D*)GetHistogram(histName[1]);
	hGE->SetTitle("GE Energy");
  hGE->GetXaxis()->SetTitle("Energy (arb)");
  hGE->GetYaxis()->SetTitle("Counts");
  hGE->SetFillColor(kRed);
	hGE->Draw();
	cout << nPlotted << " drawn to GE histogram." << endl;
	cEnergyHist->cd(2);
	toDraw = "energyLYSOGC >> " + histName[0] + plotArgsLYSO;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hLYSO = (TH1D*)GetHistogram(histName[0]);
	hLYSO->SetTitle("LYSO Energy");
	hLYSO->GetXaxis()->SetTitle("Energy (pC)");
	hLYSO->GetYaxis()->SetTitle("Counts");
	hLYSO->SetFillColor(kBlue);
	hLYSO->Draw();
	cout << nPlotted << " drawn to LYSO histogram." << endl;
	TObjArray *ret = new TObjArray();
	ret->Add(hGE);
	ret->Add(hLYSO);
  return ret;
}

TH1D* COINCRun::PlotWaveform(int nEvent, int nBL)
{
	TCanvas *cWaveforms;
	TH1D *hRaw;
	string cName, cDesc, histName;
	string cutName = "_" + to_string(nEvent) + "_" + to_string(nBL) + "bl";
	cName = cPrefix + "cWaveform" + cutName;
	cDesc = "Raw and Diff. Waveforms Event " + to_string(nEvent);
	histName = hPrefix + "hRawWaveform" + cutName;
	// Get the waveforms here so we know the sizes for the histograms
	GetEvent(nEvent);
	vector<double> wfRaw = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cWaveforms = GetCanvas(cName.c_str())) == 0)
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hRaw = (TH1D*)GetHistogram(histName)) == 0)
		hRaw = new TH1D(histName.c_str(), "Raw Waveform", wfRaw.size(), 0.0, (double)(wfRaw.size()-1)*(1000/event->GetClockFreq()));
	// Found - redraw on a new canvas, even if it's already drawn
	else
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		hRaw = (TH1D*)GetHistogram(histName);
		hRaw->Draw();
		return hRaw;
	}

	// Fill the histograms
	for(size_t i=0;i < wfRaw.size();i++)
		hRaw->Fill(i*(1000/event->GetClockFreq()), wfRaw.at(i));

	// Draw it
  hRaw->GetXaxis()->SetTitle("Time (ns)");
  hRaw->GetYaxis()->SetTitle("ADC Counts");
  hRaw->SetFillColor(kRed);
	hRaw->SetFillStyle(0000);
	hRaw->Draw();

	return hRaw;
}

TH2D* COINCRun::PlotWaveformStack(TCut inCut, int nBL, double yMin, double yMax)
{
	TCanvas *cWaveforms;
	string cName, cDesc;
	string cutName = "_" + (string)inCut.GetName() + "_" + to_string(nBL) + "bl";
	cName = cPrefix + "cWaveformStack" + cutName;
	cDesc = "Stacked Raw Waveforms";
	string histName = hPrefix + "hWaveformStack" + "_" + cutName;
	TH2D *hWaves;
	int wfLen = (int)event->GetWFRaw().size();

	if((cWaveforms = GetCanvas(cName.c_str())) == 0)
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	// Check for one of the histograms existing
	if((hWaves = (TH2D*)GetHistogram(histName)) == 0)
		hWaves = new TH2D(histName.c_str(), "Raw Waveforms, Stacked", wfLen, 0, (wfLen-1)*(1000/event->GetClockFreq()), yMax-yMin, yMin, yMax);
	else
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		cWaveforms->cd();
		hWaves->Draw("colz");
		return hWaves;
	}

	// Create a new tree with the cut
	cout << "Copying tree using selection. This may take a moment." << endl;
	// Make a temp file to hold the new tree, since the current file is read only
	TFile *fTemp = new TFile("temp.root", "RECREATE");
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	cout << "Cut tree has " << tSelection->GetEntries() << " events based on your cut." << endl;
	rootFile->cd();

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		vector<double> rawWF = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);
		for(size_t k=0;k < rawWF.size();k++)
			hWaves->Fill(k*(1000/event->GetClockFreq()), rawWF.at(k));
	}

	hWaves->GetXaxis()->SetTitle("Time (ns)");
	hWaves->GetYaxis()->SetTitle("ADC Counts");
	hWaves->Draw("colz");
	// Clean up
	delete tSelection;
	fTemp->Close();
	rootFile->cd();
	return hWaves;
}

TH1D* COINCRun::PlotAverageWaveform(TCut inCut, int nBL)
{
	TCanvas *cAvgWaveform;
	TH1D *hAvgWave;
	string cName, cDesc;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cAvgWaveform" + cutName;
	cDesc = "Average Waveform";
	string histName = hPrefix + "hAvgWaveform" + "_" + cutName;

	if((cAvgWaveform = GetCanvas(cName.c_str())) == 0)
		cAvgWaveform = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	// Check for one of the histograms existing
	if((hAvgWave = (TH1D*)GetHistogram(histName)) == 0)
		hAvgWave = new TH1D(histName.c_str(), "Average Waveform",(int)event->GetWFRaw().size(), 0, ((int)event->GetWFRaw().size()-1)*(1000/event->GetClockFreq()));
	else
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		cAvgWaveform->cd();
		hAvgWave->Draw();
		return hAvgWave;
	}

	// Create a new tree with the cut
	cout << "Copying tree using selection. This may take a moment." << endl;
	// Make a temp file to hold the new tree, since the current file is read only
	TFile *fTemp = new TFile("temp.root", "RECREATE");
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	cout << "Cut tree has " << tSelection->GetEntries() << " events based on your cut." << endl;
	rootFile->cd();

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		vector<double> rawWF = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);
		for(size_t k=0;k < rawWF.size();k++)
			hAvgWave->Fill(k*(1000/event->GetClockFreq()), rawWF[k]);
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}
	hAvgWave->Scale(1.0/(double)tSelection->GetEntries());
	hAvgWave->GetXaxis()->SetTitle("Time (ns)");
	hAvgWave->GetYaxis()->SetTitle("ADC Counts");
	hAvgWave->SetFillColor(kBlue);
	hAvgWave->SetFillStyle(0000);
	hAvgWave->Draw();
	// Clean up
	delete tSelection;
	fTemp->Close();
	rootFile->cd();

	return hAvgWave;
}

TH1D* COINCRun::PlotTimeBetweenCoincEvents(TCut inCut, string plotArgs)
{
	TCanvas *cCoincDT;
	TH1D *hCoincDT;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cCoincDT" + cutName;
	cDesc = "Time Between Coincident Events";
	histName = hPrefix + "CoincDT" + cutName;


	if((cCoincDT = GetCanvas(cName.c_str())) == 0)
		cCoincDT = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if(!(hCoincDT = (TH1D*)GetHistogram(histName)) == 0)
	{
		cout << "Histograms found in gDirectory. Delete them or change the names to redraw." << endl;
		cCoincDT->cd();
		hCoincDT->Draw();
		return hCoincDT;
	}

	// Get the time of the first event (offset)
	GetEvent(0);
	double sGE = event->GetTimestampGE(true);
	double sLYSO = event->GetTimestampLYSO(true);

	// Subtract the offset, ROOT style
	int nPlotted = 0;
	char temp[256];
	string sTemp = histName + plotArgs;
	sprintf(temp, "((timestampLYSONS - %f) - (timestampGENS - %f)) >> %s", sLYSO, sGE, sTemp.c_str());
	nPlotted = eventTree->Draw(temp, inCut, "NBQ");
	hCoincDT = (TH1D*)GetHistogram(histName.c_str());
	hCoincDT->SetTitle("Time Between Coincident Events");
	hCoincDT->GetXaxis()->SetTitle("tLYSO - tGE (ns)");
	hCoincDT->GetYaxis()->SetTitle("Counts");
	hCoincDT->Draw();
	cout << nPlotted << " events plotted." << endl;

	return hCoincDT;
}

TH2D* COINCRun::PlotChargeMap(TCut inCut, bool gc)
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
	TFile *fTemp = new TFile("temp.root", "RECREATE");
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
TObjArray* COINCRun::PlotChargeProj(TCut inCut, bool gc)
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
	TFile *fTemp = new TFile("temp.root", "RECREATE");
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

TH2D* COINCRun::PlotSGPosMap(TCut inCut, string plotArgs)
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
	string toDraw = "gaussY98Pos:gaussX98Pos >> " + histName + plotArgs;
	int nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hSGPos = (TH2D*)GetHistogram(histName);
	hSGPos->SetTitle("Sliding Gauss Position Map");
	hSGPos->GetXaxis()->SetTitle("SGX Position (mm)");
	hSGPos->GetYaxis()->SetTitle("SGY Position (mm)");
	hSGPos->Draw("colz");
	cout << nPlotted << " events plotted based on cut." << endl;
	return hSGPos;
}

TH2D* COINCRun::PlotSLPosMap(TCut inCut, string plotArgs)
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
	string toDraw = "lercheY98Pos:lercheX98Pos >> " + histName + plotArgs;
	int nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hSLPos = (TH2D*)GetHistogram(histName);
	hSLPos->SetTitle("Sliding Lerche Position Map");
	hSLPos->GetXaxis()->SetTitle("SLX Position (mm)");
	hSLPos->GetYaxis()->SetTitle("SLY Position (mm)");
	hSLPos->Draw("colz");
	cout << nPlotted << " events plotted based on cut." << endl;
	return hSLPos;
}
