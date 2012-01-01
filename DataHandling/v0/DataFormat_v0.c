#include "DataFormat_v0.h"


int create_main_directory_v0(int num, ...)
{
	FILE *fp;
	char *path_chooser;
	DIR	*dir_main_folder;
	char main_dir_path[600];
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   	
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);	
	strcat(main_dir_path, "/SpikePatternGeneratorData");
	if ((dir_main_folder = opendir(main_dir_path)) != NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s already has SpikeGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder or delete SpikeGeneratorData directory.\n\n");		        		
                return 0;
        }

	mkdir(main_dir_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

        printf ("DataFormat_v0: Created SpikePatternGeneratorData folder in: %s.\n", path_chooser);
        printf ("DataFormat_v0: SpikePatternGeneratorData path is: %s.\n\n", main_dir_path); 
        
	if (!create_main_meta_file(main_dir_path))
		return 0;
		
	if ((fp = fopen("./path_initial_directory", "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", path_chooser);
	fclose (fp);		

	return 1;
}

int create_main_meta_file(char * main_dir_path)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;
	int i,j;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
		
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------SpikeGenerator - Main Meta File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"NUM_OF_LAYERS\t%d\n",	all_network->layer_count);
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];
		fprintf(fp,"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n",	i, ptr_layer->neuron_group_count);		
	}
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			fprintf(fp,"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n", i, j, ptr_neuron_group->neuron_count);					
		}
	}
	fprintf(fp,"MAX_PATTERN_LENGTH\t%d\n", all_stimulus_patterns.max_pattern_length);
	fprintf(fp,"MIN_PATTERN_LENGTH\t%d\n", all_stimulus_patterns.min_pattern_length);	
	fprintf(fp,"NUM_OF_PATTERNS\t%d\n", all_stimulus_patterns.num_of_patterns);		
	fprintf(fp,"INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS\t%d\n", INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS);
	fprintf(fp,"MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%d\n",  MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS);
	fprintf(fp,"INJECTED_CURRENT_NOISE_VARIANCE\t%f\n", injected_current_noise_variance);
	fprintf(fp,"INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%d\n", injected_current_noise_addition_interval_ms);
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_MEAN\t%f\n", initial_neuron_membrane_voltage_mean);
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_VARIANCE\t%f\n", initial_neuron_membrane_voltage_variance);	
	fprintf(fp,"----------SpikeGenerator - End of Main Meta File----------\n");
	fclose(fp);
	return 1;
}


int save_main_directory_v0(int num, ...)
{
	int i;
	char *path_chooser;
	DIR	*dir_main_folder;
	char main_dir_path[600];
	GtkWidget *text_view; 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   	
    	text_view = va_arg ( arguments, GtkWidget *);   	
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikeGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikeGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikeGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        if(!save_notes(main_dir_path, text_view))
        	return 0;
        
        if(!save_drawn_stimulus_current(main_dir_path))
        	return 0;   
        	
	if(!save_neuron_params(main_dir_path))
        	return 0;      
      
	for (i = 0; i < all_stimulus_patterns.num_of_patterns ; i++)
	{
		if(!create_data_directory(main_dir_path, i))
        		return 0;
        }
	return 1;
}

int save_notes(char* main_dir_path, GtkWidget *text_view)
{
	char *text_buffer;
	GtkTextIter start, end;
	int char_count;
	char  temp_path[600];
	int i;
	FILE *fp;

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));	
       	gtk_text_buffer_get_start_iter ( buffer, &start);
        gtk_text_buffer_get_end_iter ( buffer, &end);
        text_buffer = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
	char_count = gtk_text_buffer_get_char_count(buffer);

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/notes");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
	for (i = 0; i < char_count; i++)
	{
		fprintf(fp, "%c", text_buffer[i]);		
	}
	fclose(fp);

	if ((fp = fopen("./initial_note", "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't find directory: %s\n\n", "./initial_note"); return 0; }
	for (i = 0; i < char_count; i++)
	{
		fprintf(fp, "%c", text_buffer[i]);		
	}
	fclose(fp);
	
	return 1;
}

