// Class LYSOEvent member function definitions
#include "LYSOEvent.hh"

ClassImp(LYSOEvent)

LYSOEvent::LYSOEvent()
{
	Clear();
}

LYSOEvent::~LYSOEvent()
{
	// Does nothing
}

vector<double> LYSOEvent::GetCharge()
{
	return charge;
}

vector<double> LYSOEvent::GetChargeGC()
{
	return chargeGC;
}

double LYSOEvent::GetEnergy()
{
	return energy;
}

double LYSOEvent::GetEnergyGC()
{
	return energyGC;
}


double LYSOEvent::GetTimestamp(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampNS;
	else
		return timestamp;
}

double LYSOEvent::GetGaussXPos()
{
	return gaussXPos;
}

double LYSOEvent::GetGaussYPos()
{
	return gaussYPos;
}

double LYSOEvent::GetGaussSXPos()
{
	return gaussSXPos;
}

double LYSOEvent::GetGaussSYPos()
{
	return gaussSYPos;
}

vector<double> LYSOEvent::GetChi2XPos()
{
	return chi2XPos;
}

vector<double> LYSOEvent::GetChi2YPos()
{
	return chi2YPos;
}

bool LYSOEvent::ErrInput()
{
	return errInput;
}

bool LYSOEvent::ErrOutOfRange()
{
	return errOutOfRange;
}

int LYSOEvent::GetNSlidePos()
{
	return nSlidePos;
}

double LYSOEvent::GetLercheXPos()
{
	return lercheXPos;
}

double LYSOEvent::GetLercheYPos()
{
	return lercheYPos;
}

vector<double> LYSOEvent::GetChi2LXPos()
{
	return chi2LXPos;
}

vector<double> LYSOEvent::GetChi2LYPos()
{
	return chi2LYPos;
}

void LYSOEvent::SetCharge(vector<double> newCharge)
{
	charge = newCharge;
	return;
}

void LYSOEvent::SetChargeGC(vector<double> newChargeGC)
{
	chargeGC = newChargeGC;
	return;
}

void LYSOEvent::SetEnergy(double newEnergy)
{
	energy = newEnergy;
	return;
}

void LYSOEvent::SetEnergyGC(double newEnergyGC)
{
	energyGC = newEnergyGC;
	return;
}


void LYSOEvent::SetTimestamp(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampNS = newTimestamp;
	else
		timestamp = newTimestamp;
	return;
}

void LYSOEvent::SetGaussXPos(double newGaussXPos)
{
	gaussXPos = newGaussXPos;
	return;
}

void LYSOEvent::SetGaussYPos(double newGaussYPos)
{
	gaussYPos = newGaussYPos;
	return;
}

void LYSOEvent::SetGaussSXPos(double newGaussSXPos)
{
	gaussSXPos = newGaussSXPos;
	return;
}

void LYSOEvent::SetGaussSYPos(double newGaussSYPos)
{
	gaussSYPos = newGaussSYPos;
	return;
}

void LYSOEvent::SetChi2XPos(vector<double> newChi2XPos)
{
	chi2XPos = newChi2XPos;
	return;
}

void LYSOEvent::SetChi2YPos(vector<double> newChi2YPos)
{
	chi2YPos = newChi2YPos;
	return;
}

void LYSOEvent::SetErrInput(bool newErrInput)
{
	errInput = newErrInput;
	return;
}

void LYSOEvent::SetErrOutOfRange(bool newErrOutOfRange)
{
	errOutOfRange = newErrOutOfRange;
	return;
}

void LYSOEvent::SetNSlidePos(int newNSlidePos)
{
	nSlidePos = newNSlidePos;
	return;
}

void LYSOEvent::SetLercheXPos(double newLercheXPos)
{
	lercheXPos = newLercheXPos;
	return;
}

void LYSOEvent::SetLercheYPos(double newLercheYPos)
{
	lercheYPos = newLercheYPos;
	return;
}

void LYSOEvent::SetChi2LXPos(vector<double> newChi2LXPos)
{
	chi2LXPos = newChi2LXPos;
	return;
}

void LYSOEvent::SetChi2LYPos(vector<double> newChi2LYPos)
{
	chi2LYPos = newChi2LYPos;
	return;
}

