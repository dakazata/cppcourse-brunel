#include "Simulation.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Simulation::Simulation()
{}

void Simulation::run()
{
	///Creation of network
	Network* net = new Network(N_TOTAL);
	
	///Creation of targets in the network
	net->makeTargets();
	
	//cout << "Running simulation ... " << endl;
	
	///Launches the network updates
	net->update(SIM_END_TIME / H);
	
	///Writes onto an external file
	net->writeFile();
	
}


