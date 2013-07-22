#include "ParseLYSO.hh"

ClassImp(ParseLYSO)

ParseLYSO::ParseLYSO()
{
	// Parameterless constructor, for ROOT. Not used.
}

// Member function definitions
ParseLYSO::ParseLYSO(string newInFileName, string newOutFileName)
{
  inFileName = newInFileName;
  outFileName = newOutFileName;

  event = new LYSOEvent();

  rootFile = nullptr;
  eventTree = nullptr;
  word = 0;
  lastVertTimestamp = 0;
  lastRealTimestamp = 0;
  numCurrEvent = 0;
  numTotalEvents = 0;
  nInputError = 0;
  nOutOfRange = 0;
  error = false;
	gainCorrect.clear();

  // Start by opening the files
  OpenLYSOFile();
  OpenROOTFile();
	LoadGainCorrection();
}

ParseLYSO::~ParseLYSO()
{
  // Close the files
  inFile.close();
  rootFile->Close();
  delete event;
}

void ParseLYSO::OpenLYSOFile()
{
  // Open the file as binary
  inFile.open(inFileName.c_str(), ios::binary);

  // Make sure we opened it
  if(!inFile.good())
  {
    cout << "Failed to open the LYSO data file." << endl;
    error = true;
    return;
  }
  else
    cout << "LYSO data file opened." << endl;

  // Determine how many events there are. Get the file size in bytes and divide
  // by the number of words we expect
  int begin = inFile.tellg();
  inFile.seekg(0, ios::end);
  int end = inFile.tellg();
  inFile.seekg(0);
  // File size, in # of words
  int fileSize = (end - begin)/2;
  // 2033 file header words, 1 event header word, pixel words, 2 timestamp words
  numTotalEvents = (fileSize - 2033)/(1 + NUM_LYSO_PIXELS + 2);
  cout << numTotalEvents << " total events expected." << endl;

  // Read the file header
  ReadFileHeader();
  return;
}

void ParseLYSO::OpenROOTFile()
{
  // Make a ROOT file object
  rootFile = new TFile(outFileName.c_str(), "RECREATE");

  // Confirm we actually opened something
  if(rootFile == NULL)
  {
    cout << "Failed to open ROOT output data file." << endl;
    error = true;
    return;
  }
  else
    cout << "ROOT output data file " << outFileName << " opened." << endl;

  return;
}

// The gain correction file should be NUM_LYSO_PIXELS lines of fractions
// representing the gain correction
void ParseLYSO::LoadGainCorrection()
{
	ifstream gainFile;
	string buf;

	gainFile.open("/PACSS/gaincorr.txt");

	if(!gainFile.good())
	{
		cout << "Failed to open gain correction file." << endl;
		error = true;
		return;
	}
	else
		cout << "Gain correction file opened: ";

	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		getline(gainFile, buf);
		double gc = (double)atoi(buf.c_str())/100.0;
		gainCorrect.push_back(gc);
		cout << gainCorrect[i] << " ";
	}
	cout << endl;

	gainFile.close();
	return;
}

void ParseLYSO::ReadWord()
{
  // Read one word (16 bits = 2 bytes) into word
  inFile.read((char*)&word, 2);

  // Endian swap it, since most computers use big endian
  EndianSwap(word);
  return; 
}

void ParseLYSO::ReadFileHeader()
{
  // The file header is 2032 words. Let's skip it
  for(int i=0;i < 2033;i++)
  {
    ReadWord();
  }

  cout << "Finished reading file header." << endl;
  return;
}

