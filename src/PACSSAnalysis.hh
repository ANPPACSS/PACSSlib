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

		// Analysis functions - declare static so we can use without an instance
		//static void CalcSlidingGaussXYPosition(COINCEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);
		static void CalcSlidingGaussXYPosition(vector<double> charge, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);
		static void CalcSlidingLercheXYPosition(vector<double> charge, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);
		//static void CalcSlidingLercheXYPosition(COINCEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);
		//static void CalcSlidingLercheXYPosition(LYSOEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos);
		static vector<double> SubtractBaseline(vector<double> aWave, int nSamples);
		static double CalcFWHM(TH1D *hProjection);
		static vector<double> DifferentiateWaveform(vector<double> aWave, int nBLSamples);
		static double CalcIMax(vector<double> aCurrentWave);
		static double CalcDiffMin(vector<double> aCurrentWave);
		static int CalcTXSample(vector<double> wave, double fracTX, int nBL);
		//static int CalcT50Offset(vector<double> aWave, int nBL);
		//static int CalcT90Offset(vector<double> aWave, int nBL);
		static double CalcEnergySimple(vector<double> aWave, int nBL, int nAvg);
		static vector<double> PoleZeroCorrect(vector<double> aWave, double decayConst);
		static vector<double> TrapezoidalFilter(vector<double> aWave, int nPeak, int nGap, double PZCorr);
		static void ChanNumToXYPos(int channel, int &x, int &y);

		// Useful other functions

		ClassDef(PACSSAnalysis, 1);
};

#endif
