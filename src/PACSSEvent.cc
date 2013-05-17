// Class PACSSEvent member function definitions
#include "PACSSEvent.hh"

ClassImp(PACSSEvent)

PACSSEvent::PACSSEvent()
{
	// Nothing to see here
}

PACSSEvent::~PACSSEvent()
{
	// Does nothing
}

void PACSSEvent::ChanNumToXYPos(int channel, int &x, int &y)
{
	// Convert to mm: 49mm / 8 pixels = 6.125mm per pixel
	// Assume the x,y position in mm is the middle of the pixel
	x = 6.125*((channel % 8)+0.5);
	y = 6.125*(floor(channel/8)+0.5);
	return;
}
