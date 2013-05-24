#ifndef LYSORUN_HH
#define LYSORUN_HH

#include "PACSSRun.hh"
#include "LYSOEvent.hh"
#include "PACSSAnalysis.hh"

class LYSORun: public PACSSRun
{
	protected:
		// Event type
		LYSOEvent *event;

	public:
		LYSORun();
		LYSORun(string newFileName);
		virtual ~LYSORun();

		LYSOEvent *GetEvent();
		LYSOEvent *GetEvent(int nEvent);
		LYSOEvent *GetNextEvent();

		// Traverse ROOT to find stuff
		TObject		 *GetHistogram(string histName);
		TCanvas		 *GetCanvas(string canvName);
		// Save the histograms to file for loading later
		void				SaveHistogram(string histName, string hFileName);

		// Plotting functions
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


		ClassDef(LYSORun, 1);
};

#endif
