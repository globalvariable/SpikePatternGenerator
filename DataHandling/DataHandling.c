#include "DataHandling.h"


int initialize_spike_pattern_generator_data_read_write_handlers(void)
{
	create_spike_pattern_generator_data_directory[0] = &create_spike_pattern_generator_data_directory_v0;
	save_spike_pattern_generator_data_directory[0] = &save_spike_pattern_generator_data_directory_v0;
	load_spike_pattern_generator_data_directory[0] = &load_spike_pattern_generator_data_directory_v0;
	
	spike_pattern_generator_data_get_num_of_layers[0] = spike_pattern_generator_data_get_num_of_layers_v0;
	spike_pattern_generator_data_get_num_of_neuron_groups_in_layer[0] = spike_pattern_generator_data_get_num_of_neuron_groups_in_layer_v0;
	spike_pattern_generator_data_get_num_of_neurons_in_neuron_group[0] = spike_pattern_generator_data_get_num_of_neurons_in_neuron_group_v0;
	spike_pattern_generator_data_get_num_of_patterns[0] = spike_pattern_generator_data_get_num_of_patterns_v0;
	spike_pattern_generator_data_get_pattern_length[0] = spike_pattern_generator_data_get_pattern_length_v0;
	spike_pattern_generator_data_get_num_of_spikes_in_pattern[0] = spike_pattern_generator_data_get_num_of_spikes_in_pattern_v0;
	spike_pattern_generator_data_get_next_spike_time_stamp_in_pattern[0] = spike_pattern_generator_data_get_next_spike_time_stamp_in_pattern_v0;
	
		
	return 1;
}

int is_spike_pattern_generator_data(char *spike_pattern_generator_data_path)
{
	char path[600];
	char line[200];
	FILE *fp;
	int line_cntr = 0;
	strcpy(path, spike_pattern_generator_data_path);
	strcat(path, "/meta");
	if ((fp = fopen(path, "r")) == NULL)  { printf ("ERROR: DataHandling: Couldn't read file: %s\n\n", path); return 0; }
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path);  fclose(fp); return 0; } else {line_cntr++;}   
	fclose(fp);   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n" ) == 0)
		return 1;
	else
		return 0;	
}

int get_spike_pattern_generator_data_format_version(int *version, char *spike_pattern_generator_data_path)
{
	char path[600];
	char line[200];
	char word[10];
	int line_cntr = 0;
	FILE *fp;
	if (is_spike_pattern_generator_data(spike_pattern_generator_data_path))
	{
		strcpy(path, spike_pattern_generator_data_path);
		strcat(path, "/meta");		
		if ((fp = fopen(path, "r")) == NULL)  { printf ("ERROR: DataHandling: Couldn't read file: %s\n\n", path); return 0; }
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: DataHandling: Couldn' t read %d th line of %s\n", line_cntr, path);  fclose(fp); return 0; } else {line_cntr++;}   
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: DataHandling: Couldn' t read %d th line of %s\n", line_cntr, path);  fclose(fp); return 0; } else {line_cntr++;}   
		if (!(get_word_in_line('\t', 1, word, line, TRUE)))
			return 0;
		fclose(fp);   	
		*version = (int)atof(word);
		return 1;
	}
	return 0;
}
