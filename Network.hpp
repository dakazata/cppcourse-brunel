#ifndef NETWORK_H
#define NETWORK_H

/*!
 * \file Network.hpp
 * \brief Network class
 * \author Daniella Zarza
 */

#include <vector>
#include "Neuron.hpp"
#include "Constants.hpp"

/*!
 * \class Network
 * \brief Class containing simulation of a population of neurons
 * 
 * Neurons in the network interact via their target connections.
 * Upon spiking a neuron sends a signal to its targets
 *\
 */

class Network
{
	private:
		int nb_neurons_;					//!< Total number of neurons in
		std::vector<Neuron*> neurons_; 		//!< Points to each neuron in the network
		std::vector<double> spike_times_;		//!< Keeps all the spikes over the simulation time
		std::vector<unsigned int> neuron_idx_;	//!< Keeps the indices of the spiking neuron
		std::vector<std::vector<unsigned int>> targets_; //!< Associates each neuron with its post-synaptic neurons
		
		
	public:
		//! Constructor
		/*!
		 * \param an integer representing the total number of neurons in the network
		 */
		Network(int totalneurons);
		
		//! Destructor
		/*! 
		 * Deletes pointers from neurons_ vector 
		 */
		~Network();
				
		//! Add a neuron to the vector neurons_
		/*! 
		 * \param neuron points toeward the neuron being added
		 */
		void addNeuron(Neuron* neuron);
		
		//! Creates targets for all neurons in the network
		/*!
		 * Randomly created indices which correspond to the neurons a 
		 * neuron chould be connected to. It runs through al the neurons 
		 * in the network and connects each one to 10% of the neurons in the network
		 */
		void makeTargets();
		
		//! Sets the external current of the network
		/*! 
		 * \param external current to be passed on to neurons
		 */
		void setExternalCurrent(double current);
		
		//! Update of the network
		/*!
		 * Iterates through the neurons_ vector (each neuron) and updates them.
		 * Also deals with the sending of spikes. When a neuron spikes during its
		 * update it sends a signal into the buffer of all targets.
		 * It stores the spike times (in spike_times_) associated to the
		 * corresponding neuron index in neuron_idx_
		 * 
		 * \param Number of times we need to udate the network
		 */
		void update(unsigned int simulation_steps);

		//! Writes onto external file
		/*! Writes the spike times and the associated index of neuron
		 * which is spiking. Data is used to plot graphs.
		 */
		void writeFile() const;
};


#endif

