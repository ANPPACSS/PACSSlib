/* PACSSAnalysis.cc
Implementation file for PACSSAnalysis class. See PACSSAnalysis.hh for details.
*/

#include "PACSSAnalysis.hh"

ClassImp(PACSSAnalysis)

PACSSAnalysis::PACSSAnalysis()
{
	// Do nothing
}

PACSSAnalysis::~PACSSAnalysis()
{
	// Do nothing
}

// ANALYSIS FUNCTIONS
void PACSSAnalysis::CalcSlidingGaussXYPosition(COINCEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos)
{
	int x, y;
	vector<double> charge = event->GetChargeGC();
	TH1D hX("hX", "", 8, 0.0, 49.0);
	TH1D hY("hY", "", 8, 0.0, 49.0);

	// Project the charge
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		event->ChanNumToXYPos(i, x, y);
		hX.Fill(x, charge[i]);
		hY.Fill(y, charge[i]);
	}

	// Gauss parameters and value trackers
	TF1 fitGauss("fitGauss", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]");
	double slidePosition = 0.0;
	double minChi2X = 50000000.0;			// something big
	double posMinX = 0.0;
	double minChi2Y = 50000000.0;
	double posMinY = 0.0;
	double ampX = hX.GetBinContent(hX.GetMaximumBin());
	double TX = hX.GetBinContent(hX.GetMinimumBin());
	double ampY = hY.GetBinContent(hY.GetMaximumBin());
	double TY = hY.GetBinContent(hY.GetMinimumBin());
	xChi2.clear();
	yChi2.clear();
	// Slide
	for(int i=0;i < nSlidePos;i++)
	{
		double tempChi2;
		// Gauss calculation
		fitGauss.FixParameter(0, ampX);
		fitGauss.FixParameter(1, slidePosition);
  	fitGauss.FixParameter(2, 5.09); // sigma in mm
		fitGauss.SetParameter(3, TX);
		hX.Fit("fitGauss", "NBQ");
		tempChi2 = (double)fitGauss.GetChisquare();
		if(tempChi2 < minChi2X)
		{
			minChi2X = tempChi2;
			posMinX = slidePosition;
		}
		xChi2.push_back(tempChi2);
		fitGauss.FixParameter(0, ampY);
		fitGauss.FixParameter(2, 5.06);
		fitGauss.SetParameter(3, TY);
		hY.Fit("fitGauss", "NBQ");
		tempChi2 = (double)fitGauss.GetChisquare();
		if(tempChi2 < minChi2Y)
		{
			minChi2Y = tempChi2;
			posMinY = slidePosition;
		}
		yChi2.push_back(tempChi2);
		slidePosition += 49.0/(double)nSlidePos;
	}
	xPos = posMinX;
	yPos = posMinY;

	return;
}

void PACSSAnalysis::CalcSlidingLercheXYPosition(COINCEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos)
{
	int x, y;
	vector<double> charge = event->GetChargeGC();
	TH1D hX("hX", "", 8, 0.0, 49.0);
	TH1D hY("hY", "", 8, 0.0, 49.0);

	// Project the charge
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		event->ChanNumToXYPos(i, x, y);
		hX.Fill(x, charge[i]);
		hY.Fill(y, charge[i]);
	}

	// Fitting function and value trackers
	string temp = "(sqrt(((x-[2])**2)+2.25))";
	string ex = "(exp((-1.0)*[1]*"+temp+"))";
  string sLerche = "[0]*[1]*"+ex+"/"+temp+"*(atan((25.0-[3])/"+temp+")-atan((-25.0-[3])/"+temp+"))";
  sLerche += "+[4]";
	TF1 fitLerche("lerche", sLerche.c_str());
	double slidePosition = 0.0;
	double minChi2LX = 50000000.0;			// something big
	double posMinLX = 0.0;
	double minChi2LY = 50000000.0;
	double posMinLY = 0.0;
	double ampLX = hX.GetBinContent(hX.GetMaximumBin());
	double TLX = hX.GetBinContent(hX.GetMinimumBin());
	double ampLY = hY.GetBinContent(hY.GetMaximumBin());
	double TLY = hY.GetBinContent(hY.GetMinimumBin());
	xChi2.clear();
	yChi2.clear();
	for(int i=0;i < nSlidePos;i++)
	{
		double tempChi2;
		fitLerche.SetParameter(0, ampLX*3.0);
	 	fitLerche.FixParameter(1, 0.2071);//alpha
		fitLerche.FixParameter(2, slidePosition);
	 	fitLerche.FixParameter(3, 36.4);//yo
		fitLerche.SetParameter(4, TLX);
		hX.Fit("lerche", "NBQ");
		tempChi2 = (double)fitLerche.GetChisquare();
		if(tempChi2 < minChi2LX)
		{
			minChi2LX = tempChi2;
			posMinLX = slidePosition;
		}
		xChi2.push_back(tempChi2);
		fitLerche.SetParameter(0, ampLY*3.0);
		fitLerche.FixParameter(1, 0.2004);
		fitLerche.FixParameter(3, 35.8);
		fitLerche.SetParameter(4, TLY);
		hY.Fit("lerche", "NBQ");
		tempChi2 = (double)fitLerche.GetChisquare();
		if(tempChi2 < minChi2LY)
		{
			minChi2LY = tempChi2;
			posMinLY = slidePosition;
		}
		yChi2.push_back(tempChi2);
		slidePosition += 49.0/(double)nSlidePos;
	}
	xPos = posMinLX;
	yPos = posMinLY;

	return;
}
