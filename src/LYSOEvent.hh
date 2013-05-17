#ifndef LYSOEVENT_HH
#define LYSOEVENT_HH

#include "PACSSEvent.hh"

class LYSOEvent: public PACSSEvent, public TObject
{
	protected:
		vector<double> charge;
		vector<double> chargeGC;
		double				 energy;
		double				 energyGC;
		double				 timestamp;
		double				 timestampNS;
		double 				 gaussXPos;
		double 				 gaussYPos;
		double 				 gaussSXPos;
		double				 gaussSYPos;
		vector<double> chi2XPos;
		vector<double> chi2YPos;
		bool					 errInput;
		bool					 errOutOfRange;
		int						 nSlidePos;
		double			   lercheXPos;
		double				 lercheYPos;
		vector<double> chi2LXPos;
		vector<double> chi2LYPos;

	public:
		LYSOEvent();
		virtual ~LYSOEvent();

		// Getter functions
		vector<double> GetCharge();
		vector<double> GetChargeGC();
		double				 GetEnergy();
		double				 GetEnergyGC();
		double				 GetTimestamp(bool inNanoSecs=false);
		double				 GetGaussXPos();
		double				 GetGaussYPos();
		double				 GetGaussSXPos();
		double				 GetGaussSYPos();
		vector<double> GetChi2XPos();
		vector<double> GetChi2YPos();
		bool					 ErrInput();
		bool					 ErrOutOfRange();
		int					   GetNSlidePos();
		double				 GetLercheXPos();
		double				 GetLercheYPos();
		vector<double> GetChi2LXPos();
		vector<double> GetChi2LYPos();

		// Setter functions
		void					 SetCharge(vector<double> newCharge);
		void					 SetChargeGC(vector<double> newChargeGC);
		void					 SetEnergy(double newEnergy);
		void					 SetEnergyGC(double newEnergyGC);
		void					 SetTimestamp(double newTimestampNS, bool inNanoSecs=false);
		void					 SetGaussXPos(double newGaussXPos);
		void					 SetGaussYPos(double newGaussYPos);
		void					 SetGaussSXPos(double newGaussSXPos);
		void					 SetGaussSYPos(double newGaussSYPos);
		void					 SetChi2XPos(vector<double> newChi2XPos);
		void					 SetChi2YPos(vector<double> newChi2YPos);
		void					 SetErrInput(bool newErrInput);
		void					 SetErrOutOfRange(bool newErrOutOfRange);
		void					 SetNSlidePos(int newNSlidePos);
		void					 SetLercheXPos(double newLercheXPos);
		void					 SetLercheYPos(double newLercheYPos);
		void					 SetChi2LXPos(vector<double> newChi2LXPos);
		void					 SetChi2LYPos(vector<double> newChi2LYPos);

		// Analysis functions
		//void 					 CalcGaussXYPos(TH1D hProjX, TH1D hProjY);
		//void 					 CalcLercheXYPos(TH1D hProjX, TH1D hProjY);
		void				   CalcXYPosition(TH1D *hProjX, TH1D *hProjY);

		// Other useful functions
		void					 Clear();

		ClassDef(LYSOEvent, 1);
};

#endif
