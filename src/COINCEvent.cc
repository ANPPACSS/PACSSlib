#include "COINCEvent.hh"

ClassImp(COINCEvent)

COINCEvent::COINCEvent()
{
	Clear();
}

// Construct using the events
COINCEvent::COINCEvent(LYSOEvent *newLYSO, GEEvent *newGE)
{
	// Copy the LYSO attributes
	charge = newLYSO->GetCharge();
	chargeGC = newLYSO->GetChargeGC();
	energyLYSO = newLYSO->GetEnergy();
	energyGC = newLYSO->GetEnergyGC();
	timestampLYSO = newLYSO->GetTimestamp(false);
	timestampLYSONS = newLYSO->GetTimestamp(true);
	gaussXPos = newLYSO->GetGaussXPos();
	gaussYPos = newLYSO->GetGaussYPos();
	gaussSXPos = newLYSO->GetGaussSXPos();
	gaussSYPos = newLYSO->GetGaussSYPos();
	lercheXPos = newLYSO->GetLercheXPos();
	lercheYPos = newLYSO->GetLercheYPos();
	chi2XPos = newLYSO->GetChi2XPos();
	chi2YPos = newLYSO->GetChi2YPos();
	errInput = newLYSO->ErrInput();
	errOutOfRange = newLYSO->ErrOutOfRange();
	nSlidePos = newLYSO->GetNSlidePos();
	chi2LXPos = newLYSO->GetChi2LXPos();
	chi2LYPos = newLYSO->GetChi2LYPos();

	// Copy the GE attributes
	energyGE = newGE->GetEnergy();
	energyFirst = newGE->GetEnergyFirst();
	energyMax = newGE->GetEnergyMax();
	timestampGE = newGE->GetTimestamp(false);
	timestampGENS = newGE->GetTimestamp(true);
	timestampT50 = newGE->GetTimestampT50(false);
	timestampT50NS = newGE->GetTimestampT50(true);
	T50Offset = newGE->GetT50Offset(false);
	T50OffsetNS = newGE->GetT50Offset(true);
	wfRaw = newGE->GetWFRaw();
	wfEnergy = newGE->GetWFEnergy();
	wfDiff = newGE->GetWFDiff();
	IMax = newGE->GetIMax();
	channel = newGE->GetChannel();
}

COINCEvent::~COINCEvent()
{
}

// Getters
// LYSO
vector<double> COINCEvent::GetCharge()
{
	return charge;
}

vector<double> COINCEvent::GetChargeGC()
{
	return chargeGC;
}

double COINCEvent::GetEnergyLYSO()
{
	return energyLYSO;
}

double COINCEvent::GetEnergyGC()
{
	return energyGC;
}


double COINCEvent::GetTimestampLYSO(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampLYSONS;
	else
		return timestampLYSO;
}

double COINCEvent::GetGaussXPos()
{
	return gaussXPos;
}

double COINCEvent::GetGaussYPos()
{
	return gaussYPos;
}

double COINCEvent::GetGaussSXPos()
{
	return gaussSXPos;
}

double COINCEvent::GetGaussSYPos()
{
	return gaussSYPos;
}

double COINCEvent::GetLercheXPos()
{
	return lercheXPos;
}

double COINCEvent::GetLercheYPos()
{
	return lercheYPos;
}

vector<double> COINCEvent::GetChi2XPos()
{
	return chi2XPos;
}

vector<double> COINCEvent::GetChi2YPos()
{
	return chi2YPos;
}

vector<double> COINCEvent::GetChi2LXPos()
{
	return chi2LXPos;
}

vector<double> COINCEvent::GetChi2LYPos()
{
	return chi2LYPos;
}

// GE
double COINCEvent::GetEnergyGE()
{
	return energyGE;
}

double COINCEvent::GetEnergyMax()
{
	return energyMax;
}

double COINCEvent::GetEnergyFirst()
{
	return energyFirst;
}

double COINCEvent::GetTimestampGE(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampGENS;
	else
		return timestampGE;
}

double COINCEvent::GetTimestampT50(bool inNanoSecs)
{
	if(inNanoSecs)
		return timestampT50NS;
	else
		return timestampT50;
}

