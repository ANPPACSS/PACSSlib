/* ALYSOEvent.hh
Header for LYSOEvent class. All the traits are inherited from ALYSOEvent - the difference is inheriting
from TObject, which is required for ROOT I/O.
*/

#ifndef LYSOEVENT_HH
#define LYSOEVENT_HH

#include "ALYSOEvent.hh"

class LYSOEvent: public ALYSOEvent, public TObject
{
	protected:

	public:
		LYSOEvent();
		virtual ~LYSOEvent();

		ClassDef(LYSOEvent, 1);
};

#endif