/*void *LYSOEvent::CalcGaussXYPos(void *hProj)
{
	TF1 fitGauss("fitGauss", "gaus");

	// Basic Gauss fit - let ROOT figure it out
	fitGauss.SetParameters(hProjX.GetMaximum(), hProjX.GetMaximumBin(), 5.0);
	hProjX.Fit("fitGauss", "NBQ");
	SetGaussXPos(fitGauss.GetParameter(1));
	fitGauss.SetParameters(hProjY.GetMaximum(), hProjY.GetMaximumBin(), 5.0);
	hProjY.Fit("fitGauss", "NBQ");
	SetGaussYPos(fitGauss.GetParameter(1));

	// Sliding gauss fit - slide nSlidePos times over the charge distribution
	TF1 sGauss("sGauss", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]");
	sGauss.FixParameter(2, 5.0); // sigma in mm
	double slidePosition = 0.0;
	double minChi2X = 500000.0;			// something big
	double posMinX = 0.0;
	double minChi2Y = 500000.0;
	double posMinY = 0.0;
	double ampX = hProjX.GetBinContent(hProjX.GetMaximumBin());
	double ampY = hProjY.GetBinContent(hProjY.GetMaximumBin());
	// Loop over each dimension, sliding the gauss fit
	for(int i=0;i < nSlidePos;i++)
	{
		double tempChi2;
		fitGauss.FixParameter(0, ampX);
		fitGauss.FixParameter(1, slidePosition);
		hProjX.Fit("fitGauss", "NBQ");
		tempChi2 = (double)fitGauss.GetChisquare();
		if(tempChi2 < minChi2X)
		{
			minChi2X = tempChi2;
			posMinX = slidePosition;
		}
		chi2XPos.push_back(tempChi2);
		fitGauss.FixParameter(0, ampY);
		hProjY.Fit("fitGauss", "NBQ");
		tempChi2 = (double)fitGauss.GetChisquare();
		if(tempChi2 < minChi2Y)
		{
			minChi2Y = tempChi2;
			posMinY = slidePosition;
		}
		chi2YPos.push_back(tempChi2);
		slidePosition += 49.0/(double)nSlidePos;
	}
	SetGaussSXPos(posMinX);
	SetGaussSYPos(posMinY);

	return;
}

void LYSOEvent::CalcLercheXYPos(TH1D hProjX, TH1D hProjY)
{
	// Lerche distribution
	string temp = "(sqrt(((x-[2])**2)+0.25))";
	string ex = "(exp((-1.0)*[1]*"+temp+"))";
  string sLerche = "[0]*[1]*"+ex+"/"+temp+"*(atan((4.0-[3])/"+temp+")-atan((-4.0-[3])/"+temp+"))";
  sLerche += "+[4]";
	// Histograms to slide on
	TF1 fitLerche("lerche", sLerche.c_str());

	// Fix the fit parameters. For starters, we'll use A = 44, sigma = 0.7
	// which is a typical 511 keV event
	//fitGauss.FixParameter(0, 44.0);
	fitLerche.FixParameter(1, 1.42);
	fitLerche.FixParameter(3, 5.98);
	double slidePosition = 0.0;
	double minChi2X = 500000.0;			// something big
	double posMinX = 0.0;
	double minChi2Y = 500000.0;
	double posMinY = 0.0;
	double ampX = hProjX.GetBinContent(hProjX.GetMaximumBin());
	double TX = hProjX.GetBinContent(hProjX.GetMinimumBin());
	double ampY = hProjY.GetBinContent(hProjY.GetMaximumBin());
	double TY = hProjY.GetBinContent(hProjY.GetMinimumBin());
	// Loop over each dimension, sliding the gauss fit
	for(int i=0;i < nSlidePos;i++)
	{
		double tempChi2;
		fitLerche.SetParameter(0, ampX*3.0);
		fitLerche.FixParameter(2, slidePosition);
		fitLerche.SetParameter(4, TX);
		hProjX.Fit("lerche", "NBQ");
		tempChi2 = (double)fitLerche.GetChisquare();
		if(tempChi2 < minChi2X)
		{
			minChi2X = tempChi2;
			posMinX = slidePosition;
		}
		chi2LXPos.push_back(tempChi2);
		fitLerche.SetParameter(0, ampY*3.0);
		fitLerche.SetParameter(4, TY);
		hProjY.Fit("lerche", "NBQ");
		tempChi2 = (double)fitLerche.GetChisquare();
		if(tempChi2 < minChi2Y)
		{
			minChi2Y = tempChi2;
			posMinY = slidePosition;
		}
		chi2LYPos.push_back(tempChi2);
		slidePosition += 49.0/(double)nSlidePos;
	}
	SetLercheXPos(posMinX);
	SetLercheYPos(posMinY);

	return;
}*/

