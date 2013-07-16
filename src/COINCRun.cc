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
	// Position analysis
	string aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_98pos.root";
	posFile = new TFile(aName.c_str(), "READ");
	if(posFile)
	{
		posTree = (TTree*)posFile->Get("98Pos");
		posTree->SetBranchAddress("lercheX98Pos", &lXPos);
		posTree->SetBranchAddress("lercheY98Pos", &lYPos);
		rootFile->cd();
		eventTree->AddFriend(posTree);
	}
	// Waveform analysis
	aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_diffimax.root";
	wfDiffFile = new TFile(aName.c_str(), "READ");
	if(wfDiffFile)
	{
		wfDiffTree = (TTree*)wfDiffFile->Get("DiffWaveIMax");
		rootFile->cd();
		eventTree->AddFriend(wfDiffTree);
	}
	// T50 offset analysis
	aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_t50deltat.root";
	t50File = new TFile(aName.c_str(), "READ");
	if(t50File)
	{
		t50Tree = (TTree*)t50File->Get("T50Samples");
		t50Tree->SetBranchAddress("t50LYSO", &t50LYSO);
		t50Tree->SetBranchAddress("t50Ge", &t50Ge);
		t50Tree->SetBranchAddress("deltaT", &deltaT);
		rootFile->cd();
		eventTree->AddFriend(t50Tree);
	}
	// Separately calculated energy values
	aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_energysimple.root";
	eSimpleFile = new TFile(aName.c_str(), "READ");
	if(eSimpleFile)
	{
		eSimpleTree = (TTree*)eSimpleFile->Get("EnergySimple");
		rootFile->cd();
		eventTree->AddFriend(eSimpleTree);
	}
	// Flood field correction factors
	aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_floodcorrect.root";
	floodFile = new TFile(aName.c_str(), "READ");
	if(floodFile)
	{
		floodTree = (TTree*)floodFile->Get("FloodCorrect");
		rootFile->cd();
		eventTree->AddFriend(floodTree);
	}

// Flood field corrected positions
	aName = fileName;
	aName.erase(aName.size()-5, 5); // erase the last 5 characters (.root)
	aName += "_98posfc.root";
	posFCFile = new TFile(aName.c_str(), "READ");
	if(posFCFile)
	{
		posFCTree = (TTree*)posFCFile->Get("98Pos");
		rootFile->cd();
		eventTree->AddFriend(posFCTree);
	}

  // How many events? iEvent = 0 from PACSSRun initialization
  numEvents = eventTree->GetEntries();
  cout << numEvents << " events in data file." << endl;
  eventTree->GetEntry(iEvent);
}