int save_drawn_stimulus_current(char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/DrawnStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - DrawnStimulusCurrent File----------\n");		
	for (j = 0; j< all_stimulus_patterns.max_pattern_length; j++)
	{
		for (k=0; k<all_network->layer_count; k++)
		{
			ptr_layer = all_network->layers[k];			
			for (m=0; m<ptr_layer->neuron_group_count; m++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[m];
				for (n=0; n<ptr_neuron_group->neuron_count; n++)
				{
					fprintf(fp, "%.16E\t", all_stimulus_patterns.drawn_stimulus_currents[k][m][n][j]);
				}
				fprintf(fp,"\n");
			}
		}			
	}
	fprintf(fp,"----------SpikeGenerator - End of DrawnStimulusCurrent File----------\n");			
	fclose(fp);
	return 1;
}

int save_neuron_params(char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	Neuron		*ptr_neuron;

	//	double v;  load it from inial_neuron_dynamics log
	double a;
	double b;
	double c;
	double d;
	double k;
	double C;
	double v_resting;
	double v_threshold;
	double v_peak;
//	double I_inject;
	bool inhibitory;
	double E_excitatory;
	double E_inhibitory;
	double tau_excitatory;
	double tau_inhibitory;
	
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/NeuronParameters");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - NeuronParameters File----------\n");		
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				ptr_neuron = &(ptr_neuron_group->neurons[n]);	
				a = ptr_neuron->a;
				b = ptr_neuron->b;
				c = ptr_neuron->c;
				d = ptr_neuron->d;
				k = ptr_neuron->k;
				C = 1.0/ptr_neuron->E;
				v_resting = ptr_neuron->v_resting;
				v_threshold = ptr_neuron->v_threshold + ptr_neuron->v_resting;
				v_peak = ptr_neuron->v_peak + ptr_neuron->v_resting;
				inhibitory = ptr_neuron->inhibitory;
				E_excitatory = ptr_neuron->E_excitatory + ptr_neuron->v_resting;
				E_inhibitory = ptr_neuron->E_inhibitory + ptr_neuron->v_resting;
				tau_excitatory = -1.0/ptr_neuron->decay_rate_excitatory;
				tau_inhibitory = -1.0/ptr_neuron->decay_rate_inhibitory;								
				fprintf(fp, "%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%d\t%.16E\t%.16E\t%.16E\t%.16E\t", a, b, c, d, k, C, v_resting, v_threshold, v_peak, inhibitory, E_excitatory, E_inhibitory, tau_excitatory, tau_inhibitory);
				fprintf(fp,"\n");
			}
		}			
	}
	fprintf(fp,"----------SpikeGenerator - End of NeuronParameters File----------\n");			
	fclose(fp);
	return 1;
}

int create_data_directory(char *main_dir_path, int pattern_num)
{
	char data_directory_name[10];
	char data_directory_num[10];
	char  data_directory_path[600];	
	DIR	*dir_data_directory;	
	
	if (pattern_num <10)
	{
		strcpy(data_directory_name, "dat0000");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);
	}
	else if (pattern_num <100)
	{
		strcpy(data_directory_name, "dat000");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);		
	}
	else if (pattern_num <1000)
	{
		strcpy(data_directory_name, "dat00");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (pattern_num <10000)
	{
		strcpy(data_directory_name, "dat0");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (pattern_num <100000)
	{
		strcpy(data_directory_name, "dat");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);			
	}	
	else
	{
		printf("DataFormat_v0: ERROR: bumber of patterns %d.\n", pattern_num);
		printf("DataFormat_v0: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, main_dir_path);	
	strcat(data_directory_path, "/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) != NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s already has %s folder.\n", main_dir_path, data_directory_name);		
                return 0;
        }
	mkdir(data_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);	

	if (save_data_files(data_directory_path, pattern_num))
		return 1;
	return 0;
}

int save_data_files(char  *data_directory_path, int pattern_num)
{
	if (!save_meta_data(data_directory_path, pattern_num))
		return 0;
	if (!save_raw_stimulus_current(data_directory_path, pattern_num))
		return 0;
	if (!save_noisy_stimulus_current(data_directory_path, pattern_num))
		return 0;		
	if (!save_spike_timestamps(data_directory_path, pattern_num))
		return 0;		
	return 1;
}

int save_meta_data(char *data_directory_path, int pattern_num)
{
	char temp_path[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	int i, j, k;
			
 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------SpikeGenerator - Meta Data File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"PATTERN_LENGTH_MS\t%d", all_stimulus_patterns.pattern_lengths_ms[pattern_num]); 	
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGES\n"); 	
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				fprintf(fp, "%.16E\n", initial_neuron_dynamics.v[pattern_num][i][j][k]);
			}
		}
	}	

	fprintf(fp,"----------SpikeGenerator - End of Meta Data File----------\n");
	fclose(fp);	
	return 1;
}

