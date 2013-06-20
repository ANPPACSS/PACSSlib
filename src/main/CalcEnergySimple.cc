#include "../COINCEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcEnergySimple(string inFileName, string outFileName, int nBL, int nAvg);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
  int nBL, nAvg;

  // Handle the command line arguments
  switch(argc)
  {
    case 5:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
      nBL = atoi(argv[3]);
			nAvg = atoi(argv[4]);
      cout << "Calculating energy using average over the last " << nAvg << " samples with " << nBL;
			cout << " samples averaged for the baseline." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [COINC ROOT file] [analysis output ROOT file] [n bl samples] [n avg samples]";
			cout << endl;
      return 1;
  }

  CalcEnergySimple(inFileName, outFileName, nBL, nAvg);

  return 0;
}

void CalcEnergySimple(string inFileName, string outFileName, int nBL, int nAvg)
{
	double EnergySimple;
	// ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("EnergySimple", "EnergySimple");

	string bName = "energyGES";
	tAnalysis->Branch(bName.c_str(), &EnergySimple);
 	cout << "ROOT file loaded, tree created." << endl;
	
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		// Do analysis
		EnergySimple = PACSSAnalysis::CalcEnergySimple(event->GetWFRaw(), nBL, nAvg);

    if(i % 10000 == 0)
      cout << "Calculating energy for event " << i << "(= " << EnergySimple << ")." << endl;
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated values written to EnergySimple tree in " << inFileName << endl;
  delete event;
	return;
}
