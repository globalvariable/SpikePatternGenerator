#include "DataHandling.h"


int initialize_data_read_write_handlers(void)
{
	create_main_directory[0] = &create_main_directory_v0;
	create_data_directory[0] = &create_data_directory_v0;
	write_spike_time_stamp[0] = &write_spike_time_stamp_v0;
	
	write_notes_to_files[0] = &write_notes_to_files_v0;
	write_additional_notes_to_files[0] = &write_additional_notes_to_files_v0;	

	load_main_directory[0] = &load_main_directory_v0;
	read_spike_time_stamp[0] = &ead_spike_time_stamp_v0;
	
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

int get_format_version(int *version, char *spike_pattern_generator_data_path)
{
	char path[600];
	char line[200];
	char word[10];
	int line_cntr = 0;
	FILE *fp;
	if (is_spike_pattern_generator_data(spike_pattern_generator_data_path))
	{
		strcpy(path, blue_spike_data_path);
		strcat(path, "/meta");		
		if ((fp = fopen(path, "r")) == NULL)  { printf ("ERROR: DataHandling: Couldn't read file: %s\n\n", path); return 0; }
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: DataHandling: Couldn' t read %d th line of %s\n", line_cntr, path);  fclose(fp); return 0; } else {line_cntr++;}   
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: DataHandling: Couldn' t read %d th line of %s\n", line_cntr, path);  fclose(fp); return 0; } else {line_cntr++;}   
		if (!(get_word_in_line('\t', 1, word, line, TRUE)))
			return 0;
		fclose(fp);   	
		*version = atof(word);
		return 1;
	}
	return 0;
}
