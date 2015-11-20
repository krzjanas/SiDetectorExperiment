#include <vector>
#include <iostream>

#include "../Headers/ParticleSource.hpp"
#include "../Headers/SensorRes.hpp"
#include "../Headers/SiDetector.hpp"
#include "../Headers/Reconstruction.hpp"
#include "../Headers/StarEventCounter.hpp"
#include "../Tree/MakeTrees.hpp"

#include "../ConfigureSiDet.hpp"

using namespace std;

Int_t main(){
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Parameters
		
	ConfigureSiDet const conf = ConfigureSiDet();

	// ------------------------------------------------------------------------------------------------------------------------------- //	
	// Objects
	
	ParticleSource   source        = ParticleSource(conf.optSo, conf.parX1, conf.parX2, conf.parY1, conf.parY2, conf.parT1, conf.parT2);
	SiDetector const detector      = SiDetector(conf.layersNumber, conf.firstLayer, conf.deltaLayer, conf.acceptance, conf.blurryOpt,
												conf.blurryPar, conf.pixelSize, conf.pixelEfficiency);
	Reconstruction   reconstructor = Reconstruction(conf.layersNumber, conf.firstLayer, conf.deltaLayer, conf.pixelSize);
	MakeTrees        trees         = MakeTrees("Tree/ResultsTrees.root", conf.layersNumber);
		 
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Main Loop
	
	StarEventCounter stepper = StarEventCounter( conf.maxEvents, conf.stepsInLoop);
	stepper.beforeLoop();
	for(Int_t i = 0; i<conf.maxEvents; i++){		
		stepper(i);
		
		source.doExperiment();
		std::vector<SensorRes> eventResults = detector.getResults( source );
		reconstructor.doReconstruction( eventResults );	
				
		trees.Fill( source, reconstructor, eventResults );
	}
	stepper.afterLoop();
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Finish program
	
	trees.Write();


	return 0;
	
}
