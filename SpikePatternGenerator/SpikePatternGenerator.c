#include "SpikePatternGenerator.h"

static TrialStats *spike_pattern_generator_trial_stats = NULL;
static Network *spike_pattern_generator_network = NULL;
static CurrentPatterns *spike_pattern_generator_current_patterns = NULL;
CurrentPatternGraph	*spike_pattern_generator_current_pattern_graph = NULL;

int main( int argc, char *argv[])
{
	gtk_init(&argc, &argv);
 	spike_pattern_generator_set_network(allocate_network(spike_pattern_generator_get_network()));   // deallocates previously allocated external network and brings a new one.	
	spike_pattern_generator_set_trial_stats(allocate_trial_stats( spike_pattern_generator_get_trial_stats()));
	spike_pattern_generator_set_current_patterns(allocate_current_patterns( spike_pattern_generator_get_network(), spike_pattern_generator_get_trial_stats(), spike_pattern_generator_get_current_patterns()));
	create_gui();
	gtk_main();
	return 0;
}

TrialStats *spike_pattern_generator_get_trial_stats(void)
{
	return spike_pattern_generator_trial_stats;
}
void spike_pattern_generator_set_trial_stats(TrialStats *trial_stats)
{
	spike_pattern_generator_trial_stats = trial_stats;
}

Network *spike_pattern_generator_get_network(void)
{
	return spike_pattern_generator_network;
}

void spike_pattern_generator_set_network(Network *network)
{
	spike_pattern_generator_network = network;
}

CurrentPatterns *spike_pattern_generator_get_current_patterns(void)
{
	return spike_pattern_generator_current_patterns;
}
void spike_pattern_generator_set_current_patterns(CurrentPatterns *current_patterns)
{
	spike_pattern_generator_current_patterns = current_patterns;
}

CurrentPatternGraph *spike_pattern_generator_get_current_pattern_graph(void)
{
	return spike_pattern_generator_current_pattern_graph;
}
void spike_pattern_generator_set_current_pattern_graph(CurrentPatternGraph *graph)
{
	spike_pattern_generator_current_pattern_graph = graph;
}
