#ifndef PARSELYSO_HH
#define PARSELYSO_HH

#include "LYSOEvent.hh"

#define CHARGE_INCREMENT 0.03418

class ParseLYSO
{
  protected:
    // Basic file stuff
    string     inFileName;
    string     outFileName;
    ifstream   inFile;

    // ROOT file stuff
    TFile     *rootFile;
    TTree     *eventTree;

    // Each word is 16 bits, little endian
    uint16_t   word;

    // Event information
    LYSOEvent *event;
    uint32_t   lastVertTimestamp;             // For the clock reset problem
    uint64_t   lastRealTimestamp;

    // Other stuff
    int        numCurrEvent;
    int        numTotalEvents;
    bool       inputError;
    int        nInputError;
    bool       outOfRange;
    int        nOutOfRange;
		int				 numSlidePositions;
		vector<double> gainCorrect;

    // File handling functions
    void       OpenLYSOFile();
    void       OpenROOTFile();
		void			 LoadGainCorrection();

    // Parsing functions
    void       ReadWord();
    void       ReadFileHeader();
    void       ReadEvent();
    void       EndianSwap(uint16_t &bitsToSwap);

  public:
    bool       error;

		ParseLYSO();
		ParseLYSO(string newInFileName, string newOutFileName, int nPositions);
    virtual ~ParseLYSO();

    // ParseLYSO has one purpose!
    bool       ReadAllEvents();
    
    ClassDef(ParseLYSO, 1);
};

#endif
