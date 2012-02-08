#ifndef SPIKEPATTERNGENERATOR_H
#define SPIKEPATTERNGENERATOR_H


#include "Gui.h"
#include "../../TrialControllers/Library/TrialStats/TrialStats.h"

TrialStats *spike_pattern_generator_get_trial_stats(void);
void spike_pattern_generator_set_trial_stats(TrialStats *trial_stats);
Network *spike_pattern_generator_get_network(void);
void spike_pattern_generator_set_network(Network *network);

#endif
