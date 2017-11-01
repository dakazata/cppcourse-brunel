#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
 * Constants file 
 */ 

//SIMULATION CONSTANTS
const long SIM_END_TIME (1000);				//!< the max time of simulation (1 second)
const long CURRENT_START (0);				//!< time at which external current starts running
const long CURRENT_END (1000);				//!< time at which external current stops running

//NETWORK CONSTANTS
const int N_TOTAL(12500);					//!< total number of neurons in simulation
const int N_EXCITATORY (N_TOTAL * 0.8);		//!< number of excitatory neurons	
const int N_INHIBITORY (N_TOTAL * 0.2);		//!< number of inhibitory neurons 

//NEURON CONSTANTS	
const double H (0.1);						//!< steps in time	
const double TAU (20.0);					//!< tau of neuron membrane 
const double C(1.0);						//!< capacity of neuron membrane 
const double R (TAU / C) ;					//!< resistance of neuron membrane	
const double THR_POT (20.0);				//!< threshold potential 
const double RESET_POT(0.0);				//!< reset potential 
const double REF_TIME(2.0);     			//!< time in which potential stays at the reset potential after firing	
const double J_AMP_EXCIT (0.1);				//!< amplitude of PSP signal sent by excitatory neuron after it spikes	
const double J_AMP_INHIB (0.5);				//!< amplitude of PSP signal sent by inhibitory neurons after it spikes		
const double D (1.5);						//!< time delay (in ms)
const int D_STEPS(D / H);					//!< time delay in steps
const int C_EXCITATORY (N_EXCITATORY * 0.1);				//!< number of excitatory connections for each neuron
const int C_INHIBITORY (N_INHIBITORY * 0.1);				//!< number of inhibitory connections for each neuron	
const int C_TOTAL (C_EXCITATORY + C_INHIBITORY);			//!< number of total connections for each neuron	
const int ETA (2.0);						//!< constant for random background noise
const double V_EXT  (ETA * THR_POT / (J_AMP_EXCIT * TAU));	//!< constant for random background noise 



#endif
