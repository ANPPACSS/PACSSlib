#ifndef COINCEVENT_HH
#define COINCEVENT_HH

#include "BaseGEEvent.hh"
#include "GEEvent.hh"
#include "BaseLYSOEvent.hh"
#include "LYSOEvent.hh"

class COINCEvent: public BaseGEEvent, public BaseLYSOEvent, public TObject
{
	protected:

	public:
		COINCEvent();
		// Use default copy constructors - the classes have simple attributes
		COINCEvent(const LYSOEvent &newLYSO, const GEEvent &newGE); 
		virtual ~COINCEvent();

		void		 			 CopyEvents(const LYSOEvent &newLYSO, const GEEvent &newGE);

		void					 Clear();

		ClassDef(COINCEvent, 1);
};

#endif
