#include "Simulation.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Simulation::Simulation()
{}

void Simulation::run()
{
	//create network
	Network net(N_TOTAL);
	
	//create targets
	net.makeTargets();
	
	cout << "Running simulation ... " << endl;
	
	net.update(SIM_END_TIME / H);
	
	net.writeFile();
	
}


