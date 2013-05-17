#ifndef COINCEVENT_HH
#define COINCEVENT_HH

#include "GEEvent.hh"
#include "LYSOEvent.hh"

class COINCEvent: public TObject
{
	protected:
		vector<double> charge;
		vector<double> chargeGC;
		double				 energyLYSO;
		double				 energyGC;
		double				 timestampLYSO;
		double				 timestampLYSONS;
		double 				 gaussXPos;
		double 				 gaussYPos;
		double 				 gaussSXPos;
		double				 gaussSYPos;
		double				 lercheXPos;
		double 				 lercheYPos;
		vector<double> chi2XPos;
		vector<double> chi2YPos;
		vector<double> chi2LXPos;
		vector<double> chi2LYPos;
		bool					 errInput;
		bool					 errOutOfRange;
		int						 nSlidePos;
		// GE
		double				 energyFirst;
		double				 energyMax;
		double				 energyGE; // energyMax - energyFirst
		double				 timestampGE;
		double				 timestampGENS;
		double				 timestampT50;
		double				 timestampT50NS;
		double				 T50Offset;
		double				 T50OffsetNS;
		vector<double> wfRaw;
		vector<double> wfEnergy;
		vector<double> wfDiff;
		double				 IMax;
		int						 channel;

	public:
		COINCEvent();
		COINCEvent(LYSOEvent *newLYSO, GEEvent *newGE);
		virtual ~COINCEvent();

		// Getters
		// LYSO
		vector<double> GetCharge();
		vector<double> GetChargeGC();
		double				 GetEnergyLYSO();
		double				 GetEnergyGC();
		double				 GetTimestampLYSO(bool inNanoSecs=false);
		double				 GetGaussXPos();
		double				 GetGaussYPos();
		double				 GetGaussSXPos();
		double				 GetGaussSYPos();
		double				 GetLercheXPos();
		double				 GetLercheYPos();
		vector<double> GetChi2XPos();
		vector<double> GetChi2YPos();
		vector<double> GetChi2LXPos();
		vector<double> GetChi2LYPos();
		bool					 ErrInput();
		bool					 ErrOutOfRange();
		int					   GetNSlidePos();
		// GE
		double				 GetEnergyGE();
		double				 GetEnergyMax();
		double				 GetEnergyFirst();
		double 				 GetTimestampGE(bool inNanoSecs=false);
		double 				 GetTimestampT50(bool inNanoSecs=false);
		double				 GetT50Offset(bool inNanoSecs=false);
		vector<double> GetWFRaw();
		vector<double> GetWFEnergy();
		vector<double> GetWFDiff();
		double				 GetIMax();
		int						 GetChannel();

		// Setters
		// LYSO
		void					 SetCharge(vector<double> newCharge);
		void					 SetChargeGC(vector<double> newChargeGC);
		void					 SetEnergyLYSO(double newEnergy);
		void					 SetEnergyGC(double newEnergyGC);
		void					 SetTimestampLYSO(double newTimestampNS, bool inNanoSecs=false);
		void					 SetGaussXPos(double newGaussXPos);
		void					 SetGaussYPos(double newGaussYPos);
		void					 SetGaussSXPos(double newGaussSXPos);
		void					 SetGaussSYPos(double newGaussSYPos);
		void					 SetLercheXPos(double newLercheXPos);
		void					 SetLercheYPos(double newLercheYPos);
		void					 SetChi2XPos(vector<double> newChi2XPos);
		void					 SetChi2YPos(vector<double> newChi2YPos);
		void					 SetChi2LXPos(vector<double> newChi2LXPos);
		void					 SetChi2LYPos(vector<double> newChi2LYPos);
		void					 SetErrInput(bool newErrInput);
		void					 SetErrOutOfRange(bool newErrOutOfRange);
		void					 SetNSlidePos(int newNSlidePos);
		// GE
		void					 SetEnergyGE(double newEnergy);
		void					 SetEnergyMax(double newEnergyMax);
		void					 SetEnergyFirst(double newEnergyFirst);
		void 					 SetTimestampGE(double newTimestamp, bool inNanoSecs=false);
		void 					 SetTimestampT50(double newTimestampT50, bool inNanoSecs=false);
		void					 SetT50Offset(double newT50Offset, bool inNanoSecs=false);
		void 					 SetWFRaw(vector<double> newWFRaw);
		void 					 SetWFEnergy(vector<double> newWFEnergy);
		void					 SetWFDiff(vector<double> newWFDiff);
		void					 SetIMax(double newIMax);
		void					 SetChannel(int newChannel);

		void		 			 CopyEvents(LYSOEvent *newLYSO, GEEvent *newGE);
		void					 CalcT1ToT2TimeNS(double T1, double T2, double &time);

		void					 Clear();

		ClassDef(COINCEvent, 1);
};

#endif
