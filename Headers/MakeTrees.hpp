#ifndef MakeTrees_hpp
#define MakeTrees_hpp

#include <vector>

#include <TFile.h>
#include <TTree.h>

#include "ParticleSource.hpp"
#include "SensorRes.hpp"
#include "Reconstruction.hpp"

class MakeTrees{
	
	private:
		const Int_t m_layersNumber;
	
		TFile * output;
		
		TTree * tracksTree;
			Float_t v_T_x0;
			Float_t v_T_y0;
			Float_t v_T_t0;		
			Float_t v_T_tan;
			Float_t v_T_off;
			
		TTree * recoTree;
			Bool_t  v_R_reco;
			Int_t   v_R_nPoints;		
			Float_t v_R_slope;
			Float_t v_R_offset;
			Float_t v_R_theta;
			Float_t v_R_slopeErr;
			Float_t v_R_offsetErr;
			Float_t v_R_thetaErr;							
			Float_t v_R_chi;
			
		std::vector<TTree *> sensorsTree;		
			Float_t v_S_real;
			Float_t v_S_blurry;	
			Bool_t  v_S_observed;	
			Float_t v_S_measured;			
			Bool_t  v_S_isReco;		
			Float_t v_S_recoVal;		
	
	public:
		
		MakeTrees(TString const & outputFile, Int_t const f_layersNumber);
			
		~MakeTrees();
		
		void Write();
				
		void Print();
	
		void Fill(ParticleSource const & source, Reconstruction const & reconstructor, std::vector<SensorRes> const & eventResults);
	
};

		
#endif
