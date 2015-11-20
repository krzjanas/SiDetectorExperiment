#ifndef VisEvent_hpp
#define VisEvent_hpp

#include <TCanvas.h>

class VisEvent{
	private:	
		Int_t const evNum;

		TCanvas * can;
	
	public:
	
		VisEvent(Int_t const f_evNum);
	
};

#endif
