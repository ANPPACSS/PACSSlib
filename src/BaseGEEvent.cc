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
		return timestampGE*(1000.0/clockFreq);
	else
		return timestampGE;
}

const vector<double> BaseGEEvent::GetWFRaw() const
{
	return wfRaw;
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

void BaseGEEvent::SetTimestampGE(double newTimestamp)
{
	timestampGE = newTimestamp;
	return;
}

void BaseGEEvent::SetWFRaw(vector<double> newWFRaw)
{
	wfRaw = newWFRaw;
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

void BaseGEEvent::ClearEvent()
{
	timestampGE = 0.0;
	energyGE = 0.0;
	energyGEMax = 0.0;
	energyGEFirst = 0.0;
	wfRaw.clear();
	wfLYSO.clear();
	channel = 0;
	clockFreq = 0;
}
