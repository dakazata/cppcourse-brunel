**Neuron Project**

Author : Daniella Zarza

**Description**

The program simulates Nicolas Brunel's "Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons". The simulation runs a network of 12500 neurons in which, 10000 are inhibitory and 2500 are inhibitory. The neurons interact with each other by sending spikes to each other as well as receiving random external spikes. Spikes are generated once the membrane potential surpasses the potential threshold, and they are received by the post-synaptic neurons after a certain delay, which is modelled using a ring-buffer. The signal sent by each neuron depends on whether it is excitatory or inhibitory. 

The model can be simulated using different parameters. These can be changed in the Constants.hpp file. The Brunel paper idicates four different possible simulations in which we change the G and the ETA parameters. 

The program produces a text file containing two columns : spike time and the neuron which spiked correspondingly. This document can be used to plot a graph (see "Result Graphs" section).

**Compilation and Execution**

The project uses CMAKE in order to compile and run. In order to compile go to the folder containing the .hpp and .cpp files and enter cmake ./ (keep in mind that if existant, the CMakeCache.txt files must be deleted before this command is entered). Next enter make. Finally run the program by entering ./neuron

**Doxygen Documentation**

The doxygen document corresponding to the program is automatically created when thr command make is entered

**Unit Testing**

Several unit tests are provided in the NeuronTests.cpp file. They can be run by netering the command ./neurontest

**Result Graphs**

The resulting graphs can be plotted using python in a Jupyter Notebook. The four cases that can be produced are
A: G = 3 and ETA = 2
B: G = 6 and ETA = 4
C: G = 5 and ETA = 2
D: G = 4.5 and ETA = 0.9

The resulting graphs can be seen in the folder "Graphs"
