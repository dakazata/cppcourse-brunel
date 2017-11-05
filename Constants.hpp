#ifndef CONSTANTS_H
#define CONSTANTS_H


/*!
 * \file Constants.hpp
 * \brief Group of constants used in the program
 * \author Daniella Zarza
 */

//GENERAL CONSTANTS
constexpr double H (0.1);						//!< A Time -Step conversion. ONe step is 0.1 ms

//SIMULATION CONSTANTS
constexpr double SIM_END_TIME (500);			//!< the maximum time of simulation (1 second)
constexpr long CURRENT_START (0);				//!< time in steps at which external current starts running
constexpr long CURRENT_END (10000);				//!< time in steps at which external current stops running

//NETWORK CONSTANTS
constexpr int N_TOTAL(12500);					//!< total number of neurons in simulation
constexpr int N_EXCITATORY (N_TOTAL * 0.8);		//!< number of excitatory neurons	
constexpr int N_INHIBITORY (N_TOTAL * 0.2);		//!< number of inhibitory neurons 

//NEURON CONSTANTS						
constexpr double TAU (20.0);					//!< tau of neuron membrane 
constexpr double C(1.0);						//!< capacity of neuron membrane 
constexpr double R (TAU / C) ;					//!< resistance of neuron membrane	
constexpr double THR_POT (20.0);				//!< threshold potential 
constexpr double RESET_POT(0.0);				//!< reset potential 
constexpr double REF_TIME(2.0);     			//!< time in which potential stays at the reset potential after firing	
constexpr double G (4.5);
constexpr double J_AMP_EXCIT (0.1);				//!< amplitude of PSP signal sent by excitatory neuron after it spikes	
constexpr double J_AMP_INHIB (-G * J_AMP_EXCIT);		//!< amplitude of PSP signal sent by inhibitory neurons after it spikes		
constexpr double D (1.5);						//!< time delay (in ms)
constexpr int D_STEPS(D / H);					//!< time delay in steps
constexpr int C_EXCITATORY (N_EXCITATORY * 0.1);				//!< number of excitatory connections for each neuron
constexpr int C_INHIBITORY (N_INHIBITORY * 0.1);				//!< number of inhibitory connections for each neuron	
constexpr int C_TOTAL (C_EXCITATORY + C_INHIBITORY);			//!< number of total connections for each neuron	


constexpr double ETA (0.9);										//!< constant for random background noise
constexpr double NU_THR (THR_POT / (J_AMP_EXCIT * TAU));
constexpr double NU_EXT  (ETA * NU_THR);	//!< constant for random background noise 

#endif
