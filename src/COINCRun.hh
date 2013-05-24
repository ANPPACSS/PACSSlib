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
		// Save the histograms to file for loading later
		void				SaveHistogram(string histName, string hFileName);

		// Plotting functions
		TObjArray* PlotEnergyHist(TCut inCut="",string plotArgsGE="(100000,0.0,1.0e7)",string plotArgslYSO="(3048,-10.0,2023.0)");
		TH1D*		   PlotWaveform(int nEvent, int nBL); // need to add diff wf
		TH2D*	 		 PlotWaveformStack(TCut inCut = "", int nBL=600, double yMin=0.0, double yMax=65535.0);
		TH1D*		   PlotAverageWaveform(TCut inCut="", int nBL=600);
		TH1D*			 PlotTimeBetweenCoincEvents(TCut inCut="", string plotArgs="(500, -5000.0, 5000.0)");
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
		//void				PlotSLPosProj(TCut inCut="", string plotArgsX="(98,0.0,49.0)", string plotArgsY="(98,0.0,49.0)");

		//void				PlotT1ToT2Dist(double T1=0.10, double T2=0.90, string plotArgs="(500, -5000.0, 5000.0)");
		//void				PlotT10ToT90GMap(double eGELow=0.0, double eGEHigh=16383.0);
		//void				PlotTXToT90SGMap(double fracA, double eGELow=0.0, double eGEHigh=16383.0);
		//void				PlotSlideChi2();
		//void				PlotSlideChi2(int nEvent);
		//void				PlotSlideChi2Min();
		//void				PlotAOverEMap(TCut inCut = "",int nX=49,double xMin=0.0,double xMax=49.0,int nY=49, double yMin=0.0, double yMax=49.0);
		//void			  PlotTXToT90VS1D(double fracA, char dim, double eGELow=0.0, eGEHigh=16383.0);
		//void				PlotAOverEDist(double eGELow=0.0, double eGEHigh=16383.0);
		//void 				PlotDiffWF(int nEvent);
		//void				PlotSGaussProj(double eGELow=0.0, double eGEHigh=16383.0);


		ClassDef(COINCRun, 1);
};

#endif
