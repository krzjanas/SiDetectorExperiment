#include "../Headers/VisEvent.hpp"

#include <TString.h>

VisEvent::VisEvent(Int_t f_evNum): conf(ConfigureSiDet()), evNum(f_evNum),
	hLeft(-conf.firstLayer), hRight(conf.firstLayer+conf.layersNumber*conf.deltaLayer), hUp(conf.acceptance*1.25), hDown(-hUp),
	can(0), coordianteHistogram(0)
{
	TString tmpN = "cVisualisationEvent";
	tmpN += evNum;
	TString tmpT = "Visualisation for Event ";
	tmpT += evNum;
	
	can = new TCanvas(tmpN, tmpT,1200,800);
	can->SetGrid();
	tmpN[0]='h';
	coordianteHistogram = new TH2D(tmpN,tmpT,100,hLeft,hRight,100,hDown,hUp);
	coordianteHistogram->SetStats(0);
	coordianteHistogram->GetXaxis()->SetTitle("z [mm]");
	coordianteHistogram->GetYaxis()->SetTitle("y [mm]");
	coordianteHistogram->GetXaxis()->CenterTitle();
	coordianteHistogram->GetYaxis()->CenterTitle();
	coordianteHistogram->Draw();
	
	originLines.push_back(new TLine(0.0,hDown,0.0,hUp));
	originLines.push_back(new TLine(hLeft,0.0,hRight,0.0));
	for(UInt_t i = 0; i<originLines.size(); i++){
		originLines[i]->SetLineColor(1);
		originLines[i]->SetLineStyle(1);
		originLines[i]->SetLineWidth(1);
		originLines[i]->Draw();
	}
}

void VisEvent::drawSensors(){
	can->cd();
	
	for(Int_t i = 0; i<conf.layersNumber; i++){
		sensorLines.push_back(new TLine(conf.firstLayer+i*conf.deltaLayer, -conf.acceptance, conf.firstLayer+i*conf.deltaLayer, conf.acceptance));
	}
	
	for(UInt_t i = 0; i<sensorLines.size(); i++){
		sensorLines[i]->SetLineColor(kGray+1);
		sensorLines[i]->SetLineStyle(1);
		sensorLines[i]->SetLineWidth(4);
		sensorLines[i]->Draw();
	}	
	
}

void VisEvent::drawInitialBorder(){
	can->cd();
	
	initialBorders.push_back(new TLine(conf.parX1,conf.parY1,conf.parX2,conf.parY1));
	initialBorders.push_back(new TLine(conf.parX1,conf.parY2,conf.parX2,conf.parY2));
	initialBorders.push_back(new TLine(conf.parX1,conf.parY1,conf.parX1,conf.parY2));
	initialBorders.push_back(new TLine(conf.parX2,conf.parY1,conf.parX2,conf.parY2));
	
	if(conf.optSo[0] == 'U' || conf.optSo[0] == 'u'){
		initialBorders[2]->SetLineStyle(1);
		initialBorders[3]->SetLineStyle(1);
	} else {
		initialBorders[2]->SetLineStyle(2);
		initialBorders[3]->SetLineStyle(2);
	}		
	
	if(conf.optSo[1] == 'U' || conf.optSo[1] == 'u'){
		initialBorders[0]->SetLineStyle(1);
		initialBorders[1]->SetLineStyle(1);
	} else {
		initialBorders[0]->SetLineStyle(2);
		initialBorders[1]->SetLineStyle(2);
	}		
	
	for(UInt_t i = 0; i<initialBorders.size(); i++){
		initialBorders[i]->SetLineColor(kRed-4);
		initialBorders[i]->SetLineWidth(2);
		initialBorders[i]->Draw();
	}		
}

void VisEvent::drawInitialPoint(Float_t x0, Float_t y0){
	can->cd();
	
	initialPoint.push_back(new TMarker(x0,y0,24));
	initialPoint.push_back(new TMarker(x0,y0,7));
	initialPoint.push_back(new TMarker(x0,y0,5));
	for(UInt_t i = 0; i<initialPoint.size(); i++){
		initialPoint[i]->SetMarkerColor(kRed-4);
		initialPoint[i]->SetMarkerSize(3);
		initialPoint[i]->Draw();
	}		
	
}

void VisEvent::drawTracks(Float_t x0, Float_t y0, Float_t offO, Float_t tgO, Bool_t reco, Float_t offN, Float_t tgN){
	can->cd();
	
	if( hRight*tgO+offO-y0 > hUp ){
		trackLines.push_back(new TLine(0.0,offO,(hUp-y0)/tgO,hUp));
	} else if ( (hRight - x0)*tgO+y0 < hDown ){
		trackLines.push_back(new TLine(0.0,offO,(hDown-y0)/tgO,hDown));
	} else {
		trackLines.push_back(new TLine(0.0,offO,hRight,(hRight-x0)*tgO+y0));
	}
	trackLines[0]->SetLineColor(kRed);
	trackLines[0]->SetLineStyle(1);
	
	
	if( reco ){
		if( hRight*tgN+offN > hUp ){
			trackLines.push_back(new TLine(0.0,offN,(hUp-offN)/tgN,hUp));
		} else if ( hRight*tgN+offN < hDown ){
			trackLines.push_back(new TLine(0.0,offN,(hDown-offN)/tgN,hDown));	
		} else {
			trackLines.push_back(new TLine(0.0,offN,hRight,hRight*tgN+offN));
		}
		trackLines.back()->SetLineColor(kGreen+2);
		trackLines.back()->SetLineStyle(1);		
	}
	
	if( x0 < 0 ){
		trackLines.push_back(new TLine(x0,y0,0.0,offO));
		trackLines.back()->SetLineColor(kRed);
		trackLines.back()->SetLineStyle(2);
	}
	
	for(UInt_t i = 0; i<trackLines.size(); i++){
		trackLines[i]->SetLineWidth(2);
		trackLines[i]->Draw(); 
	}
	
	
}

