#include "ReadTrees.hpp"

ReadTrees::ReadTrees(TString const & fileName, Int_t f_sensorsNumber) : sensorsNumber(f_sensorsNumber) {
	TTree * tmpTree;
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName);
	if (!f || !f->IsOpen()) {
		f = new TFile(fileName);
	}
	f->GetObject("Tracks",tmpTree);
	tracks = TreeTracks(tmpTree);
	f->GetObject("Reco",tmpTree);
	reco = TreeReco(tmpTree);
	
	sensors = std::vector<TreeSensor>();
	
	for(Int_t i = 0; i<sensorsNumber; i++){
		TString senName = "Sensor_";
		senName += i;
		f->GetObject(senName,tmpTree);

		sensors.push_back(TreeSensor(tmpTree));
	}
	
	f->Close();
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