void ParseLYSO::ReadEvent()
{
  inputError = false;
  outOfRange = false;

  // Clear out the values in the current event object
  event->ClearEvent();

  // Each event is: one header word
  //                NUM_LYSO_PIXELS words containing charge values
  //                one timestamp word (if timestamps are on)
  // Check for Out of Range and Input Error (bits 12 and 11, respectively)
  ReadWord();
  if(((word >> 11) & 0x0001) == 1)
  {
    event->SetErrInput(true);
    nInputError++;
  }
  if(((word >> 12) & 0x0001) == 1)
  {
    event->SetErrOutOfRange(true);
    nOutOfRange++;
  }

  // Read in the charge values
  vector<double> chargeVect;
	vector<double> chargeGCVect;
  chargeVect.clear();
	chargeGCVect.clear();
  for(int i=0;i < NUM_LYSO_PIXELS;i++)
  {
    ReadWord();
    // Charge is stored as a signed integer increment value, which
    // must be multiplied by a system-specific charge increment value
    int16_t chargePart = (int16_t)word;
    double charge = (double)chargePart * CHARGE_INCREMENT;
		double chargeGC = (double)chargePart*CHARGE_INCREMENT/gainCorrect[i];
    chargeVect.push_back(charge);
		// Apply the gain correction
		chargeGCVect.push_back(chargeGC);

    // Add to the energy (sum charge)
    event->SetEnergyLYSO(event->GetEnergyLYSO() + charge);
		event->SetEnergyLYSOGC(event->GetEnergyLYSOGC() + chargeGC);
  }
  event->SetCharge(chargeVect);
	event->SetChargeGC(chargeGCVect);

  // Timestamp: unsigned 32 bit integer, units of nanoseconds? (need confirm)
  // 2 words, lower then upper
  uint32_t currTimestamp = 0;
  ReadWord();
  currTimestamp = word;
  ReadWord();
  currTimestamp = currTimestamp | (word << 16);

  // Was there a timestamp rollover?
  if(currTimestamp < lastVertTimestamp)
  {
    cout << "Timestamp rollover detected. Attempting to correct..." << endl;
    // Determine the time gap we need to correct for. Start with the max
    // size of a 32 bit unsigned integer, subtract the last timestamp
    // before the reset, then add this timestamp
    uint64_t resetOffset=(uint64_t)(((0xFFFFFFFF+1) - lastVertTimestamp)+currTimestamp);
    lastVertTimestamp = currTimestamp;
    // Don't forget to convert to nanoseconds!
		lastRealTimestamp += resetOffset;
    event->SetTimestampLYSO((double)lastRealTimestamp);
		//event->SetTimestampLYSO((double)(lastRealTimestamp*CLOCK_MULT_LYSO), true);
  }
  // No clock reset - just add the time since the last event
  else
  {
    // Don't forget to convert to nanoseconds!
    //uint64_t realTimestamp = (uint64_t)(currTimestamp - lastVertTimestamp) + lastRealTimestamp;
    lastRealTimestamp += (uint64_t)(currTimestamp - lastVertTimestamp);
		event->SetTimestampLYSO((double)lastRealTimestamp);
		//event->SetTimestampLYSO((double)(lastRealTimestamp*CLOCK_MULT_LYSO), true);
    lastVertTimestamp = currTimestamp;
  }

  return;
}

bool ParseLYSO::ReadAllEvents()
{
  // ROOT shrubbery
  eventTree = new TTree("LYSOEvents", "LYSOEvents");
  eventTree->Branch("event", &event);

  // Make sure there were no errors opening the files and reading the file
  // header
  if(error == true)
  {
    cout << "Something went wrong!. Conversion failed." << endl;
    return false;
  }

  int nFilled = 0;
  for(numCurrEvent = 0;numCurrEvent < numTotalEvents;numCurrEvent++)
  {
    // Read one event and add it to the event tree
    ReadEvent();
    if((inputError == false) && (outOfRange == false))
    {
      eventTree->Fill();
      nFilled++;
    }
    if(numCurrEvent % 10000 == 0)
		{
        cout << "Processing event " << numCurrEvent << ": ";
				cout << "E= " << event->GetEnergyLYSOGC() << ", ";
				cout << endl;
		}
  }

  cout << numCurrEvent << " events read." << endl;
  cout << nFilled << " events without error." << endl;

  rootFile->cd();
  rootFile->Write();
  cout << "Input errors detected: " << nInputError << endl;
  cout << "Out of ranges detected: " << nOutOfRange << endl;
  cout << "Conversion to ROOT complete." << endl;
  return true;
}

// Swap between little and big endian bit representations
void ParseLYSO::EndianSwap(uint16_t &bitsToSwap)
{
  bitsToSwap = (bitsToSwap >> 8) | (bitsToSwap << 8);
  return;
}
