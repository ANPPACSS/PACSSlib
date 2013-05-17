// Class GEEvent member function defintions
#include "GEEvent.hh"

ClassImp(GEEvent)

GEEvent::GEEvent()
{
	Clear();
}

GEEvent::~GEEvent()
{
	// Does nothing
}

double GEEvent::GetEnergy()
{
	return energy;
}

double GEEvent::GetEnergyMax()
{
	return energyMax;
}

double GEEvent::GetEnergyFirst()
{
	return energyFirst;
}

double GEEvent::GetTimestamp(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampNS;
	else
		return timestamp;
}

double GEEvent::GetTimestampT50(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampT50NS;
	else
		return timestampT50;
}

double GEEvent::GetT50Offset(bool inNanoSecs)
{
	if(inNanoSecs)
		return T50OffsetNS;
	else
		return T50Offset;
}

vector<double> GEEvent::GetWFRaw()
{
	return wfRaw;
}

vector<double> GEEvent::GetWFEnergy()
{
	return wfEnergy;
}

vector<double> GEEvent::GetWFDiff()
{
	return wfDiff;
}

double GEEvent::GetIMax()
{
	return IMax;
}

int GEEvent::GetChannel()
{
	return channel;
}

/*double GEEvent::GetT10ToT90(bool inNanoSecs)
{
	if(inNanoSecs)
		return T10ToT90NS;
	else
		return T10ToT90;
}*/

void GEEvent::SetEnergy(double newEnergy)
{
	energy = newEnergy;
	return;
}

void GEEvent::SetEnergyMax(double newEnergyMax)
{
	energyMax = newEnergyMax;
	return;
}

void GEEvent::SetEnergyFirst(double newEnergyFirst)
{
	energyFirst = newEnergyFirst;
	return;
}

void GEEvent::SetTimestamp(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampNS = newTimestamp;
	else
		timestamp = newTimestamp;
	return;
}

void GEEvent::SetTimestampT50(double newTimestampT50, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampT50NS = newTimestampT50;
	else
		timestampT50 = newTimestampT50;
	return;
}

void GEEvent::SetT50Offset(double newT50Offset, bool inNanoSecs)
{
	if(inNanoSecs)
		T50OffsetNS = newT50Offset;
	else
		T50Offset = newT50Offset;
	return;
}

void GEEvent::SetWFRaw(vector<double> newWFRaw)
{
	wfRaw = newWFRaw;
	return;
}

void GEEvent::SetWFEnergy(vector<double> newWFEnergy)
{
	wfEnergy = newWFEnergy;
	return;
}

void GEEvent::SetWFDiff(vector<double> newWFDiff)
{
	wfDiff = newWFDiff;
	return;
}

void GEEvent::SetIMax(double newIMax)
{
	IMax = newIMax;
	return;
}

void GEEvent::SetChannel(int newChannel)
{
	channel = newChannel;
	return;
}

/*void GEEvent::SetT10ToT90(double newT10ToT90, bool inNaoSecs)
{
	if(inNanoSecs)
		T10ToT90NS = newT10ToT90;
	else
		T10ToT90 = newT10ToT90;
	return;
}*/

// Determine the time between the STRUCK-generated timestamp (based on the
// external trigger time) and the T50 time of the WF
void GEEvent::CalcT50Offset()
{
	TH1D hWF("hWF", "", GE_RAW_WF_LEN, 0, GE_RAW_WF_LEN-1);

	// Fill a histogram with the WF values and determine the baseline
	double baseline = 0.0;
	size_t nSamples = 0;
	// Low number of samples-> don't bother since we probably don't care anyway
	if(wfRaw.size() < 50)
		nSamples = 2;
	else
		nSamples = 50;
	for(size_t i=0;i < wfRaw.size();i++)
	{
		if(i < nSamples)
			baseline += wfRaw.at((int)i);
		hWF.Fill((int)i, wfRaw.at((int)i));
	}
	baseline /= (double)nSamples;

	// Find the maximum valued bin, then step backwards in time until we hit
	// half the amplitude of said maximum bin
	int iBin = hWF.GetMaximumBin();
	double maxValue = hWF.GetBinContent(iBin);
	while((hWF.GetBinContent(iBin)-baseline) > ((maxValue-baseline)*0.50))
		iBin--;

	// Set the offset values
	SetT50Offset((double)(iBin-(GE_RAW_WF_LEN/2)), false);
	SetT50Offset((double)((iBin-(GE_RAW_WF_LEN/2))*CLOCK_MULT_GE), true);

	return;
}

