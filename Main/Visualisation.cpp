#include <iostream>

#include <TMath.h>
#include <TApplication.h>

#include "../Tree/ReadTrees.hpp"
#include "../Headers/VisEvent.hpp"
#include "../ConfigureSiDet.hpp"

using namespace std;

Int_t main(){
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Parameters
		
	ConfigureSiDet const conf = ConfigureSiDet();
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Read Event	
	
	ReadTrees trees = ReadTrees("Tree/ResultsTrees.root", conf.layersNumber);
	Int_t evNumber = -1;
	cout << "Type event number: (0-" << trees.GetEntries() <<")"<< endl;
	cin >> evNumber;
	if( evNumber < 0 || evNumber >= trees.GetEntries() ){
		cout <<"You set wrong event number" << endl;
		return 1;
	}
	trees.GetEntry(evNumber);

	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Start Visualisation	

	TApplication * app = new TApplication("app",0,0);
	
	VisEvent vis = VisEvent(evNumber);
	vis.drawSensors();
	vis.drawInitialBorder();
	vis.drawInitialPoint(trees.tracks->x0, trees.tracks->y0);
	vis.drawTracks(trees.tracks->x0, trees.tracks->y0,trees.tracks->off,trees.tracks->tan,trees.reco->reco,trees.reco->offset,trees.reco->slope);

	for(Int_t i = 0; i < conf.layersNumber; i++){		
		SensorRes sen = SensorRes( trees.sensors[i]->real, trees.sensors[i]->blurry, trees.sensors[i]->observed, 
								   trees.sensors[i]->measured, trees.sensors[i]->isReco, trees.sensors[i]->recoVal, trees.sensors[i]->recoErr );
		
		vis.drawSensorCrossing(i,sen);
	}

	vis.drawLegend();
	vis.printVis("Vis/EventVis.png");

	app->Run(kTRUE);
	return 0;
}
