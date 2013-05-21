/* BaseLYSOEvent.cc
Implementation source file for BaseLYSOEvent base class. See BaseLYSOEvent.hh for details.
*/
#include "BaseLYSOEvent.hh"

ClassImp(BaseLYSOEvent)

BaseLYSOEvent::BaseLYSOEvent()
{
	ClearEvent();
}

BaseLYSOEvent::~BaseLYSOEvent()
{
	// Does nothing
}

vector<double> BaseLYSOEvent::GetCharge()
{
	return charge;
}

vector<double> BaseLYSOEvent::GetChargeGC()
{
	return chargeGC;
}

double BaseLYSOEvent::GetEnergyLYSO()
{
	return energyLYSO;
}

double BaseLYSOEvent::GetEnergyLYSOGC()
{
	return energyLYSOGC;
}

double BaseLYSOEvent::GetTimestampLYSO(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampLYSONS;
	else
		return timestampLYSO;
}

bool BaseLYSOEvent::ErrInput()
{
	return errInput;
}

bool BaseLYSOEvent::ErrOutOfRange()
{
	return errOutOfRange;
}

void BaseLYSOEvent::SetCharge(vector<double> newCharge)
{
	charge = newCharge;
	return;
}

void BaseLYSOEvent::SetChargeGC(vector<double> newChargeGC)
{
	chargeGC = newChargeGC;
	return;
}

void BaseLYSOEvent::SetEnergyLYSO(double newEnergy)
{
	energyLYSO = newEnergy;
	return;
}

void BaseLYSOEvent::SetEnergyLYSOGC(double newEnergyGC)
{
	energyLYSOGC = newEnergyGC;
	return;
}

void BaseLYSOEvent::SetTimestampLYSO(double newTimestampNS, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampLYSONS = newTimestampNS;
	else
		timestampLYSO = newTimestampNS;
	return;
}

void BaseLYSOEvent::SetErrInput(bool newErrInput)
{
	errInput = newErrInput;
	return;
}

void BaseLYSOEvent::SetErrOutOfRange(bool newErrOutOfRange)
{
	errOutOfRange = newErrOutOfRange;
	return;
}

void BaseLYSOEvent::ChanNumToXYPos(int channel, int &x, int &y)
{
  // Convert to mm: 49mm / 8 pixels = 6.125mm per pixel
  // Assume the x,y position in mm is the middle of the pixel
  x = 6.125*((channel % 8)+0.5);
  y = 6.125*(floor(channel/8)+0.5);
  return;
}

void BaseLYSOEvent::ClearEvent()
{
	charge.clear();
	chargeGC.clear();
	energyLYSO = 0.0;
	energyLYSOGC = 0.0;
	timestampLYSONS = 0.0;
	timestampLYSO = 0.0;
	errInput = false;
	errOutOfRange = false;
	return;
}
