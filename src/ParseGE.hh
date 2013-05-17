#ifndef PARSEGE_HH
#define PARSEGE_HH

#include "GEEvent.hh"

// Marker definitions
#define STRUCK_FIRST_EVENT   0xABBAABBA
#define STRUCK_REG_EVENT     0xDEADBEEF
#define STRUCK_LAST_EVENT    0xE0F0E0F

class ParseGE
{
  protected:
    // Basic file stuff
    string   inFileName;
    string   outFileName;
    ifstream dataFile;

    // ROOT file stuff
    TFile   *rootFile;
    TTree   *eventTree;

    // File header stuff
    int      fileNumber;
    //int fileDataFormat;
    //int num3302Modules;
    //int SIS3820ClockMode;
    //int SIS3302ClockMode;
    //int rawSampleStartIndex;
    int      rawSampleLength;
    //int decimationMode;
    //int energySampleMode;
    int      energySampleLength;
    //int energyGateLength;
    //int preTriggerDelay;
		bool		 rawWrap;
		int 		 rawStartIndex;
    
    // Event data stuff
    int      numCurrEvent;
    int      numTotalEvents;
    GEEvent *event;
    uint32_t word;

    // Useful things
    uint32_t header;
    uint32_t bufferLength;
    uint32_t eventLength;
    bool     doneReading;
		uint32_t clockMultiplier;

    void     OpenGEFile();
    void     OpenROOTFile();
    void     ReadWord();
    void     ReadFileHeader(bool suppressOutput=false);
    void     ReadEventBufferHeader();
    void     ReadSingleEvent();
    void     ReadEventBuffer();

  public:
    bool     error;

		ParseGE();
		// Default clock is 100 MHz, so multiply by 10. 20 for 50 MHz
    ParseGE(string newInFileName, string newOutFileName, int clockMult=10);
    virtual ~ParseGE();

    bool ReadAllEvents();

    ClassDef(ParseGE, 1);
};

#endif
