#ifndef PACSSEVENT_HH
#define PACSSEVENT_HH

// C/C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdint.h>

// ROOT includes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TObject.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TGraph.h>
#include <TCut.h>

// Useful definitions for handling PACSS data
#define NUM_LYSO_PIXELS  64
#define CLOCK_MULT_LYSO 100		// Units are 100 ns
#define CLOCK_MULT_GE    10		// Units are samples (@ 100MHz)
#define GE_RAW_WF_LEN  1500   // Number of samples in raw GE trace

using namespace std;

#endif
