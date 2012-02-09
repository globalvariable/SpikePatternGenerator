#ifndef SPIKEPATTERNGENERATOR_H
#define SPIKEPATTERNGENERATOR_H


#include "Gui.h"
#include "../../TrialControllers/Library/TrialStats/TrialStats.h"
#include "../../NeuroSim/Library/Patterns/CurrentPatterns.h"
#include "../../NeuroSim/Library/Graphs/CurrentPatternGraph.h"

TrialStats *spike_pattern_generator_get_trial_stats(void);
void spike_pattern_generator_set_trial_stats(TrialStats *trial_stats);
Network *spike_pattern_generator_get_network(void);
void spike_pattern_generator_set_network(Network *network);
CurrentPatterns *spike_pattern_generator_get_current_patterns(void);
void spike_pattern_generator_set_current_patterns(CurrentPatterns *current_patterns);
CurrentPatternGraph *spike_pattern_generator_get_current_pattern_graph(void);
void spike_pattern_generator_set_current_pattern_graph(CurrentPatternGraph *graph);


#endif
