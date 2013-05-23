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
		//void				SaveHistogram(string histName, string fileName);

		// Plotting functions
		void				PlotEnergyHist(TCut inCut="",string plotArgsGE="(100000,0.0,1.0e7)",string plotArgslYSO="(2048,-10.0,1023.0)");
		void				PlotWaveform(int nEvent); // need to add diff wf
		void				PlotWaveformStack(TCut inCut = "");
		void			  PlotAverageWaveform(TCut inCut="");
		void				PlotTimeBetweenCoincEvents(TCut inCut="", string plotArgs="(500, -5000.0, 5000.0)");
		void				PlotChargeMap(TCut inCut="", bool gc=true);
		void				PlotChargeProj(TCut inCut="", bool gc=true);
		void				PlotSGPosMap(TCut inCut="",string plotArgs="(98,0.0,49.0,98,0.0,49.0)");
		/*void				PlotSGPosProj(TCut inCut="",string aFileName, int nPos, string plotArgsX="(98,0.0,49.0)", string plotArgsY="(98,0.0,49.0)");
		void				PlotSLPosMap(TCut inCut="", string plotArgs="(98,0.0,49.0,98,0.0,49.0)");
		void				PlotSLPosProj(TCut inCut="", string plotArgsX="(98,0.0,49.0)", string plotArgsY="(98,0.0,49.0)");
		void				PlotT1ToT2Dist(double T1=0.10, double T2=0.90, string plotArgs="(500, -5000.0, 5000.0)");*/
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