double COINCEvent::GetT50Offset(bool inNanoSecs)
{
	if(inNanoSecs)
		return T50OffsetNS;
	else
		return T50Offset;
}

vector<double> COINCEvent::GetWFRaw()
{
	return wfRaw;
}

vector<double> COINCEvent::GetWFEnergy()
{
	return wfEnergy;
}

vector<double> COINCEvent::GetWFDiff()
{
	return wfDiff;
}

double COINCEvent::GetIMax()
{
	return IMax;
}

int COINCEvent::GetChannel()
{
	return channel;
}

// Setters
// LYSO
bool COINCEvent::ErrInput()
{
	return errInput;
}

bool COINCEvent::ErrOutOfRange()
{
	return errOutOfRange;
}

int COINCEvent::GetNSlidePos()
{
	return nSlidePos;
}

void COINCEvent::SetCharge(vector<double> newCharge)
{
	charge = newCharge;
	return;
}

void COINCEvent::SetChargeGC(vector<double> newChargeGC)
{
	chargeGC = newChargeGC;
	return;
}

void COINCEvent::SetEnergyLYSO(double newEnergy)
{
	energyLYSO = newEnergy;
	return;
}

void COINCEvent::SetEnergyGC(double newEnergyGC)
{
	energyGC = newEnergyGC;
	return;
}

void COINCEvent::SetTimestampLYSO(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampLYSONS = newTimestamp;
	else
		timestampLYSO = newTimestamp;
	return;
}

void COINCEvent::SetGaussXPos(double newGaussXPos)
{
	gaussXPos = newGaussXPos;
	return;
}

void COINCEvent::SetGaussYPos(double newGaussYPos)
{
	gaussYPos = newGaussYPos;
	return;
}

void COINCEvent::SetGaussSXPos(double newGaussSXPos)
{
	gaussSXPos = newGaussSXPos;
	return;
}

void COINCEvent::SetGaussSYPos(double newGaussSYPos)
{
	gaussSYPos = newGaussSYPos;
	return;
}

void COINCEvent::SetLercheXPos(double newLercheXPos)
{
	lercheXPos = newLercheXPos;
	return;
}

void COINCEvent::SetLercheYPos(double newLercheYPos)
{
	lercheYPos = newLercheYPos;
	return;
}

void COINCEvent::SetChi2XPos(vector<double> newChi2XPos)
{
	chi2XPos = newChi2XPos;
	return;
}

void COINCEvent::SetChi2YPos(vector<double> newChi2YPos)
{
	chi2YPos = newChi2YPos;
	return;
}

void COINCEvent::SetChi2LXPos(vector<double> newChi2LXPos)
{
	chi2LXPos = newChi2LXPos;
	return;
}

void COINCEvent::SetChi2LYPos(vector<double> newChi2LYPos)
{
	chi2LYPos = newChi2LYPos;
	return;
}

void COINCEvent::SetErrInput(bool newErrInput)
{
	errInput = newErrInput;
	return;
}

void COINCEvent::SetErrOutOfRange(bool newErrOutOfRange)
{
	errOutOfRange = newErrOutOfRange;
	return;
}

void COINCEvent::SetNSlidePos(int newNSlidePos)
{
	nSlidePos = newNSlidePos;
	return;
}
// GE
void COINCEvent::SetEnergyGE(double newEnergy)
{
	energyGE = newEnergy;
	return;
}

void COINCEvent::SetEnergyMax(double newEnergyMax)
{
	energyMax = newEnergyMax;
	return;
}

void COINCEvent::SetEnergyFirst(double newEnergyFirst)
{
	energyFirst = newEnergyFirst;
	return;
}

void COINCEvent::SetTimestampGE(double newTimestamp, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampGENS = newTimestamp;
	else
		timestampGE = newTimestamp;
	return;
}

void COINCEvent::SetTimestampT50(double newTimestampT50, bool inNanoSecs)
{
	if(inNanoSecs)
		timestampT50NS = newTimestampT50;
	else
		timestampT50 = newTimestampT50;
	return;
}

void COINCEvent::SetT50Offset(double newT50Offset, bool inNanoSecs)
{
	if(inNanoSecs)
		T50OffsetNS = newT50Offset;
	else
		T50Offset = newT50Offset;
	return;
}

