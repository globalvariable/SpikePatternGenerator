#ifndef SPIKEPATTERNGENERATOR_DATAFORMAT_V0_H
#define SPIKEPATTERNGENERATOR_DATAFORMAT_V0_H
#include <rtai_shm.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <gtk/gtk.h>
#include <string.h>

#include "./../../BlueSpike/Library/Misc/Misc.h"
#include "./../../NeuroSim/Library/Network/Network.h"
#include "../../Pattern/Pattern.h"

int create_spike_pattern_generator_data_directory_v0(int num, ...);
int save_spike_pattern_generator_data_directory_v0(int num, ...);
int load_spike_pattern_generator_data_directory_v0(int num, ...);

int spike_pattern_generator_data_get_num_of_layers_v0(int num, ...);
int spike_pattern_generator_data_get_num_of_neuron_groups_in_layer_v0(int num, ...);
int spike_pattern_generator_data_get_num_of_neurons_in_neuron_group_v0(int num, ...);
int spike_pattern_generator_data_get_num_of_patterns_v0(int num, ...);
int spike_pattern_generator_data_get_pattern_length_v0(int num, ...);
int spike_pattern_generator_data_get_num_of_spikes_in_pattern_v0(int num, ...);
int spike_pattern_generator_data_get_all_spike_time_stamps_in_pattern_v0(int num, ...);



#endif