void GEEvent::CalcT1ToT2Time(double fracA, double fracB, int &nSamples)
{
	// Determine the baseline and fill the histogram
  TH1D *hWF = new TH1D("hWF", "", GE_RAW_WF_LEN, 0, GE_RAW_WF_LEN-1);
  double baseline = 0.0;
  for(size_t i=0;i < wfRaw.size();i++)
  {
    if(i < 50)
    	baseline += wfRaw.at((int)i);
	  hWF->Fill((int)i, wfRaw.at((int)i));
  }
  baseline /= 50.0;

	// Find the max bin, then find the bin containing maxVal*fracB
  int maxBin = hWF->GetMaximumBin();
  double maxValue = hWF->GetBinContent(maxBin);
	while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*fracB))
    maxBin--;
  nSamples = maxBin;
	// Find fracA and determine the number of values between them
  while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*fracA))
    maxBin--;
  nSamples -= maxBin;

  delete hWF;
  return;
}

void GEEvent::CalcT1ToT2TimeNS(double fracA, double fracB, int &timeNS)
{
  TH1D *hWF = new TH1D("hWF", "", GE_RAW_WF_LEN, 0, GE_RAW_WF_LEN-1);
  double baseline = 0.0;
  for(size_t i=0;i < wfRaw.size();i++)
  {
    if(i < 50)
    	baseline += wfRaw.at((int)i);
	  hWF->Fill((int)i, wfRaw.at((int)i));
  }
  baseline /= 50.0;

  int maxBin = hWF->GetMaximumBin();
  double maxValue = hWF->GetBinContent(maxBin);
	while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*fracB))
    maxBin--;
  timeNS = maxBin;
  while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*fracA))
    maxBin--;
  timeNS -= maxBin;
	// Convert to NS
	timeNS *= CLOCK_MULT_GE;

  delete hWF;
  return;
}

void GEEvent::CalcIMax()
{
	// How many samples in the linear regression window
	int nSamples = 10; // 200 ns
	size_t wfLen = GetWFRaw().size();

	double bl = 0.0;
	size_t nBL = 0;
	// Make sure we accommodate for low numbers of samples
	if(GetWFRaw().size() < 50)
		nBL = 2;
	else
		nBL = 50;
	for(int k=0;k < (int)nBL;k++)
		bl += GetWFRaw().at(k);
	bl /= (double)nBL;

	// Copy the raw WF
	wfDiff = GetWFRaw();
	// Subtract the baseline
	for(size_t i=0;i < wfDiff.size();i++)
		wfDiff[i] -= bl;

	double temp1 = 0.0;
	double temp2 = wfDiff[0];
	wfDiff[0] = 0.0;
	double imax = 0.0;
	// Loop over the waveform
	for(size_t k=1;k < wfLen;k++)
	{
		temp1 = wfDiff[k-1] + wfDiff[k] - temp2 - wfDiff[k-1]/nSamples;
		temp2 = wfDiff[k];
		wfDiff[k] = temp1;
		if(temp1 > imax)
			imax = temp1;
	}

	SetIMax(imax);
	//cout << "IMax: " << imax << endl;
	return;
}

void GEEvent::Clear()
{
	timestamp = 0.0;
	energy = 0.0;
	energyMax = 0.0;
	energyFirst = 0.0;
	timestampNS = 0.0;
	timestampT50NS = 0.0;
	T50Offset = 0.0;
	T50OffsetNS = 0.0;
	wfRaw.clear();
	wfEnergy.clear();
	wfDiff.clear();
	IMax = 0.0;
	channel = 0;
	//T10ToT90 = 0.0;
	//T10ToT90NS = 0.0;
}
