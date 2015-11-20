#include "ReadTrees.hpp"

ReadTrees::ReadTrees(TString const & fileName, Int_t f_sensorsNumber) : sensorsNumber(f_sensorsNumber) {
		
	tracks = TreeTracks(fileName,"Tracks");
	reco = TreeReco(fileName,"Reco");
	
	entries = tracks.fChain->GetEntries();

	sensors = std::vector<TreeSensor>();
	for(Int_t i = 0; i<sensorsNumber; i++){
		TString senName = "Sensor_";
		senName += i;
		sensors.push_back(TreeSensor(fileName,senName));
	}
	 
}

Int_t ReadTrees::GetEntry(Long64_t entry){
	Int_t a, b;
	a = tracks.GetEntry(entry);
	b = reco.GetEntry(entry);
	if( b < a ) a = b;
	for(Int_t i = 0; i<sensorsNumber; i++){
		b = sensors[i].GetEntry(entry);
		if( b < a ) a = b;
	}
	return b;
}
