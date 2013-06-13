#ifndef COINCRUN_HH
#define COINCRUN_HH

#include "PACSSRun.hh"
#include "COINCEvent.hh"
#include "PACSSAnalysis.hh"

class COINCRun: public PACSSRun
{
	protected:
		// Event type
		COINCEvent *event;
		// Analysis stuff
		TFile *posFile;
		TTree *posTree;
		TFile *wfDiffFile;
		TTree *wfDiffTree;
		TFile *t50File;
		TTree *t50Tree;
		TFile *eSimpleFile;
		TTree *eSimpleTree;
		TFile *floodFile;
		TTree *floodTree;
		TFile *posFCFile;
		TTree *posFCTree;

	public:
		COINCRun();
		COINCRun(string newFileName);
		virtual ~COINCRun();

		COINCEvent *GetEvent();
		COINCEvent *GetEvent(int nEvent);
		COINCEvent *GetNextEvent();

		// Traverse ROOT to find stuff
		TObject		 *GetHistogram(string histName);
		TCanvas		 *GetCanvas(string canvName);
		TTree			 *GetEventTree();
		// Save the histograms to file for loading later
		void				SaveHistogram(string histName, string hFileName);

		// Plotting functions
		TObjArray* PlotEnergyHist(TCut inCut="",string plotArgsGE="(65536,0.0,6.0e6)",string plotArgslYSO="(3048,-10.0,2023.0)");
		TH1D*			 PlotEnergySimple(TCut inCut="", string plotArgs="(65536*2,-65535.0,65536.0)");
		TH1D*		   PlotWaveform(int nEvent, int nBL); 
		TObjArray* PlotWaveformWithT50(int nEvent, int nBL);
		TH2D*	 		 PlotWaveformStack(TCut inCut = "", int nBL=600, double yMin=0.0, double yMax=65535.0,bool useT50=true);
		TH2D*	 		 PlotDiffWaveformStack(TCut inCut = "", double yMin=0.0, double yMax=65535.0);
		TH1D*		   PlotAverageWaveform(TCut inCut="", int nBL=600, bool useT50=true);
		TH1D*		   PlotAverageDiffWaveform(TCut inCut="");
		TH1D*			 PlotTimeBetweenCoincEvents(TCut inCut="", string plotArgs="(500, -5000.0, 5000.0)", bool useTCorr=true);
		TH2D*			 PlotChargeMap(TCut inCut="", bool gc=true);
		TObjArray* PlotChargeProj(TCut inCut="", bool gc=true);
		TH2D*			 PlotSGPosMap(TCut inCut="",string plotArgs="(98,0.0,49.0,98,0.0,49.0)");
		TObjArray* PlotSGChi2ByPos(TCut inCut="");
		TObjArray* PlotSGChi2(TCut inCut, double xMin=0.0, double xMax=1e5);
		TObjArray* PlotSGMinChi2(TCut inCut="",double xMin=0.0, double xMax=1e5);
		TObjArray* PlotSGPosProj(TCut inCut="", string plotArgsX="(98,0.0,49.0)", string plotArgsY="(98,0.0,49.0)");
		TH2D*			 PlotSLPosMap(TCut inCut="", string plotArgs="(98,0.0,49.0,98,0.0,49.0)");
		TObjArray* PlotSLChi2ByPos(TCut inCut="");
		TObjArray* PlotSLChi2(TCut inCut, double xMin=0.0, double xMax=1e5);
		TObjArray* PlotSLMinChi2(TCut inCut="",double xMin=0.0, double xMax=1e5);
		TObjArray* PlotSLPosProj(TCut inCut="", string plotArgsX="(98,0.0,49.0)", string plotArgsY="(98,0.0,49.0)");
		TH2D* 		 PlotIMaxOverEVsE(TCut inCut, string plotArgs="(65536,0.0,6.0e6,5000, 0.0, 10e-3)");
		TH1D*			 PlotIMaxOverEDist(TCut inCut, string plotArgs="(5000, 0.0, 10e-3)");

		ClassDef(COINCRun, 1);
};

#endif
