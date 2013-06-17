/* BaseGEEvent.cc
Implementation source file for BaseGEEvent base class. See BaseGEEvent.hh for details.
*/
#include "BaseGEEvent.hh"

ClassImp(BaseGEEvent)

BaseGEEvent::BaseGEEvent()
{
	ClearEvent();
}

BaseGEEvent::~BaseGEEvent()
{
	// Does nothing
}

const double BaseGEEvent::GetEnergyGE() const
{
	return energyGE;
}

const double BaseGEEvent::GetEnergyGEMax() const
{
	return energyGEMax;
}

const double BaseGEEvent::GetEnergyGEFirst() const
{
	return energyGEFirst;
}

const double BaseGEEvent::GetTimestampGE(bool inNanoSecs) const
{
	if(inNanoSecs)
		return timestampGENS;
	else
		return timestampGE;
}

const vector<double> BaseGEEvent::GetWFRaw() const
{
	return wfRaw;
}

const vector<double> BaseGEEvent::GetWFEnergy() const
{
	return wfEnergy;
}

const vector<double> BaseGEEvent::GetWFDiff() const
{
	return wfDiff;
}

const vector<double> BaseGEEvent::GetWFLYSO() const
{
	return wfLYSO;
}

const int BaseGEEvent::GetChannel() const
{
	return channel;
}

const int BaseGEEvent::GetClockFreq() const
{
	return clockFreq;
}

void BaseGEEvent::SetEnergyGE(double newEnergy)
{
	energyGE = newEnergy;
	return;
}

void BaseGEEvent::SetEnergyGEMax(double newEnergyMax)
{
	energyGEMax = newEnergyMax;
	return;
}

void BaseGEEvent::SetEnergyGEFirst(double newEnergyFirst)
{
	energyGEFirst = newEnergyFirst;
	return;
}

void BaseGEEvent::SetTimestampGE(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampGENS = newTimestamp;
	else
		timestampGE = newTimestamp;
	return;
}

void BaseGEEvent::SetWFRaw(vector<double> newWFRaw)
{
	wfRaw = newWFRaw;
	return;
}

void BaseGEEvent::SetWFEnergy(vector<double> newWFEnergy)
{
	wfEnergy = newWFEnergy;
	return;
}

void BaseGEEvent::SetWFDiff(vector<double> newWFDiff)
{
	wfDiff = newWFDiff;
	return;
}

void BaseGEEvent::SetWFLYSO(vector<double> newWFLYSO)
{
	wfLYSO = newWFLYSO;
	return;
}

void BaseGEEvent::SetChannel(int newChannel)
{
	channel = newChannel;
	return;
}

void BaseGEEvent::SetClockFreq(int newClockFreq)
{
	clockFreq = newClockFreq;
	return;
}

/*void BaseGEEvent::CalcT1ToT2Time(double fracA, double fracB, int &nTime, bool inNanoSecs)
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
}*/

void BaseGEEvent::ClearEvent()
{
	timestampGE = 0.0;
	energyGE = 0.0;
	energyGEMax = 0.0;
	energyGEFirst = 0.0;
	timestampGENS = 0.0;
	wfRaw.clear();
	wfEnergy.clear();
	wfDiff.clear();
	wfLYSO.clear();
	channel = 0;
	clockFreq = 0;
}
