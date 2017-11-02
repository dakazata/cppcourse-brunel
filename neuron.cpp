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
	clock_(0),
	t_spike_(0),
	type_ (typeneurone),
	targets_(),
	buffer_(), 
	potentials_()
{
	assert(TAU != 0);
	c1_ = exp(- H / TAU);
	c2_= R*(1.0 - c1_);
	
	for (int i(0); i <= D_STEPS ; i++)
	{
		buffer_.push_back(0);
	}
	
	if (type_ == "excitatory")
	{
		j_ = J_AMP_EXCIT;
	}
	else if (type_ == "inhibitory")
	{
		j_ = J_AMP_INHIB;
	}
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
/*
vector<double> Neuron::getSpikeTimes() const
{
	return spike_times_;
}
*/
vector<int> Neuron::getTargets() const
{
	return targets_;
}

vector<double> Neuron::getBuffer() const
{
	return buffer_;
}

string Neuron::getType() const
{
	return type_;
}

double Neuron::getJ() const
{
	return j_;
}

vector<double> Neuron::getPotentials() const
{
	return potentials_;
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

double Neuron::solveMembEquation(double current)
{
	return (c1_ * memb_pot_) + (current * c2_);
}

///Buffer methods
void Neuron::resetBufferValue(long time)
{
	buffer_[index(time)] = 0.0;
}

unsigned int Neuron::index(long time)
{
	return time % (D_STEPS+ 1);
}

/*unsigned int Neuron::getJ(long time)
{
	return buffer_[index(time)];
}*/

/*void Neuron::addJ(unsigned long time, string type)
{
	assert(index(time + D_STEPS) <= buffer_.size());
	
	if (type == "excitatory")
	{
		buffer_[index(time + D_STEPS)] += J_AMP_EXCIT;
	} 
	else if (type == "inhibitory")
	{
		buffer_[index(time + D_STEPS)] += J_AMP_INHIB;
	}
	buffer_[index(time + D_STEPS)] += 1;
}*/

void Neuron::addTarget(int target_id)
{
	assert(target_id < N_TOTAL);
	targets_.push_back(target_id);
}

void Neuron::receive(unsigned long time , double j_amp)
{
	assert(index(time + D_STEPS) <= buffer_.size());
	buffer_[index(time + D_STEPS)] += j_amp;
}

void Neuron::updatePot(double current)
{
	static random_device rd;
	static mt19937 gen(rd());
	static poisson_distribution<int> pois (V_EXT);
	memb_pot_ = solveMembEquation(current) + buffer_[index(clock_)] + pois(gen)* J_AMP_EXCIT;
}

///*Si la neurone is refractory we set its potential to 0
///else if it surpasses the threshold potential we set a spike
///we save this spike time in the vectors spike_times_, we augment the 
///nb_spikes, and we set the variable t_spike to the current time;

bool Neuron::update(unsigned int steps, double current)
{
	if (steps < 1) return false;
	
	bool spike(false);
	
	for (unsigned int i(0) ; i < steps ; i++)
	{
		if (memb_pot_ > THR_POT)
		{
			nb_spikes_++;
			spike = true;
			t_spike_ = clock_;
		} 		
		
		if ((clock_ - t_spike_) < (REF_TIME / H))
		{
			setMembranePotential(RESET_POT);			
		} 
		else 
		{
			updatePot(current);
		}
		
		resetBufferValue(clock_);
		
		++clock_;
		
		//potentials_.push_back(memb_pot_);
	}
		
	return spike;
}
