
#include <vector>
#include <iostream>

#include "../Headers/ParticleSource.hpp"
#include "../Headers/SensorRes.hpp"
#include "../Headers/SiDetector.hpp"
#include "../Headers/Reconstruction.hpp"
#include "../Headers/StarEventCounter.hpp"
#include "../Headers/MakeTrees.hpp"

using namespace std;

Int_t main(){
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Parameters
		
	// Source parameters:
	TString const optSo = "UUU"; 		// Distributions for x_0 / y_0 / th_0 -> U = Uniform, G = Gaus 
	Float_t const parX1 =  2.0;			// Parameters for each distributions
	Float_t const parX2 = -2.0; 
	Float_t const parY1 =  2.0; 
	Float_t const parY2 = -2.0; 
	Float_t const parT1 =  TMath::Pi()/10;
	Float_t const parT2 = -TMath::Pi()/10;
	          
	// Detector parameters:
	Int_t   const layersNumber    = 6; 	// Number of layers (sensors) in detector
	Float_t const firstLayer      = 40.0; 	// Position of first sensor
	Float_t const deltaLayer      = 30.0; 	// Distance between sensors
	Float_t const acceptance      = 50.0;	// Accepnance: half of sensor size
	Char_t  const blurryOpt       = 'G';	// Distributions for hit blurring 
	Float_t const blurryPar       = 0.25; 	// Parameter of above distribution
	Float_t const pixelSize       = 0.25; 	// Pixel size
	Float_t const pixelEfficiency = 2.0;	// Pixel efficiency
	
	// Loop parameters
	Int_t   const maxEvents    = 100000;
	Int_t   const stepsInLoop  = 50;
	//~ Int_t   const maxEvents    = 5;
	//~ Int_t   const stepsInLoop  = 1;

	// ------------------------------------------------------------------------------------------------------------------------------- //	
	// Objects
	
	ParticleSource   source        = ParticleSource(optSo, parX1, parX2, parY1, parY2, parT1, parT2);
	SiDetector const detector      = SiDetector(layersNumber, firstLayer, deltaLayer, acceptance, blurryOpt, blurryPar, pixelSize, pixelEfficiency);
	Reconstruction   reconstructor = Reconstruction(layersNumber, firstLayer, deltaLayer, pixelSize);
	MakeTrees        trees         = MakeTrees("ResultsTrees.root", layersNumber);
		 
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Main Loop
	
	StarEventCounter stepper = StarEventCounter( maxEvents, stepsInLoop);
	stepper.beforeLoop();
	for(Int_t i = 0; i<maxEvents; i++){		
		stepper(i);
		
		source.doExperiment();
		std::vector<SensorRes> eventResults = detector.getResults( source );
		reconstructor.doReconstruction( eventResults );	
		
		//~ reconstructor.print();
		
		trees.Fill( source, reconstructor, eventResults);
	}
	stepper.afterLoop();
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Finish program
	
	trees.Write();


	return 0;
	
}
