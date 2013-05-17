#ifndef GEEVENT_HH
#define GEEVENT_HH

#include "PACSSEvent.hh"

class GEEvent: public PACSSEvent, public TObject
{
	protected:
		double				 energyFirst;
		double				 energyMax;
		double				 energy; // energyMax - energyFirst
		double				 timestamp;
		double				 timestampNS;
		double				 timestampT50;
		double				 timestampT50NS;
		double				 T50Offset;
		double				 T50OffsetNS;
		vector<double> wfRaw;
		vector<double> wfEnergy;
		vector<double> wfDiff;
		double				 IMax;
		int						 channel;
		//double			 T10ToT90;
		//double			 T10ToT90NS;

	public:
		GEEvent();
		virtual ~GEEvent();

		// Getter functions
		double				 GetEnergy();
		double				 GetEnergyMax();
		double				 GetEnergyFirst();
		double 				 GetTimestamp(bool inNanoSecs=false);
		double 				 GetTimestampT50(bool inNanoSecs=false);
		double				 GetT50Offset(bool inNanoSecs=false);
		vector<double> GetWFRaw();
		vector<double> GetWFEnergy();
		vector<double> GetWFDiff();
		double				 GetIMax();
		int						 GetChannel();
		//double			 GetT10ToT90(bool inNanoSecs=false);

		// Setter functions
		void					 SetEnergy(double newEnergy);
		void					 SetEnergyMax(double newEnergyMax);
		void					 SetEnergyFirst(double newEnergyFirst);
		void 					 SetTimestamp(double newTimestamp, bool inNanoSecs=false);
		void 					 SetTimestampT50(double newTimestampT50, bool inNanoSecs=false);
		void					 SetT50Offset(double newT50Offset, bool inNanoSecs=false);
		void 					 SetWFRaw(vector<double> newWFRaw);
		void 					 SetWFEnergy(vector<double> newWFEnergy);
		void					 SetWFDiff(vector<double> newWFDiff);
		void					 SetIMax(double newIMax);
		void					 SetChannel(int newChannel);
		//void					 SetT10ToT90(double newT10ToT90, bool inNanoSecs=false);

		// Analysis functions
		void					 CalcT50Offset();
		void					 CalcT1ToT2Time(double fracA, double fracB, int &nSamples);
		void					 CalcT1ToT2TimeNS(double fracA, double fracB, int &timeNS);
		void					 CalcIMax();

		// Other useful functions
		void					 Clear();

		// For ROOT
		ClassDef(GEEvent, 1);
};

#endif
