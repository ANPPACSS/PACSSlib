/* AGEEvent.hh
Header for AGEEvent base class. This class is inherited by:
	1. GEEvent, which holds the SIS raw event information (no analysis)
	2. COINCEvent, which holds the raw paired event information
This class only contains event traits which are parsed directly from the STRUCK data file. Calculated
values should either be made another branch of the TTree containing *Event, or another TTree entirely.

NOTE: COINCEvent inherits from BOTH AGEEvent and ALYSOEvent - this means we should avoid using the same
name for attributes or member functions in these two classes!
*/

#ifndef AGEEVENT_HH
#define AGEEVENT_HH

#include "PACSSEvent.hh"

class AGEEvent
{
	protected:
		double				 energyGEFirst;
		double				 energyGEMax;
		double				 energyGE; // energyMax - energyFirst
		double				 timestampGE;
		double				 timestampGENS; // this depends on the clock frequency so determine at parsing time
		vector<double> wfRaw;
		vector<double> wfEnergy;
		vector<double> wfDiff;
		int						 channel; // "ADCID"
		int						 clockFreq; // We changed clock frequencies so making it an attribute is easiest

	public:
		AGEEvent();
		virtual ~AGEEvent();

		// Getter functions
		double				 GetEnergyGE();
		double				 GetEnergyGEMax();
		double				 GetEnergyGEFirst();
		double 				 GetTimestampGE(bool inNanoSecs=false);
		vector<double> GetWFRaw();
		vector<double> GetWFEnergy();
		vector<double> GetWFDiff();
		int						 GetChannel();
		int						 GetClockFreq(); // in MHz

		// Setter functions
		void					 SetEnergyGE(double newEnergy);
		void					 SetEnergyGEMax(double newEnergyMax);
		void					 SetEnergyGEFirst(double newEnergyFirst);
		void 					 SetTimestampGE(double newTimestamp, bool inNanoSecs=false);
		void 					 SetWFRaw(vector<double> newWFRaw);
		void 					 SetWFEnergy(vector<double> newWFEnergy);
		void					 SetWFDiff(vector<double> newWFDiff);
		void					 SetChannel(int newChannel);
		void					 SetClockFreq(int newClockFreq); // in MHz

		//void					 CalcT1ToT2Time(double fracA, double fracB, int &nTime, bool inNanoSecs=false);

		// Other useful functions
		void					 Clear();

		// For ROOT
		ClassDef(AGEEvent, 1);
};

#endif
