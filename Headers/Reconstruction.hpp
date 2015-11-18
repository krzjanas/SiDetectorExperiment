#ifndef Reconstruction_hpp
#define Reconstruction_hpp

#include <vector>

#include <TMath.h>

#include "SensorRes.hpp"

class Reconstruction {

	private:

		const Int_t   m_layersNumber;
		const Float_t m_firstLayer;
		const Float_t m_deltaLayer;	
		const Float_t m_pixelError;	
	
		Bool_t  m_reco;
		Int_t   m_nPoints;
	
		Float_t m_slope;
		Float_t m_offset;
		Float_t m_slopeErr;
		Float_t m_offsetErr;
		
		Float_t m_chi;

	
	public:
		Reconstruction(Int_t const f_layersNumber = 5, Float_t const f_firstLayer = 40.0, Float_t const f_deltaLayer = 30.0, Float_t const f_pixelSize = 0.25);
		
		void doReconstruction( std::vector<SensorRes> & results );		
		
		Bool_t  isReco()       const { return m_reco; };
		Int_t   getNPoints()   const { return m_nPoints; };
		
		Float_t getSlope()     const { return m_slope; };
		Float_t getOffset()    const { return m_offset; };
		Float_t getSlopeErr()  const { return m_slopeErr; };
		Float_t getOffsetErr() const { return m_offsetErr; };
		
		Float_t getChi()       const { return m_chi; };
		
		Float_t getTheta()     const { return TMath::ATan( m_slope ); };	
		Float_t getThetaErr()  const { return m_slopeErr / ( 1 + m_slope*m_slope) ; };	
		
		void print();
		
		void linearFit(std::vector<Float_t> const & xi, std::vector<Float_t> const & yi);
	
};


#endif
