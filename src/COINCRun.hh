#ifndef COINCRUN_HH
#define COINCRUN_HH

#include "PACSSRun.hh"
#include "COINCEvent.hh"

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
		TH1D*			  Get1DHist(string histName);
		TH2D*				Get2DHist(string histName);

		// Plotting functions
		void				PlotEnergyHist(int nGe=16384,double xMinGe=0.0,double xMaxGe=16383.0,int nLYSO=2048, double xMinLYSO=-10.0, double xMaxLYSO=1023.0);
		void				PlotEnergySlice(int rowXlow=0, int rowXup=7, int rowYlow=0, int rowYup=7);
		void				PlotWaveforms(int nEvent);
		void				PlotWaveformStack(TCut inCut = "");
		//void			  PlotAverageWaveform(TCut inCut="");
		//void				PlotTimeBetweenEvents(int nStart, int nEnd);
		void				PlotTimeBetweenCoincEvents(int nX=500, double xMin=-5000.0, double xMax=5000.0);
		void			  PlotTimeBetweenCoincEvents(int nStart, int nEnd, int nX=500, double xMin=-5000.0, double xMax=5000.0);
		void				PlotChargeMap(double eg1=0.0, double eg2=16383.0, double el1=-10.0, double el2=2048.0, bool gc=true);
		void			  PlotChargeMap(int nEvent, bool gc=true);
		void				PlotChargeProj(double eg1=0.0, double eg2=16383.0, double el1=-10.0, double el2=2048.0, bool gc=true);
		void				PlotChargeProj(int nEvent, bool gc=true);
		void				PlotChargeProjSlice(double eg1=0.0, double eg2=16383.0, double el1=-10.0, double el2=2048.0, int rowXlow=0, int rowXup=7, int rowYlow=0, int rowYup=7);
		void				PlotGPosMap(TCut inCut = "", int nX=49,double xMin=0.0,double xMax=49.0,int nY=49, double yMin=0.0, double yMax=49.0);
		void				PlotGPosProj(TCut inCut = "", int nX=49,double xMin=0.0,double xMax=49.0,int nY=49,double yMin=0.0,double yMax=49.0);
		void				PlotSGPosMap(TCut inCut = "",int nX=49,double xMin=0.0,double xMax=49.0,int nY=49, double yMin=0.0, double yMax=49.0);
		//void				PlotLerchePositionMap();
		//void				PlotSlideLerchePositionMap();
		void				PlotT1ToT2Dist(double T1=0.10, double T2=0.90, int nX=500, double xMin=-5000.0, double xMax=5000.0);
		void				PlotT1ToT2SGMap(double T1=0.10, double T2=0.90);
		//void				PlotT10ToT90GMap(double eGELow=0.0, double eGEHigh=16383.0);
		//void				PlotTXToT90SGMap(double fracA, double eGELow=0.0, double eGEHigh=16383.0);
		//void				PlotSlideChi2();
		//void				PlotSlideChi2(int nEvent);
		//void				PlotSlideChi2Min();
		void				PlotAOverEMap(TCut inCut = "",int nX=49,double xMin=0.0,double xMax=49.0,int nY=49, double yMin=0.0, double yMax=49.0);
		//void			  PlotTXToT90VS1D(double fracA, char dim, double eGELow=0.0, eGEHigh=16383.0);
		//void				PlotAOverEDist(double eGELow=0.0, double eGEHigh=16383.0);
		//void 				PlotDiffWF(int nEvent);
		//void				PlotSGaussProj(double eGELow=0.0, double eGEHigh=16383.0);

		// Save the histograms to file for loading later. Can specify just one
		//void			SaveHistograms(string histName="");

		vector<double> SubtractBaseline(vector<double> aWF, int nSampAvg);

		ClassDef(COINCRun, 1);
};

#endif
