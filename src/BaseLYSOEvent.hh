/* BaseLYSOEvent.hh
Header for BaseLYSOEvent base class. This class is inherited by:
  1. LYSOEvent, which holds the Vertilon raw event information (no analysis)
	2. COINCEvent, which holds the raw paired event information
This class only contains event traits which are parsed directly from the Vertilon log file. Calculated
values should either be made another branch of the TTree containing *Event, or another TTree entirely.

NOTE: COINCEvent inherits from BOTH BaseGEEvent and BaseLYSOEvent - this means we should avoid using the same
name for attributes or member functions in these two classes!
*/
#ifndef BASELYSOEVENT_HH
#define BASELYSOEVENT_HH

#include "PACSSEvent.hh"

class BaseLYSOEvent
{
	protected:
		vector<double> charge;
		vector<double> chargeGC;
		double				 energyLYSO;
		double				 energyLYSOGC;
		double				 timestampLYSO;
		double				 timestampLYSONS;
		bool					 errInput;
		bool					 errOutOfRange;

	public:
		BaseLYSOEvent();
		virtual ~BaseLYSOEvent();

		// Getter functions
		vector<double> GetCharge();
		vector<double> GetChargeGC();
		double				 GetEnergyLYSO();
		double				 GetEnergyLYSOGC();
		double				 GetTimestampLYSO(bool inNanoSecs=false);
		bool					 ErrInput();
		bool					 ErrOutOfRange();

		// Setter functions
		void					 SetCharge(vector<double> newCharge);
		void					 SetChargeGC(vector<double> newChargeGC);
		void					 SetEnergyLYSO(double newEnergy);
		void					 SetEnergyLYSOGC(double newEnergyGC);
		void					 SetTimestampLYSO(double newTimestampNS, bool inNanoSecs=false);
		void					 SetErrInput(bool newErrInput);
		void					 SetErrOutOfRange(bool newErrOutOfRange);

		// Other useful functions
		void					 ChanNumToXYPos(int channel, int &x, int &y);
		void					 Clear();

		ClassDef(BaseLYSOEvent, 1);
};

#endif