int save_raw_stimulus_current(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/RawStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - RawStimulusCurrent File----------\n");		
		
	for (k=0; k<all_network->layer_count; k++)
	{
		ptr_layer = all_network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns.pattern_lengths_ms[pattern_num]; j++)
				{				
					fprintf(fp, "%.16E\n", all_stimulus_patterns.raw_stimulus_currents[pattern_num][k][m][n][j]);						
				}
			}
		}
	}			

	fprintf(fp,"----------SpikeGenerator - RawStimulusCurrent File----------\n");			
	fclose(fp);
	return 1;
}

int save_noisy_stimulus_current(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/NoisyStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - NoisyStimulusCurrent File----------\n");		
		
	for (k=0; k<all_network->layer_count; k++)
	{
		ptr_layer = all_network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns.pattern_lengths_ms[pattern_num]; j++)
				{
					fprintf(fp, "%.16E\n", all_stimulus_patterns.noisy_stimulus_currents[pattern_num][k][m][n][j]);						
				}
			}
		}
	}			

	fprintf(fp,"----------SpikeGenerator - NoisyStimulusCurrent File----------\n");			
	fclose(fp);
	return 1;
}

int save_spike_timestamps(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int i;

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/SpikeTimeStamp");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - SpikeTimeStamp File----------\n");		
	
	for (i=0; i<spike_pattern_time_stamps.num_of_time_stamps_in_pattern[pattern_num]; i++)
	{
		fprintf(fp,"%llu\t", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].peak_time);
		fprintf(fp,"%d\t", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].mwa_or_layer);		
		fprintf(fp,"%d\t", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].channel_or_neuron_group);		
		fprintf(fp,"%d\n", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].unit_or_neuron);									
	}			

	fprintf(fp,"----------SpikeGenerator - SpikeTimeStamp File----------\n");			
	fclose(fp);
	return 1;
}


int load_main_directory_v0(int num, ...)
{
	int i;
	char *path_chooser;
	DIR	*dir_main_folder;
	char main_dir_path[600];
	GtkWidget *text_view; 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   	
    	text_view = va_arg ( arguments, GtkWidget *);   	
	va_end ( arguments );
	
	
	if (!deallocate_patterns())		// do this before destroying network since this is allocated according to network
		return 0;
	if (!destroy_network())
		return 0;
	
	
	strcpy(main_dir_path, path_chooser);						// SpikeGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikeGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikeGeneratorData directory.\n\n");		        		
                return 0;
        }

	if (!read_main_meta_file(main_dir_path))
		return 0;
		
        if(!read_notes(main_dir_path, text_view))
        	return 0;
        
        if(!read_drawn_stimulus_current(main_dir_path))
        	return 0;   
        	
	if(!read_neuron_params(main_dir_path))
        	return 0;      
        	
 	for (i = 0; i < all_stimulus_patterns.num_of_patterns ; i++)
	{
		if(!read_data_directory(main_dir_path, i))
        		return 0;
        }
               	
	return 1;
}

int read_main_meta_file(char * main_dir_path)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;
	int i,j;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
		
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------SpikeGenerator - Main Meta File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"NUM_OF_LAYERS\t%d\n",	all_network->layer_count);
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];
		fprintf(fp,"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n",	i, ptr_layer->neuron_group_count);		
	}
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			fprintf(fp,"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n", i, j, ptr_neuron_group->neuron_count);					
		}
	}
	fprintf(fp,"MAX_PATTERN_LENGTH\t%d\n", all_stimulus_patterns.max_pattern_length);
	fprintf(fp,"MIN_PATTERN_LENGTH\t%d\n", all_stimulus_patterns.min_pattern_length);	
	fprintf(fp,"NUM_OF_PATTERNS\t%d\n", all_stimulus_patterns.num_of_patterns);		
	fprintf(fp,"INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS\t%d\n", INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS);
	fprintf(fp,"MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%d\n",  MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS);
	fprintf(fp,"INJECTED_CURRENT_NOISE_VARIANCE\t%f\n", injected_current_noise_variance);
	fprintf(fp,"INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%d\n", injected_current_noise_addition_interval_ms);
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_MEAN\t%f\n", initial_neuron_membrane_voltage_mean);
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_VARIANCE\t%f\n", initial_neuron_membrane_voltage_variance);	
	fprintf(fp,"----------SpikeGenerator - End of Main Meta File----------\n");
	fclose(fp);
	return 1;
}