COINCRun::~COINCRun()
{
	// Clean up
	delete event;

	if(posFile)
		posFile->Close();
	if(wfDiffFile)
		wfDiffFile->Close();
	if(t50File)
		t50File->Close();
	if(floodFile)
		floodFile->Close();
	if(posFCFile)
		posFCFile->Close();
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
	if(hFileName == fileName)
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

// Set the commonly used histogram labels/fill flags
// use &hist to avoid making a copy (and thus having to return) the pointer
/*TH1D *SetHistStyles(TH1D *hist, string title, string xTitle, string yTitle, int lineColor, int fillStyle)
{
	hist->SetTitle(title.c_str());
	hist->GetXaxis()->SetTitle(xTitle.c_str());
	hist->GetYaxis()->SetTitle(yTitle.c_str());
	hist->SetLineColor(lineColor);
	hist->SetFillColor(lineColor);
	hist->SetFillStyle(fillStyle);

	return;
}*/

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
		cEnergyHist = new TCanvas(cName.c_str(), cDesc.c_str(), 500, 1000);
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
	// Draw Ge
	string toDraw = "energyGE >> " + histName[1] + plotArgsGE;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hGE = (TH1D*)GetHistogram(histName[1]);
	//SetHistStyles(hGE, "GE Energy", "Energy (arb)", "Counts", kRed, 1);
	hGE->SetTitle("GE Energy");
  hGE->GetXaxis()->SetTitle("Energy (arb)");
  hGE->GetYaxis()->SetTitle("Counts");
  hGE->SetFillColor(kRed);
	hGE->Draw();
	cout << nPlotted << " drawn to GE histogram." << endl;
	cEnergyHist->cd(2);
	// Draw LYSO
	toDraw = "energyLYSOGC >> " + histName[0] + plotArgsLYSO;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hLYSO = (TH1D*)GetHistogram(histName[0]);
	//SetHistStyles(hLYSO, "LYSO Energy", "Energy (pC)", "Counts", kBlue, 1);
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

TH1D* COINCRun::PlotEnergySimple(TCut inCut, string plotArgs)
{
	TCanvas *cEnergyHist;
	TH1D *hGE;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "PlotEnergySimple" + cutName;
	cDesc = "(Simple) Energy Spectrum";
	histName = hPrefix + "PlotEnergySimple" + cutName;

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cEnergyHist = GetCanvas(cName.c_str())) == 0)
		cEnergyHist = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);

	// Make sure we don't have the histograms already available to us. Closing the canvas window
	// does not delete the histograms, no need to recreate them if they exist
	// found - will need to process
	if(!(hGE = (TH1D*)GetHistogram(histName)) == 0)
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		cEnergyHist->cd();
		hGE->Draw();
  	return hGE;
	}

	// Fill the histograms
	int nPlotted = 0;
	// Scale GE energy
	string toDraw = "EnergySimple >> " + histName + plotArgs;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hGE = (TH1D*)GetHistogram(histName);
	hGE->SetTitle("Simple Energy");
  hGE->GetXaxis()->SetTitle("Energy (arb)");
  hGE->GetYaxis()->SetTitle("Counts");
  hGE->SetFillColor(kRed);
	hGE->Draw();
	cout << nPlotted << " drawn to GE histogram." << endl;
  return hGE;
}

TH1D* COINCRun::PlotWaveform(int nEvent, int nBL)
{
	TCanvas *cWaveforms;
	TH1D *hRaw;
	TH1D *hDiff;
	string cName, cDesc, histName[2];
	string cutName = "_" + to_string(nEvent) + "_" + to_string(nBL) + "bl";
	cName = cPrefix + "cWaveform" + cutName;
	cDesc = "Raw and Diff. Waveforms Event " + to_string(nEvent);
	histName[0] = hPrefix + "hRawWaveform" + cutName;
	histName[1] = hPrefix + "hDiffWaveform" + cutName;
	// Get the waveforms here so we know the sizes for the histograms
	GetEvent(nEvent);
	vector<double> *wfDiff = new vector<double>();
	wfDiffTree->SetBranchAddress("wfDiff", &wfDiff);
	wfDiffTree->GetEntry(nEvent);
	vector<double> wfRaw = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cWaveforms = GetCanvas(cName.c_str())) == 0)
	{	
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cWaveforms->Divide(1,2);
	}
	if((hRaw = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hRaw = new TH1D(histName[0].c_str(), "Raw Waveform", wfRaw.size(), 0.0, (double)(wfRaw.size()-1)*(1000/event->GetClockFreq()));
		hDiff = new TH1D(histName[1].c_str(), "Diff Waveform", wfDiff->size(), 0.0, (double)(wfDiff->size()-1)*(1000/event->GetClockFreq()));
	}
	// Found - redraw on a new canvas, even if it's already drawn
	else
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		cWaveforms->cd(1);
		hRaw = (TH1D*)GetHistogram(histName[0]);
		hRaw->Draw();
		cWaveforms->cd(2);
		hDiff = (TH1D*)GetHistogram(histName[1]);
		hDiff->Draw();
		return hRaw;
	}

	for(size_t i=0;i < wfRaw.size();i++)
	{
		hRaw->Fill(i*(1000/event->GetClockFreq()), wfRaw.at(i));
		hDiff->Fill(i*(1000/event->GetClockFreq()), wfDiff->at(i));
	}

	// Draw it
  cWaveforms->cd(1);
	hRaw->GetXaxis()->SetTitle("Time (ns)");
  hRaw->GetYaxis()->SetTitle("ADC Counts");
  hRaw->SetFillColor(kRed);
	hRaw->SetFillStyle(0000);
	hRaw->Draw();
	cWaveforms->cd(2);
  hDiff->GetXaxis()->SetTitle("Time (ns)");
  hDiff->GetYaxis()->SetTitle("ADC Counts");
  hDiff->SetFillColor(kRed);
	hDiff->SetFillStyle(0000);
	hDiff->Draw();

	wfDiffTree->ResetBranchAddress(wfDiffTree->GetBranch("wfDiff"));
	delete wfDiff;
	return hRaw;
}

