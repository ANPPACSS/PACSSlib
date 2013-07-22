#include "../COINCEvent.hh"
#include "../PACSSAnalysis.hh"

void CalcDiffWaveIMax(string inFileName, string outFileName, int nBLSamples);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
  int nBLSamples;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
      nBLSamples = atoi(argv[3]);
      cout << "Calculating DiffWave and IMax with baseline averaged over " << nBLSamples << " samples." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [COINC ROOT file] [analysis output ROOT file] [n bl samples]" << endl;
      return 1;
  }

  CalcDiffWaveIMax(inFileName, outFileName, nBLSamples);

  return 0;
}

void CalcDiffWaveIMax(string inFileName, string outFileName, int nBLSamples)
{
  vector<double> wfDiff;
	double IMax, diffMin;
	// ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("COINCEvents");
	COINCEvent *event = new COINCEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("DiffWaveIMax", "DiffWaveIMax");

	string bName = "IMax";
	tAnalysis->Branch(bName.c_str(), &IMax);	
	bName = "diffMin";
	tAnalysis->Branch(bName.c_str(), &diffMin);	
 	cout << "ROOT file loaded, tree created." << endl;
	
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		// Do analysis
		wfDiff = PACSSAnalysis::DifferentiateWaveform(event->GetWFRaw(), nBLSamples);
		IMax = PACSSAnalysis::CalcIMax(wfDiff);
		diffMin = PACSSAnalysis::CalcDiffMin(wfDiff);

    if(i % 10000 == 0)
      cout << "Calculating diffwave and imax for event " << i << "." << endl;
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated values written to DiffWaveIMax tree in " << inFileName << endl;
  delete event;
	return;
}
