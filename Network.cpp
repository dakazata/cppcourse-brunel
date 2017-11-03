#include "Network.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <random>

using namespace std;


///CONSTRUCTOR

Network::Network(int totalneurons)
	: nb_neurons_(totalneurons),
	  spike_times_(),
	  neuron_idx_(),
	  targets_(N_TOTAL , vector<unsigned int>(0))
	  
{
	cout << "Creating network" << endl;
	///Fill up network...
	///...with excitatory neurons
	for (int i(0) ; i < (nb_neurons_ * 0.8) ; i++)
	{
		Neuron* n = new Neuron(i + 1 , "excitatory");
		addNeuron(n);
		assert (i < N_EXCITATORY);
	}
	
	///...and with inhibitory neurons
	for (int i(0) ; i < (nb_neurons_ * 0.2) ; i++)
	{
		Neuron* n = new Neuron(i + 10000, "inhibitory");
		addNeuron(n);
		assert(i < N_INHIBITORY);
	}
	
	///Sets external current 
	setExternalCurrent(0.0);
	
	assert (neurons_.size() == N_TOTAL);
}
	
///Destructor
Network::~Network()
{
	for (auto& n : neurons_)
	{
		delete n;
		n = nullptr;
	}
}

///GETTERS

vector<Neuron*> Network::getNeurons() const
{
	return neurons_;
}

vector<unsigned int> Network::getIndices() const
{
	return neuron_idx_;
}

vector<vector<unsigned int>> Network::getTargets() const
{
	return targets_;
}

///SPECIFIC NETWORK FUNCTIONS

void Network::addNeuron(Neuron* neuron)
{
	assert(neuron != nullptr);
	neurons_.push_back(neuron);
}

void Network::setExternalCurrent(double current)
{
	for (auto& n: neurons_)
	{
		n->setCurrent(current);
	}
}

void Network::makeTargets()
{
	cout << "Making targets ... " << endl;
	
	///Random generator 
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disE(0 , N_EXCITATORY -1);
	uniform_int_distribution<> disI(N_EXCITATORY,N_TOTAL -1);
	
	///Generate C_TOTAL connections for each neuron in the network
	for (size_t source(0); source < nb_neurons_ ; source++)
	{
		for (size_t i(0) ; i < C_EXCITATORY ; i++)
		{
			auto indice = disE(gen);
			targets_[indice].push_back(source);
			assert(targets_[indice].size() > 0);
		}	
		
		for (size_t i(0) ; i < C_INHIBITORY ; i++)
		{
			int indice = disI(gen);
			targets_[indice].push_back(source);
			assert(targets_[indice].size() > 0);
		}	
		
	}
	cout << "Finished making targets..." << endl;
}

void Network::writeFile() const
{
	cout << "Writing to file... " << endl;
	
	///Creation and opening of external file
	ofstream textfile;
	textfile.open("Spike_Times.txt");	
	
	assert(spike_times_.size() == neuron_idx_.size());
	
	for (size_t i(0) ; i < spike_times_.size() ; i++)
	{
		textfile << spike_times_[i] << '\t' << neuron_idx_[i] << '\n' ;
	}
	
	/*
	///NELVE LE
	for (size_t i(0) ; i< neurons_.size(); i+=100)
	{
		textfile << neurons_[i]->getNbSpikes() << endl;
	}*/
	
	///Closing of external file
	textfile.close();
}

///UPDATE FUNCTION

void Network::update(unsigned int simulation_steps)
{
	cout << "Updating Network ..." << endl;
	
	unsigned int steps_made(0);
	bool spike(false);
	
	while(steps_made < simulation_steps)
	{
		assert(!neurons_.empty());
		
		///We go through every neuron in the network at every step
		for (size_t i (0); i < neurons_.size(); i++)
		{	
			assert(neurons_[i] != nullptr);
		
			spike = neurons_[i]->update(1); //current is normally 0 when we update network
			
			///If neuron spikes ...
			if (spike)
			{	
				///...we go through each of its targets...
				for (auto& t :targets_[i])
				{
					///...ad we send a spike
					neurons_[t]->receive(steps_made + D_STEPS , neurons_[t]->getJ());
				}
				
				///Keeps track of spikes and corresponding neurn IDs
				spike_times_.push_back(steps_made *H);
				neuron_idx_.push_back(i);
			}
		}			
		
		///Increments steps
		++steps_made;
	}
}


