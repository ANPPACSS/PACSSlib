/* BaseGEEvent.hh
Header for BaseGEEvent base class. This class is inherited by:
	1. GEEvent, which holds the SIS raw event information (no analysis)
	2. COINCEvent, which holds the raw paired event information
This class only contains event traits which are parsed directly from the STRUCK data file. Calculated
values should either be made another branch of the TTree containing *Event, or another TTree entirely.

NOTE: COINCEvent inherits from BOTH BaseGEEvent and BaseLYSOEvent - this means we should avoid using the same
name for attributes or member functions in these two classes!
*/

#ifndef BASEGEEVENT_HH
#define BASEGEEVENT_HH

#include "PACSSEvent.hh"

class BaseGEEvent
{
	protected:
		double				 energyGEFirst;
		double				 energyGEMax;
		double				 energyGE; // energyMax - energyFirst
		double				 timestampGE; // Samples
		vector<double> wfRaw;
		vector<double> wfLYSO;
		int						 channel; // "ADCID"
		int						 clockFreq; // MHz

	public:
		BaseGEEvent();
		virtual ~BaseGEEvent();

		// Getter functions
		const double				 GetEnergyGE() const;
		const double				 GetEnergyGEMax() const;
		const double				 GetEnergyGEFirst() const;
		const double 				 GetTimestampGE(bool inNanoSecs=false) const;
		const vector<double> GetWFRaw() const;
		const vector<double> GetWFLYSO() const;
		const int						 GetChannel() const;
		const int						 GetClockFreq() const; // in MHz

		// Setter functions
		void					 SetEnergyGE(double newEnergy);
		void					 SetEnergyGEMax(double newEnergyMax);
		void					 SetEnergyGEFirst(double newEnergyFirst);
		void 					 SetTimestampGE(double newTimestamp);
		void 					 SetWFRaw(vector<double> newWFRaw);
		void					 SetWFLYSO(vector<double> newWFLYSO);
		void					 SetChannel(int newChannel);
		void					 SetClockFreq(int newClockFreq); // in MHz

		// Other useful functions
		void					 ClearEvent();

		// For ROOT
		ClassDef(BaseGEEvent, 1);
};

#endif
