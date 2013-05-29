#include "PACSSRun.hh"

ClassImp(PACSSRun)

PACSSRun::PACSSRun()
{
	fileName = "";
	cPrefix.clear();
	hPrefix.clear();
	rootFile = nullptr;
	eventTree = nullptr;
	iEvent = 0;
	numEvents = 0;
	SetReportFreq(10000);
}

PACSSRun::PACSSRun(string newFileName)
{
	fileName = newFileName;

	// Prepare the canvas/hist prefix strings
	cPrefix.clear();
	cPrefix.append("c_" + fileName + "_");
	hPrefix.clear();
	hPrefix.append("h_" + fileName + "_");

	// These will be reset anyway, but just to be safe
	rootFile = nullptr;
	eventTree = nullptr;

	iEvent = 0;
	numEvents = 0;
	SetReportFreq(10000);
}

PACSSRun::~PACSSRun()
{
	// Do nothing
}

int PACSSRun::GetReportFreq()
{
	return reportFreq;
}

int PACSSRun::GetNumEvents()
{
	return numEvents;
}

void PACSSRun::SetReportFreq(int newReportFreq)
{
	reportFreq = newReportFreq;
	return;
}
