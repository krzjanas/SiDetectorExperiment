#ifndef ConfigureSiDet_h
#define ConfigureSiDet_h

#include <TString.h>
#include <TMath.h>

class ConfigureSiDet{
	public:
		
	// Source parameters:
	TString const optSo = "UUU"; 		// Distributions for x_0 / y_0 / th_0 -> U = Uniform, G = Gaus 
	Float_t const parX1 =  2.0;			// Parameters for each distributions
	Float_t const parX2 = -2.0; 
	Float_t const parY1 =  2.0; 
	Float_t const parY2 = -2.0; 
	Float_t const parT1 =  TMath::Pi()*0.60;
	Float_t const parT2 = -TMath::Pi()*0.60;
	          
	// Detector parameters:
	Int_t   const layersNumber    = 5; 	// Number of layers (sensors) in detector
	Float_t const firstLayer      = 40.0; 	// Position of first sensor
	Float_t const deltaLayer      = 30.0; 	// Distance between sensors
	Float_t const acceptance      = 50.0;	// Accepnance: half of sensor size
	Char_t  const blurryOpt       = 'G';	// Distributions for hit blurring ( "G"aus / "U"nniform )
	Float_t const blurryPar       = 0.25; 	// Parameter of above distribution
	Float_t const pixelSize       = 0.25; 	// Pixel size
	Float_t const pixelEfficiency = 1.0;	// Pixel efficiency
	
	// Loop parameters
	Int_t   const maxEvents    = 100000;
	Int_t   const stepsInLoop  = 50;		
		

};

#endif