int read_notes(char* main_dir_path, GtkWidget *text_view)
{
	char *text_buffer;
	GtkTextIter start, end;
	int char_count;
	char  temp_path[600];
	int i;
	FILE *fp;

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));	
       	gtk_text_buffer_get_start_iter ( buffer, &start);
        gtk_text_buffer_get_end_iter ( buffer, &end);
        text_buffer = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
	char_count = gtk_text_buffer_get_char_count(buffer);

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/notes");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
	for (i = 0; i < char_count; i++)
	{
		fprintf(fp, "%c", text_buffer[i]);		
	}
	fclose(fp);

	if ((fp = fopen("./initial_note", "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't find directory: %s\n\n", "./initial_note"); return 0; }
	for (i = 0; i < char_count; i++)
	{
		fprintf(fp, "%c", text_buffer[i]);		
	}
	fclose(fp);
	
	return 1;
}

int read_drawn_stimulus_current(char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/DrawnStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - DrawnStimulusCurrent File----------\n");		
	for (j = 0; j< all_stimulus_patterns.max_pattern_length; j++)
	{
		for (k=0; k<all_network->layer_count; k++)
		{
			ptr_layer = all_network->layers[k];			
			for (m=0; m<ptr_layer->neuron_group_count; m++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[m];
				for (n=0; n<ptr_neuron_group->neuron_count; n++)
				{
					fprintf(fp, "%.16E\t", all_stimulus_patterns.drawn_stimulus_currents[k][m][n][j]);
				}
				fprintf(fp,"\n");
			}
		}			
	}
	fprintf(fp,"----------SpikeGenerator - End of DrawnStimulusCurrent File----------\n");			
	fclose(fp);
	return 1;
}

int read_neuron_params(char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	Neuron		*ptr_neuron;

	//	double v;  load it from inial_neuron_dynamics log
	double a;
	double b;
	double c;
	double d;
	double k;
	double C;
	double v_resting;
	double v_threshold;
	double v_peak;
//	double I_inject;
	bool inhibitory;
	double E_excitatory;
	double E_inhibitory;
	double tau_excitatory;
	double tau_inhibitory;
	
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/NeuronParameters");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - NeuronParameters File----------\n");		
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				ptr_neuron = &(ptr_neuron_group->neurons[n]);	
				a = ptr_neuron->a;
				b = ptr_neuron->b;
				c = ptr_neuron->c;
				d = ptr_neuron->d;
				k = ptr_neuron->k;
				C = 1.0/ptr_neuron->E;
				v_resting = ptr_neuron->v_resting;
				v_threshold = ptr_neuron->v_threshold + ptr_neuron->v_resting;
				v_peak = ptr_neuron->v_peak + ptr_neuron->v_resting;
				inhibitory = ptr_neuron->inhibitory;
				E_excitatory = ptr_neuron->E_excitatory + ptr_neuron->v_resting;
				E_inhibitory = ptr_neuron->E_inhibitory + ptr_neuron->v_resting;
				tau_excitatory = -1.0/ptr_neuron->decay_rate_excitatory;
				tau_inhibitory = -1.0/ptr_neuron->decay_rate_inhibitory;								
				fprintf(fp, "%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%.16E\t%d\t%.16E\t%.16E\t%.16E\t%.16E\t", a, b, c, d, k, C, v_resting, v_threshold, v_peak, inhibitory, E_excitatory, E_inhibitory, tau_excitatory, tau_inhibitory);
				fprintf(fp,"\n");
			}
		}			
	}
	fprintf(fp,"----------SpikeGenerator - End of NeuronParameters File----------\n");			
	fclose(fp);
	return 1;
}



