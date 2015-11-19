#include "MakeTrees.hpp"


MakeTrees::MakeTrees(TString const & outputFile, Int_t const f_layersNumber) : m_layersNumber(f_layersNumber){
	output = new TFile(outputFile, "RECREATE");

	int branchStyle = 1 ;
	TTree::SetBranchStyle(branchStyle);	
	TBranch *branch;		
		
	tracksTree = new TTree("Tracks","Tracks");
		branch = tracksTree->Branch("x0",  &v_T_x0, "x0/F" );	 branch->SetAutoDelete(kFALSE);
		branch = tracksTree->Branch("y0",  &v_T_y0, "y0/F" );	 branch->SetAutoDelete(kFALSE);
		branch = tracksTree->Branch("t0",  &v_T_t0, "t0/F" );	 branch->SetAutoDelete(kFALSE);
		branch = tracksTree->Branch("tan", &v_T_tan,"tan/F");	 branch->SetAutoDelete(kFALSE);
		branch = tracksTree->Branch("off", &v_T_off,"off/F");	 branch->SetAutoDelete(kFALSE);

	recoTree   = new TTree("Reco","Reco");
		branch = recoTree->Branch("reco",      &v_R_reco,      "reco/O" );		 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("nPoints",   &v_R_nPoints,   "nPoints/I" );		 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("slope",     &v_R_slope,     "slope/F" );		 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("offset",    &v_R_offset,    "offset/F" );		 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("theta",     &v_R_theta,     "theta/F" );		 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("slopeErr",  &v_R_slopeErr,  "slopeErr/F" );	 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("offsetErr", &v_R_offsetErr, "offsetErr/F" );	 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("thetaErr",  &v_R_thetaErr,  "thetaErr/F" );	 branch->SetAutoDelete(kFALSE);
		branch = recoTree->Branch("chi",       &v_R_chi,       "chi/F" );		 branch->SetAutoDelete(kFALSE);

	sensorsTree = std::vector<TTree *>();
	for(Int_t i = 0; i < m_layersNumber; i++){
		TString name = "Sensor_";
		name += i;
		sensorsTree.push_back( new TTree(name,name) );
			branch = sensorsTree.back()->Branch("real",     &v_S_real,     "real/F" );	 branch->SetAutoDelete(kFALSE);
			branch = sensorsTree.back()->Branch("blurry",   &v_S_blurry,   "blurry/F" );	 branch->SetAutoDelete(kFALSE);
			branch = sensorsTree.back()->Branch("observed", &v_S_observed, "observed/O" );	 branch->SetAutoDelete(kFALSE);
			branch = sensorsTree.back()->Branch("measured", &v_S_measured, "measured/F" );	 branch->SetAutoDelete(kFALSE);
			branch = sensorsTree.back()->Branch("isReco",   &v_S_isReco,   "isReco/O" );	 branch->SetAutoDelete(kFALSE);
			branch = sensorsTree.back()->Branch("recoVal",  &v_S_recoVal,  "recoVal/F" );	 branch->SetAutoDelete(kFALSE);
	}
}

MakeTrees::~MakeTrees(){
	//~ delete tracksTree;
	//~ delete recoTree;
	//~ for( Int_t i = 0; i<m_layersNumber; i++){
		//~ delete sensorsTree[i];
	//~ }	
}

void MakeTrees::Write(){
	tracksTree->Write();
	recoTree->Write();
	for( Int_t i = 0; i<m_layersNumber; i++){
		sensorsTree[i]->Write();
	}
	
	output->Write();
	output->Close();
}
	
void MakeTrees::Print(){
	tracksTree->Print();
	recoTree->Print();
	for( Int_t i = 0; i<m_layersNumber; i++){
		sensorsTree[i]->Print();
	}
}

void MakeTrees::Fill(ParticleSource const & source, Reconstruction const & reconstructor, std::vector<SensorRes> const & eventResults){
	v_T_x0  = source.x0();
	v_T_y0  = source.y0();
	v_T_t0  = source.t0();		
	v_T_tan = source.tan();
	v_T_off = source.off();
	tracksTree->Fill();

	v_R_reco      = reconstructor.isReco();
	v_R_nPoints   = reconstructor.getNPoints();		
	v_R_slope     = reconstructor.getSlope();
	v_R_offset    = reconstructor.getOffset();
	v_R_slopeErr  = reconstructor.getSlopeErr();
	v_R_offsetErr = reconstructor.getOffsetErr();					
	v_R_chi       = reconstructor.getChi();
	v_R_theta     = reconstructor.getTheta();
	v_R_thetaErr  = reconstructor.getThetaErr();
	recoTree->Fill();
	
	for( Int_t i = 0; i<m_layersNumber; i++){
		v_S_real     = eventResults[i].GetReal();
		v_S_blurry   = eventResults[i].GetBlurry();	
		v_S_observed = eventResults[i].GetObserved();	
		v_S_measured = eventResults[i].GetMeasured();			
		v_S_isReco   = eventResults[i].GetIsReco();		
		v_S_recoVal  = eventResults[i].GetRecoVal();	
		sensorsTree[i]->Fill();	
	}
}

