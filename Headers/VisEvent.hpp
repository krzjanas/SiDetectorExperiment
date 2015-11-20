#ifndef VisEvent_hpp
#define VisEvent_hpp

#include <vector>
#include <TCanvas.h>
#include <TH2D.h>

#include <TLine.h>
#include <TMarker.h>
#include <TLegend.h>

#include "../ConfigureSiDet.hpp"
#include "SensorRes.hpp"

class VisEvent{
	private:	
		ConfigureSiDet conf;
	
		Int_t const evNum;
		Float_t const hLeft;
		Float_t const hRight;
		Float_t const hUp;
		Float_t const hDown;

		TCanvas * can;
		TH2D	* coordianteHistogram;
		std::vector<TLine *> originLines;
		
		std::vector<TLine *> sensorLines;
		std::vector<TLine *> initialBorders;
		
		std::vector<TMarker *> initialPoint;
		
		std::vector<TLine *> trackLines;
		
		std::vector<TLine *> sensorCrossingLine;
		std::vector<TMarker *> sensorCrossingMarker;
		
		TLegend * legend;
		std::vector<TMarker *> markLeg;
	
	public:
	
		VisEvent(Int_t const f_evNum);
	
		void drawSensors();
		void drawInitialBorder();
		void drawInitialPoint(Float_t x0, Float_t y0);
		void drawTracks(Float_t x0, Float_t y0, Float_t offO, Float_t tgO, Bool_t reco, Float_t offN, Float_t tgN);
		void drawSensorCrossing(Int_t senNum, SensorRes senRes);
		
		void drawLegend();
		
		void printVis(TString const & outputName);
};

#endif
