#include "ParseGE.hh"

ClassImp(ParseGE)

// Member function definitions
ParseGE::ParseGE()
{
	// Parameterless constructor, for ROOT. Not used.
}

ParseGE::ParseGE(string newInFileName, string newOutFileName, int clockFreq, int channel)
{
  inFileName = newInFileName;
  outFileName = newOutFileName;

  event = new GEEvent();

  rootFile = nullptr;
  eventTree = nullptr;
  word = 0;
  numCurrEvent = 0;
  numTotalEvents = 0;
  header = 0;
  bufferLength = 0;
  eventLength = 0;
  error = false;
  doneReading = false;
	rawWrap = false;
	rawStartIndex = 0;
	this->clockFreq = clockFreq;
	this->channel = channel;

  OpenGEFile();
  OpenROOTFile();
}

ParseGE::~ParseGE()
{
  // Close the files and clean up
  dataFile.close();
  rootFile->Close();
  delete event;
}

// Open the STRUCK file and read the file header
void ParseGE::OpenGEFile()
{
  // Open file as binary
  dataFile.open(inFileName.c_str(), ios::binary);

  // Make sure it exists, etc
  if(!dataFile.good())
  {
    cout << "Failed to open the STRUCK data file." << endl;
    error = true;
    return;
  }
  else
    cout << "STRUCK data file opened." << endl;

  // Read the file header
  ReadFileHeader();

  // Determine the length of each event
  // 2(adcidtimestamp) + rawsignals + trapsignals + emax+efirst+flags+marker
  eventLength = 2 + (rawSampleLength/2) + energySampleLength + 4;
	cout << "STRUCK event length: " << eventLength << endl;

	// Check for data wrap - read to the first end marker and see how it adds up
	uint32_t nWords = 0;
	while(word != STRUCK_REG_EVENT)
	{
		ReadWord();
		nWords++;
	}
	cout << nWords << " words detected." << endl;
	// No wrap: (4header, first buffer event) + 2adcinfo + rawLength + energy length + 4trailer
	// Wrap: (4header) + 2adcinfo + 2rawinfo + rawLength + energyLength + 4trailer
	// eventLength does not include the event buffer header
	if(nWords == (eventLength + 6))
	{
		rawWrap = true;
		cout << "Raw trace wrap detected. Parsing accordingly..." << endl;
	}
	// Go back to where we were so we don't miss any events
	dataFile.seekg(0);
	ReadFileHeader(true);

  return;
}

// Open the ROOT file for writing
void ParseGE::OpenROOTFile()
{
  // Open the root file, recreate if necessary
  rootFile = new TFile(outFileName.c_str(), "RECREATE");

  // Confirm we actually opened something
  if(rootFile == nullptr)
  {
    cout << "Failed to open ROOT output data file." << endl;
    error = true;
    return;
  }
  else
    cout << "ROOT output data file " << outFileName << " opened." << endl;

  return;
}

// Read just one word (32 bits = 4 bytes)
void ParseGE::ReadWord()
{
  // Make sure the file is still ok
  if(!dataFile.good())
  {
    error = true;
    return;
  }

  // Read 32 bits into word
  dataFile.read((char*)&word, 4);
  return;
}

// Read the file header, which includes raw sample length, energy length, etc
void ParseGE::ReadFileHeader(bool suppressOutput)
{
  cout << "Reading file header." << endl;
  // File number
  ReadWord();
  fileNumber = (int)word;
	if(!suppressOutput)
  	cout << "File number: " << fileNumber << "." << endl;
  // File format
  ReadWord();
  // Number of 3302 modules
  ReadWord();
	if(!suppressOutput)
  	cout << "Number of 3302 modules: " << (int)word << "." << endl;
  // SIS3820/3302 clock mode
  ReadWord();
  // Raw sample start index and length
  ReadWord();
  rawSampleLength = (int)(word & 0x0000FFFF);
	if(!suppressOutput)
  	cout << "Raw sample length: " << rawSampleLength << " samples." << endl;
  // Decimation mode, FIR gap and length
  ReadWord();
  // Energy sample mode
  ReadWord();
  // Readout mode
  ReadWord();
  // Energy sample start indices
  ReadWord();
  // Energy sample length
  ReadWord();
  energySampleLength = (int)(word >> 16);
	if(!suppressOutput)
  	cout << "Energy sample length: " << energySampleLength << " samples." << endl;
  // Energy gate length
  ReadWord();
  // Trigger gate length
  ReadWord();
  // Pre trigger delay
  ReadWord();
	if(!suppressOutput)
  	cout << "Pre-trigger delay: " << (int)word << " samples." << endl;
  // Reserved? Who knows what these are, if anything
  ReadWord();
  ReadWord();
  ReadWord();

  return;
}