void COINCEvent::SetWFRaw(vector<double> newWFRaw)
{
	wfRaw = newWFRaw;
	return;
}

void COINCEvent::SetWFEnergy(vector<double> newWFEnergy)
{
	wfEnergy = newWFEnergy;
	return;
}

void COINCEvent::SetWFDiff(vector<double> newWFDiff)
{
	wfDiff = newWFDiff;
	return;
}

void COINCEvent::SetIMax(double newIMax)
{
	IMax = newIMax;
	return;
}

void COINCEvent::SetChannel(int newChannel)
{
	channel = newChannel;
	return;
}

// Construct using the events
void COINCEvent::CopyEvents(LYSOEvent *newLYSO, GEEvent *newGE)
{
	// For good measure
	Clear();

	// Copy the LYSO attributes
	charge = newLYSO->GetCharge();
	chargeGC = newLYSO->GetChargeGC();
	energyLYSO = newLYSO->GetEnergy();
	energyGC = newLYSO->GetEnergyGC();
	timestampLYSO = newLYSO->GetTimestamp(false);
	timestampLYSONS = newLYSO->GetTimestamp(true);
	gaussXPos = newLYSO->GetGaussXPos();
	gaussYPos = newLYSO->GetGaussYPos();
	gaussSXPos = newLYSO->GetGaussSXPos();
	gaussSYPos = newLYSO->GetGaussSYPos();
	lercheXPos = newLYSO->GetLercheXPos();
	lercheYPos = newLYSO->GetLercheYPos();
	chi2XPos = newLYSO->GetChi2XPos();
	chi2YPos = newLYSO->GetChi2YPos();
	errInput = newLYSO->ErrInput();
	errOutOfRange = newLYSO->ErrOutOfRange();
	nSlidePos = newLYSO->GetNSlidePos();
	chi2LXPos = newLYSO->GetChi2LXPos();
	chi2LYPos = newLYSO->GetChi2LYPos();

	// Copy the GE attributes
	energyGE = newGE->GetEnergy();
	energyFirst = newGE->GetEnergyFirst();
	energyMax = newGE->GetEnergyMax();
	timestampGE = newGE->GetTimestamp(false);
	timestampGENS = newGE->GetTimestamp(true);
	timestampT50 = newGE->GetTimestampT50(false);
	timestampT50NS = newGE->GetTimestampT50(true);
	T50Offset = newGE->GetT50Offset(false);
	T50OffsetNS = newGE->GetT50Offset(true);
	wfRaw = newGE->GetWFRaw();
	wfEnergy = newGE->GetWFEnergy();
	wfDiff = newGE->GetWFDiff();
	IMax = newGE->GetIMax();
	channel = newGE->GetChannel();
}

void COINCEvent::CalcT1ToT2TimeNS(double T1, double T2, double &time)
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
	while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*T2))
		maxBin--;
	time = maxBin;
	while((hWF->GetBinContent(maxBin)-baseline) > ((maxValue-baseline)*T1))
		maxBin--;
	time -= maxBin;
	time *= CLOCK_MULT_GE;

	delete hWF;
	return;
}

void COINCEvent::Clear()
{
	// Clar the LYSO attributes
	charge.clear();
	chargeGC.clear();
	energyLYSO = 0.0;
	energyGC = 0.0;
	timestampLYSO = 0.0;
	timestampLYSONS = 0.0;
	gaussXPos = 0.0;
	gaussYPos = 0.0;
	gaussSXPos = 0.0;
	gaussSYPos = 0.0;
	lercheXPos = 0.0;
	lercheYPos = 0.0;
	chi2XPos.clear();
	chi2YPos.clear();
	errInput = false;
	errOutOfRange = false;
	nSlidePos = 0;
	chi2LXPos.clear();
	chi2LYPos.clear();

	// Clear the GE attributes
	energyGE = 0.0;
	energyFirst = 0.0;
	energyMax = 0.0;
	timestampGE = 0.0;
	timestampGENS = 0.0;
	timestampT50 = 0.0;
	timestampT50NS = 0.0;
	T50Offset = 0.0;
	T50OffsetNS = 0.0;
	wfRaw.clear();
	wfEnergy.clear();
	wfDiff.clear();
	IMax = 0.0;
	channel = 0;
	
	return;
}