void VisEvent::drawSensorCrossing(Int_t senNum, SensorRes senRes){
	can->cd();

	Float_t xx0 = conf.firstLayer+senNum*conf.deltaLayer - 0.5;
	Float_t xxk = conf.firstLayer+senNum*conf.deltaLayer + 0.5;
	
	UInt_t beginVec = sensorCrossingLine.size(); 
	
	
	if( senRes.GetReal() < conf.acceptance && senRes.GetReal() > -conf.acceptance ){
		sensorCrossingLine.push_back(new TLine(xx0, senRes.GetReal(), xxk, senRes.GetReal()));
		sensorCrossingMarker.push_back(new TMarker((xx0+xxk)/2.0, senRes.GetReal(),5));
		sensorCrossingLine.back()->SetLineColor(kRed);
		sensorCrossingMarker.back()->SetMarkerColor(kRed);
	}
	if( senRes.GetBlurry() < conf.acceptance && senRes.GetBlurry() > -conf.acceptance ){
		sensorCrossingLine.push_back(new TLine(xx0, senRes.GetBlurry(), xxk, senRes.GetBlurry()));
		sensorCrossingMarker.push_back(new TMarker((xx0+xxk)/2.0, senRes.GetBlurry(),5));
		sensorCrossingLine.back()->SetLineColor(kOrange+2);
		sensorCrossingMarker.back()->SetMarkerColor(kOrange+2);
	}	
	if( senRes.GetObserved() ){
		sensorCrossingLine.push_back(new TLine(xx0, senRes.GetMeasured(), xxk, senRes.GetMeasured()));
		sensorCrossingMarker.push_back(new TMarker((xx0+xxk)/2.0, senRes.GetMeasured(),5));
		sensorCrossingLine.back()->SetLineColor(kCyan+2);
		sensorCrossingMarker.back()->SetMarkerColor(kCyan+2);
	}	
	if( senRes.GetIsReco() ){
		sensorCrossingLine.push_back(new TLine(xx0, senRes.GetRecoVal(), xxk, senRes.GetRecoVal()));
		sensorCrossingMarker.push_back(new TMarker((xx0+xxk)/2.0, senRes.GetRecoVal(),5));
		sensorCrossingLine.back()->SetLineColor(kGreen+2);
		sensorCrossingMarker.back()->SetMarkerColor(kGreen+2);
	}	
	
	for(UInt_t i = beginVec; i < sensorCrossingLine.size(); i++){
		sensorCrossingLine[i]->SetLineStyle(1);
		sensorCrossingLine[i]->SetLineWidth(1);
		sensorCrossingLine[i]->Draw();
		sensorCrossingMarker[i]->SetMarkerSize(7);
		sensorCrossingMarker[i]->Draw();
	}
	
}

void VisEvent::drawLegend(){
	can->cd();
	
	legend = new TLegend(0.91,0.4,0.99,0.9);
	legend->SetHeader("The Legend:");
	if(sensorLines.size() > 0 ){
		legend->AddEntry(sensorLines[0], "Sensor","L");
	}	
	if(initialPoint.size() > 0 ){
		markLeg.push_back(new TMarker(0.0, 0.0,24));
		markLeg.back()->SetMarkerColor(kRed-4);
		markLeg.back()->SetMarkerSize(1);
		legend->AddEntry(markLeg.back(), "Initial Point","PM");
	}	
	if(trackLines.size() > 0){
		legend->AddEntry(trackLines[0], "Real Track","L");
		legend->AddEntry(trackLines[1], "Reco Track","L");
	}
	if(sensorCrossingMarker.size() > 0){
		markLeg.push_back(new TMarker(0.0, 0.0,5));
		markLeg.back()->SetMarkerColor(kRed);
		legend->AddEntry(markLeg.back(), "CP: Real","MP");
		markLeg.push_back(new TMarker(0.0, 0.0,5));	
		markLeg.back()->SetMarkerColor(kOrange+2);
		legend->AddEntry(markLeg.back(), "CP: Blurry","MP");		
		markLeg.push_back(new TMarker(0.0, 0.0,5));
		markLeg.back()->SetMarkerColor(kCyan+2);
		legend->AddEntry(markLeg.back(), "CP: Measured","PM");	
		markLeg.push_back(new TMarker(0.0, 0.0,5));
		markLeg.back()->SetMarkerColor(kGreen+2);
		legend->AddEntry(markLeg.back(), "CP: Reco","MP");
	}
	
	legend->Draw();
	
}

void VisEvent::printVis(TString const & outputName){
	can->Print(outputName);
}
