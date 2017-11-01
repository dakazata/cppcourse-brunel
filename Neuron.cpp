#include <iostream>
#include "Neuron.hpp"
#include <cmath>
#include <cassert>
#include <random>

using namespace std;

Neuron::Neuron(int id ,string typeneurone , double courant)
	:id_ (id),
	memb_pot_(0.0),
	nb_spikes_(0),
	i_ext_(courant),
	//refractory_(false),
	clock_(0),
	t_spike_(0),
	type_ (typeneurone),
	spike_times_(),
	targets_(),
	buffer_()
{
	assert(TAU != 0);
	c1_ = exp(- H / TAU);
	c2_= R*(1.0 - c1_);
}

int Neuron::getId() const
{
	return id_;
}

double Neuron::getMembranePotential() const
{
	return memb_pot_;
}

int Neuron::getNbSpikes() const
{
	return nb_spikes_;
}

vector<double> Neuron::getSpikeTimes() const
{
	return spike_times_;
}

vector<int> Neuron::getTargets() const
{
	return targets_;
}

Buffer Neuron::getBuffer() const
{
	return buffer_;
}

string Neuron::getType() const
{
	return type_;
}

void Neuron::setId(int i)
{
	id_ = i;
}
		
void Neuron::setCurrent(double current)
{
	i_ext_ = current;
}

void Neuron::setMembranePotential(double pot)
{
	memb_pot_ = pot;
}
/*		
bool Neuron::isRefractory()
{
	return refractory_;
}
*/
double Neuron::solveMembEquation()
{
	
	return (c1_ * memb_pot_) + (i_ext_ * c2_);
}

void Neuron::addSpikeTime(double time)
{
	spike_times_.push_back(time);
}

void Neuron::addTarget(int target_id)
{
	assert(target_id < N_TOTAL);
	targets_.push_back(target_id);
}

void Neuron::receive(unsigned long time , string type)
{
	buffer_.addJ(time , type);
}

///*Si la neurone is refractory we set its potential to 0
///else if it surpasses the threshold potential we set a spike
///we save this spike time in the vectors spike_times_, we augment the 
///nb_spikes, and we set the variable t_spike to the current time;

bool Neuron::update(unsigned int time, unsigned int steps, double current)
{
	bool spike(false);
	clock_ = time;
	unsigned int t_stop = clock_ + steps;
	i_ext_ = current;
	
	static random_device rd;
	static mt19937 gen(rd());
	static poisson_distribution<int> pois (2);//V_EXT * C_EXCITATORY * H * J_AMP_EXCIT);
	
	while (clock_ < t_stop)
	{
		if (memb_pot_ > THR_POT)
		{
			addSpikeTime(clock_*H);
			nb_spikes_++;
			spike = true;
			t_spike_ = clock_;
			//refractory_ = true;		
		} 
		
		if ((clock_ - t_spike_) < (REF_TIME / H))
		{
			setMembranePotential(RESET_POT);			
		} else {
			memb_pot_ = solveMembEquation()  + (buffer_.getJ(time)) + pois(gen)* J_AMP_EXCIT;
			buffer_.resetValue(time);
		}

		clock_++;
	}
	
	return spike;
}
