#ifndef PATTERN_H
#define PATTERN_H


#include "../../NeuroSim/Library/Network/Network.h"
#include "../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.h"
#include "Graphs.h"
#include <gtkdatabox.h>
#include <gtkdatabox_ruler.h>
#include <gtkdatabox_lines.h>
#include <gtkdatabox_grid.h>

#define MAX_CURRENT_VALUE 500
#define MIN_CURRENT_VALUE	-100

struct AllStimulusPatterns
{
	double		****drawn_stimulus_currents;  // num_of_layers * num_of_neuron_groups * num_of_neurons * pattern_lengths
	double 		*****raw_stimulus_currents;   /// num_of_patterns * num_of_layers * num_of_neuron_groups * num_of_neurons * pattern_lengths
	double 		*****noisy_stimulus_currents;   /// num_of_patterns * num_of_layers * num_of_neuron_groups *num_of_neurons * pattern_lengths
	TimeStampMs	*pattern_lengths_ms;
	TimeStampMs	max_pattern_length;
	TimeStampMs	min_pattern_length;
	int			num_of_patterns;		
} all_stimulus_patterns;

struct NeuronDynamics
{
	double *****v;   /// num_of_patterns * num_of_layers * num_of_neuron_groups * num_of_neurons * pattern_length
	double *****u;   /// num_of_patterns * num_of_layers * num_of_neuron_groups *num_of_neurons  * pattern_length
} neuron_dynamics;

struct InitialNeuronDynamics
{
	double ****v;   /// num_of_layers * num_of_neuron_groups * num_of_neurons 
	double ****u;   ///  num_of_layers * num_of_neuron_groups *num_of_neurons 
} initial_neuron_dynamics;

bool allocate_patterns(TimeStampMs min_pattern_length, TimeStampMs max_pattern_length, int num_of_patterns);


#endif
