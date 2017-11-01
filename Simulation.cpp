#include "Simulation.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Simulation::Simulation()
	:simulation_time_(0)
{}

void Simulation::run()
{
	//create network
	Network net(N_TOTAL);
	
	//create targets
	net.makeTargets();
	
	cout << "Running simulation ... " << endl;
	
	while (simulation_time_ * H < SIM_END_TIME)
	{
		//cout << "Time: " << simulation_time_ * H << endl;	
		
		//update la network a chaque increment de temps de sim
		net.update(simulation_time_ , 1 , 0.0); //on fait un step et on donne un i_Ext de 0.0
		
		simulation_time_++;
	}
	
	net.writeFile();
	
}


