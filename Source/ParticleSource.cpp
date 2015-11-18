#include "../Headers/ParticleSource.hpp"

ParticleSource::ParticleSource( TString const & options, Float_t const parX1, Float_t const parX2, 
		Float_t const parY1, Float_t const parY2, Float_t const parT1, Float_t const parT2 )
		
		: m_optX(options[0]), m_optY(options[1]), m_optT(options[2]), m_parX1(parX1), m_parX2(parX2), m_parY1(parY1), m_parY2(parY2), m_parT1(parT1), m_parT2(parT2), m_x0(0.0), m_y0(0.0), m_t0(0.0),
		randX( new TRandom3(0) ), randY( new TRandom3(0) ),randT( new TRandom3(0) )

{
	
}

		
ParticleSource::~ParticleSource(){
	delete randX;
	delete randY;
	delete randT;
}




void ParticleSource::doExperiment(){
	
	switch( m_optX ){
		case ('g'):
		case ('G'):
			m_x0 = randX->Gaus(m_parX1, m_parX2);
			break;
		default:
			m_x0 = randX->Uniform(m_parX1, m_parX2);
	}
	switch( m_optY ){
		case ('g'):
		case ('G'):
			m_y0 = randY->Gaus(m_parY1, m_parY2);
			break;
		default:
			m_y0 = randY->Uniform(m_parY1, m_parY2);
	}
	switch( m_optT ){
		case ('g'):
		case ('G'):
			m_t0 = randT->Gaus(m_parT1, m_parT2);
			break;
		default:
			m_t0 = randT->Uniform(m_parT1, m_parT2);
	}
		
}