void ParseGE::ReadEventBufferHeader()
{
  // Event marker
  ReadWord();
  header = word;

  // 2 more words, values unknown
  ReadWord();
  ReadWord();

  // Number of words in the event buffer
  ReadWord();
  bufferLength = word/eventLength;

  return;
}

void ParseGE::ReadSingleEvent()
{
  // Clear the event
  event->ClearEvent();

	// Get the clock frequency
	event->SetClockFreq(clockFreq);

  // First word: ADCID lower 16, timestamp top word in the upper 16
  ReadWord();
	// Convert to something sensical - index starts at 1 to be consistent with the labels on the card
  uint32_t ADCID = (((word & 0x0000FFFF) % 8) + 1);
	event->SetChannel((int)ADCID);
	//cout << "ADCID: " << ADCID << endl;
  uint64_t timestamp = word >> 16;
  ReadWord();
  timestamp = (timestamp << 32) + word;
  event->SetTimestampGE((double)timestamp, false);
	event->SetTimestampGE((double)(timestamp*(1000/clockFreq)), true);
	
	// Account for the extra 2 words from the wrap
	if(rawWrap)
	{
		ReadWord();
		// Determine where the first raw sample is. This number is always even
		ReadWord();
		rawStartIndex = (int)word;
	}

  // Raw samples, read in as unsigned and convert to double
  vector<uint16_t> rawTrace;
	vector<uint16_t> rawWrapTrace;
  rawTrace.clear();
	rawWrapTrace.clear();
  if(rawSampleLength > 0)
  {
		// If there is a raw signal wrap, we must start there first. The wrap, which is the end of the trace
		// comes first in the data file
    for(int i=0;i < rawSampleLength;i += 2)
    {
      ReadWord();
			if(rawWrap && (i < rawStartIndex))
			{
				rawWrapTrace.push_back((uint16_t)(word & 0x0000FFFF));
				rawWrapTrace.push_back((uint16_t)((word & 0xFFFF0000) >> 16));
			}
			else
			{
      	// Break up into two 16 bit pieces
      	rawTrace.push_back((uint16_t)(word & 0x0000FFFF));
      	rawTrace.push_back((uint16_t)((word & 0xFFFF0000) >> 16));
			}
    }
  }
	// Append the wrap vector (might be empty)
	rawTrace.insert(rawTrace.end(), rawWrapTrace.begin(), rawWrapTrace.end());

	// Cast whole vector as double
	vector<double> dRawTrace(rawTrace.begin(), rawTrace.end());
  event->SetWFRaw(dRawTrace);

  // Energy samples
  vector<int> energyTrace;
  energyTrace.clear();
  if(energySampleLength > 0)
  {
    for(int i=0;i < energySampleLength;i++)
    {
      ReadWord();
      energyTrace.push_back((int)word);
    }
  }
	// Cast as double
	vector<double> dEnergyTrace(energyTrace.begin(), energyTrace.end());
  event->SetWFEnergy(dEnergyTrace);

  // Maximum energy value
  ReadWord();
  int energyMax = (int)word;
	event->SetEnergyGEMax(energyMax);
	// First energy value (first sample, kind of a fake basline)
  ReadWord();
	int energyFirst = (int)word;
	event->SetEnergyGEFirst((double)energyFirst);
  event->SetEnergyGE((double)(energyMax - energyFirst));

  // Pileup flags
  ReadWord();

  // Trailer word
  ReadWord();
  header = word;

  return;
}

void ParseGE::ReadEventBuffer()
{
  // Reset the counter and read the event buffer header
  numCurrEvent = 0;
  ReadEventBufferHeader();
  if(header == STRUCK_LAST_EVENT)
  {
    doneReading = true;
    return;
  }
	/*if(header != STRUCK_REG_EVENT)
	{
		cout << "Event header mismatch - uh oh!" << endl;
		return;
	}*/

  // Loop over this buffer. bufferLength is unsigned, so compare to unsigned!
	// The buffer maxes out ~2048 events (with the shortest trace sampling)
  for(uint16_t i=0;i < bufferLength;i++)
  {
    // Read one event and add it to the ROOT tree
    ReadSingleEvent();
		if(event->GetChannel() == channel)
		{
    	eventTree->Fill();
    	numCurrEvent++;
    	numTotalEvents++;
		}

    if(i % 10000 == 0)
    {
      cout << "Processing event " << numCurrEvent << "." << endl;
    }

  }

  return;
}

bool ParseGE::ReadAllEvents()
{
  // Make sure there were no errors up until this point
  if(error == true)
  {
    cout << "Something went wrong! Conversion failed." << endl;
    return false;
  }

  // Create ROOT shrubbery
  eventTree = new TTree("GEEvents", "GEEvents");
  eventTree->Branch("event", &event);

  // Loop over the file until we fine the EOF
  while(doneReading == false)
    ReadEventBuffer();

  cout << "Finished conversion. " << numTotalEvents << " events converted.";
  cout << endl;

  rootFile->cd();
  rootFile->Write();
  return true;
}
