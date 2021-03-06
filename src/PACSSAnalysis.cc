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
void PACSSAnalysis::CalcSlidingGaussXYPosition(vector<double> charge, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos)
{
	int x, y;
	//vector<double> charge = event->GetChargeGC();
	TH1D hX("hX", "", 8, 0.0, 49.0);
	TH1D hY("hY", "", 8, 0.0, 49.0);

	// Project the charge
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		PACSSAnalysis::ChanNumToXYPos(i, x, y);
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

/*
void PACSSAnalysis::CalcSlidingGaussXYPosition(LYSOEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos)
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
}*/

void PACSSAnalysis::CalcSlidingLercheXYPosition(vector<double> charge, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos)
{
	int x, y;
	TH1D hX("hX", "", 8, 0.0, 49.0);
	TH1D hY("hY", "", 8, 0.0, 49.0);

	// Project the charge
	for(int i=0;i < NUM_LYSO_PIXELS;i++)
	{
		PACSSAnalysis::ChanNumToXYPos(i, x, y);
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

/*void PACSSAnalysis::CalcSlidingLercheXYPosition(LYSOEvent *event, double &xPos, vector<double> &xChi2, double &yPos, vector<double> &yChi2, int nSlidePos)
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
}*/

// Subtract the baseline. Use the first ~20% of samples as the average
vector<double> PACSSAnalysis::SubtractBaseline(vector<double> aWave, int nSamples)
{
	// If 0, don't subtract the baseline
	if(nSamples == 0)
		return aWave;
	vector<double> retWave;
	double bl = 0.0;
	size_t nSampBL = (size_t)nSamples;
	for(size_t i=0;i < nSampBL;i++)
		bl += aWave[i];
	bl /= nSampBL;
	for(size_t i=0;i < aWave.size();i++)
		retWave.push_back(aWave[i]-bl);
	return retWave;
}

// Calculate the FWHM using a standard method. Make sure there are no reflections first!
double PACSSAnalysis::CalcFWHM(TH1D *hProjection)
{
	int bin1 = hProjection->FindFirstBinAbove(hProjection->GetMaximum()/2.0);
	int bin2 = hProjection->FindLastBinAbove(hProjection->GetMaximum()/2.0);
	return hProjection->GetBinCenter(bin2) - hProjection->GetBinCenter(bin1);
}

vector<double> PACSSAnalysis::DifferentiateWaveform(vector<double> aWave, int nBLSamples)
{
	vector<double> wfDiff = aWave;
	wfDiff = SubtractBaseline(wfDiff, nBLSamples);

	double temp1 = 0.0;
	double temp2 = wfDiff[0];
	wfDiff[0] = 0.0;
  // Loop over the waveform
  for(size_t k=1;k < wfDiff.size();k++)
  {
    temp1 = wfDiff[k-1] + wfDiff[k] - temp2 - wfDiff[k-1]/10;
    temp2 = wfDiff[k];
    wfDiff[k] = temp1;
  }

	return wfDiff;
}

double PACSSAnalysis::CalcIMax(vector<double> aCurrentWave)
{
	double IMax = 0.0;
	for(size_t i=0;i < aCurrentWave.size();i++)
	{
		if(fabs(aCurrentWave[i]) > fabs(IMax))
			IMax = aCurrentWave[i];
	}
	return IMax;
}

double PACSSAnalysis::CalcDiffMin(vector<double> aCurrentWave)
{
	double diffMin = 1.0e10;
	for(size_t i=0;i < aCurrentWave.size();i++)
	{
		if(aCurrentWave[i] < diffMin)
			diffMin = aCurrentWave[i];
	}
	return diffMin;
}

/*int PACSSAnalysis::CalcT50Offset(vector<double> aWave, int nBL)
{
	TH1D hWF("hWF", "", (int)aWave.size(), 0, (int)aWave.size()-1);
	// Subtract baseline
	aWave = SubtractBaseline(aWave, nBL);
	for(size_t i=0;i < aWave.size();i++)
		hWF.Fill((int)i, aWave.at(i));

	int maxBin = hWF.GetMaximumBin();
	int iBin = maxBin; // Start at the maximum and work backwards
	double maxVal = hWF.GetBinContent(maxBin);
	while(hWF.GetBinContent(iBin) > (maxVal*0.5))
		iBin--;

	return iBin;
}

int PACSSAnalysis::CalcT90Offset(vector<double> aWave, int nBL)
{
	TH1D hWF("hWF", "", (int)aWave.size(), 0, (int)aWave.size()-1);
	// Subtract baseline
	aWave = SubtractBaseline(aWave, nBL);
	for(size_t i=0;i < aWave.size();i++)
		hWF.Fill((int)i, aWave.at(i));

	int maxBin = hWF.GetMaximumBin();
	int iBin = maxBin; // Start at the maximum and work backwards
	double maxVal = hWF.GetBinContent(maxBin);
	while(hWF.GetBinContent(iBin) > (maxVal*0.9))
		iBin--;

	return iBin;
}*/

int PACSSAnalysis::CalcTXSample(vector<double> wave, double fracTX, int nBL)
{
	TH1D hWF("hWF", "", (int)wave.size(), 0, (int)wave.size()-1);
	// Subtract baseline
	wave = SubtractBaseline(wave, nBL);
	for(size_t i=0;i < wave.size();i++)
		hWF.Fill((int)i, wave.at(i));

	int maxBin = hWF.GetMaximumBin();
	int iBin = maxBin; // Start at the maximum and work backwards
	double maxVal = hWF.GetBinContent(maxBin);
	while(hWF.GetBinContent(iBin) > (maxVal*fracTX))
		iBin--;

	return iBin;
}

double PACSSAnalysis::CalcEnergySimple(vector<double> aWave, int nBL, int nAvg)
{
	// Subtract the baseline
	vector<double> wf = SubtractBaseline(aWave, nBL);

	// Average the last nAvg samples
	int wfLen = (int)wf.size();
	double highAvg = 0.0;
	for(int i=0;i < nAvg;i++)
		highAvg += wf.at(wfLen-nAvg+i);
	highAvg /= nAvg;

	// Assume baseline is 0
	return highAvg;
}

vector<double> PACSSAnalysis::PoleZeroCorrect(vector<double> aWave, double decayConst)
{
	if(aWave.size() <= 1)
  {
	  cout << "Waveform is 1 sample or less! Returning original waveform..." << endl;
		return aWave;
  }

	double multiplier = exp(-1.0/decayConst);
	vector<double> ret(aWave.begin(), aWave.end());
	for(int i=1;i < (int)ret.size();i++)
	{
		ret.at(i) = ret.at(i-1) - multiplier*aWave.at(i-1) + aWave.at(i);
	}
	return ret;
}

vector<double> PACSSAnalysis::TrapezoidalFilter(vector<double> aWave, int nPeak, int nGap, double PZCorr)
{
	if(aWave.size() <= 1)
	{
		cout << "Waveform is 1 sample or less! Returning original waveform..." << endl;
		return aWave;
	}

	vector<double> temp(aWave.size());
	vector<double> trapWave(aWave);
	temp.at(0) = aWave.at(0);
	trapWave.at(0) = (PZCorr+1)*aWave.at(0);
	double scratch = 0.0;
	for(int i=1;i < (int)aWave.size();i++)
	{
		scratch = aWave.at(i) - ((i >= nPeak) ? aWave.at(i-nPeak) : 0.0)
		 - ((i >= nGap + nPeak) ? aWave.at(i - nGap - nPeak) : 0.0)
		 + ((i >= nGap + 2*nPeak) ? aWave.at(i - nGap - 2*nPeak) : 0.0);
		temp.at(i) = temp.at(i-1) + scratch;
		trapWave.at(i) = trapWave.at(i-1) + temp.at(i) + PZCorr*scratch;
	}
	return trapWave;
}

void PACSSAnalysis::ChanNumToXYPos(int channel, int &x, int &y)
{
	x = 6.125*((channel % 8) + 0.5);
	y = 6.125*(floor(channel / 8.0) + 0.5);
	return;
}
