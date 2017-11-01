#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Neuron.hpp"
#include "Constants.hpp"

class Network
{
	private:
		int nb_neurons_;
		std::vector<Neuron*> neurons_; 		//stores neurons in the network
		
	public:
		//Constructor
		Network(int totalneurons);
		
		//Destructor
		~Network();
		
		//add a neuron to the vector neurons_
		//void addNeuron(Neuron* neuron);
		
		void makeTargets();
		
		void setExternalCurrent(double current);
		
		//update
		void update(unsigned int time, unsigned int steps, double current);

};


#endif

