#ifndef PACSSRUN_HH
#define PACSSRUN_HH

#include "PACSSEvent.hh"

class PACSSRun: public TObject
{
	protected:
		string fileName;
		string cPrefix;
		string hPrefix;
		TFile *rootFile;
		TTree *eventTree;
		int 	 reportFreq;
		int 	 iEvent;
		int 	 numEvents;
		
	public:
		PACSSRun();
		PACSSRun(string newFileName);
		virtual ~PACSSRun();

		int 	 GetReportFreq();
		int 	 GetNumEvents();

		void 	 SetReportFreq(int newReportFreq);

		ClassDef(PACSSRun, 1);
};

#endif
