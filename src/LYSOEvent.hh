/* ALYSOEvent.hh
Header for LYSOEvent class. All the traits are inherited from ALYSOEvent - the difference is inheriting
from TObject, which is required for ROOT I/O.
*/

#ifndef LYSOEVENT_HH
#define LYSOEVENT_HH

#include "BaseLYSOEvent.hh"

class LYSOEvent: public BaseLYSOEvent, public TObject
{
	protected:

	public:
		LYSOEvent();
		virtual ~LYSOEvent();

		ClassDef(LYSOEvent, 1);
};

#endif
