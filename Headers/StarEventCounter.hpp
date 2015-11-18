#ifndef StarEventCounter_hpp
#define StarEventCounter_hpp

#include <ostream>
#include <string>

class StarEventCounter{
	private:
		const int m_maxEvent;
		const int m_steps;
		const int m_eventsInStep;
		
		void m_doStep(int const currentStep) const;
		
	public:
		StarEventCounter(int const f_maxEvent, int const f_steps) : m_maxEvent(f_maxEvent), m_steps(f_steps), m_eventsInStep(f_maxEvent/f_steps) {};
	
		void beforeLoop(std::string const & headline = "PROGRESS") const;			
		void afterLoop(std::string const & headline  = "FINISHED") const;
		
		void isStep(int const currentEvent) const
			{ if( !(currentEvent % m_eventsInStep) )  m_doStep( currentEvent / m_eventsInStep ); };
			
		void operator() (int const currentEvent) const 
			{ if( !(currentEvent % m_eventsInStep) )  m_doStep( currentEvent / m_eventsInStep ); };
};

void StarEventCounter::beforeLoop(std::string const & headline) const{
	
	int half1 = ( m_steps + 16 - headline.size() - 2 );
	int half2;
	if( half1 % 2 ){
		half1 = half1 / 2 + 1;
		half2 = half1;
	} else {
		half1 = half1 / 2 + 1;
		half2 = half1 - 1;
	}
	std::cout << std::endl;
	for(int i = 0; i<half1; i++){
		std::cout << "-";
	}
	std::cout << " " << headline << " ";
	for(int i = 0; i<half2; i++){
		std::cout << "-";
	}	
	std::cout << std::endl;
}

void StarEventCounter::m_doStep(int const currentStep) const {
	
	std::cout << "\r" ;
	std::cout << "|" ; 
	for(int i = 0; i<currentStep; i++){
		std::cout << "*";
	}
	std::cout << ">" ;
	for(int i = currentStep; i<m_steps-1; i++){
		std::cout << "_";
	}
	std::cout << "|";
	std::cout << " Complete ";
	std::cout.width( 3 );
	std::cout << 100*currentStep/m_steps;
	std::cout << "%";
	std::cout << std::flush;
}
	
void StarEventCounter::afterLoop(std::string const & headline) const{
	std::cout << "\r" ;
	std::cout << "|" ; 
	for(int i = 0; i<m_steps; i++){
		std::cout << "*";
	}
	std::cout << "| Complete  100%";
	beforeLoop(headline);
	std::cout << std::endl;
}

/*

************* PROGRESS **************
|-------->____________| Complete  45%
************* FINISHED **************

*/




#endif
