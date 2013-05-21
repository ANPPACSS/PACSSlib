/* PACSSAnalysis.hh
This class contains analysis functions for PACSS data. The function should take as its first argument, a pointer
to the COINCEvent object. If it calculates multiple values, these values should be passed by reference. The more
"correct" way to do this is pass COINCEvent by const reference, however then I would have to change BaseLYSOEvent
to have const ChanNumToXYPos() const, which I'm too lazy to do right now. How to use:
PACSSAnalysis::AnalysisFunction(pCOINCEvent, val1, val2, ...)
where pCOINCEvent is a pointer to a COINCEvent object
*/

#ifndef PACSSANALYSIS_H
#define PACSSANALYSIS_H

#include "COINCEvent.hh"

class PACSSAnalysis
{
	protected:
		
	public:
		PACSSAnalysis();
		virtual ~PACSSAnalysis();

		// Analysis functions
		void CalcSlidingGaussXYPosition(COINCEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);
		void CalcSlidingLercheXYPosition(COINCEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);

		// Useful other functions

		ClassDef(PACSSAnalysis, 1);
};

#endif
