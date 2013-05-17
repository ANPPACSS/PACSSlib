#include "GERun.hh"

ClassImp(GERun)

GERun::GERun()
{
	event = new GEEvent();

	cPlotEnergyHist = nullptr;
}

// Make sure to instantiate the base class with an argument!
GERun::GERun(string newFileName): PACSSRun(newFileName)
{
	// Open the ROOT file
	rootFile = new TFile(fileName.c_str(), "READ");
	cout << "GE data file " << fileName << " loaded." << endl;
	// Get the event tree
	eventTree = (TTree*)rootFile->Get("GEEvents");
	// Attach an event object
	event = new GEEvent();
	eventTree->SetBranchAddress("event", &event);

	// How many events? iEvent = 0 from PACSSRun initialization
	numEvents = eventTree->GetEntries();
	cout << numEvents << " events in data file." << endl;
	eventTree->GetEntry(iEvent);

	// Canvas pointers - start as nullptr
	cPlotEnergyHist = nullptr;
}

GERun::~GERun()
{
	rootFile->cd();
	rootFile->Close();
	delete event;

	if(cPlotEnergyHist != nullptr)
		delete cPlotEnergyHist;
}

GEEvent* GERun::GetEvent()
{
	return event;
}

GEEvent* GERun::GetEvent(int nEvent)
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

GEEvent* GERun::GetNextEvent()
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

void GERun::PlotEnergyHist()
{
	if(cPlotEnergyHist != nullptr)
		delete cPlotEnergyHist;
	
	string cName = cPrefix + "cPlotEnergyHist";
	cPlotEnergyHist = new TCanvas(cName.c_str(), "LYSO Energy", 800, 600);

  TH1D *hEnergy = new TH1D("hEnergy", "GE Energy", 16384, 0, 16383);

	// Plot it, quietly!
	eventTree->Draw("energy >> hEnergy", "", "NRQ");

  /*for(int i=0;i < numEvents;i++)
  {
    double energy = GetEvent(i)->GetEnergy();
    hEnergy->Fill(energy);

    if(i % reportFreq == 0)
    {
      cout << "Processing event " << i << " with energy " << energy;
      cout << "." << endl;
    }
  }*/

  hEnergy->Draw();
  hEnergy->GetXaxis()->SetTitle("Energy (arb)");
  hEnergy->GetYaxis()->SetTitle("Counts");
  hEnergy->SetFillColor(kRed);
  return;
}

