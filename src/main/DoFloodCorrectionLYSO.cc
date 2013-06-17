#include "../LYSOEvent.hh"
#include "../PACSSAnalysis.hh"

void DoFloodCorrection(string inFileName, string outFileName, string corrFileName);

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;
	string corrFileName;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
      corrFileName = (string)argv[3];
      cout << "Calculating flood-corrected charge vectors using " << corrFileName << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [LYSO ROOT file] [analysis output ROOT file] [flood corr file (.txt)]";
			cout << endl;
      return 1;
  }

  DoFloodCorrection(inFileName, outFileName, corrFileName);

  return 0;
}

void DoFloodCorrection(string inFileName, string outFileName, string corrFileName)
{
	// ROOT stuff
  TFile *rootFile = new TFile(inFileName.c_str(), "READ");
	TTree *eventTree = (TTree*)rootFile->Get("LYSOEvents");
	LYSOEvent *event = new LYSOEvent();
	eventTree->SetBranchAddress("event", &event);

	// Handle the output
	TFile *fOut = new TFile(outFileName.c_str(), "RECREATE");
	// Create the TTree for Analysis only if there isn't one already
	TTree *tAnalysis = new TTree("FloodCorrect", "FloodCorrect");
	
	// Open the correction factor file
	ifstream corrFile;
	string buf;

	corrFile.open(corrFileName.c_str());

	if(!corrFile.good())
	{
		cout << "Failed to open flood correction file." << endl;
		return;
	}
	else
		cout << "Flood correction file opened: ";

	vector<double> floodCorrect;
	floodCorrect.clear();
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		getline(corrFile, buf);
		double gc = (double)atof(buf.c_str());
		floodCorrect.push_back(gc);
		cout << floodCorrect[i] << " ";
	}
	cout << endl;
	corrFile.close();

	vector<double> chargeFC(NUM_LYSO_PIXELS);
	string bName = "chargeFC";
	tAnalysis->Branch(bName.c_str(), &chargeFC);
 	cout << "ROOT file loaded, tree created." << endl;
	
	// Loop over all the events
  for(int i=0;i < eventTree->GetEntries();i++)
  {
		// Grab this event
		eventTree->GetEntry(i);

		// Do analysis
		for(int k=0;k < NUM_LYSO_PIXELS;k++)
			chargeFC.at(k) = event->GetCharge().at(k)/floodCorrect[k];

    if(i % 10000 == 0)
		{
      cout << "Calculating flood correction for " << i << ":  " << chargeFC.at(32) << " fc vs ";
			cout << event->GetCharge().at(32) << " no correction." << endl;
		}
		tAnalysis->Fill();
  }
  
	tAnalysis->Write();
	fOut->Close();
  rootFile->Close();
  cout << "Calculated values written to FloodCorrect tree in " << inFileName << endl;
  delete event;
	return;
}
