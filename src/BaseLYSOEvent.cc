/* ALYSOEvent.cc
Implementation source file for ALYSOEvent base class. See ALYSOEvent.hh for details.
*/
#include "ALYSOEvent.hh"

ClassImp(ALYSOEvent)

ALYSOEvent::ALYSOEvent()
{
	Clear();
}

ALYSOEvent::~ALYSOEvent()
{
	// Does nothing
}

vector<double> ALYSOEvent::GetCharge()
{
	return charge;
}

vector<double> ALYSOEvent::GetChargeGC()
{
	return chargeGC;
}

double ALYSOEvent::GetEnergyLYSO()
{
	return energyLYSO;
}

double ALYSOEvent::GetEnergyLYSOGC()
{
	return energyLYSOGC;
}

double ALYSOEvent::GetTimestampLYSO(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampLYSONS;
	else
		return timestampLYSO;
}

bool ALYSOEvent::ErrInput()
{
	return errInput;
}

bool ALYSOEvent::ErrOutOfRange()
{
	return errOutOfRange;
}

void ALYSOEvent::SetCharge(vector<double> newCharge)
{
	charge = newCharge;
	return;
}

void ALYSOEvent::SetChargeGC(vector<double> newChargeGC)
{
	chargeGC = newChargeGC;
	return;
}

void ALYSOEvent::SetEnergyLYSO(double newEnergy)
{
	energyLYSO = newEnergy;
	return;
}

void ALYSOEvent::SetEnergyLYSOGC(double newEnergyGC)
{
	energyLYSOGC = newEnergyGC;
	return;
}


void ALYSOEvent::SetTimestampLYSO(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampLYSONS = newTimestamp;
	else
		timestampLYSO = newTimestamp;
	return;
}

void ALYSOEvent::SetErrInput(bool newErrInput)
{
	errInput = newErrInput;
	return;
}

void ALYSOEvent::SetErrOutOfRange(bool newErrOutOfRange)
{
	errOutOfRange = newErrOutOfRange;
	return;
}

void ALYSOEvent::ChanNumToXYPos(int channel, int &x, int &y)
{
  // Convert to mm: 49mm / 8 pixels = 6.125mm per pixel
  // Assume the x,y position in mm is the middle of the pixel
  x = 6.125*((channel % 8)+0.5);
  y = 6.125*(floor(channel/8)+0.5);
  return;
}


void ALYSOEvent::Clear()
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
