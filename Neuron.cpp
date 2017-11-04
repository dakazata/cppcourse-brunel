#include <iostream>
#include "Neuron.hpp"
#include <cmath>
#include <cassert>
#include <random>

using namespace std;


Neuron::Neuron(int id, bool typeneurone, bool bgnoise , double current)
	:id_ (id),	
	nb_spikes_(0),
	memb_pot_(0.0),
	i_ext_(current),
	clock_(0),
	t_spike_(0),   ///Starts at 20 so that neuron does not go straight into refractory state
	type_ (typeneurone),
	receivesBGNoise_(bgnoise),
	buffer_(), 
	potentials_(),
	spike_times_()
{
	///Calculates constants
	assert(TAU != 0);
	c1_ = exp(- H / TAU);
	c2_= R*(1.0 - c1_);
	
	///Inititates buffer
	for (int i(0); i <= D_STEPS ; i++)
	{
		buffer_.push_back(0);
	}
	
	///Initiates the j_ variable depending on the type_ variable
	if (type_) ///If true, the neuron is excitatory
	{
		j_ = J_AMP_EXCIT;
	}
	else 
	{
		j_ = J_AMP_INHIB;
	}
}

///GETTERS

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

vector<double> Neuron::getSpikeTimesNeuron() const
{
	return spike_times_;
}

vector<double> Neuron::getBuffer() const
{
	return buffer_;
}

double Neuron::getJ() const
{
	return j_;
}

vector<double> Neuron::getPotentials() const
{
	return potentials_;
}

///SETTERS

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

void Neuron::setBackgroundNoise(bool noise)
{
	receivesBGNoise_ = noise;
}


///SPECIFIC NEURON FUNCTIONS

bool Neuron::isExcitatory() const
{
	return type_;
}

void Neuron::receive(unsigned long time , double j_amp)
{	
	const auto t_out = time % (D_STEPS + 1);
	assert(t_out < buffer_.size());
	buffer_[t_out] += j_amp;
}

void Neuron::updatePotential()
{	
	assert (index(clock_) < buffer_.size());
	memb_pot_ = c1_ * memb_pot_ + i_ext_ * c2_ + buffer_[index(clock_)];
	
	if (receivesBGNoise_)
	{
		random_device rd;
		mt19937 gen(rd());
		poisson_distribution<int> pois (V_EXT * H);
		
		memb_pot_ += pois(gen)* J_AMP_EXCIT;
	}
}

///SPECIFIC BUFFER FUNCTIONS

void Neuron::resetBufferValue(long time)
{
	buffer_[index(time)] = 0.0;
}

unsigned int Neuron::index(long time)
{
	return time % (D_STEPS+ 1);
}

///UPDATE FUNCTION

bool Neuron::update(unsigned int steps)
{
	if (steps < 1) return false;
	
	bool spike(false); ///Initiates boolean to be returned

	for (unsigned int i(0) ; i < steps ; i++)
	{
		if (memb_pot_ > THR_POT)
		{
			nb_spikes_++;
			spike = true;
			t_spike_ = clock_;
			spike_times_.push_back(clock_);
		} 		
		
		///Checks if neuron is in a refractory state
		if ( !spike_times_.empty() and (clock_ - t_spike_) < (REF_TIME / H))
		{
			setMembranePotential(RESET_POT);			
		} 
		else 
		{
			updatePotential();
		}
		
		///Reset buffer value
		resetBufferValue(clock_);
		
		///Increment time
		++clock_;
		
	}
		
	return spike;
}
