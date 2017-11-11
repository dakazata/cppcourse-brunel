#ifndef SIMULATION_H
#define SIMULATION_H

/*!
 * \file Simulation.hpp
 * \brief Simulation class
 * \author Daniella Zarza
 */
 
#include "Constants.hpp"
#include "Network.hpp"

/*!
 * \class Simulation
 * \brief Class takes care of simulating the network 
 */

class Simulation
{
	public:
		
		//! constructor
		/*!
		 * \brief Initiates simulation by default
		 */	
		Simulation();
		
		//! Destructor
		/*!
		 * \brief destroys simulation by default
		 */	
		~Simulation() = default;
	
		//! Runs the simulation
		/*!
		 *  Takes care of creating a pointer towards a network. Then it
		 *  creates the targets in the network and launches a sequence 
		 * 	network updates. Finally it writes onto an external file
		 */	
		void run();
};



#endif
