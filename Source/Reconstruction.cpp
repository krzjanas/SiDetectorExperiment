#include "../Headers/Reconstruction.hpp"

#include <ostream>

#include <TGraphErrors.h>
#include <TF1.h>
#include <TFitResultPtr.h>
#include <TCanvas.h>
#include <TH2D.h>

Reconstruction::Reconstruction(Int_t const f_layersNumber, Float_t const f_firstLayer, Float_t const f_deltaLayer, Float_t const f_pixelSize )

	: m_layersNumber(f_layersNumber), m_firstLayer(f_firstLayer), m_deltaLayer(f_deltaLayer), m_pixelError( f_pixelSize / 3.464101615 ) ,
	
	m_reco(kFALSE), m_nPoints(0), m_slope(0.0), m_offset(0.0), m_slopeErr(0.0), m_offsetErr(0.0), m_chi(0.0)
{
	
}

void Reconstruction::doReconstruction( std::vector<SensorRes> & results){
	
	m_nPoints = 0;
	for(UInt_t i = 0; i < results.size(); i++){
		if( results[i].GetObserved() ) m_nPoints++;
	}
	
	if( m_nPoints > 2 ){
		
		m_reco = kTRUE;
		
		std::vector<Float_t> xxx, yyy;
		
		TGraphErrors * graph = new TGraphErrors( m_nPoints );
		Int_t idPoint = 0;
		for(UInt_t i = 0; i < results.size(); i++){
			if( results[i].GetObserved() ){
				
				xxx.push_back(m_firstLayer + i * m_deltaLayer);
				yyy.push_back(results[i].GetMeasured());
								
				graph->SetPoint(idPoint, m_firstLayer + i * m_deltaLayer, results[i].GetMeasured());
				graph->SetPointError(idPoint, 0.0, m_pixelError);
				idPoint++;
			}
		}
		
		linearFit(xxx,yyy);
					
		TF1 * fit = new TF1("fit","pol1",0.0,m_firstLayer + m_layersNumber * m_deltaLayer);
		graph->Fit("fit","WQ");		
		fit = graph->GetFunction("fit");
		
		m_chi       = fit->GetChisquare(); 
		m_slope     = fit->GetParameter(1); 
		m_slopeErr  = fit->GetParError(1); 
		m_offset    = fit->GetParameter(0); 
		m_offsetErr = fit->GetParError(0); 

		for(UInt_t i = 0; i < results.size(); i++){
			if( results[i].GetObserved() ) results[i].SetReco( m_slope * ( m_firstLayer + i*m_deltaLayer ) + m_offset );
		}
				
		delete fit;
		delete graph;
		
	} else { 
		m_reco = kFALSE;
		m_slope = 9999.0;
		m_offset = 9999.0;
		m_slopeErr = 9999.0;
		m_offsetErr = 9999.0;		
		m_chi = 9999.0;	
	}
	
}
		

void Reconstruction::linearFit(std::vector<Float_t> const & xi, std::vector<Float_t> const & yi){
	
	Float_t S = 0;
	Float_t S_x = 0;
	Float_t S_y = 0;
	Float_t S_xx = 0;
	Float_t S_xy = 0;
	Float_t S_yy = 0;
	
	for(UInt_t i = 0; i<xi.size(); i++){
		S += 1;
		S_x += xi[i];
		S_y += yi[i];
		S_xx += xi[i] * xi[i];
		S_xy += xi[i] * yi[i];
		S_yy += yi[i] * yi[i];
	}
	
	Float_t D = S*S_xx - S_x*S_x;
	
	Float_t a = ( S*S_xy - S_x*S_y )/D;
	Float_t b = ( S_xx*S_y - S_x*S_xy )/D;
	
	Float_t dy2 = S_yy - a*S_xy - b*S_y;
	
	Float_t da2 = S/(S - 2) * dy2/D;
	Float_t db2 = da2 * S_xx/S;

	
	
	m_chi       = dy2 / m_pixelError / m_pixelError; 
	m_slope     = a; 
	m_slopeErr  = TMath::Sqrt(da2); 
	m_offset    = b; 
	m_offsetErr = TMath::Sqrt(db2); 
	
}
		
