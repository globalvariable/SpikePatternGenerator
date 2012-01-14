#include "SpikePatternGeneratorNetwork.h" 

static Network *spike_pattern_generator_network = NULL;

Network *spike_pattern_generator_get_network(void)
{
	return spike_pattern_generator_network;
}

void spike_pattern_generator_set_network(Network *network)
{
	spike_pattern_generator_network = network;
}

