#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <string>
//#include "Buffer.hpp"
#include "Constants.hpp"

class Neuron
{
	private:	
		double c1_, c2_; 				//for the membrane equation
		
		int id_;
		double memb_pot_;
		int nb_spikes_;
		double i_ext_;
		unsigned int clock_;				//local clock in steps
		unsigned int t_spike_;
		double j_;
		std::string type_;      ///FAIRE UN ENUM POUR LE TYOPE
		
		//std::vector<double> spike_times_; 		//contains time(t*h) of spikes
		std::vector<int> targets_;		//contient les ids des neurones auxquels il donne un signal
		std::vector<double> buffer_;
		std::vector<double> potentials_;

	public:
		Neuron(int id, std::string typeneurone = "excitatory", double courant = 0.0); 			//constructeur	
		~Neuron() = default;	//destructeur
		
		int getId() const;
		double getMembranePotential() const;
		int getNbSpikes() const;
		//std::vector<double> getSpikeTimes() const;
		std::vector<int> getTargets() const;
		std::vector<double> getBuffer() const;
		std::string getType() const;
		double getJ() const;
		std::vector<double> getPotentials() const;
		
		void setId(int);
		void setCurrent(double);
		void setMembranePotential(double);
		
		double solveMembEquation(double);
		
		//buffer methods
		void resetBufferValue(long time);
		unsigned int index(long time);
		void addJ(unsigned long time, std::string type);
		
		//void addSpikeTime(unsigned int time);
		
		void addTarget(int target_ide);
		
		void receive(unsigned long , double);
		
		
		void updatePot(double current);

		bool update(unsigned int steps, double current = 0.0); 		//methode appele a chaque pas de temps dans le main
		
	
};

#endif
