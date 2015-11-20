#ifndef ReadTrees_h
#define ReadTrees_h

#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>

#include "Trees/TreeReco.hpp"
#include "Trees/TreeSensor.hpp"
#include "Trees/TreeTracks.hpp"

class ReadTrees {
	public:
		TreeTracks tracks;	
		TreeReco reco;
		std::vector<TreeSensor> sensors;
		
		
	private:
		Int_t sensorsNumber;	
		Long64_t entries;
		
	public:		
		ReadTrees(TString const & fileName, Int_t f_sensorsNumber);

		Int_t GetEntry(Long64_t entry);
		Long64_t GetEntries() const { return entries; };
};

#endif
