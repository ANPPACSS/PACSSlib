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

  // How many events? iEvent = 0 from PACSSRun initialization
  numEvents = eventTree->GetEntries();
  cout << numEvents << " events in data file." << endl;
  eventTree->GetEntry(iEvent);
}

COINCRun::~COINCRun()
{
	// Clean up
	delete event;

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

// Return a TH1D pointer - checks gDirectory, which is the default structure for histogram storage
// when histograms are drawn to a canvas
TH1D* COINCRun::Get1DHist(string histName)
{
	// Return the histogram
	return (TH1D*)gDirectory->FindObject(histName.c_str());
}

// Return a TH2D pointer
TH2D* COINCRun::Get2DHist(string histName)
{
	return (TH2D*)gDirectory->FindObject(histName.c_str());
}

vector<double> COINCRun::SubtractBaseline(vector<double> aWF, int nSampAvg)
{
	double avg = 0.0;
	vector<double> bWF;
	for(size_t i=0;i < (size_t)nSampAvg;i++)
		avg += aWF.at(i);
	avg /= nSampAvg;
	for(size_t i=0;i < aWF.size();i++)
		bWF.push_back(aWF.at(i)-avg);
	return bWF;
}

// Plot energy histograms from both detectors on one canvas
void COINCRun::PlotEnergyHist(int nGe, double xMinGe, double xMaxGe, int nLYSO, double xMinLYSO, double xMaxLYSO)
{
	TCanvas *cEnergyHist;
	TH1D *hLYSO;
	TH1D *hGE;
	string cName, cDesc, histName[2];
	string canvParams = to_string(nGe) + to_string(xMinGe) + to_string(xMaxGe) + to_string(nLYSO) + to_string(xMinLYSO) + to_string(xMaxLYSO);
	cName = cPrefix + "cEnergyHist" + canvParams;
	cDesc = "Energy Spectra";
	histName[0] = fileName + "_" + "EnergyLYSO" + to_string(nLYSO) + to_string(xMinLYSO) + to_string(xMaxLYSO);
	histName[1] = fileName + "_" + "EnergyGE" + to_string(nGe) + to_string(xMinGe) + to_string(xMaxGe);

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cEnergyHist = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
	{
		cEnergyHist = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cEnergyHist->Divide(1, 2);
	}

	// Make sure we don't have the histograms already available to us. Closing the canvas window
	// does not delete the histograms, no need to recreate them if they exist
	// Not found - will need to process
	if((hLYSO = Get1DHist(histName[0])) == 0)
	{
		hLYSO = new TH1D(histName[0].c_str(), "LYSO Energy", nLYSO, xMinLYSO, xMaxLYSO);
  	hGE = new TH1D(histName[1].c_str(), "GE Energy", nGe, xMinGe, xMaxGe);
	}
	// Found - redraw on a new canvas, even if it's already drawn
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hGE = Get1DHist(histName[1]);
		cEnergyHist->cd(1);
		hGE->Draw();
		cEnergyHist->cd(2);
		hLYSO->Draw();
		return;
	}

	// Fill the histograms, no cuts
	cEnergyHist->cd(1);
	// Scale GE energy
	string toDraw = "energyGE >> " + histName[1];
	eventTree->Draw(toDraw.c_str(), "", "NRQ");
  hGE->GetXaxis()->SetTitle("Energy (arb)");
  hGE->GetYaxis()->SetTitle("Counts");
  hGE->SetFillColor(kRed);
	hGE->Draw();
	cEnergyHist->cd(2);
	toDraw = "energyGC >> " + histName[0];
	eventTree->Draw(toDraw.c_str(), "", "NRQ");
	hLYSO->GetXaxis()->SetTitle("Energy (pC)");
	hLYSO->GetYaxis()->SetTitle("Counts");
	hLYSO->SetFillColor(kBlue);
	hLYSO->Draw();
	cout << numEvents << " events plotted." << endl;

  return;
}

