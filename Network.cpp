#include "Network.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <random>

using namespace std;


//Constructor
Network::Network(int totalneurons)
	: nb_neurons_(totalneurons)
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
		Neuron* n = new Neuron(i + 10000, "inhibitory");
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
	uniform_int_distribution<> disE(0, 9999);
	uniform_int_distribution<> disI(10000 , 12499);

	//premiere boucle parcourt toutes les neurones 
	for (auto& n : neurons_)
	{
		for (size_t i(0) ; i <= C_EXCITATORY ; i++)
		{
			int indice = disE(gen);
			neurons_[indice]->addTarget(n->getId());
		}
		
		for (size_t i(0) ; i <= C_INHIBITORY ; i++)
		{
			int indice = disI(gen);
			neurons_[indice]->addTarget(n->getId());
		}		
	}
}

//update
void Network::update(unsigned int time, unsigned int steps, double current)
{
	bool spike(false);
	unsigned int t_stop = time + steps;
	
	for (unsigned int i(time) ; i < t_stop ; i++)
	{
		//for every neuron in the network
		for (auto n: neurons_)
		{	
			spike = n->update(time, steps, current); //current is normally 0 when we update network
		
			if (spike)
			{	
				//on envoir a tous les neurones avec les id presentes dans le targets de la neurone
				for (auto& id: n->getTargets())
				{
					neurons_[id]->receive(time , n->getType());
				}
			}
		}
		++time;
	}
}

void Network::writeFile() const
{
	cout << "Writing to file: " << endl;
	ofstream textfile;
	textfile.open("Spike_Times.txt");	
	
	for (size_t i(0) ; i < neurons_.size() ; i++)
	{
		for (auto spiket : neurons_[i]->getSpikeTimes())
		{
			textfile << spiket << '\t' << i+1 << '\n' ;
		}
	}
	
	textfile.close();
}
