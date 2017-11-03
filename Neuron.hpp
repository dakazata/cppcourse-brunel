#ifndef NEURON_H
#define NEURON_H

/*!
 * \file Neuron.hpp
 * \brief Neuron class
 * \author Daniella Zarza
 */

#include <vector>
#include <string>
#include "Constants.hpp"

/*!
 * \class Neuron
 * \brief Class containing characteristics and functions of a single neuron
 * 
 * The class takes care of all the actions performed by a neuron such as :
 * - Updating the potential for every step of time
 * - Receiving spiking signals from pre-synaptic neurons in the network and external signals
 * - Having a refractory period after spiking
 */
 
class Neuron
{
	private:	
	
		int id_;				//!< Neuron ID - Identifies the neuron in the network				
		int nb_spikes_;			//!< Number of spikes
		double c1_, c2_; 		//!< Constants used in the calculation of the membrane potential	
		double memb_pot_;		//!< Membrane potential (in mV)
		double i_ext_;			//!< External current (in mA)
		double j_;				//!< PSP Amplitude sent to post-synaptic neurons upon spiking
		unsigned int clock_;	//!< Local clock (in steps)		
		unsigned int t_spike_;	//!< Time at which neuron last spike (in steps)
		std::string type_;      //!< String stating the type of neuron: excitatory or inhibitory
		std::vector<double> buffer_;		//!< Ring buffer which stores the incoming spikes at each step
		std::vector<double> potentials_;	//!< Potentials saved at every time step

	public:
		
		//! Constructor
		/*! 
		 * \brief Initiates a Neuron by setting initial parameters
		 * \param id : Id of neuron in the network
		 * \param typeneurone : string giving type of neurone
		 * \param current : Will intiates the external current given to the neuron
		 */
		Neuron(int id, std::string typeneurone = "excitatory", double current = 0.0); 	
		
		//! Destructor
		/*!
		 * \brief destroy neuron by default
		 */	
		~Neuron() = default;	
		
		
//============================GETTERS===================================


		//! Getter of the neuron ID
		/*!
		 * \return Returns the id_ value
		 */
		int getId() const;
		
		//! Getter of the membrane potential
		/*!
		 * \return Returns the memb_pot_ value
		 */
		double getMembranePotential() const;
		
		//! Getter of the number of Spikes
		/*!
		 * \return Returns the nb_spikes_ value
		 */
		int getNbSpikes() const;
		
		//! Getter of the neurons's buffer
		/*!
		 * \return Returns the buffer_ vector
		 */
		std::vector<double> getBuffer() const;
		
		//! Getter of the neuron type
		/*!
		 * \return Returns the string type_ ("excitatory" or "inhibitory")
		 */
		std::string getType() const;
		
		//! Getter of the PSP Amplitude
		/*!
		 * \brief The value of the amplitude depends on the type of neuron
		 * \return Returns the j_ value
		 */
		double getJ() const;
		
		//! Getter of the ensemble of potentials
		/*!
		 * \return Returns the potentials_ vector
		 */
		std::vector<double> getPotentials() const;
		
		
//============================SETTERS===================================


		//! Setter of the neuron's ID
		/*!
		 * \param ID (and int) to be affceted as the neuron's ID
		 */
		void setId(int);
		
		//! Setter of the nuron's external current
		/*!
		 * \param The current (a double) coming from outside the network
		 */
		void setCurrent(double);
		
		//! Setter of the membran potential
		/*!
		 * The potential is updated at every time step
		 * \param The potential (a double) to be affected to memb_pot_
		 */
		void setMembranePotential(double);
		
		
//=====================SPECIFIC NEURON FUNCTIONS========================		
		
		
		//! Solves membrane equation
		/*!
		 * Uses the membrane equation, the incoming spikes kept in the 
		 * buffer, and randomly generated spikes to calculate the
		 * membrane potential
		 * \return Returns the value of the membrane equation
		 */
		double solveMembEquation();
		
		//! Takes care of receiving spikes from pre-synaptic neurons
		/*!
		 * \brief Reads the buffer for the specific time
		 * \param time : current time (in steps)
		 * \param j_amp : the amplitude from the incoming spike
		 */
		void receive(unsigned long time, double j_amp);
		
		//! Updates potential
		void updatePot();
		
		
//====================SPECIFIC BUFFER FUNCTIONS=========================	
		
		
		//! Resets the Buffer value to 0
		/*!
		 * It "empties out" the current buffer box to 0 to be refilled 
		 * again
		 * \param time : current step 
		 */
		void resetBufferValue(long time);
		
		//! Index method
		/*!
		  Finds the corresponding box corresponding to the current time,
		  * taking into account the delay
		 * \param time : current step 
		 * \return The index of the box corresponding to the time
		 */
		unsigned int index(long time);
		
		//! Adds value to the respective box in the buffer_ vector
		/*!
		 * Every time that the neuron has an incoming spike, we add j_ 
		 * to the buffer_ box
		 * \param time : corresponding step in time
		 * \param type : type of neuron sending the incoming spike
		 */
		void addJ(unsigned long time, std::string type);
				
		
//==========================UPDATE FUNCTION=============================		
		
		
		//! Update function
		/*! 
		 * \brief At every step the neuron gets updated. 
		 * 
		 * This function deals with the updating of the membrane, ehich
		 * depends on whether or not the neuron is in the refractory 
		 * period. It checks to see if the membrane potential has reached
		 * the threshold potential. In this case the neuron spikes.
		 * 
		 * \param steps : number of steps to make 
		 * \return  A boolean indicating whether the neuron has spiked (true) or not
		 */
		bool update(unsigned int steps); 	
		
	
};

#endif
