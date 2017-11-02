#include "Network.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <random>

using namespace std;


//Constructor
Network::Network(int totalneurons)
	: nb_neurons_(totalneurons),
	  spike_times_(),
	  neuron_idx_(),
	  targets_(N_TOTAL, vector<unsigned int> ())
{
	cout << "Ceating network" << endl;
	///remplissage avec neurones excitatoires et inhibitoires
	//boucle se parcout N_EXCIT fois
	for (int i(0) ; i < (nb_neurons_ * 0.8) ; i++)
	{
		Neuron* n = new Neuron(i + 1 , "excitatory");
		addNeuron(n);
		assert (i < N_EXCITATORY);
	}
	
	//boucle se parcourt N_INHIB fois
	for (int i(0) ; i < (nb_neurons_ * 0.2) ; i++)
	{
		Neuron* n = new Neuron(i + 80, "inhibitory");
		addNeuron(n);
		assert(i < N_INHIBITORY);
	}
}
	
//destructeur
Network::~Network()
{
	for (auto& n : neurons_)
	{
		delete n;
		n = nullptr;
	}
}
		
//add a neuron to the vector neurons_
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
	//random generator 
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disE(0 , 9999);
	uniform_int_distribution<> disI(10000, 12499);
	
	//for every neuron
	//targets size is N_TOTAL
	for (size_t n(0); n < nb_neurons_ ; n++)
	{
		for (size_t i(0) ; i <= C_EXCITATORY ; i++)
		{
			int indice = disE(gen);
			targets_[indice].push_back(n);
		}
		
		for (size_t i(0) ; i <= C_INHIBITORY ; i++)
		{
			int indice = disI(gen);
			targets_[indice].push_back(n);
		}	
	}
	cout << "finished making targets" << endl;
}

//update
//time given in steps
void Network::update(unsigned int simulation_steps)//(unsigned int time, unsigned int steps, double current)
{
	cout << "Updating Network ..." << endl;
	unsigned int steps_made(0);
	bool spike(false);
	//unsigned int t_stop = time + steps;
	
	while(steps_made < simulation_steps)
	{
		cout << steps_made << " steps made" << endl;
		
		assert(!neurons_.empty());
		//for every neuron in the network
		for (size_t i (0); i < neurons_.size(); i++)//Neuron* n : neurons_)
		{	
			assert(neurons_[i] != nullptr);
		
			spike = neurons_[i]->update(1); //current is normally 0 when we update network
		
			if (spike)
			{	
				for (auto& t :targets_[i])
				{
					neurons_[t]->receive(steps_made + D_STEPS , neurons_[t]->getJ());
				}
				//on envoie a tous les neurones avec les id presentes dans le targets de la neurone
				
				spike_times_.push_back(steps_made *H);
				neuron_idx_.push_back(i);
			}
		}			
		++steps_made;
	}
}

void Network::writeFile() const
{
	cout << "Writing to file: " << endl;
	ofstream textfile;
	textfile.open("Spike_Times.txt");	
	
	assert(spike_times_.size() == neuron_idx_.size());
	for (size_t i(0) ; i < spike_times_.size() ; i++)
	{
		textfile << spike_times_[i] << '\t' << neuron_idx_[i] << '\n' ;
	}
	
	///NELVE LE
	for (size_t i(0) ; i< neurons_.size(); i+=100)
	{
		textfile << neurons_[i]->getNbSpikes() << endl;
	}
	
	
	textfile.close();
}
