#include "../Headers/SiDetector.hpp"

SiDetector::SiDetector(Int_t const f_layersNumber, Float_t const f_firstLayer, Float_t const f_deltaLayer, Float_t const f_acceptance,
			  Char_t const f_blurryOpt, Float_t const f_blurryPar, Float_t const f_pixelSize, Float_t const f_pixelEfficiency)
			  
			: m_layersNumber(f_layersNumber), m_firstLayer(f_firstLayer), m_deltaLayer(f_deltaLayer), m_acceptance(f_acceptance),
			  m_blurryOpt(f_blurryOpt), m_blurryPar(f_blurryPar), m_pixelSize(f_pixelSize), m_pixelEfficiency(f_pixelEfficiency) 
	  
{
	for( Int_t i = 0; i<m_layersNumber; i++){
		randomsForBlurry.push_back   ( new TRandom3() );
		randomsForObserved.push_back ( new TRandom3() );
	}
}

SiDetector::~SiDetector()
{
	for( Int_t i = 0; i<m_layersNumber; i++){
		delete randomsForBlurry[i];
		delete randomsForObserved[i];
	}
}



std::vector<SensorRes> SiDetector::getResults(ParticleSource const & particle) const {
	
	std::vector<SensorRes> sensors = std::vector<SensorRes>();
	
	Float_t real;
	Float_t blurry;	
	Bool_t  observed;	
	Float_t measured;
			
	for( Int_t i =0; i<m_layersNumber; i++){
		
		// Real Value
		real = particle.tan() * ( m_firstLayer + i*m_deltaLayer ) + particle.off();

		// Blurry Value		
		switch( m_blurryOpt ){
			case('u'):
			case('U'):
				blurry = randomsForBlurry[i]->Uniform(real-m_blurryPar,real+m_blurryPar);
				break;
			default:
				blurry = randomsForBlurry[i]->Gaus(real,m_blurryPar);			
		}	

		// Is observed?			
		observed = blurry > -m_acceptance && blurry < m_acceptance && randomsForObserved[i]->Rndm() < m_pixelEfficiency;

		// Where is measured?						
		if( observed ){
			Int_t pixelNum = blurry / m_pixelSize;
			measured = ( 0.5 + pixelNum ) * m_pixelSize;
		} else {
			measured = 9999.0;
		}
		
		sensors.push_back( SensorRes( real, blurry, observed, measured ) );
	}
		
		
	return sensors;
}