TObjArray* COINCRun::PlotWaveformWithT50(int nEvent, int nBL)
{
	TCanvas *cWaveforms;
	TH1D *hRaw;
	TH1D *hT50;
	string cName, cDesc, histName[2];
	string cutName = "_" + to_string(nEvent) + "_" + to_string(nBL) + "bl";
	cName = cPrefix + "cWaveformT50" + cutName;
	cDesc = "Raw and Offset Waveforms, Event " + to_string(nEvent);
	histName[0] = hPrefix + "hRawWaveformT50" + cutName;
	histName[1] = hPrefix + "hOffsetWaveform" + cutName;
	// Get the waveforms here so we know the sizes for the histograms
	int offset;
	t50Tree->SetBranchAddress("T50Offset", &offset);
	GetEvent(nEvent);
	vector<double> wfRaw = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);
	int cConv = 1000/event->GetClockFreq();
	cout << "Offset is " << offset << endl;

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cWaveforms = GetCanvas(cName.c_str())) == 0)
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	if((hRaw = (TH1D*)GetHistogram(histName[0])) == 0)
	{
		hRaw = new TH1D(histName[0].c_str(), "Raw Waveform", wfRaw.size(), 0.0, (double)(wfRaw.size())*cConv);
		hT50 = new TH1D(histName[1].c_str(),"Offset Waveform",wfRaw.size(),0.0,(double)(wfRaw.size()-1)*cConv);
	}
	// Found - redraw on a new canvas, even if it's already drawn
	else
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		hRaw = (TH1D*)GetHistogram(histName[0]);
		hRaw->Draw();
		hT50 = (TH1D*)GetHistogram(histName[1]);
		hT50->Draw();
		TObjArray *ret = new TObjArray();
		ret->Add(hRaw);
		ret->Add(hT50);
		return ret;
	}

	for(size_t i=0;i < wfRaw.size();i++)
	{
		hRaw->Fill(i*cConv, wfRaw.at(i));
		hT50->Fill((i+offset)*cConv, wfRaw.at(i));
	}

	// Draw it
	hRaw->GetXaxis()->SetTitle("Time (ns)");
  hRaw->GetYaxis()->SetTitle("ADC Counts");
  hRaw->SetLineColor(kBlack);
	hRaw->SetFillStyle(0000);
	hRaw->Draw();
  hT50->GetXaxis()->SetTitle("Time (ns)");
  hT50->GetYaxis()->SetTitle("ADC Counts");
  hT50->SetLineColor(kRed);
	hT50->SetFillStyle(0000);
	hT50->Draw("same");
	TLegend *leg = new TLegend(0.63,0.38,0.78,0.53);
	leg->AddEntry(hRaw, "Raw");
	leg->AddEntry(hT50, "T50 Offset");
	leg->Draw();

	t50Tree->ResetBranchAddress(t50Tree->GetBranch("T50Offset"));
	TObjArray *ret = new TObjArray();
	ret->Add(hRaw);
	ret->Add(hT50);
	ret->Add(leg);
	return ret;
}