void COINCRun::PlotEnergySlice(int rowXlow, int rowXup, int rowYlow, int rowYup)
{
	TCanvas *cEnergySlice;
	TH1D *hGE;
	TH1D *hLYSO;
	string cName, cDesc, histName[2];
	string win = to_string(rowXlow) + to_string(rowXup) + to_string(rowYlow) + to_string(rowYup);
	cName = cPrefix + "cEnergySlice" + win;
	cDesc = "Energy Spectra, Select Slices";
	histName[0] = fileName + "_" + "EnergyGESlice" + win;
	histName[1] = fileName + "_" + "EnergyLYSOSlice" + win;

	if((cEnergySlice = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
	{
		cEnergySlice = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cEnergySlice->Divide(1,2);
	}
	if((hGE = Get1DHist(histName[0])) == 0)
	{
		hGE = new TH1D(histName[0].c_str(), "GE Energy (Sliced)", 16384, 0, 16383.0);
		hLYSO = new TH1D(histName[1].c_str(), "LYSO Energy (Sliced)", 4116, -10.0, 2047.0);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		hLYSO = Get1DHist(histName[1]);
		cEnergySlice->cd(1);
		hLYSO->Draw();
		cEnergySlice->cd(2);
		hGE->Draw();
	}

	PACSSEvent e;
	vector<double> charge;
	int nPlotted = 0;
	for(int i=0;i < numEvents;i++)
	{
		GetEvent(i);
		charge = event->GetChargeGC();
		int iMax = 0;
		double max = 0.0;
		for(int k=0;k < 64;k++)
		{
			if(charge.at(k) > max)
				iMax = k;
		}
		int x, y;
		e.ChanNumToXYPos(iMax, x, y);
		if((y >= rowXlow) && (y <= rowXup) && (x >= rowYlow) && (x <= rowYup))
		{
			hGE->Fill(event->GetEnergyGE());
			hLYSO->Fill(event->GetEnergyGC());
			nPlotted++;
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << "." << endl;
	}

	cEnergySlice->cd(2);
	hLYSO->GetXaxis()->SetTitle("Charge (pC)");
	hLYSO->GetYaxis()->SetTitle("Counts");
	hLYSO->SetFillColor(kBlue);
	hLYSO->Draw();
	cEnergySlice->cd(1);
	hGE->GetXaxis()->SetTitle("Energy (arb)");
	hGE->GetYaxis()->SetTitle("Counts");
	hGE->SetFillColor(kRed);
	hGE->Draw();
	cout << nPlotted << " events plotted." << endl;
	return;
}

void COINCRun::PlotWaveforms(int nEvent)
{
	TCanvas *cWaveforms;
	TH1D *hRaw;
	TH1D *hDiff;
	string cName, cDesc, histName[2];
	cName = cPrefix + "cWaveforms" + to_string(nEvent);
	cDesc = "Raw and Diff. Waveforms Event " + to_string(nEvent);
	histName[0] = fileName + "_" + "RawWaveform" + to_string(nEvent);
	histName[1] = fileName + "_" + "DiffWaveform" + to_string(nEvent);
	// Get the waveforms here so we know the sizes for the histograms
	GetEvent(nEvent);
	vector<double> wfRaw = event->GetWFRaw();
	vector<double> wfDiff = event->GetWFDiff();

	// Check for the TCanvas object existing. Not in gDirectory, because that would make sense
	if((cWaveforms = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
	{
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cWaveforms->Divide(1, 2);
	}
	if((hRaw = Get1DHist(histName[0])) == 0)
	{
		hRaw = new TH1D(histName[0].c_str(), "Raw Waveform", wfRaw.size(), 0.0, (double)(wfRaw.size()-1));
  	hDiff = new TH1D(histName[1].c_str(), "Diff. Waveform", wfDiff.size(), 0.0, (double)(wfDiff.size()-1));
	}
	// Found - redraw on a new canvas, even if it's already drawn
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		//hRaw = Get1DHist(histName[0]);
		hDiff = Get1DHist(histName[1]);
		cWaveforms->cd(1);
		hRaw->Draw();
		cWaveforms->cd(2);
		hDiff->Draw();
		return;
	}

	// Fill the histograms
	for(size_t i=0;i < wfRaw.size();i++)
		hRaw->Fill(i, wfRaw.at(i));
	for(size_t i=0;i < wfDiff.size();i++)
		hDiff->Fill(i, wfDiff.at(i));

	// Draw it
	cWaveforms->cd(1);
  hRaw->GetXaxis()->SetTitle("Sample #");
  hRaw->GetYaxis()->SetTitle("ADC Counts");
  hRaw->SetFillColor(kRed);
	hRaw->SetFillStyle(0000);
	hRaw->Draw();
	cWaveforms->cd(2);
	hDiff->GetXaxis()->SetTitle("Sample #");
	hDiff->GetYaxis()->SetTitle("Current (arb)");
	hDiff->SetFillColor(kBlue);
	hDiff->SetFillStyle(0000);
	hDiff->Draw();

	return;
}

void COINCRun::PlotWaveformStack(TCut inCut)
{
	TCanvas *cWaveforms;
	string cName, cDesc, histName;
	cName = cPrefix + "cWaveforms";
	cDesc = "Stacked Raw Waveforms";

	if((cWaveforms = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cWaveforms = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	else
	{
		cout << "Canvas found." << endl;
		cWaveforms->Update();
		return;
	}

	// Create a new tree with the cut
	cout << "Copying tree using selection. This may take a moment." << endl;
	rootFile->cd();
	TTree *tSelection = (TTree*)eventTree->CopyTree(inCut);
	tSelection->SetDirectory(0);
	COINCEvent *e2 = new COINCEvent();
	tSelection->SetBranchAddress("event", &e2);
	cout << "Cut tree has " << tSelection->GetEntries() << " events." << endl;

	for(int i=0;i < tSelection->GetEntries();i++)
	{
		tSelection->GetEntry(i);
		vector<double> rawWF = SubtractBaseline(e2->GetWFRaw(), 500);
		string histName = "hWaveform" + to_string(i);
		TH1D *hWaves = new TH1D(histName.c_str(), "Raw Waveform", rawWF.size(), 0.0, (double)(rawWF.size()-1));
		for(size_t k=0;k < rawWF.size();k++)
			hWaves->Fill(k, rawWF.at(k));
		hWaves->Draw("same");
	}
	cWaveforms->Update();
	return;
}

void COINCRun::PlotTimeBetweenCoincEvents(int nX, double xMin, double xMax)
{
	TCanvas *cCoincDT;
	TH1D *hCoincDT;
	string cName, cDesc, histName;
	string histParams = to_string(nX) + to_string(xMin) + to_string(xMax);
	cName = cPrefix + "cCoincDT" + to_string(0) + "-" + to_string(numEvents-1) + histParams;
	cDesc = "Time Between Coincident Events";
	histName = fileName + "_" + "CoincDT" + to_string(0) + "-" + to_string(numEvents-1) + histParams;


	if((cCoincDT = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cCoincDT = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hCoincDT = Get1DHist(histName)) == 0)
		hCoincDT = new TH1D(histName.c_str(), "Time Between Coinc. Events", nX, xMin, xMax);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cCoincDT->cd();
		hCoincDT->Draw();
		return;
	}

	// Get the time of the first event (offset)
	GetEvent(0);
	double sGE = event->GetTimestampGE(true);
	double sLYSO = event->GetTimestampLYSO(true);

	// Subtract the offset, ROOT style
	char temp[256];
	sprintf(temp, "((timestampLYSONS - %f) - (timestampGENS - %f)) >> %s", sLYSO, sGE, histName.c_str());
	eventTree->Draw(temp, "", "NRQ");

	hCoincDT->GetXaxis()->SetTitle("tLYSO - tGE (ns)");
	hCoincDT->GetYaxis()->SetTitle("Counts");
	hCoincDT->Draw();

	return;
}

void COINCRun::PlotTimeBetweenCoincEvents(int nStart, int nEnd, int nX, double xMin, double xMax)
{
	if(nEnd > (numEvents-1))
	{
		cout << "Please enter a valid event range." << endl;
		return;
	}
	TCanvas *cCoincDT;
	TH1D *hCoincDT;
	string cName, cDesc, histName;
	string histParams = to_string(nX) + to_string(xMin) + to_string(xMax);
	cName = cPrefix + "cCoincDT" + to_string(nStart) + "-" + to_string(nEnd) + histParams;
	cDesc = "Time Between Coincident Events";
	histName = fileName + "_" + "CoincDT" + to_string(nStart) + "-" + to_string(nEnd) + histParams;


	if((cCoincDT = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cCoincDT = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hCoincDT = Get1DHist(histName)) == 0)
		hCoincDT = new TH1D(histName.c_str(), "Time Between Coinc. Events", nX, xMin, xMax);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cCoincDT->cd();
		hCoincDT->Draw();
		return;
	}

	// Get the time of the first event (offset)
	GetEvent(0);
	double sGE = event->GetTimestampGE(true);
	double sLYSO = event->GetTimestampLYSO(true);

	char temp[256], temp2[256];
	sprintf(temp, "((timestampLYSONS - %f) - (timestampGENS - %f)) >> %s", sLYSO, sGE, histName.c_str());
	sprintf(temp2, "(Entry$ >= %d) && (Entry$ <= %d)", nStart, nEnd);
	TCut cuts = temp2;
	eventTree->Draw(temp, cuts, "NRQ");

	hCoincDT->GetXaxis()->SetTitle("tLYSO - tGE (ns)");
	hCoincDT->GetYaxis()->SetTitle("Counts");
	hCoincDT->Draw();
	return;
}

// Arguments: energy window--> eGE1, eGE2, eLYSO1, eLYSO2
void COINCRun::PlotChargeMap(double eg1, double eg2, double el1, double el2, bool gc)
{
	TCanvas *cChargeMap;
	TH2D *hCharge;
	string cName, cDesc, histName;
	string cuts = to_string((int)eg1)+to_string((int)eg2)+to_string((int)el1)+to_string((int)el2)+(gc ? "gc" : "");
	cName = cPrefix + "cChargeMap" + cuts;
	cDesc = "Charge Map " + (string)(gc ? "(Gain Corrected)" : "");
	histName = fileName + "_" + "ChargeMap" + cuts;

	if((cChargeMap = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cChargeMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hCharge = Get2DHist(histName)) == 0)
		hCharge = new TH2D(histName.c_str(), "Charge Map", 8, 0.0, 8.0, 8, 0.0, 8.0);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cChargeMap->cd();
		hCharge->Draw("colz");
		return;
	}

	PACSSEvent e;
	int x, y;
	int nPlotted = 0;
	for(int i=0;i < numEvents;i++)
	{
		GetEvent(i);
		double eg = event->GetEnergyGE();
		double el = event->GetEnergyGC();
		if((eg > eg1) && (eg < eg2) && (el > el1) && (el < el2))
		{
			vector<double> cgc;
			if(gc)
				cgc = event->GetChargeGC();
			else
				cgc = event->GetCharge();
			for(int k=0;k < NUM_LYSO_PIXELS;k++)
			{
				e.ChanNumToXYPos(k, x, y);
				hCharge->Fill(x, y, cgc.at(k));
			}
			nPlotted++;
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << "." << endl;
	}

	hCharge->Draw("colz");
	hCharge->GetXaxis()->SetTitle("X Pixel");
	hCharge->GetYaxis()->SetTitle("Y Pixel");
	cout << nPlotted << " events plotted." << endl;
	return;
}

// Arguments: event number
void COINCRun::PlotChargeMap(int nEvent, bool gc)
{
	TCanvas *cChargeMap;
	TH2D *hCharge;
	string cName, cDesc, histName;
	string cuts = to_string(nEvent);
	cName = cPrefix + "cChargeMap" + cuts + (gc ? "gc" : "");
	cDesc = "Charge Map" + (string)(gc ? " (Gain Corrected) " : "") + ", Event " + cuts;
	histName = fileName + "_" + "ChargeMap" + cuts + (gc ? "gc" : "");

	if((cChargeMap = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cChargeMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hCharge = Get2DHist(histName)) == 0)
		hCharge = new TH2D(histName.c_str(), "Charge Map", 8, 0.0, 8.0, 8, 0.0, 8.0);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cChargeMap->cd();
		hCharge->Draw();
		return;
	}

	PACSSEvent e;
	int x, y;
	GetEvent(nEvent);
	vector<double> cgc;
	if(gc)
		cgc = event->GetChargeGC();
	else
		cgc = event->GetCharge();
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		e.ChanNumToXYPos(i, x, y);
		hCharge->Fill(x, y, cgc.at(i));
	}

	hCharge->Draw("colz");
	hCharge->GetXaxis()->SetTitle("X Pixel");
	hCharge->GetYaxis()->SetTitle("Y Pixel");
	cout << "Charge map for event " << nEvent << " plotted." << endl;
	return;
}

// Arguments: energy window
void COINCRun::PlotChargeProj(double eg1, double eg2, double el1, double el2, bool gc)
{
	TCanvas *cChargeProj;
	TH1D *hX;
	TH1D *hY;
	string cName, cDesc, histName[2];
	string cuts = to_string((int)eg1)+to_string((int)eg2)+to_string((int)el1)+to_string((int)el2)+(gc ? "gc" : "");
	cName = cPrefix + "cChargeProj" + cuts + (gc ? "gc" : "");
	cDesc = "Charge Projections" + (string)(gc ? " (Gain Corrected)" : "");
	histName[0] = fileName + "_" + "ChargeXProj" + cuts + (gc ? "gc" : "");
	histName[1] = fileName + "_" + "ChargeYProj" + cuts + (gc ? "gc" : "");

	if((cChargeProj = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
	{
		cChargeProj = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cChargeProj->Divide(1,2);
	}
	if((hX = Get1DHist(histName[0])) == 0)
	{
		hX = new TH1D(histName[0].c_str(), "Charge X Projection", 8, 0.0, 8.0);
		hY = new TH1D(histName[1].c_str(), "Charge Y Projection", 8, 0.0, 8.0);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		cChargeProj->cd(1);
		hX->Draw();
		hY = Get1DHist(histName[1]);
		cChargeProj->cd(2);
		hY->Draw();
		return;
	}

	PACSSEvent e;
	int x, y;
	vector<double> charge;
	int nPlotted = 0;
	for(int i=0;i < numEvents;i++)
	{
		GetEvent(i);
		double eg = event->GetEnergyGE();
		double el = event->GetEnergyGC();
		if((eg > eg1) && (eg < eg2) && (el > el1) && (el < el2))
		{
			if(gc)
				charge = event->GetChargeGC();
			else
				charge = event->GetCharge();
			for(int k=0;k < NUM_LYSO_PIXELS;k++)
			{
				e.ChanNumToXYPos(k, x, y);
				hX->Fill(x, charge.at(k));
				hY->Fill(y, charge.at(k));
			}
			nPlotted++;
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << "." << endl;
	}

	cChargeProj->cd(1);
	hX->GetXaxis()->SetTitle("X Pixel");
	hX->GetYaxis()->SetTitle("Proj. Charge (pC)");
	hX->Draw();
	cChargeProj->cd(2);
	hY->GetXaxis()->SetTitle("Y Pixel");
	hY->GetYaxis()->SetTitle("Proj. Charge (pC)");
	hY->Draw();
	cout << nPlotted << " events plotted." << endl;
	return;
}

void COINCRun::PlotChargeProj(int nEvent, bool gc)
{
	return;
}

void COINCRun::PlotChargeProjSlice(double eg1, double eg2, double el1, double el2, int rowXlow, int rowXup, int rowYlow, int rowYup)
{
	TCanvas *cChargeProjSlice;
	TH1D *hX;
	TH1D *hY;
	string cName, cDesc, histName[2];
	string cuts = to_string((int)eg1)+to_string((int)eg2)+to_string((int)el1)+to_string((int)el2);
	cuts += to_string(rowXlow) + to_string(rowXup) + to_string(rowYlow) + to_string(rowYup);
	cName = cPrefix + "cChargeProjSlice" + cuts;
	cDesc = "Charge Projections (Sliced)";
	histName[0] = fileName + "_" + "ChargeXProjSlice" + cuts;
	histName[1] = fileName + "_" + "ChargeYProjSlice" + cuts;

	if((cChargeProjSlice = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
	{
		cChargeProjSlice = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cChargeProjSlice->Divide(1,2);
	}
	if((hX = Get1DHist(histName[0])) == 0)
	{
		hX = new TH1D(histName[0].c_str(), "Charge X Slice Projection", 8, 0.0, 8.0);
		hY = new TH1D(histName[1].c_str(), "Charge Y Slice Projection", 8, 0.0, 8.0);
	}
	else
	{
		cout << "Histograms found in gDirectory." << endl;
		cChargeProjSlice->cd(1);
		hX->Draw();
		hY = Get1DHist(histName[1]);
		cChargeProjSlice->cd(2);
		hY->Draw();
		return;
	}

	PACSSEvent e;
	int x, y;
	vector<double> charge;
	for(int i=0;i < numEvents;i++)
	{
		GetEvent(i);
		double eg = event->GetEnergyGE();
		double el = event->GetEnergyGC();
		if((eg > eg1) && (eg < eg2) && (el > el1) && (el < el2))
		{
			charge = event->GetChargeGC();
			for(int k=0;k < NUM_LYSO_PIXELS;k++)
			{
				e.ChanNumToXYPos(k, x, y);
				if((y >= rowXlow) && (y <= rowXup))
					hX->Fill(x, charge.at(k));
				if((x >= rowYlow) && (x <= rowYup))
					hY->Fill(y, charge.at(k));
			}
		}
		if(i % reportFreq == 0)
			cout << "Processing event " << i << "." << endl;
	}

	cChargeProjSlice->cd(1);
	hX->GetXaxis()->SetTitle("X Pixel");
	hX->GetYaxis()->SetTitle("Proj. Charge (pC)");
	hX->Draw();
	cChargeProjSlice->cd(2);
	hY->GetXaxis()->SetTitle("Y Pixel");
	hY->GetYaxis()->SetTitle("Proj. Charge (pC)");
	hY->Draw();
	return;
}

void COINCRun::PlotGPosMap(TCut inCut, int nX, double xMin, double xMax, int nY, double yMin, double yMax)
{	
	TCanvas *cGPosMap;
	TH2D *hGPos;
	string cName, cDesc, histName;
	string canvParams = to_string(nX) + to_string(xMin) + to_string(xMax) + to_string(nY) + to_string(yMin) + to_string(yMax);
	cName = cPrefix + "cGPosMap" + (string)inCut.GetName() + canvParams;
	cDesc = "Gauss Position";
	histName = fileName + "_" + "GPosMap" + (string)inCut.GetName() + canvParams;

	if((cGPosMap = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cGPosMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hGPos = Get2DHist(histName)) == 0)
		hGPos = new TH2D(histName.c_str(), "Gauss Position Map", nX, xMin, xMax, nY, yMin, yMax);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cGPosMap->cd();
		hGPos->Draw("colz");
		return;
	}
	eventTree->Project(histName.c_str(), "gaussYPos:gaussXPos", inCut, "NRQ");
	hGPos->Draw("colz");
	hGPos->GetXaxis()->SetTitle("GX Position");
	hGPos->GetYaxis()->SetTitle("GY Position");
	return;
}

void COINCRun::PlotGPosProj(TCut inCut, int nX, double xMin, double xMax, int nY, double yMin, double yMax)
{
	TCanvas *cGPosProj;
	TH1D *hGPosProjX;
	TH1D *hGPosProjY;
	string cName, cDesc, histName[2];
	string canvParams = to_string(nX) + to_string(xMin) + to_string(xMax) + to_string(nY) + to_string(yMin) + to_string(yMax);
	cName = cPrefix + "cGPosProj" + (string)inCut.GetName() + canvParams;
	cDesc = "Gauss Position Projections";
	histName[0] = fileName + "_" + "GPosProjX" + (string)inCut.GetName() + to_string(nX) +to_string(xMin)+to_string(xMax);
	histName[1] = fileName + "_" + "GPosProjY" + (string)inCut.GetName() + to_string(nY)+to_string(yMin)+to_string(yMax);

	if((cGPosProj = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
	{
		cGPosProj = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 1080);
		cGPosProj->Divide(1,2);
	}
	if((hGPosProjX = Get1DHist(histName[0])) == 0)
	{
		hGPosProjX = new TH1D(histName[0].c_str(), "GPos X Projection", nX, xMin, xMax);
		hGPosProjY = new TH1D(histName[1].c_str(), "GPos Y Projection", nY, yMin, yMax);
	}
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cGPosProj->cd(1);
		hGPosProjX->Draw();
		hGPosProjY = Get1DHist(histName[1]);
		cGPosProj->cd(2);
		hGPosProjY->Draw();
		return;
	}
	cGPosProj->cd(1);
	string toDraw = "gaussXPos >> " + histName[0];
	eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hGPosProjX->Draw();
	hGPosProjX->GetXaxis()->SetTitle("GX Position");
	hGPosProjX->GetYaxis()->SetTitle("Counts");
	cGPosProj->cd(2);
	toDraw = "gaussYPos >> " + histName[1];
	eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hGPosProjY->Draw();
	hGPosProjY->GetXaxis()->SetTitle("GY Position");
	hGPosProjY->GetYaxis()->SetTitle("Counts");
	return;
}

void COINCRun::PlotSGPosMap(TCut inCut, int nX, double xMin, double xMax, int nY, double yMin, double yMax)
{	
	TCanvas *cSGPosMap;
	TH2D *hSGPos;
	string cName, cDesc, histName;
	string canvParams = to_string(nX) + to_string(xMin) + to_string(xMax) + to_string(nY) + to_string(yMin) + to_string(yMax);
	cName = cPrefix + "cSGPosMap" + inCut.GetName();
	cDesc = "Sliding Gauss Position";
	histName = fileName + "_" + "SGPosMap" + inCut.GetName()+canvParams;

	if((cSGPosMap = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cSGPosMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hSGPos = Get2DHist(histName)) == 0)
		hSGPos = new TH2D(histName.c_str(), "Sliding Gauss Map", nX, xMin, xMax, nY, yMin, yMax);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cSGPosMap->cd();
		hSGPos->Draw("colz");
		return;
	}
	eventTree->Project(histName.c_str(), "gaussSYPos:gaussSXPos", inCut, "NRQ");
	hSGPos->Draw("colz");
	hSGPos->GetXaxis()->SetTitle("SGX Position");
	hSGPos->GetYaxis()->SetTitle("SGY Position");
	return;
}

void COINCRun::PlotAOverEMap(TCut inCut, int nX, double xMin, double xMax, int nY, double yMin, double yMax)
{
	TCanvas *cAOverEMap;
	TH2D *hAOverEMap;
	string cName, cDesc, histName;
	string canvParams = to_string(nX) + to_string(xMin) + to_string(xMax) + to_string(nY) + to_string(yMin) + to_string(yMax);
	cName = cPrefix + "cAOverEMap" + inCut.GetName()+canvParams;
	cDesc = "IMax Over E vs E";
	histName = fileName + "_" + "AOverEMap" + inCut.GetName()+canvParams;

	if((cAOverEMap = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cAOverEMap = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hAOverEMap = Get2DHist(histName)) == 0)
		hAOverEMap = new TH2D(histName.c_str(), "A Over E Map", nX, xMin, xMax, nY, yMin, yMax);
	
	string toDraw = "(IMax/(energyGE)):(energyGE) >> " + histName;
	eventTree->Draw(toDraw.c_str(), inCut, "NRQ");
	hAOverEMap->GetXaxis()->SetTitle("Energy (arb)");
	hAOverEMap->GetYaxis()->SetTitle("IMax/Energy (arb)");
	hAOverEMap->Draw("colz");
	return;
}

void COINCRun::PlotT1ToT2Dist(double T1, double T2, int nX, double xMin, double xMax)
{
	TCanvas *cTXToT90Dist;
	TH1D *hTXToT90Dist;
	string cName, cDesc, histName;
	string canvParams = to_string(nX) + to_string(xMin) + to_string(xMax);
	cName = cPrefix + "cT1ToT2Dist" + to_string((int)T1) + to_string((int)T2)+canvParams;
	cDesc = "T" + to_string((int)(T1*100.0)) + " to T" + to_string((int)(T2*100.0)) + " Distribution";
	histName = fileName + "_" + "TXToT90Dist" + to_string((int)T1) + to_string((int)T2)+canvParams;

	if((cTXToT90Dist = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cTXToT90Dist = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hTXToT90Dist = (TH1D*)Get1DHist(histName)) == 0)
		hTXToT90Dist = new TH1D(histName.c_str(), "T1 to T2 Dist", nX, xMin, xMax);
	else
	{
		cTXToT90Dist->cd();
		hTXToT90Dist->Draw();
		return;
	}

	for(int i=0;i < numEvents;i++)
	{
		double time;
		GetEvent(i);
		event->CalcT1ToT2TimeNS(T1, T2, time);
		hTXToT90Dist->Fill(time);

		if(i % reportFreq == 0)
		{
			cout << "Processing event " << i << "." << endl;
			cout << "Time: " << time << endl;
		}
	}

	hTXToT90Dist->Draw();
	hTXToT90Dist->GetXaxis()->SetTitle("T1 to T2 time (ns)");
	hTXToT90Dist->GetYaxis()->SetTitle("Counts");
	return;
}

void COINCRun::PlotT1ToT2SGMap(double T1, double T2)
{
	TCanvas *cTXToT90Map;
	TH2D *hTXToT90Map;
	string cName, cDesc, histName;
	cName = cPrefix + "cT1ToT2Map" + to_string((int)T1) + to_string((int)T2);
	cDesc = "T" + to_string((int)T1*100.0) + " to T" + to_string((int)T2*100.0) + " Map";
	histName = fileName + "_" + "TXToT90Map" + to_string((int)T1) + to_string((int)T2);
	const int NSPOS = event->GetNSlidePos();

	if((cTXToT90Map = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(cName.c_str())) == 0)
		cTXToT90Map = new TCanvas(cName.c_str(), cDesc.c_str(), 800, 600);
	if((hTXToT90Map = (TH2D*)Get2DHist(histName)) == 0)
		hTXToT90Map = new TH2D(histName.c_str(), "T1 to T2 Map", NSPOS-2, 0.0, 8.0, NSPOS-2, 0.0, 8.0);
	else
	{
		cout << "Histogram found in gDirectory." << endl;
		cTXToT90Map->cd();
		hTXToT90Map->Draw();
		return;
	}

	double xyVals[NSPOS][NSPOS];
	int nXYVals[NSPOS][NSPOS];
	for(int i=0;i < NSPOS;i++)
	{
		for(int k=0;k < NSPOS;k++)
		{
			xyVals[i][k] = 0.0;
			nXYVals[i][k] = 0;
		}
	}

	int nPlotted = 0;
	for(int i=0;i < numEvents;i++)
	{
		GetEvent(i);
		double xPos = event->GetGaussSXPos();
		double yPos = event->GetGaussSYPos();

		double time = 0;
		event->CalcT1ToT2TimeNS(T1, T2, time);

		xyVals[(int)(xPos*(double)NSPOS/8.0)][(int)(yPos*(double)NSPOS/8.0)] += time;
		nXYVals[(int)(xPos*(double)NSPOS/8.0)][(int)(yPos*(double)NSPOS/8.0)]++;
		nPlotted++;
		if(i % reportFreq == 0)
			cout << "Processing event " << i << "." << endl;
	}

	// Find the averages
	for(int i=0;i < NSPOS;i++)
	{
		for(int k=0;k < NSPOS;k++)
			{
				if(nXYVals[i][k] != 0)
					xyVals[i][k] /= (double)nXYVals[i][k];
			}
	}

	// Add to histogram
	for(int i=0;i < NSPOS;i++)
	{
		for(int k=0;k < NSPOS;k++)
			hTXToT90Map->Fill((double)i*8.0/NSPOS, (double)k*8.0/NSPOS, xyVals[i][k]);
	}

	hTXToT90Map->Draw("colz");
	hTXToT90Map->GetXaxis()->SetTitle("X Pixel");
	hTXToT90Map->GetYaxis()->SetTitle("Y Pixel");
	hTXToT90Map->GetZaxis()->SetTitle("T1 to T2 (ns)");
	cout << nPlotted << " events plotted." << endl;

	return;
}
