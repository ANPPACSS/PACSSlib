#ifndef GERUN_HH
#define GERUN_HH

#include "GEEvent.hh"
#include "PACSSRun.hh"

class GERun: public PACSSRun
{
	protected:
		// Event type for this run
		GEEvent *event;

		// Canvases
		TCanvas *cPlotEnergyHist;

	public:
		GERun();
		GERun(string newFileName);
		virtual ~GERun();

		GEEvent *GetEvent();
		GEEvent *GetEvent(int nEvent);
		GEEvent *GetNextEvent();

		// Plotting functions
		void		 PlotEnergyHist();

		ClassDef(GERun, 1);
};

#endif