TH2D* COINCRun::PlotWaveformStack(TCut inCut, int nBL, double yMin, double yMax, bool useT50)
{
	TCanvas *cWaveforms;
	string cName, cDesc;
	string cutName = "_" + (string)inCut.GetName() + "_" + to_string(nBL) + "bl" + (string)(useT50 ? "t50":"");
	cName = cPrefix + "cWaveformStack" + cutName;
	cDesc = "Stacked Raw Waveforms";
	string histName = hPrefix + "hWaveformStack" + "_" + cutName;
	TH2D *hWaves;
	int wfLen = (int)event->GetWFRaw().size();

	if((cWaveforms = GetCanvas(cName.c_str())) == 0)
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
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
	int t50LYSO, t50GE;
	t50Tree->SetBranchAddress("t50LYSO", &t50LYSO);
	t50Tree->SetBranchAddress("t50Ge", &t50GE);

	// Create a new tree with the cut
	cout << "Copying tree using selection. This may take a moment." << endl;
	// Make a temp file to hold the new tree, since the current file is read only
	TFile *fTemp = new TFile("plotwfstack_temp.root", "RECREATE");
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	cout << "Cut tree has " << tSelection->GetEntries() << " events based on your cut." << endl;
	rootFile->cd();

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		vector<double> rawWF = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);
		for(size_t k=0;k < rawWF.size();k++)
		{
			if(useT50)
				hWaves->Fill((k+(t50GE-t50LYSO))*(1000/event->GetClockFreq()), rawWF.at(k));
			else
				hWaves->Fill(k*(1000/event->GetClockFreq()), rawWF.at(k));
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	hWaves->GetXaxis()->SetTitle("Time (ns)");
	hWaves->GetYaxis()->SetTitle("ADC Counts");
	hWaves->Draw("colz");
	// Clean up
	delete tSelection;
	fTemp->Close();
	rootFile->cd();
	t50Tree->ResetBranchAddress(t50Tree->GetBranch("t50Ge"));
	t50Tree->ResetBranchAddress(t50Tree->GetBranch("t50LYSO"));
	return hWaves;
}

TH2D* COINCRun::PlotDiffWaveformStack(TCut inCut, double yMin, double yMax)
{
	TCanvas *cWaveforms;
	string cName, cDesc;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cDiffWaveformStack" + cutName;
	cDesc = "Stacked Diff Waveforms";
	string histName = hPrefix + "hDiffWaveformStack" + "_" + cutName;
	TH2D *hWaves;

	vector<double> *wfDiff = new vector<double>();
	wfDiffTree->SetBranchAddress("wfDiff", &wfDiff);
	wfDiffTree->GetEntry(0);
	int wfLen = (int)wfDiff->size();

	if((cWaveforms = GetCanvas(cName.c_str())) == 0)
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	// Check for one of the histograms existing
	if((hWaves = (TH2D*)GetHistogram(histName)) == 0)
		hWaves = new TH2D(histName.c_str(), "Diff Waveforms, Stacked", wfLen, 0, (wfLen-1)*(1000/event->GetClockFreq()), yMax-yMin, yMin, yMax);
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
	TFile *fTemp = new TFile("plotwfstack_temp.root", "RECREATE");
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	cout << "Cut tree has " << tSelection->GetEntries() << " events based on your cut." << endl;
	rootFile->cd();

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		for(size_t k=0;k < wfDiff->size();k++)
			hWaves->Fill(k*(1000/event->GetClockFreq()), wfDiff->at(k));

		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}

	hWaves->GetXaxis()->SetTitle("Time (ns)");
	hWaves->GetYaxis()->SetTitle("ADC Counts");
	hWaves->Draw("colz");
	// Clean up
	delete tSelection;
	fTemp->Close();
	rootFile->cd();
	wfDiffTree->ResetBranchAddress(wfDiffTree->GetBranch("wfDiff"));
	delete wfDiff;
	return hWaves;
}