int read_data_directory(char *main_dir_path, int pattern_num)
{
	char data_directory_name[10];
	char data_directory_num[10];
	char  data_directory_path[600];	
	DIR	*dir_data_directory;	
	
	if (pattern_num <10)
	{
		strcpy(data_directory_name, "dat0000");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);
	}
	else if (pattern_num <100)
	{
		strcpy(data_directory_name, "dat000");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);		
	}
	else if (pattern_num <1000)
	{
		strcpy(data_directory_name, "dat00");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (pattern_num <10000)
	{
		strcpy(data_directory_name, "dat0");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (pattern_num <100000)
	{
		strcpy(data_directory_name, "dat");
		sprintf(data_directory_num, "%d" , pattern_num);
		strcat(data_directory_name, data_directory_num);			
	}	
	else
	{
		printf("DataFormat_v0: ERROR: bumber of patterns %d.\n", pattern_num);
		printf("DataFormat_v0: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, main_dir_path);	
	strcat(data_directory_path, "/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) != NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s already has %s folder.\n", main_dir_path, data_directory_name);		
                return 0;
        }
	mkdir(data_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);	

	if (read_data_files(data_directory_path, pattern_num))
		return 1;
	return 0;
}

int read_data_files(char  *data_directory_path, int pattern_num)
{
	if (!read_meta_data(data_directory_path, pattern_num))
		return 0;
	if (!read_raw_stimulus_current(data_directory_path, pattern_num))
		return 0;
	if (!read_noisy_stimulus_current(data_directory_path, pattern_num))
		return 0;		
	if (!read_spike_timestamps(data_directory_path, pattern_num))
		return 0;		
	return 1;
}

int read_meta_data(char *data_directory_path, int pattern_num)
{
	char temp_path[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	int i, j, k;
			
 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------SpikeGenerator - Meta Data File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"PATTERN_LENGTH_MS\t%d", all_stimulus_patterns.pattern_lengths_ms[pattern_num]); 	
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGES\n"); 	
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				fprintf(fp, "%.16E\n", initial_neuron_dynamics.v[pattern_num][i][j][k]);
			}
		}
	}	

	fprintf(fp,"----------SpikeGenerator - End of Meta Data File----------\n");
	fclose(fp);	
	return 1;
}

int read_raw_stimulus_current(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/RawStimulusCurrent");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - RawStimulusCurrent File----------\n");		
		
	for (k=0; k<all_network->layer_count; k++)
	{
		ptr_layer = all_network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns.pattern_lengths_ms[pattern_num]; j++)
				{				
					fprintf(fp, "%.16E\n", all_stimulus_patterns.raw_stimulus_currents[pattern_num][k][m][n][j]);						
				}
			}
		}
	}			

	fprintf(fp,"----------SpikeGenerator - RawStimulusCurrent File----------\n");			
	fclose(fp);
	return 1;
}

int read_noisy_stimulus_current(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/NoisyStimulusCurrent");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - NoisyStimulusCurrent File----------\n");		
		
	for (k=0; k<all_network->layer_count; k++)
	{
		ptr_layer = all_network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns.pattern_lengths_ms[pattern_num]; j++)
				{
					fprintf(fp, "%.16E\n", all_stimulus_patterns.noisy_stimulus_currents[pattern_num][k][m][n][j]);						
				}
			}
		}
	}			

	fprintf(fp,"----------SpikeGenerator - NoisyStimulusCurrent File----------\n");			
	fclose(fp);
	return 1;
}

int read_spike_timestamps(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int i;

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/SpikeTimeStamp");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikeGenerator - SpikeTimeStamp File----------\n");		
	
	for (i=0; i<spike_pattern_time_stamps.num_of_time_stamps_in_pattern[pattern_num]; i++)
	{
		fprintf(fp,"%llu\t", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].peak_time);
		fprintf(fp,"%d\t", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].mwa_or_layer);		
		fprintf(fp,"%d\t", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].channel_or_neuron_group);		
		fprintf(fp,"%d\n", spike_pattern_time_stamps.pattern_time_stamps[pattern_num][i].unit_or_neuron);									
	}			

	fprintf(fp,"----------SpikeGenerator - SpikeTimeStamp File----------\n");			
	fclose(fp);
	return 1;
}


