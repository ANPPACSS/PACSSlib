#include "COINCEvent.hh"

ClassImp(COINCEvent)

COINCEvent::COINCEvent()
{
	Clear();
}

// Construct using the events - uses default constructors of both (since LYSOEvent and GEEvent
// inherit from the bases)
COINCEvent::COINCEvent(const LYSOEvent &newLYSO, const GEEvent &newGE): BaseGEEvent(newGE), BaseLYSOEvent(newLYSO)
{
}

COINCEvent::~COINCEvent()
{
}

// Just in case we already have an instance
void COINCEvent::CopyEvents(const LYSOEvent &newLYSO, const GEEvent &newGE)
{
	// For good measure
	Clear();

	// Copy the LYSO attributes
	charge = newLYSO.GetCharge();
	chargeGC = newLYSO.GetChargeGC();
	energyLYSO = newLYSO.GetEnergyLYSO();
	energyLYSOGC = newLYSO.GetEnergyLYSOGC();
	timestampLYSO = newLYSO.GetTimestampLYSO(false);
	errInput = newLYSO.ErrInput();
	errOutOfRange = newLYSO.ErrOutOfRange();

	// Copy the GE attributes
	energyGE = newGE.GetEnergyGE();
	energyGEFirst = newGE.GetEnergyGEFirst();
	energyGEMax = newGE.GetEnergyGEMax();
	timestampGE = newGE.GetTimestampGE(false);
	wfRaw = newGE.GetWFRaw();
	channel = newGE.GetChannel();
	clockFreq = newGE.GetClockFreq();
	wfLYSO = newGE.GetWFLYSO();
}

void COINCEvent::Clear()
{
	// Clear the LYSO attributes
	BaseLYSOEvent::ClearEvent();
	// Clear the GE attributes
	BaseGEEvent::ClearEvent();
	
	return;
}