TH1D* COINCRun::PlotAverageWaveform(TCut inCut, int nBL, bool useT50)
{
	TCanvas *cAvgWaveform;
	TH1D *hAvgWave;
	string cName, cDesc;
	string cutName = "_" + (string)inCut.GetName() + "_" + to_string(nBL)+(string)(useT50 ? "t50":"");
	cName = cPrefix + "cAvgWaveform" + cutName;
	cDesc = "Average Waveform";
	string histName = hPrefix + "hAvgWaveform" + cutName;

	if((cAvgWaveform = GetCanvas(cName.c_str())) == 0)
		cAvgWaveform = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	// Check for one of the histograms existing
	if((hAvgWave = (TH1D*)GetHistogram(histName)) == 0)
		hAvgWave = new TH1D(histName.c_str(), "Average Waveform",(int)event->GetWFRaw().size(), 0, ((int)event->GetWFRaw().size())*(1000/event->GetClockFreq()));
	else
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		cAvgWaveform->cd();
		hAvgWave->Draw();
		return hAvgWave;
	}
	int t50GE, t50LYSO;
	t50Tree->SetBranchAddress("t50LYSO", &t50LYSO);
	t50Tree->SetBranchAddress("t50Ge", &t50GE);

	// Create a new tree with the cut
	cout << "Copying tree using selection. This may take a moment." << endl;
	// Make a temp file to hold the new tree, since the current file is read only
	TFile *fTemp = new TFile("plotavgwf_temp.root", "RECREATE");
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	cout << "Cut tree has " << tSelection->GetEntries() << " events based on your cut." << endl;
	rootFile->cd();

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		vector<double> rawWF = PACSSAnalysis::SubtractBaseline(event->GetWFRaw(), nBL);
		for(size_t k=0;k < rawWF.size();k++)
		{
			if(useT50)
				hAvgWave->Fill((k+(t50GE-t50LYSO))*(1000/event->GetClockFreq()), rawWF[k]);
			else
				hAvgWave->Fill(k*(1000/event->GetClockFreq()), rawWF[k]);
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << endl;
	}
	hAvgWave->Scale(1.0/(double)tSelection->GetEntries());
	hAvgWave->GetXaxis()->SetTitle("Time (ns)");
	hAvgWave->GetYaxis()->SetTitle("ADC Counts");
	hAvgWave->SetLineColor(kBlack);
	hAvgWave->SetFillStyle(0000);
	hAvgWave->Draw();
	// Clean up
	delete tSelection;
	fTemp->Close();
	rootFile->cd();
	t50Tree->ResetBranchAddress(t50Tree->GetBranch("t50Ge"));
	t50Tree->ResetBranchAddress(t50Tree->GetBranch("t50LYSO"));

	return hAvgWave;
}

TH1D* COINCRun::PlotAverageDiffWaveform(TCut inCut)
{
	TCanvas *cAvgWaveform;
	TH1D *hAvgWave;
	string cName, cDesc;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cAvgDiffWaveform" + cutName;
	cDesc = "Average Diff Waveform";
	string histName = hPrefix + "hAvgDiffWaveform" + cutName;
	vector<double> *wfDiff = new vector<double>();
	wfDiffTree->SetBranchAddress("wfDiff", &wfDiff);
	wfDiffTree->GetEntry(0);
	int wfLen = (int)wfDiff->size();

	if((cAvgWaveform = GetCanvas(cName.c_str())) == 0)
		cAvgWaveform = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	// Check for one of the histograms existing
	if((hAvgWave = (TH1D*)GetHistogram(histName)) == 0)
		hAvgWave = new TH1D(histName.c_str(), "Average Diff Waveform",wfLen,0,(wfLen-1)*(1000/event->GetClockFreq()));
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
	TFile *fTemp = new TFile("plotavgwf_temp.root", "RECREATE");
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	cout << "Cut tree has " << tSelection->GetEntries() << " events based on your cut." << endl;
	rootFile->cd();

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		for(size_t k=0;k < wfDiff->size();k++)
			hAvgWave->Fill(k*(1000/event->GetClockFreq()), wfDiff->at(k));
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
	wfDiffTree->ResetBranchAddress(wfDiffTree->GetBranch("wfDiff"));
	delete wfDiff;
	return hAvgWave;
}

