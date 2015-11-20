#include "ReadTrees.hpp"
#include <iostream>

ReadTrees::ReadTrees(TString const & fileName, Int_t f_sensorsNumber) : sensorsNumber(f_sensorsNumber) {

	tracks =new TreeTracks(fileName,"Tracks");
	reco = new TreeReco(fileName,"Reco");
	entries = tracks->fChain->GetEntries();

	sensors = std::vector<TreeSensor *>();
	for(Int_t i = 0; i<sensorsNumber; i++){
		TString senName = "Sensor_";
		senName += i;
		sensors.push_back(new TreeSensor(fileName,senName));
	} 
	 
}

void ReadTrees::GetEntry(Long64_t entry){
	tracks->GetEntry(entry);
	reco->GetEntry(entry);
	for(Int_t i = 0; i<sensorsNumber; i++){
		sensors[i]->GetEntry(entry);
	}
}