void LYSOEvent::CalcXYPosition(TH1D *hProjX, TH1D *hProjY)
{
	// Gauss distribution
	TF1 fitGauss("fitGauss", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]");
	TF1 fitGaussLame("fitGaussLame", "gaus", 0.0, 49.0);
	// Lerche distribution
	string temp = "(sqrt(((x-[2])**2)+2.25))";
	string ex = "(exp((-1.0)*[1]*"+temp+"))";
  string sLerche = "[0]*[1]*"+ex+"/"+temp+"*(atan((25.0-[3])/"+temp+")-atan((-25.0-[3])/"+temp+"))";
  sLerche += "+[4]";
	// Histograms to slide on
	TF1 fitLerche("lerche", sLerche.c_str());

	// Basic Gauss fit - let ROOT figure it out
	fitGaussLame.SetParameters(hProjX->GetMaximum(), hProjX->GetMaximumBin(), 5.0);
	hProjX->Fit("fitGaussLame", "NRQ");
	SetGaussXPos(fitGaussLame.GetParameter(1));
	fitGaussLame.SetParameters(hProjY->GetMaximum(), hProjY->GetMaximumBin(), 5.0);
	hProjY->Fit("fitGaussLame", "NRQ");
	SetGaussYPos(fitGaussLame.GetParameter(1));

	// Sliding fits - gauss and lerche
	double slidePosition = 0.0;
	// Gauss parameters and value trackers
	double minChi2X = 50000000.0;			// something big
	double posMinX = 0.0;
	double minChi2Y = 50000000.0;
	double posMinY = 0.0;
	double ampX = hProjX->GetBinContent(hProjX->GetMaximumBin());
	double TX = hProjX->GetBinContent(hProjX->GetMinimumBin());
	double ampY = hProjY->GetBinContent(hProjY->GetMaximumBin());
	double TY = hProjY->GetBinContent(hProjY->GetMinimumBin());
	// Lerche parameters and value trackers
	double minChi2LX = 50000000.0;			// something big
	double posMinLX = 0.0;
	double minChi2LY = 50000000.0;
	double posMinLY = 0.0;
	double ampLX = hProjX->GetBinContent(hProjX->GetMaximumBin());
	double TLX = hProjX->GetBinContent(hProjX->GetMinimumBin());
	double ampLY = hProjY->GetBinContent(hProjY->GetMaximumBin());
	double TLY = hProjY->GetBinContent(hProjY->GetMinimumBin());
	// Loop over each dimension, sliding the gauss fit
	for(int i=0;i < nSlidePos;i++)
	{
		double tempChi2;
		// Gauss calculation
		fitGauss.FixParameter(0, ampX);
		fitGauss.FixParameter(1, slidePosition);
	  fitGauss.FixParameter(2, 5.09); // sigma in mm
		fitGauss.SetParameter(3, TX);
		hProjX->Fit("fitGauss", "NBQ");
		tempChi2 = (double)fitGauss.GetChisquare();
		if(tempChi2 < minChi2X)
		{
			minChi2X = tempChi2;
			posMinX = slidePosition;
		}
		chi2XPos.push_back(tempChi2);
		fitGauss.FixParameter(0, ampY);
		fitGauss.FixParameter(2, 5.06);
		fitGauss.SetParameter(3, TY);
		hProjY->Fit("fitGauss", "NBQ");
		tempChi2 = (double)fitGauss.GetChisquare();
		if(tempChi2 < minChi2Y)
		{
			minChi2Y = tempChi2;
			posMinY = slidePosition;
		}
		chi2YPos.push_back(tempChi2);

		// Lerche calculation
		fitLerche.SetParameter(0, ampLX*3.0);
	  fitLerche.FixParameter(1, 0.2071);//alpha
		fitLerche.FixParameter(2, slidePosition);
	  fitLerche.FixParameter(3, 36.4);//yo
		fitLerche.SetParameter(4, TLX);
		hProjX->Fit("lerche", "NBQ");
		tempChi2 = (double)fitLerche.GetChisquare();
		if(tempChi2 < minChi2LX)
		{
			minChi2LX = tempChi2;
			posMinLX = slidePosition;
		}
		chi2LXPos.push_back(tempChi2);
		fitLerche.SetParameter(0, ampLY*3.0);
		fitLerche.FixParameter(1, 0.2004);
		fitLerche.FixParameter(3, 35.8);
		fitLerche.SetParameter(4, TLY);
		hProjY->Fit("lerche", "NBQ");
		tempChi2 = (double)fitLerche.GetChisquare();
		if(tempChi2 < minChi2LY)
		{
			minChi2LY = tempChi2;
			posMinLY = slidePosition;
		}
		chi2LYPos.push_back(tempChi2);
		slidePosition += 49.0/(double)nSlidePos;
	}
	SetGaussSXPos(posMinX);
	SetGaussSYPos(posMinY);
	SetLercheXPos(posMinLX);
	SetLercheYPos(posMinLY);

	return;
}
	

/*void LYSOEvent::CalcXYPosition(TH1D hProjX, TH1D hProjY)
{
	thread t1(CalcGaussXYPos, hProjX, hProjY);
	thread t2(CalcLercheXYPos, hProjX, hProjY);

	t1.join();
	t2.join();
	return;
}*/

void LYSOEvent::Clear()
{
	charge.clear();
	chargeGC.clear();
	energy = 0.0;
	energyGC = 0.0;
	timestampNS = 0.0;
	timestamp = 0.0;
	gaussXPos = 0.0;
	gaussYPos = 0.0;
	gaussSXPos = 0.0;
	gaussSYPos = 0.0;
	chi2XPos.clear();
	chi2YPos.clear();
	errInput = false;
	errOutOfRange = false;
	nSlidePos = 0;
	lercheXPos = 0.0;
	lercheYPos = 0.0;
	chi2LXPos.clear();
	chi2LYPos.clear();
	return;
}
