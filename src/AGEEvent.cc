/* AGEEvent.cc
Implementation source file for AGEEvent abstract class. See AGEEvent.hh for details.
*/
#include "AGEEvent.hh"

ClassImp(AGEEvent)

AGEEvent::AGEEvent()
{
	Clear();
}

AGEEvent::~AGEEvent()
{
	// Does nothing
}

double AGEEvent::GetEnergyGE()
{
	return energy;
}

double AGEEvent::GetEnergyGEMax()
{
	return energyMax;
}

double AGEEvent::GetEnergyGEFirst()
{
	return energyFirst;
}

double AGEEvent::GetTimestampGE(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampNS;
	else
		return timestamp;
}

vector<double> AGEEvent::GetWFRaw()
{
	return wfRaw;
}

vector<double> AGEEvent::GetWFEnergyGE()
{
	return wfEnergy;
}

vector<double> AGEEvent::GetWFDiff()
{
	return wfDiff;
}

int AGEEvent::GetChannel()
{
	return channel;
}

int AGEEvent::GetClockFreq()
{
	return clockFreq;
}

void AGEEvent::SetEnergyGE(double newEnergy)
{
	energy = newEnergy;
	return;
}

void AGEEvent::SetEnergyGEMax(double newEnergyMax)
{
	energyMax = newEnergyMax;
	return;
}

void AGEEvent::SetEnergyGEFirst(double newEnergyFirst)
{
	energyFirst = newEnergyFirst;
	return;
}

void AGEEvent::SetTimestampGE(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampNS = newTimestamp;
	else
		timestamp = newTimestamp;
	return;
}

void AGEEvent::SetWFRaw(vector<double> newWFRaw)
{
	wfRaw = newWFRaw;
	return;
}

void AGEEvent::SetWFEnergy(vector<double> newWFEnergy)
{
	wfEnergy = newWFEnergy;
	return;
}

void AGEEvent::SetWFDiff(vector<double> newWFDiff)
{
	wfDiff = newWFDiff;
	return;
}

void AGEEvent::SetChannel(int newChannel)
{
	channel = newChannel;
	return;
}

void AGEEvent::SetClockFreq(int newClockFreq)
{
	clockFreq = newClockFreq;
	return;
}

void AGEEvent::CalcT1ToT2Time(double fracA, double fracB, int &nTime, bool inNanoSecs)
{
	// Make sure there is a waveform
	if(wfRaw.size() == 0)
	{
		cout << "Waveform is empty!" << endl;
		return;
	}

	// Determine the baseline and fill the histogram.
	// Use the first ~20% of samples as the baseline
  TH1I *hWF = new TH1I("hWF", "", (int)wfRaw.size(), 0, (int)wfRaw.size()-1);
  double baseline = 0.0;
	// Let the type converison do the rounding, it's not important to be exact
	int blLength = (int)wfRaw.size()/5;
  for(size_t i=0;i < wfRaw.size();i++)
  {
    if(i < blLength)
    	baseline += wfRaw.at((int)i);
	  hWF->Fill((int)i, wfRaw.at((int)i));
  }
  baseline /= (double)blLength;

	// Find the max bin, then find the bin containing maxVal*fracB
  int maxBin = hWF->GetMaximumBin();
  double maxValue = hWF->GetBinContent(maxBin);
	while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*fracB))
    maxBin--;
  nTime = maxBin;
	// Find fracA and determine the number of values between them
  while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*fracA))
    maxBin--;
  nTime -= maxBin;

	// Convert to ns if necessary, depending on the clock frequency
	if(inNanoSecs)
		nTime *= (1000/clockFreq);

  delete hWF;
  return;
}

void AGEEvent::Clear()
{
	timestampGE = 0.0;
	energyGE = 0.0;
	energyGEMax = 0.0;
	energyGEFirst = 0.0;
	timestampGENS = 0.0;
	wfRaw.clear();
	wfEnergy.clear();
	wfDiff.clear();
	channel = 0;
	clockFreq = 0;
}
