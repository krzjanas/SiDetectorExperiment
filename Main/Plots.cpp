#include <iostream>

#include <TMath.h>
#include <TCanvas.h>
#include <TH1D.h>

#include "../Tree/ReadTrees.hpp"
#include "../ConfigureSiDet.hpp"
#include "../Headers/StarEventCounter.hpp"

using namespace std;

Int_t main(){
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Parameters
		
	ConfigureSiDet const conf = ConfigureSiDet();
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Read Event	
	
	ReadTrees trees = ReadTrees("Tree/ResultsTrees.root", conf.layersNumber);
	
	// ------------------------------------------------------------------------------------------------------------------------------- //
	// Hitograms
	
	TH1D * hRealParamOff = new TH1D("hRealParamOff","Offset Distribution",100, -4,4);
	hRealParamOff->SetMinimum(0);
	hRealParamOff->SetStats(0);
	hRealParamOff->GetXaxis()->SetTitle("offset y [mm]");
	hRealParamOff->GetYaxis()->SetTitle("entires");
	hRealParamOff->SetLineColor(2);
	hRealParamOff->SetLineWidth(2);
	TH1D * hRecoParamOff = new TH1D("hRecoParamOff","Offset Distribution",100, -4,4);
	hRecoParamOff->SetLineColor(4);
	hRecoParamOff->SetLineWidth(2);	
	TH1D * hRealParamTan = new TH1D("hRealParamTan","Slope Distribution" ,100, -2,2);
	hRealParamTan->SetMinimum(0);
	hRealParamTan->SetStats(0);
	hRealParamTan->GetXaxis()->SetTitle("slope [1]");
	hRealParamTan->GetYaxis()->SetTitle("entires");
	hRealParamTan->SetLineColor(2);
	hRealParamTan->SetLineWidth(2);	
	TH1D * hRecoParamTan = new TH1D("hRecoParamTan","Slope Distribution" ,100, -2,2);
	hRecoParamTan->SetLineColor(4);
	hRecoParamTan->SetLineWidth(2);
		
	TH1D * hRecoErrorOff = new TH1D("hRecoErrorOff","Reco Error Offset Distribution",100, 0,2);
	hRecoErrorOff->SetMinimum(0);
	hRecoErrorOff->GetXaxis()->SetTitle("offset error [mm]");
	hRecoErrorOff->GetYaxis()->SetTitle("entires");	
	hRecoErrorOff->SetLineColor(4);
	hRecoErrorOff->SetLineWidth(2);	
	TH1D * hRecoErrorTan = new TH1D("hRecoErrorOff","Reco Error Slope Distribution" ,100, 0,0.03);
	hRecoErrorTan->SetMinimum(0);
	hRecoErrorTan->GetXaxis()->SetTitle("slope error [1]");
	hRecoErrorTan->GetYaxis()->SetTitle("entires");	
	hRecoErrorTan->SetLineColor(4);
	hRecoErrorTan->SetLineWidth(2);
			
	TH1D * hPullOff = new TH1D("hPullOff","Pull Offset Distribution",100, -3,3);
	hPullOff->SetMinimum(0);
	hPullOff->GetXaxis()->SetTitle("pull");
	hPullOff->GetYaxis()->SetTitle("entires");	
	hPullOff->SetLineColor(4);
	hPullOff->SetLineWidth(2);
			
	TH1D * hPullTan = new TH1D("hPullTan","Pull Slope Distribution" ,100, -3,3);
	hPullTan->SetMinimum(0);
	hPullTan->GetXaxis()->SetTitle("pull");
	hPullTan->GetYaxis()->SetTitle("entires");	
	hPullTan->SetLineColor(4);
	hPullTan->SetLineWidth(2);

	TH1D * hChi2 = new TH1D("hChi2","#chi^{2} Distribution" ,100, 0,1);
	hChi2->SetMinimum(0);
	hChi2->GetXaxis()->SetTitle("#chi^{2}");
	hChi2->GetYaxis()->SetTitle("entires");	
	hChi2->SetLineColor(4);
	hChi2->SetLineWidth(2);
	
	TH1D * hPullRecoVsReal[conf.layersNumber];
	TH1D * hPullRecoVsBlurry[conf.layersNumber];
	TH1D * hPullRealVsBlurry[conf.layersNumber];
	TH1D * hPullBlurryVsObserved[conf.layersNumber];
	
	for(Int_t id = 0; id < conf.layersNumber; id++){
		hPullRecoVsReal[id] = new TH1D(TString::Format("hPullRcRl%d",id),TString::Format("Pull Reco vs Real - Sensor %d",id),100, -3,3);
		hPullRecoVsReal[id]->SetMinimum(0);
		hPullRecoVsReal[id]->GetXaxis()->SetTitle("pull");
		hPullRecoVsReal[id]->GetYaxis()->SetTitle("entires");	
		hPullRecoVsReal[id]->SetLineColor(4);
		hPullRecoVsReal[id]->SetLineWidth(2);	
	
		hPullRecoVsBlurry[id] = new TH1D(TString::Format("hPullRcBl%d",id),TString::Format("Pull Reco vs Blurry - Sensor %d",id),100, -3,3);
		hPullRecoVsBlurry[id]->SetMinimum(0);
		hPullRecoVsBlurry[id]->GetXaxis()->SetTitle("pull");
		hPullRecoVsBlurry[id]->GetYaxis()->SetTitle("entires");	
		hPullRecoVsBlurry[id]->SetLineColor(4);
		hPullRecoVsBlurry[id]->SetLineWidth(2);	
	
		hPullRealVsBlurry[id] = new TH1D(TString::Format("hPullRlBl%d",id),TString::Format("Pull Real vs Blurry - Sensor %d",id),100, -3,3);
		hPullRealVsBlurry[id]->SetMinimum(0);
		hPullRealVsBlurry[id]->GetXaxis()->SetTitle("pull");
		hPullRealVsBlurry[id]->GetYaxis()->SetTitle("entires");	
		hPullRealVsBlurry[id]->SetLineColor(4);
		hPullRealVsBlurry[id]->SetLineWidth(2);		
		
		hPullBlurryVsObserved[id] = new TH1D(TString::Format("hPullBlOb%d",id),TString::Format("Pull Blurry vs Observed - Sensor %d",id),100, -3,3);
		hPullBlurryVsObserved[id]->SetMinimum(0);
		hPullBlurryVsObserved[id]->GetXaxis()->SetTitle("pull");
		hPullBlurryVsObserved[id]->GetYaxis()->SetTitle("entires");	
		hPullBlurryVsObserved[id]->SetLineColor(4);
		hPullBlurryVsObserved[id]->SetLineWidth(2);		
	}
	
	
	StarEventCounter stepper = StarEventCounter( conf.maxEvents, conf.stepsInLoop);
	stepper.beforeLoop();	
	for(Int_t i = 0; i< trees.GetEntries(); i++){
		stepper(i);		
		trees.GetEntry(i);

		if( trees.reco->reco ){
			hRealParamOff->Fill(trees.tracks->off);
			hRecoParamOff->Fill(trees.reco->offset);
			hRealParamTan->Fill(trees.tracks->tan);
			hRecoParamTan->Fill(trees.reco->slope);
			hRecoErrorOff->Fill(trees.reco->offsetErr);
			hRecoErrorTan->Fill(trees.reco->slopeErr);
			hPullOff->Fill((trees.tracks->off-trees.reco->offset)/trees.reco->offsetErr);
			hPullTan->Fill((trees.tracks->tan-trees.reco->slope)/trees.reco->slopeErr);
			
			hChi2->Fill(trees.reco->chi);
			
			for(Int_t id = 0; id < conf.layersNumber; id++){
				if(trees.sensors[id]->isReco){
					hPullRecoVsReal[id]->Fill( (trees.sensors[id]->recoVal - trees.sensors[id]->real)/trees.sensors[id]->recoErr );
					hPullRecoVsBlurry[id]->Fill( (trees.sensors[id]->recoVal - trees.sensors[id]->blurry)/
												TMath::Hypot(trees.sensors[id]->recoErr, conf.pixelSize) );
				}
				if( trees.sensors[id]->real < conf.acceptance && trees.sensors[id]->blurry < conf.acceptance &&
				    trees.sensors[id]->real > -conf.acceptance && trees.sensors[id]->blurry > -conf.acceptance){
					hPullRealVsBlurry[id]->Fill( (trees.sensors[id]->real - trees.sensors[id]->blurry) / conf.pixelSize );
				}
				if(trees.sensors[id]->observed){
					hPullBlurryVsObserved[id]->Fill( (trees.sensors[id]->blurry - trees.sensors[id]->measured) / conf.pixelSize );
				}

				
			}			
		}
	}
	stepper.afterLoop();
	
	TCanvas * canParam = new TCanvas("canParam","Parameters",1200,750);
	canParam->Divide(2,1);
	canParam->cd(1);
	hRealParamOff->Draw();
	hRecoParamOff->Draw("SAME");
	canParam->cd(2);
	hRealParamTan->Draw();
	hRecoParamTan->Draw("SAME");
	canParam->Print("Vis/Parameters.png");	
	canParam->cd(1);
	hRecoErrorOff->Draw();
	canParam->cd(2);
	hRecoErrorTan->Draw();
	canParam->Print("Vis/Errors.png");	
	canParam->cd(1);
	hPullOff->Draw();
	canParam->cd(2);
	hPullTan->Draw();
	canParam->Print("Vis/Puls.png");
	
	TCanvas * canChi2 = new TCanvas("canChi2","Chi2",1200,750);
	hChi2->Draw();
	canChi2->Print("Vis/Chi2.png");
	
	TCanvas * canSensors = new TCanvas("canSensors","Sensors",1200,700);
	canSensors->Divide(2,2);
	for(Int_t id = 0; id < conf.layersNumber; id++){
		canSensors->cd(1);
		hPullRecoVsReal[id]->Draw();
		canSensors->cd(2);
		hPullRecoVsBlurry[id]->Draw();
		canSensors->cd(3);
		hPullRealVsBlurry[id]->Draw();
		canSensors->cd(4);
		hPullBlurryVsObserved[id]->Draw();
		canSensors->Print(TString::Format("Vis/Sensor_%d.png",id));
	}
	
	return 0;
}
