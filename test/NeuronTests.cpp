#include "../gtest/include/gtest/gtest.h"
#include "../src/Neuron.hpp"
#include "../src/Network.hpp"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;


TEST (OneNeuronTest , PositiveInput)
{
	///Neuron of id = 1, excitatory type, receives no background noise, a external current is 1.01
	Neuron n(1, true , false, 1.0);
	
	///Before any updates the potential must be equal to 0
	EXPECT_EQ(0.0 , n.getMembranePotential());
	
	///One update
	n.update (1);
	
	///Expect exact value
	EXPECT_EQ(R*(1-exp(-H/TAU)), n.getMembranePotential());
	
	///Several updates
	n.update(10000);
	
	///Potential should tend to 20 and neuron should not spike
	EXPECT_NEAR(20, n.getMembranePotential() , 10e-3);
	EXPECT_EQ(0 , n.getNbSpikes());
	
}

TEST (OneNeuronTest , NegativeInput)
{
	///Neuron of id = 1, excitatory type, receives no background noise, a external current -1.0
	Neuron n(1, true , false, -1.0);
	
	///After 21 updates (the first 20 are during refractory time when potential = 0)
	n.update(1);
	
	///We should expect an exact negative value
	EXPECT_EQ(-R*(1-exp(-H/TAU)), n.getMembranePotential());
}

TEST (OneNeuronTest , SpikeTimes)
{
	///Neuron of id = 1, excitatory, does not receive background noise, and has external current = 1.01 mA
	Neuron n (1 , true, false, 1.01); 
	
	///We update the neuron enough times in order to make sure that we have 4 spikes
	n.update(3757);
	
	///We fetch the neuron's spike times vector
	std::vector<double> spike_t = n.getSpikeTimesNeuron();
	
	///The normal values for the first four spikes are: 92.4 , 166.8 , 281.2 , 375.6
	///Should expect spikes around the normal values 
	EXPECT_NEAR(924 , spike_t[0], 1);
	EXPECT_NEAR(1868 , spike_t[1], 1);
	EXPECT_NEAR(2812 , spike_t[2], 1);
	EXPECT_NEAR(3756 , spike_t[3], 1);
		
}

TEST(OneNeuronTest , RefractoryPeriod)
{
	///Neuron of id = 1, excitatory, does not receive background noise, and has external current = 1.01 mA
	Neuron n(1, true,false, 1.01 );
	
	///Update until the firs spike
	n.update(924);
	EXPECT_GT(n.getMembranePotential() , 20.0 );
	
	///Next update it should go back to zero
	n.update(1);	
	EXPECT_EQ(0.0, n.getMembranePotential());

	///20 updates later (refractory perio) it should still be zero
	n.update(19) ;  
	EXPECT_EQ(0.0, n.getMembranePotential());

}


TEST ( NetworkTest , NumberofConnections )
{
	///Initiates network with N_TOTAL neurons
	Network* net = new Network(N_TOTAL);
	
	///Variable to count the number of connections for one specific neuron
	int nb_connections(0);
	
	///Creat and fetch the targets matrix from the network
	net->makeTargets();
	vector<vector<unsigned int> > net_targets = net->getTargets();
	
	///Check how many times the neuron 0 can be found in the entire targets_ matrix
	for (size_t i(0) ; i < N_TOTAL ; i++)
	{
		assert (!net_targets[i].empty());
		for (size_t j(0) ; j < net_targets[i].size() ; j++)
		{
			if (net_targets[i][j] == 0) //looking for neuron 0 being mentioned in the targets vectors
			{
				nb_connections++;
			}
		}
	}
	
	///We can expect an exact value of connections : C_TOTAL
	EXPECT_EQ(nb_connections , C_TOTAL);
}

TEST(NeuronTest, DelayTest)
{
	///Neuron of id = 1, excitatory, does not receive background noise, and has external current 0.0
	Neuron n (1 , true, false, 0.0); 
	
	///We send a signal of size j_ to the neuron's buffer with D_STEPS of delay 
	n.receive(D_STEPS, J_AMP_EXCIT);
	
	///Before any updates we expect the potential to be zero
	EXPECT_EQ(0, n.getMembranePotential());
	
	///We update the neuron for D_STEPS so we expect the neuron has not received the signal yet
	n.update (D_STEPS);
	EXPECT_EQ(0, n.getMembranePotential());
	
	///After one update more the potential should be very near to the value transmitted
	n.update(1);
	EXPECT_EQ(J_AMP_EXCIT , n.getMembranePotential());

}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

