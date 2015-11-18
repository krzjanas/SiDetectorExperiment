#ifndef ParticleSource_hpp
#define ParticleSource_hpp

#include <TString.h>
#include <TMath.h>
#include <TRandom3.h>

class ParticleSource{
	private:
	
		const Char_t m_optX;
		const Char_t m_optY;
		const Char_t m_optT;
		
		const Float_t m_parX1;
		const Float_t m_parX2;
		const Float_t m_parY1;
		const Float_t m_parY2;
		const Float_t m_parT1;
		const Float_t m_parT2;
	
		Float_t m_x0;
		Float_t m_y0;
		Float_t m_t0;

		TRandom3 * randX;
		TRandom3 * randY;
		TRandom3 * randT;
			
	public:
		ParticleSource( TString const & options = "UUU", Float_t const parX1 = 2.0, Float_t const parX2 = -2.0, 
				Float_t const parY1 = 2.0, Float_t const parY2 = -2.0, Float_t const parT1 = 1.570796327, Float_t const parT2 = 1.570796327 );
		~ParticleSource();
		
		void doExperiment();
		
		Float_t x0()   const { return m_x0; };
		Float_t y0()   const { return m_y0; };
		Float_t t0()   const { return m_t0; };
		
		Float_t tan()  const { return TMath::Tan( m_t0 ); };
		Float_t off()  const { return m_y0 - m_x0 * TMath::Tan( m_t0 ); };
		

	
};


#endif
