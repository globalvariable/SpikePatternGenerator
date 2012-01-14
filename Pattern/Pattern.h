#ifndef PATTERN_H
#define PATTERN_H


#include "../../NeuroSim/Library/Network/Network.h"
#include "../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.h"
#include "../../BlueSpike/SpikeTimeStamp.h"
#include "../SpikePatternGenerator/SimulationGraphs.h"
#include <gtkdatabox.h>
#include <gtkdatabox_ruler.h>
#include <gtkdatabox_lines.h>
#include <gtkdatabox_grid.h>

#define INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS 			1
#define MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS 			INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS

#define MAX_CURRENT_VALUE 				500
#define MIN_CURRENT_VALUE					-100

struct StimulusPatternsInfo
{
	TimeStampMs	*pattern_lengths_ms;
	TimeStampMs	max_pattern_length;
	TimeStampMs	min_pattern_length;
	int			num_of_patterns;	
} all_stimulus_patterns_info;

struct StimulusCurrents
{
	double		****drawn_stimulus_currents;  // num_of_layers * num_of_neuron_groups * num_of_neurons * max_pattern_length
	double 		*****raw_stimulus_currents;   /// num_of_patterns * num_of_layers * num_of_neuron_groups * num_of_neurons * pattern_lengths
	double 		*****noisy_stimulus_currents;   /// num_of_patterns * num_of_layers * num_of_neuron_groups *num_of_neurons * pattern_lengths
	double 		***noise_variances;   ///num_of_layers * num_of_neuron_groups *num_of_neurons
	TimeStampMs	***noise_addition_ms_intervals;   ///num_of_layers * num_of_neuron_groups *num_of_neurons	
} all_stimulus_currents;

struct NeuronDynamics
{
	double *****v;   /// num_of_patterns * num_of_layers * num_of_neuron_groups * num_of_neurons * pattern_length
	double *****u;   /// num_of_patterns * num_of_layers * num_of_neuron_groups *num_of_neurons  * pattern_length
	double ****initial_v;   /// num_of_patterns * num_of_layers * num_of_neuron_groups * num_of_neurons 
	double ****initial_u;   ///  num_of_patterns * num_of_layers * num_of_neuron_groups *num_of_neurons 
	double ***initial_v_means;   	///  num_of_layers * num_of_neuron_groups *num_of_neurons 
	double ***initial_v_variances;   	///  num_of_layers * num_of_neuron_groups *num_of_neurons 	
} neuron_dynamics;

struct SpikePatternTimeStamps
{
	SpikeTimeStampItem	**pattern_time_stamps;		// num_of_pattern * num_of_time_stamps_in_pattern
	int					*num_of_time_stamps_in_pattern;		// num_of_pattern 
} all_spike_patterns;

bool allocate_patterns(Network *network, TimeStampMs min_pattern_length, TimeStampMs max_pattern_length, int num_of_patterns);
bool allocate_stimulus_currents(Network *network);
bool allocate_neuron_dynamics(Network *network);
bool allocate_spike_patterns(Network *network);
bool increment_time_stamp_number_of_pattern(int pattern_num);
bool add_time_stamp_to_spike_pattern_time_stamps(int pattern_num, int layer, int neuron_group, int neuron_num, TimeStamp spike_time);
void clear_spike_pattern_time_stamps(void);
bool deallocate_patterns(Network *network);
bool deallocate_stimulus_currents(Network *network);
bool deallocate_neuron_dynamics(Network *network);
bool deallocate_spike_patterns(Network *network);
#endif
