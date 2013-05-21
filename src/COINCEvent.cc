#include "COINCEvent.hh"

ClassImp(COINCEvent)

COINCEvent::COINCEvent()
{
	Clear();
}

// Construct using the events
COINCEvent::COINCEvent(LYSOEvent *newLYSO, GEEvent *newGE): BaseGEEvent(newGE), BaseLYSOEvent(newLYSO)
{
}

COINCEvent::~COINCEvent()
{
}

// Just in case we already have an instance
void COINCEvent::CopyEvents(LYSOEvent *newLYSO, GEEvent *newGE)
{
	// For good measure
	Clear();

	// Copy the LYSO attributes
	charge = newLYSO->GetCharge();
	chargeGC = newLYSO->GetChargeGC();
	energyLYSO = newLYSO->GetEnergyLYSO();
	energyLYSOGC = newLYSO->GetEnergyLYSOGC();
	timestampLYSO = newLYSO->GetTimestampLYSO(false);
	timestampLYSONS = newLYSO->GetTimestampLYSO(true);

	// Copy the GE attributes
	energyGE = newGE->GetEnergyGE();
	energyGEFirst = newGE->GetEnergyGEFirst();
	energyGEMax = newGE->GetEnergyGEMax();
	timestampGE = newGE->GetTimestampGE(false);
	timestampGENS = newGE->GetTimestampGE(true);
	wfRaw = newGE->GetWFRaw();
	wfEnergy = newGE->GetWFEnergy();
	wfDiff = newGE->GetWFDiff();
	channel = newGE->GetChannel();
	clockFreq = newGE->GetClockFreq();
}

void COINCEvent::Clear()
{
	// Clear the LYSO attributes
	BaseLYSOEvent::Clear();
	// Clear the GE attributes
	BaseGEEvent::Clear();
	
	return;
}
