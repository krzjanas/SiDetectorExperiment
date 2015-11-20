#include "../Headers/VisEvent.hpp"

#include <TString.h>

VisEvent::VisEvent(Int_t f_evNum): evNum(f_evNum), can(0){
	TString tmpN = "VisualisationEvent";
	tmpN += evNum;
	TString tmpT = "Visualisation for Event ";
	tmpT += evNum;
	
	can = new TCanvas(tmpN, tmpT);
	
}
