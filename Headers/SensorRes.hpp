#ifndef SensorRes_hpp
#define SensorRes_hpp

#include <Rtypes.h>

class SensorRes{
	private:
		
		const Float_t m_real;
		const Float_t m_blurry;	
		const Bool_t  m_observed;	
		const Float_t m_measured;	
		
		Bool_t  m_isReco;		
		Float_t m_recoVal;

	public:
		SensorRes(Float_t const f_real, Float_t const f_blurry, Bool_t const f_observed, Float_t const f_measured) : 
			m_real(f_real), m_blurry(f_blurry), m_observed(f_observed), m_measured(f_measured), m_isReco(kFALSE), m_recoVal(9999.0) {};
			
		SensorRes(Float_t const f_real, Float_t const f_blurry, Bool_t const f_observed, Float_t const f_measured, Bool_t const f_isReco, Float_t const f_recoVal) : 
			m_real(f_real), m_blurry(f_blurry), m_observed(f_observed), m_measured(f_measured), m_isReco(f_isReco), m_recoVal(f_recoVal) {};

		void	 SetReco    (Float_t const f_recoVal = 0.0) { m_isReco = kTRUE; m_recoVal = f_recoVal; };

		Float_t GetReal     () const { return m_real;     };
		Float_t GetBlurry   () const { return m_blurry;   };	
		Bool_t  GetObserved () const { return m_observed; };	
		Float_t GetMeasured () const { return m_measured; };	
		Bool_t  GetIsReco   () const { return m_isReco;   };	
		Float_t GetRecoVal  () const { return m_recoVal;  };	
	
};

#endif
