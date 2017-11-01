#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <string>
#include "Buffer.hpp"
#include "Constants.hpp"

class Neuron
{
	private:	
		double c1_, c2_; 				//for the membrane equation
		
		int id_;
		double memb_pot_;
		int nb_spikes_;
		double i_ext_;
		//bool refractory_;
		unsigned int clock_;				//local clock in steps
		unsigned int t_spike_;
		std::string type_;      ///FAIRE UN ENUM POUR LE TYOPE
		
		std::vector<double> spike_times_; 		//contains time(t*h) of spikes
		std::vector<int> targets_;		//contient les ids des neurones auxquels il donne un signal
		Buffer buffer_;

	public:
		Neuron(int id, std::string typeneurone = "excitatory", double courant = 0.0); 			//constructeur	
		~Neuron() = default;	//destructeur
		
		int getId() const;
		double getMembranePotential() const;
		int getNbSpikes() const;
		std::vector<double> getSpikeTimes() const;
		std::vector<int> getTargets() const;
		Buffer getBuffer() const;
		std::string getType() const;
		
		void setId(int);
		void setCurrent(double);
		void setMembranePotential(double);
		
		//bool isRefractory();
		
		double solveMembEquation();
		
		void addSpikeTime(double time);
		
		void addTarget(int target_ide);
		
		void receive(unsigned long , std::string);

		bool update(unsigned int time, unsigned int steps, double current); 		//methode appele a chaque pas de temps dans le main
		
	
};

#endif
