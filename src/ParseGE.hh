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
    ParseGE(string newInFileName, string newOutFileName);
    virtual ~ParseGE();

    bool ReadAllEvents();

    ClassDef(ParseGE, 1);
};

#endif
