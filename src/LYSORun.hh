#ifndef LYSORUN_HH
#define LYSORUN_HH

#include "LYSOEvent.hh"
#include "PACSSRun.hh"

class LYSORun: public PACSSRun
{
	protected:
		// Event type for this run
		LYSOEvent *event;

		// Canvases
		TCanvas *cPlotEnergyHist;

	public:
		LYSORun();
		LYSORun(string newFileName);
		virtual ~LYSORun();

		LYSOEvent *GetEvent();
		LYSOEvent *GetEvent(int nEvent);
		LYSOEvent *GetNextEvent();

		// Plotting functions
		void			 PlotEnergyHist();

		ClassDef(LYSORun, 1);
};

#endif
