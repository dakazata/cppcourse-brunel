#include "gtest/include/gtest/gtest.h"
#include "Neuron.hpp"
#include "Network.hpp"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;


/*TEST(OneNeuronTest , RefractoryPeriod)
{
	Neuron n(1);
	double current (1.01);
	
	//200 updates
	n.update(200);
	
	
	for (size_t i(0) ; i < n.getPotentials().size() ; i++)
	{
		cout << n.getPotentials()[i] << endl;
	}
}*/ 
/*TEST (OneNeuronTest , MembranePotential)
{
	Neuron n(1);
	double current(1.0);
	
	//One Update
	//should expect exact calculated value 
	n.update (1, current);
	EXPECT_EQ(20.0 * (1.0 - exp(-0.1 / 20.0)) , n.getMembranePotential());
	
	//Several updates
	//should tend to 20 and should not spike
	n.update(10000 , current);
	EXPECT_NEAR(20.0, n.getMembranePotential() , 10e-3);
	EXPECT_EQ(0 , n.getNbSpikes());
	
}

TEST (OneNeuronTest , SpikeTimes)
{
	Neuron n(1);
	double current(1.01);
	
	//spike times with 1.01 as i_ext :
	// at 92.4 ms, 186.8 ms, 281,2 ms and 375.6 ms
	
	//update the neuron 3757 times (steps) and check the spike times
	n.update(3757 , current);
	
	std::vector<double> spike_t = n.getSpikeTimes();
	
	EXPECT_EQ(924 , spike_t[0]);
	EXPECT_EQ(1848 , spike_t[1]);
	EXPECT_EQ(2791 , spike_t[2]);
	EXPECT_EQ(3734 , spike_t[3]);
		
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
* */

TEST ( NetworkTest , NumberofConnections )
{
	unsigned int nb_neurons (N_TOTAL);
	Network* net = new Network(nb_neurons);
	int nb_connections(0);
	
	net->makeTargets();
	
	vector<vector<unsigned int> > net_targets = net->getTargets();
	
	//Check combien des fois la neurone [0] se trouve dans le targets du network
	for (size_t i(0) ; i < nb_neurons  ; i++)
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
	
	EXPECT_EQ(nb_connections , C_TOTAL);
}

TEST( NetworkTest , NumberofSpikes)
{
	unsigned int nb_neurons (N_TOTAL);
	Network* net = new Network(nb_neurons);
	int nb_spikes(0);
	
	net->makeTargets();
	net->update(1000);  //run for 100 ms
	
	vector<unsigned int> spiking_indices = net->getIndices();
	
	//Check combien des fois la neurone [0] se trouve dans le targets du network
	assert (!spiking_indices.empty());
	for (size_t j(0) ; j < spiking_indices.size() ; j++)
	{
		if (spiking_indices[j] == 0) //looking for neuron 0 being mentioned in the targets vectors
		{
			nb_spikes++;
		}
	}
		
	//we expect around 4000 for 1 s. so for 100 ms we expcte around 4
	EXPECT_NEAR (4000 , nb_spikes , 1);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
