#ifndef SPIKEPATTERNGENERATOR_DATAHANDLING_H
#define SPIKEPATTERNGENERATOR_DATAHANDLING_H

#include "./v0/DataFormat_v0.h"

// Includes handling of Stimulus Generator Data Format versions starting from v0. The following versions shoudl be v1, v2, v3 and so on. 

#define SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER	1	// increment this for every new data format handling to be implemented. 

#define SPIKEPATTERNGENERATOR_DATA_FORMAT_VERSION	0	// Change this according to the intended data format/   Upper limit is MAX_NUMBER_OF_DATA_FORMAT_VER-1

int (*create_spike_pattern_generator_data_directory[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*save_spike_pattern_generator_data_directory[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*load_spike_pattern_generator_data_directory[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );

int (*spike_pattern_generator_data_get_num_of_layers[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*spike_pattern_generator_data_get_num_of_neuron_groups_in_layer[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*spike_pattern_generator_data_get_num_of_neurons_in_neuron_group[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*spike_pattern_generator_data_get_num_of_patterns[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*spike_pattern_generator_data_get_pattern_length[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*spike_pattern_generator_data_get_num_of_spikes_in_pattern[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );
int (*spike_pattern_generator_data_get_all_spike_time_stamps_in_pattern[SPIKEPATTERNGENERATOR_MAX_NUMBER_OF_DATA_FORMAT_VER]) (int num, ... );

int initialize_spike_pattern_generator_data_read_write_handlers(void);
int is_spike_pattern_generator_data(char *spike_pattern_generator_data_path);
int get_spike_pattern_generator_data_format_version(int *version, char *spike_pattern_generator_data_path);
#endif