TH1D* COINCRun::PlotTimeBetweenCoincEvents(TCut inCut, string plotArgs, bool useTCorr)
{
	TCanvas *cCoincDT;
	TH1D *hCoincDT;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName() + (string)(useTCorr ? "corr" : "");
	cName = cPrefix + "cCoincDT" + cutName;
	cDesc = "Time Between Coincident Events";
	histName = hPrefix + "CoincDT" + cutName;


	if((cCoincDT = GetCanvas(cName.c_str())) == 0)
		cCoincDT = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	if(!(hCoincDT = (TH1D*)GetHistogram(histName)) == 0)
	{
		cout << "Histograms found in gDirectory. Delete them or change the names to redraw." << endl;
		cCoincDT->cd();
		hCoincDT->Draw();
		return hCoincDT;
	}

	double tCorr;
	if(useTCorr)
		t50Tree->SetBranchAddress("corrTimestampNS", &tCorr);
	// Get the time of the first event (offset)
	GetEvent(0);
	double sGE;
	if(useTCorr)
		sGE = tCorr;
	else
		sGE = event->GetTimestampGE(true);
	double sLYSO = event->GetTimestampLYSO(true);
	cout << sGE << endl;

	// Subtract the offset, ROOT style
	char temp[256];
	string sTemp = histName + plotArgs;
	if(useTCorr)
		sprintf(temp, "((corrTimestampNS - %f) - (timestampLYSONS - %f)) >> %s", sGE, sLYSO, sTemp.c_str());
	else
		sprintf(temp, "((timestampGENS - %f) - (timestampLYSONS - %f)) >> %s", sGE, sLYSO, sTemp.c_str());
	int nPlotted = eventTree->Draw(temp, inCut, "NBQ");
	hCoincDT = (TH1D*)GetHistogram(histName.c_str());
	hCoincDT->SetTitle("Time Between Coincident Events");
	hCoincDT->GetXaxis()->SetTitle("tGE - tLYSO (ns)");
	hCoincDT->GetYaxis()->SetTitle("Counts");
	hCoincDT->SetLineColor(kBlack);
	hCoincDT->Draw();
	cout << nPlotted << " events plotted." << endl;

	t50Tree->ResetBranchAddress(t50Tree->GetBranch("corrTimestampNS"));
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
		cChargeMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
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
	TFile *fTemp = new TFile("plotchargeproj_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	int x, y;
	vector<double> charge;
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
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
		cSGPosMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
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

TObjArray* COINCRun::PlotSGChi2ByPos(TCut inCut)
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
		hSGChi2X = new TH1D(histName[0].c_str(), "X #Chi^{2}", 98, 0.0, 98.0);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y #Chi^{2}", 98, 0.0, 98.0);
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
	posTree->SetBranchAddress("chi2GX98Pos", &chi2X);
	posTree->SetBranchAddress("chi2GY98Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotsgchi2pos_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
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
	fTemp->Close();
	posTree->ResetBranchAddress(posTree->GetBranch("chi2GX98Pos"));
	posTree->ResetBranchAddress(posTree->GetBranch("chi2GY98Pos"));
	delete chi2X;
	delete chi2Y;
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* COINCRun::PlotSGChi2(TCut inCut, double xMin, double xMax)
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
		hSGChi2X = new TH1D(histName[0].c_str(), "X #Chi^{2}", (xMax-xMin), xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y #Chi^{2}", (xMax-xMin), xMin, xMax);
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
	posTree->SetBranchAddress("chi2GX98Pos", &chi2X);
	posTree->SetBranchAddress("chi2GY98Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotsgchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
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
	fTemp->Close();
	posTree->ResetBranchAddress(posTree->GetBranch("chi2GX98Pos"));
	posTree->ResetBranchAddress(posTree->GetBranch("chi2GY98Pos"));
	delete chi2X;
	delete chi2Y;
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* COINCRun::PlotSGMinChi2(TCut inCut, double xMin, double xMax)
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
		hSGChi2X = new TH1D(histName[0].c_str(), "X Min #Chi^{2}", (xMax-xMin), xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y Min #Chi^{2}", (xMax-xMin), xMin, xMax);
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
	posTree->SetBranchAddress("chi2GX98Pos", &chi2X);
	posTree->SetBranchAddress("chi2GY98Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotsgminchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		double minX = 5e10;
		double minY = 5e10;
		tSelection->GetEntry(i);
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
	fTemp->Close();
	posTree->ResetBranchAddress(posTree->GetBranch("chi2GX98Pos"));
	posTree->ResetBranchAddress(posTree->GetBranch("chi2GY98Pos"));
	delete chi2X;
	delete chi2Y;
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* COINCRun::PlotSGPosProj(TCut inCut, string plotArgsX, string plotArgsY)
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
	string toDraw = "gaussX98Pos >> " + histName[0] + plotArgsX;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hX = (TH1D*)GetHistogram(histName[0]);
	hX->SetTitle("SG X Projection");
  hX->GetXaxis()->SetTitle("SGX Position (mm)");
  hX->GetYaxis()->SetTitle("Counts");
	hX->Draw();
	cout << nPlotted << " drawn to X projection." << endl;
	cSGPosProj->cd(2);
	toDraw = "gaussY98Pos >> " + histName[1] + plotArgsY;
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
		cSLPosMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
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

TObjArray* COINCRun::PlotSLChi2ByPos(TCut inCut)
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
		hSGChi2X = new TH1D(histName[0].c_str(), "X #Chi^{2}", 98, 0.0, 98.0);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y #Chi^{2}", 98, 0.0, 98.0);
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
	posTree->SetBranchAddress("chi2LX98Pos", &chi2X);
	posTree->SetBranchAddress("chi2LY98Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotslchi2pos_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
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
	fTemp->Close();
	posTree->ResetBranchAddress(posTree->GetBranch("chi2LX98Pos"));
	posTree->ResetBranchAddress(posTree->GetBranch("chi2LY98Pos"));
	delete chi2X;
	delete chi2Y;
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* COINCRun::PlotSLChi2(TCut inCut, double xMin, double xMax)
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
		hSGChi2X = new TH1D(histName[0].c_str(), "X #Chi^{2}", (xMax-xMin), xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y #Chi^{2}", (xMax-xMin), xMin, xMax);
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
	posTree->SetBranchAddress("chi2LX98Pos", &chi2X);
	posTree->SetBranchAddress("chi2LY98Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotslchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
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
	fTemp->Close();
	posTree->ResetBranchAddress(posTree->GetBranch("chi2LX98Pos"));
	posTree->ResetBranchAddress(posTree->GetBranch("chi2LY98Pos"));
	delete chi2X;
	delete chi2Y;
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* COINCRun::PlotSLMinChi2(TCut inCut, double xMin, double xMax)
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
		hSGChi2X = new TH1D(histName[0].c_str(), "X Min #Chi^{2}", (xMax-xMin), xMin, xMax);
		hSGChi2Y = new TH1D(histName[1].c_str(), "Y Min #Chi^{2}", (xMax-xMin), xMin, xMax);
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
	posTree->SetBranchAddress("chi2LX98Pos", &chi2X);
	posTree->SetBranchAddress("chi2LY98Pos", &chi2Y);
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotslminchi2_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	rootFile->cd();
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		double minX = 5e10;
		double minY = 5e10;
		tSelection->GetEntry(i);
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
	fTemp->Close();
	posTree->ResetBranchAddress(posTree->GetBranch("chi2LX98Pos"));
	posTree->ResetBranchAddress(posTree->GetBranch("chi2LY98Pos"));
	delete chi2X;
	delete chi2Y;
	rootFile->cd();
	TObjArray *ret = new TObjArray();
	ret->Add(hSGChi2X);
	ret->Add(hSGChi2Y);
	return ret;
}

TObjArray* COINCRun::PlotSLPosProj(TCut inCut, string plotArgsX, string plotArgsY)
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
	string toDraw = "lercheX98Pos >> " + histName[0] + plotArgsX;
	nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	hX = (TH1D*)GetHistogram(histName[0]);
	hX->SetTitle("SL X Projection");
  hX->GetXaxis()->SetTitle("SLX Position (mm)");
  hX->GetYaxis()->SetTitle("Counts");
	hX->Draw();
	cout << nPlotted << " drawn to X projection." << endl;
	cSGPosProj->cd(2);
	toDraw = "lercheY98Pos >> " + histName[1] + plotArgsY;
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

TH2D* COINCRun::PlotIMaxOverEVsE(TCut inCut, string plotArgs)
{
	TCanvas *cAOverE;
	TH2D *hAOverE;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cAOverEMap" + cutName;
	cDesc = "IMax/E vs E";
	histName = hPrefix + "hAOverEMap" + cutName;
	
	if((cAOverE = GetCanvas(cName.c_str())) == 0)
		cAOverE = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	if((hAOverE = (TH2D*)GetHistogram(histName)) == 0)
	{
		hAOverE = new TH2D();
		hAOverE->SetName(histName.c_str());
		hAOverE->SetTitle("IMax/E vs E Map");
		hAOverE->GetXaxis()->SetTitle("Energy (arb)");
		hAOverE->GetYaxis()->SetTitle("IMax/E (arb)");
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		cAOverE->cd();
		hAOverE->Draw("colz");
		return hAOverE;
	}

	string toDraw = "(IMax/energyGE):energyGE>>+"+histName+plotArgs;
	int nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "colz");
	cout << nPlotted << " events plotted." << endl;
	return hAOverE;
}

TH1D* COINCRun::PlotIMaxOverEDist(TCut inCut, string plotArgs)
{
	TCanvas *cAOverE;
	TH1D *hAOverE;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cAOverEDist" + cutName;
	cDesc = "IMax/E vs E";
	histName = hPrefix + "hAOverEDist" + cutName;
	
	if((cAOverE = GetCanvas(cName.c_str())) == 0)
		cAOverE = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);
	if((hAOverE = (TH1D*)GetHistogram(histName)) == 0)
	{
		hAOverE = new TH1D();
		hAOverE->SetName(histName.c_str());
		hAOverE->SetTitle("IMax/Energy Distribution");
		hAOverE->GetXaxis()->SetTitle("IMax/Energy (arb)");
		hAOverE->GetYaxis()->SetTitle("Counts");
		hAOverE->SetLineColor(kBlack);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		cAOverE->cd();
		hAOverE->Draw();
		return hAOverE;
	}

	string toDraw = "(IMax/energyGE)>>+"+histName+plotArgs;
	int nPlotted = eventTree->Draw(toDraw.c_str(), inCut, "NBQ");
	cout << nPlotted << " events plotted." << endl;
	hAOverE->Draw();
	return hAOverE;
}

TH2D* COINCRun::PlotDriftTimeMap(TCut inCut, string plotArgs)
{
	TCanvas *cDTMap;
	TH2D *hDTMap;
	string cName, cDesc, histName;
	string cutName = "_" + (string)inCut.GetName();
	cName = cPrefix + "cPlotDTMap" + cutName;
	cDesc = "Drift Time Map";
	histName = hPrefix + "hDTMap" + cutName;

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cDTMap = GetCanvas(cName.c_str())) == 0)
		cDTMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 800);

	// Make sure we don't have the histograms already available to us. Closing the canvas window
	// does not delete the histograms, no need to recreate them if they exist
	// found - will need to process
	if(!((hDTMap = (TH2D*)GetHistogram(histName)) == 0))
	{
		cout << "Histogram found in gDirectory. Delete them or change the names to redraw." << endl;
		cDTMap->cd();
		hDTMap->Draw();
  	return hDTMap;
	}
	else
		hDTMap = new TH2D(histName.c_str(), "Drift Time Map", 98, 0.0, 49.0, 98, 0.0, 49.0);
	
	cout << "Copying tree using selection. This may take a moment." << endl;
	TFile *fTemp = new TFile("plotdriftmap_temp.root", "RECREATE");
	TTree *tSelection = eventTree->CopyTree(inCut);
	cout << tSelection->GetEntries() << " events selected based on your cut." << endl;
	posTree->AddFriend(eventTree);
	TTree *tSelection2 = posTree->CopyTree(inCut);
	cout << tSelection2->GetEntries() << " events in second tree." << endl;
	t50Tree->AddFriend(eventTree);
	TTree *tSelection3 = t50Tree->CopyTree(inCut);
	cout << tSelection3->GetEntries() << " events in third tree." << endl;
	rootFile->cd();
	vector<int> hits(100*100);
	
	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection3->GetEntry(i);
		tSelection2->GetEntry(i);
		int bin = hDTMap->Fill(lXPos,lYPos,deltaT);
		hits.at(bin)++;
		if (i % 100 == 0) {
			cout << "Processing event " << i << ", x=" << lXPos << ", y=" << lYPos << " " << "dt=" << deltaT << " ";
			cout << "bin=" << bin << "(" << hits.at(bin) << ")" << endl;
		}
	}

	cout << "Averaging histogram..." << endl;
	// Average drift time for each pixel depending on how many Fill() calls we made
	for (size_t k=101;k <= hDTMap->GetSize()-100;k++) {
		if(hits.at(k) != 0)
			hDTMap->SetBinContent(k, hDTMap->GetBinContent(k)/hits.at(k));
	}
	cout << endl;
			
	delete tSelection;
	fTemp->Close();
	//t50Tree->ResetBranchAddress(t50Tree->GetBranch("deltaT"));
	//posTree->ResetBranchAddress(posTree->GetBranch("lercheX98Pos"));
	//posTree->ResetBranchAddress(posTree->GetBranch("lercheY98Pos"));
	rootFile->cd();
	hDTMap->GetXaxis()->SetTitle("X Position (mm)");
	hDTMap->GetYaxis()->SetTitle("Y Position (mm)");
	hDTMap->Draw("colz");
	return hDTMap;
}
