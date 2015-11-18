#ifndef SiDetector_hpp
#define SiDetector_hpp

#include <vector>

#include <TRandom3.h>

#include "ParticleSource.hpp"
#include "SensorRes.hpp"

class SiDetector {
	
	public:
	
		SiDetector(Int_t const f_layersNumber = 5, Float_t const f_firstLayer = 40.0, Float_t const f_deltaLayer = 30.0, Float_t const f_acceptance = 50.0,
				  Char_t const f_blurryOpt = 'G', Float_t const f_blurryPar = 0.25, Float_t const f_pixelSize = 0.25, Float_t const f_pixelEfficiency = 1.0);
		
		~SiDetector();
		
		std::vector<SensorRes> getResults(ParticleSource const & particle) const;
		
		Float_t getFirstLayer() const {
			return m_firstLayer;
		}
		
		Float_t getDeltaLayer() const {
			return m_deltaLayer;
		}
		
		Float_t getError() const {
			return m_pixelSize / 3.464101615 ; // m_pixelSize / sqrt(12)
		}
	
	private:
	
		// Detector features	
		const Int_t   m_layersNumber;
		const Float_t m_firstLayer;
		const Float_t m_deltaLayer;				
		const Float_t m_acceptance;	
			
		const Char_t  m_blurryOpt;	
		const Float_t m_blurryPar;	
		
		const Float_t m_pixelSize;		
		const Float_t m_pixelEfficiency;
		
		std::vector<TRandom3 *> randomsForBlurry;
		std::vector<TRandom3 *> randomsForObserved;
			
};


#endif
