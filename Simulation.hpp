#ifndef SIMULATION_H
#define SIMULATION_H

#include "Constants.hpp"
#include "Network.hpp"

class Simulation
{
	private:
		int simulation_time_;
		
	public:
	
		Simulation();
		~Simulation() = default;
	
		void run();
	
	
};



#endif
