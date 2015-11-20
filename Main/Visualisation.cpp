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




	app->Run(kTRUE);
	return 0;
}
