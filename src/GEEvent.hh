/* GEEvent.hh
Header for GEEvent class. All the traits are inherited from AGEEvent - the difference is inheriting
from TObject, which is required for ROOT I/O.
*/

#ifndef GEEVENT_HH
#define GEEVENT_HH

#include "AGEEvent.hh"

class GEEvent: public AGEEvent, public TObject
{
	protected:

	public:
		GEEvent();
		virtual ~GEEvent();

		// For ROOT
		ClassDef(GEEvent, 1);
};

#endif
