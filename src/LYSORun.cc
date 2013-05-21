#include "LYSORun.hh"

ClassImp(LYSORun)

LYSORun::LYSORun()
{
	event = new LYSOEvent();

	cPlotEnergyHist = nullptr;
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

	// How many events? iEvent = 0 from PACSSRun initialization
	numEvents = eventTree->GetEntries();
	cout << numEvents << " events in data file." << endl;
	eventTree->GetEntry(iEvent);

	// Canvas pointers - start as NULL
	cPlotEnergyHist = nullptr;
}

LYSORun::~LYSORun()
{
	rootFile->cd();
	rootFile->Close();
	delete event;

	if(cPlotEnergyHist != nullptr)
		delete cPlotEnergyHist;
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

void LYSORun::PlotEnergyHist()
{
	if(cPlotEnergyHist != nullptr)
		delete cPlotEnergyHist;
	
	string cName = cPrefix + "cPlotEnergyHist";
	cPlotEnergyHist = new TCanvas(cName.c_str(), "LYSO Energy", 800, 600);

	TH1D *hEnergy = new TH1D("hEnergy", "LYSO Energy", 2068, -10.0, 1023.0);

	eventTree->Draw("energyLYSOGC >> hEnergy", "", "NBQ");

	hEnergy->Draw();
	hEnergy->GetXaxis()->SetTitle("Energy (pC)");
	hEnergy->GetYaxis()->SetTitle("Counts");
	hEnergy->SetFillColor(kBlue);
	return;
}
