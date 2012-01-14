#include "DataFormat_v0.h"


static int create_main_meta_file(Network *network, char * main_dir_path);
static int save_notes(char* main_dir_path, GtkWidget *text_view);
static int save_drawn_stimulus_current(Network *network, char *main_dir_path);
static int save_neuron_params(Network * network, char *main_dir_path);
static int save_injected_current_noise_params(Network *network, char *main_dir_path);
static int save_initial_membrane_voltage_params(Network *network, char *main_dir_path);
static int create_data_directory(Network *network, char *main_dir_path, int pattern_num);
static int save_data_files(Network *network, char  *data_directory_path, int pattern_num);
static int save_meta_data(Network *network, char *data_directory_path, int pattern_num);
static int save_raw_stimulus_current(Network *network, char *data_directory_path, int pattern_num);
static int save_noisy_stimulus_current(Network *network, char *data_directory_path, int pattern_num);
static int save_spike_timestamps(char *data_directory_path, int pattern_num);

static int read_main_meta_file(Network *network, char * main_dir_path);
static int read_notes(char* main_dir_path, GtkWidget *text_view);
static int read_drawn_stimulus_current(Network *network, char *main_dir_path);
static int read_neuron_params(Network *network, char *main_dir_path);
static int read_injected_current_noise_params(Network *network, char *main_dir_path);
static int read_initial_membrane_voltage_params(Network *network, char *main_dir_path);
static int read_data_directory(Network *network, char *main_dir_path, int pattern_num);
static int read_data_files(Network *network, char  *data_directory_path, int pattern_num);
static int read_meta_data(Network *network, char *data_directory_path, int pattern_num);
static int read_raw_stimulus_current(Network *network, char *data_directory_path, int pattern_num);
static int read_noisy_stimulus_current(Network *network, char *data_directory_path, int pattern_num);
static int read_spike_timestamps(char *data_directory_path, int pattern_num);


int create_spike_pattern_generator_data_directory_v0(int num, ...)
{
	char *path_chooser;
	Network *network;
	DIR	*dir_main_folder;
	char main_dir_path[600];
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);
     	network = va_arg ( arguments, Network *);   	
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);	
	strcat(main_dir_path, "/SpikePatternGeneratorData");
	if ((dir_main_folder = opendir(main_dir_path)) != NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s already has SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder or delete SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }

	mkdir(main_dir_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

        printf ("DataFormat_v0: INFO: Created SpikePatternGeneratorData folder in: %s.\n", path_chooser);
        printf ("DataFormat_v0: INFO: SpikePatternGeneratorData path is: %s.\n\n", main_dir_path); 
        
	if (!create_main_meta_file(network, main_dir_path))
		return 0;
		
	return 1;
}

static int create_main_meta_file(Network *network, char * main_dir_path)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;
	int i,j;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	
	printf("Saving main meta file...\n");				
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------SpikePatternGenerator - Main Meta File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"NUM_OF_LAYERS\t%d\n",	network->layer_count);
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		fprintf(fp,"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n",	i, ptr_layer->neuron_group_count);	
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			fprintf(fp,"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n", i, j, ptr_neuron_group->neuron_count);		
		}			
	}
	fprintf(fp,"MAX_PATTERN_LENGTH\t%d\n", all_stimulus_patterns_info.max_pattern_length);
	fprintf(fp,"MIN_PATTERN_LENGTH\t%d\n", all_stimulus_patterns_info.min_pattern_length);	
	fprintf(fp,"NUM_OF_PATTERNS\t%d\n", all_stimulus_patterns_info.num_of_patterns);	
	for (i = 0; i< all_stimulus_patterns_info.num_of_patterns; i++)
	{
		fprintf(fp,"PATTERN_%d_LENGTH_MS\t%d\n", i, all_stimulus_patterns_info.pattern_lengths_ms[i]);			
	}
	for (i = 0; i< all_stimulus_patterns_info.num_of_patterns; i++)
	{
		fprintf(fp,"PATTERN_%d_NUM_OF_SPIKES\t%d\n", i, all_spike_patterns.num_of_time_stamps_in_pattern[i]);			
	}		
	fprintf(fp,"INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS\t%d\n", INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS);
	fprintf(fp,"MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%d\n",  MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS);
	fprintf(fp,"PARKER_SOCHACKI_ERROR_TOLERANCE\t%.16E\n", get_maximum_parker_sochacki_error_tolerance() );
	fprintf(fp,"PARKER_SOCHACKI_MAX_ORDER\t%d\n", get_maximum_parker_sochacki_order());	
	fprintf(fp,"----------SpikePatternGenerator - End of Main Meta File----------\n");
	fclose(fp);
	printf("Saving main meta file...complete\n");				
	return 1;
}

int save_spike_pattern_generator_data_directory_v0(int num, ...)
{
	int i;
	char *path_chooser;
	Network *network;
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	GtkWidget *text_view; 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);  
    	network = va_arg ( arguments, Network *);  	
    	text_view = va_arg ( arguments, GtkWidget *);   	
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        if(!save_notes(main_dir_path, text_view))
        	return 0;
        
        if(!save_drawn_stimulus_current(network, main_dir_path))
        	return 0;   
        	
	if(!save_neuron_params(network, main_dir_path))
        	return 0;      
  
  	if(!save_injected_current_noise_params(network, main_dir_path))
        	return 0;    
        	
  	if(!save_initial_membrane_voltage_params(network, main_dir_path))
        	return 0;          
        	 	    
	for (i = 0; i < all_stimulus_patterns_info.num_of_patterns ; i++)
	{
		if(!create_data_directory(network, main_dir_path, i))
        		return 0;
        }
        
        if ((fp = fopen("./path_initial_directory", "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", path_chooser);
	fclose (fp);	
	
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
	
	printf("Saving notes file...\n");				
	
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

	printf("Saving notes file...complete\n");	
					
	return 1;
}

static int save_drawn_stimulus_current(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	printf("Saving DrawnStimulusCurrent file...\n");				

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/DrawnStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikePatternGenerator - DrawnStimulusCurrent File----------\n");		
	for (k=0; k<network->layer_count; k++)
	{
		ptr_layer = network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				fprintf(fp, "-------------Layer: %d\tNeuron Group: %d\tNeuron: %d\t----------\n", k, m, n);
				for (j = 0; j< all_stimulus_patterns_info.max_pattern_length; j++)
				{
					fprintf(fp, "%.16E\n", all_stimulus_currents.drawn_stimulus_currents[k][m][n][j]);
				}
			}
		}			
	}
	fprintf(fp,"----------SpikePatternGenerator - End of DrawnStimulusCurrent File----------\n");			
	fclose(fp);

	printf("Saving DrawnStimulusCurrent file...complete\n");					
	return 1;
}

static int save_neuron_params(Network * network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, m, n;    // not to confuse with neuron' s k
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

	printf("Saving NeuronParameters file...\n");					
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/NeuronParameters");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikePatternGenerator - NeuronParameters File----------\n");		
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				ptr_neuron = &(ptr_neuron_group->neurons[n]);	
				a = ptr_neuron->a;
				b = ptr_neuron->b;
				c = ptr_neuron->c + ptr_neuron->v_resting;
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
				fprintf(fp,"Layer: %d\tNeuron Group: %d\tNeuron: %d\n", i, m, n);												
				fprintf(fp, "%.16E\n%.16E\n%.16E\n%.16E\n%.16E\n%.16E\n%.16E\n%.16E\n%.16E\n%d\n%.16E\n%.16E\n%.16E\n%.16E\n", a, b, c, d, k, C, v_resting, v_threshold, v_peak, inhibitory, E_excitatory, E_inhibitory, tau_excitatory, tau_inhibitory);
			}
		}			
	}
	fprintf(fp,"----------SpikePatternGenerator - End of NeuronParameters File----------\n");			
	fclose(fp);
	printf("Saving NeuronParameters file...complete\n");						
	return 1;
}

static int save_injected_current_noise_params(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, j, k;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	printf("Saving InjectedCurrentNoiseParams file...\n");						
	
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/InjectedCurrentNoiseParams");
 	
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	fprintf(fp,"----------SpikePatternGenerator - InjectedCurrentNoiseParams File----------\n");		
	fprintf(fp,"INJECTED_CURRENT_NOISE_VARIANCES\n");	
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{			
				fprintf(fp,"%.16E\n", all_stimulus_currents.noise_variances[i][j][k]);
			}	
		}			
	}	
	fprintf(fp,"INJECTED_CURRENT_NOISE_ADDITION_MS_INTERVALS\n");	
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{			
				fprintf(fp,"%u\n", all_stimulus_currents.noise_addition_ms_intervals[i][j][k]);
			}	
		}			
	}
	fprintf(fp,"----------SpikePatternGenerator - End of InjectedCurrentNoiseParams File----------\n");			
	fclose(fp);
	
	printf("Saving InjectedCurrentNoiseParams file...complete\n");							
	return 1;
}
        	
static int save_initial_membrane_voltage_params(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, j, k;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	printf("Saving InitialMembraneVoltageParams file...\n");							

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/InitialMembraneVoltageParams");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	fprintf(fp,"----------SpikePatternGenerator - InitialMembraneVoltageParams File----------\n");		
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_MEANS\n");
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{			
				fprintf(fp,"%.16E\n",  neuron_dynamics.initial_v_means[i][j][k]);
			}	
		}			
	}	
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_VARIANCES\n");
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{			
				fprintf(fp,"%.16E\n",  neuron_dynamics.initial_v_variances[i][j][k]);
			}	
		}			
	}	
	fprintf(fp,"----------SpikePatternGenerator - End of InitialMembraneVoltageParams File----------\n");			
	fclose(fp);

	printf("Saving InitialMembraneVoltageParams file...complete\n");								
	return 1;

}

static int create_data_directory(Network *network, char *main_dir_path, int pattern_num)
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
	
	printf("Created data directory: %s\n", data_directory_name);	
								
	if (save_data_files(network, data_directory_path, pattern_num))
		return 1;
	return 0;
}

static int save_data_files(Network *network, char  *data_directory_path, int pattern_num)
{
	if (!save_meta_data(network, data_directory_path, pattern_num))
		return 0;
	if (!save_raw_stimulus_current(network,data_directory_path, pattern_num))
		return 0;
	if (!save_noisy_stimulus_current(network, data_directory_path, pattern_num))
		return 0;		
	if (!save_spike_timestamps(data_directory_path, pattern_num))
		return 0;		
	return 1;
}

static int save_meta_data(Network *network, char *data_directory_path, int pattern_num)
{
	char temp_path[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	int i, j, k;

	printf("Saving meta data file...\n");								
			
 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------SpikePatternGenerator - Meta Data File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"PATTERN_LENGTH_MS\t%d\n", all_stimulus_patterns_info.pattern_lengths_ms[pattern_num]);	
	fprintf(fp,"NUM_OF_SPIKES_IN_PATTERN\t%d\n", all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]);		
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGES\n"); 	
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];			
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				fprintf(fp, "%.16E\n", neuron_dynamics.initial_v[pattern_num][i][j][k]);
			}
		}
	}	

	fprintf(fp,"----------SpikePatternGenerator - End of Meta Data File----------\n");
	fclose(fp);	
	
	printf("Saving meta data file...complete\n");								
		
	return 1;
}

static int save_raw_stimulus_current(Network *network, char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	printf("Saving RawStimulusCurrent file...\n");								

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/RawStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikePatternGenerator - RawStimulusCurrent File----------\n");		
		
	for (k=0; k<network->layer_count; k++)
	{
		ptr_layer = network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns_info.pattern_lengths_ms[pattern_num]; j++)
				{				
					fprintf(fp, "%.16E\n", all_stimulus_currents.raw_stimulus_currents[pattern_num][k][m][n][j]);						
				}
			}
		}
	}			

	fprintf(fp,"----------SpikePatternGenerator - End of RawStimulusCurrent File----------\n");			
	fclose(fp);
	
	printf("Saving RawStimulusCurrent file...complete\n");									
	return 1;
}

static int save_noisy_stimulus_current(Network *network, char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	printf("Saving NoisyStimulusCurrent file...\n");								

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/NoisyStimulusCurrent");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikePatternGenerator - NoisyStimulusCurrent File----------\n");		
		
	for (k=0; k<network->layer_count; k++)
	{
		ptr_layer = network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns_info.pattern_lengths_ms[pattern_num]; j++)
				{
					fprintf(fp, "%.16E\n", all_stimulus_currents.noisy_stimulus_currents[pattern_num][k][m][n][j]);						
				}
			}
		}
	}			

	fprintf(fp,"----------SpikePatternGenerator - End of NoisyStimulusCurrent File----------\n");			
	fclose(fp);
	
	printf("Saving NoisyStimulusCurrent file...complete\n");			
							
	return 1;
}

int save_spike_timestamps(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int i;

	printf("Saving SpikeTimeStamp file...\n");								

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/SpikeTimeStamp");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	
	fprintf(fp,"----------SpikePatternGenerator - SpikeTimeStamp File----------\n");		
	
	for (i=0; i<all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]; i++)
	{
		fprintf(fp,"%llu\t", all_spike_patterns.pattern_time_stamps[pattern_num][i].peak_time);
		fprintf(fp,"%d\t", all_spike_patterns.pattern_time_stamps[pattern_num][i].mwa_or_layer);		
		fprintf(fp,"%d\t", all_spike_patterns.pattern_time_stamps[pattern_num][i].channel_or_neuron_group);		
		fprintf(fp,"%d\n", all_spike_patterns.pattern_time_stamps[pattern_num][i].unit_or_neuron);									
	}			

	fprintf(fp,"----------SpikePatternGenerator - End of SpikeTimeStamp File----------\n");			
	fclose(fp);
	
	printf("Saving SpikeTimeStamp file...complete\n");									
	return 1;
}


int load_spike_pattern_generator_data_directory_v0(int num, ...)
{
	int i;
	char *path_chooser;
	Network *network;
	DIR	*dir_main_folder;
	char main_dir_path[600];
	GtkWidget *text_view; 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   
     	network = va_arg ( arguments, Network *);      		
    	text_view = va_arg ( arguments, GtkWidget *);   	
	va_end ( arguments );
	

	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to load 
	printf("Loading %s...\n",main_dir_path);
	
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }

	if (!read_main_meta_file(network, main_dir_path))
		return 0;
		
        if(!read_notes(main_dir_path, text_view))
        	return 0;
        
        if(!read_drawn_stimulus_current(network, main_dir_path))
        	return 0;   
        	
	if(!read_neuron_params(network, main_dir_path))
        	return 0;      
 
	if(!read_injected_current_noise_params(network, main_dir_path))
		return 0;
 
	if(!read_initial_membrane_voltage_params(network, main_dir_path))
		return 0;
		        	
 	for (i = 0; i < all_stimulus_patterns_info.num_of_patterns ; i++)
	{
		if(!read_data_directory(network, main_dir_path, i))
        		return 0;
        }
        
 	printf("Loading %s...complete\n",main_dir_path);              	
	return 1;
}

int read_main_meta_file(Network *network, char * main_dir_path)
{
	char  temp_path[600];
	char line[1000];
	char word[100];	
	FILE *fp;
	int i,j;
	int line_cntr = 0;
	int num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	
	printf("Loading main meta file...\n");		
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}  		
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_layers = (int)atof(word);
//////////////////////////////////////////////////   EDIT THIS ////////////////////////////////////////
//	neurosim_set_ext_network(allocate_external_network(neurosim_get_ext_network()));   
	allocate_network(network);
	for (i=0; i<num_of_layers; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n"
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		num_of_neuron_groups_in_layer = (int)atof(word);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n"
			if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
			num_of_neurons_in_neuron_group = (int)atof(word);
			if (!add_neurons_to_layer(network, num_of_neurons_in_neuron_group, i, 0, 0, 0, 0, 0, 0, 100.0, 0, 0, 0, 0, 0, 0, 0, 1.0, 1.0, 0))	// create neurons and neuron groups with no parameter.
				return 0;
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"MAX_PATTERN_LENGTH\t%d\n"
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	all_stimulus_patterns_info.max_pattern_length = (TimeStampMs)atof(word);
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"MIN_PATTERN_LENGTH\t%d\n"
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	all_stimulus_patterns_info.min_pattern_length = (TimeStampMs)atof(word);
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_PATTERNS\t%d\n"
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	all_stimulus_patterns_info.num_of_patterns = atoi(word);
	all_stimulus_patterns_info.pattern_lengths_ms = g_new0(TimeStampMs, all_stimulus_patterns_info.num_of_patterns);
	for (i = 0 ; i < all_stimulus_patterns_info.num_of_patterns; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		all_stimulus_patterns_info.pattern_lengths_ms[i] = (TimeStampMs)atof(word);		
	}

	if (!allocate_stimulus_currents(network))
		return FALSE;
		
	if (!allocate_neuron_dynamics(network))	
		return FALSE;
		
	if (!allocate_spike_patterns(network))		
		return FALSE;
	
	for (i = 0 ; i < all_stimulus_patterns_info.num_of_patterns; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		all_spike_patterns.num_of_time_stamps_in_pattern[i] = (int)atof(word);	
		all_spike_patterns.pattern_time_stamps[i] = g_new0(SpikeTimeStampItem, all_spike_patterns.num_of_time_stamps_in_pattern[i]);		
	}	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"INJECTED_CURRENT_PATTERN_SAMPLING_INTERVAL_MS\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"MIN_INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%d\n"
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	PARKER_SOCHACKI_ERROR_TOLERANCE
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	double ps_tol = atof(word);
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	PARKER_SOCHACKI_MAX_ORDER
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	int ps_order = (int)atof(word);	
	if (!parker_sochacki_set_order_tolerance(network, ps_order, ps_tol))
		return 0;
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - End of Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}  
	fclose(fp);
	
	printf("Loading main meta file...complete\n");			
	return 1;
}

int read_notes(char* main_dir_path, GtkWidget *text_view)
{
	char line[1000];
	char  temp_path[600];	
	FILE *fp;
	int i = 0;
	GtkTextIter start, end;

	printf("Reading notes file...\n");		

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/notes");	
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));	
       	gtk_text_buffer_get_start_iter ( buffer, &start);
        gtk_text_buffer_get_end_iter ( buffer, &end);
	gtk_text_buffer_delete (buffer, &start, &end);
       	gtk_text_buffer_get_start_iter ( buffer, &start);
        gtk_text_buffer_get_end_iter ( buffer, &end);
                
        if ((fp = fopen(temp_path, "r")) == NULL)  
       	{ 
       		printf ("ERROR: SpikePatternGenerator: Couldn't find file %s\n", temp_path); 
       		printf ("ERROR: SpikePatternGenerator: N/A is loaded as note\n");
		gtk_text_buffer_set_text (gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), "N/A\n", -1);       		 
       	}
       	else
       	{
   		
		while (fgets(line, sizeof line, fp ) != NULL) 
		{ 
        		gtk_text_buffer_get_end_iter ( buffer, &end);   				
			gtk_text_buffer_insert(buffer, &end, line, -1);
			i++;
			if (i == 200)
			{
       				printf ("ERROR: SpikePatternGenerator: ./initial_note is longer than 200 lines.\n");
       				printf ("ERROR: SpikePatternGenerator: Only initial 200 lines were read.\n\n");      
       				break; 				 				
			}
		}
		fclose(fp);       		
       	}
       	
       	printf("Reading notes file...complete\n");			
	return 1;
}

static int read_drawn_stimulus_current(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	char  line[1000];	
	int line_cntr = 0;	
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

       	printf("Reading DrawnStimulusCurrent file...\n");			

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/DrawnStimulusCurrent");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }	

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - DrawnStimulusCurrent File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - DrawnStimulusCurrent File\n");
		fclose(fp);
		return 0;
	}
	  
	for (k=0; k<network->layer_count; k++)
	{
		ptr_layer = network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   			
				for (j = 0; j< all_stimulus_patterns_info.max_pattern_length; j++)
				{
					if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
					all_stimulus_currents.drawn_stimulus_currents[k][m][n][j] = atof(line);
				}
			}
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - End of DrawnStimulusCurrent File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - DrawnStimulusCurrent File\n");
		fclose(fp);
		return 0;
	}	
		
	fclose(fp);
	
       	printf("Reading DrawnStimulusCurrent file...complete\n");				
	return 1;
}

static int read_neuron_params(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, m, n;
	char  line[1000];	
	int line_cntr = 0;	
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

       	printf("Reading NeuronParameters file...\n");				
	
 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/NeuronParameters");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - NeuronParameters File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - NeuronParameters File\n");
		fclose(fp);
		return 0;
	}	
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				ptr_neuron = &(ptr_neuron_group->neurons[n]);	
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
				a = atof(line);	
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				b = atof(line);
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
				c = atof(line);	
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				d = atof(line);			
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				k = atof(line);				
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				C = atof(line);					
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				v_resting = atof(line);		
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				v_threshold = atof(line);						
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				v_peak = atof(line);						
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				inhibitory = (bool)atof(line);		
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				E_excitatory = atof(line);		
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				E_inhibitory = atof(line);						
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				tau_excitatory = atof(line);						
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				tau_inhibitory = atof(line);																															
				if (!submit_new_neuron_params(network, ptr_neuron, v_resting, a, b, c, d, k, C, v_resting, v_threshold, v_peak, 0, inhibitory, E_excitatory, E_inhibitory, tau_excitatory, tau_inhibitory))
					return 0; 
			}
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - End of NeuronParameters File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - NeuronParameters File\n");
		fclose(fp);
		return 0;
	}					
	fclose(fp);
	
       	printf("Reading NeuronParameters file...complete\n");					
	return 1;
}

static int read_injected_current_noise_params(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, j, k;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	char  line[1000];	
	int line_cntr = 0;
	
       	printf("Reading InjectedCurrentNoiseParams file...\n");					

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/InjectedCurrentNoiseParams");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - InjectedCurrentNoiseParams File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - InjectedCurrentNoiseParams File\n");
		fclose(fp);
		return 0;
	}	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}
				all_stimulus_currents.noise_variances[i][j][k] = atof(line);							
			}	
		}			
	}	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	for (i=0; i< network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{	
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}					
				all_stimulus_currents.noise_addition_ms_intervals[i][j][k] = (TimeStampMs)atof(line);
			}	
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - End of InjectedCurrentNoiseParams File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - InjectedCurrentNoiseParams File\n");
		fclose(fp);
		return 0;
	}
	fclose(fp);
	
       	printf("Reading InjectedCurrentNoiseParams file...complete\n");						
	
	return 1;
}
        	
static int read_initial_membrane_voltage_params(Network *network, char *main_dir_path)
{
	char  temp_path[600];
	FILE *fp;
	int i, j, k;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	char  line[1000];	
	int line_cntr = 0;
	
       	printf("Reading InitialMembraneVoltageParams file...\n");						

 	strcpy(temp_path, main_dir_path);
 	strcat(temp_path, "/InitialMembraneVoltageParams");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - InitialMembraneVoltageParams File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - InitialMembraneVoltageParams File\n");
		fclose(fp);
		return 0;
	}		
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	for (i=0; i< network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{	
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}										
				neuron_dynamics.initial_v_means[i][j][k] =atof(line);	
			}	
		}			
	}	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	for (i=0; i<network->layer_count; i++)
	{
		ptr_layer = network->layers[i];
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group ->neuron_count; k++)
			{		
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}														
				neuron_dynamics.initial_v_variances[i][j][k]=atof(line);	
			}	
		}			
	}	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - End of InitialMembraneVoltageParams File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - InitialMembraneVoltageParams File\n");
		fclose(fp);
		return 0;
	}	
	fclose(fp);
	
       	printf("Reading InitialMembraneVoltageParams file...complete\n");							
	return 1;

}


static int read_data_directory(Network *network, char *main_dir_path, int pattern_num)
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
	if ((dir_data_directory = opendir(data_directory_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no %s folder.\n", main_dir_path, data_directory_name);		
                return 0;
        }

       	printf("Reading data directory: %s\n", data_directory_name);							

	if (read_data_files(network, data_directory_path, pattern_num))
		return 1;
	return 0;
}

static int read_data_files(Network *network, char  *data_directory_path, int pattern_num)
{
	if (!read_meta_data(network, data_directory_path, pattern_num))
		return 0;
	if (!read_raw_stimulus_current(network, data_directory_path, pattern_num))
		return 0;
	if (!read_noisy_stimulus_current(network, data_directory_path, pattern_num))
		return 0;		
	if (!read_spike_timestamps(data_directory_path, pattern_num))
		return 0;		
	return 1;
}

static int read_meta_data(Network *network, char *data_directory_path, int pattern_num)
{
	char temp_path[600];
	FILE *fp;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	int i, j, k;
	char  line[1000];	
	int line_cntr = 0;
	
       	printf("Reading meta data file...\n");							
			
 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't open file: %s\n\n", temp_path); return 0; }
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	
	if (strcmp(line, "----------SpikePatternGenerator - Meta Data File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Meta Data File\n");
		fclose(fp);
		return 0;
	}		
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  // version	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  // creation date
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  // pattern_length	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  // num_of_spikes_in_pattern
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  // INITIAL_NEURON_MEMBRANE_VOLTAGES
	for (i=0; i< network->layer_count; i++)
	{
		ptr_layer = network->layers[i];			
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  // creation date				
				neuron_dynamics.initial_v[pattern_num][i][j][k] = atof(line);
			}
		}
	}	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - End of Meta Data File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Meta Data File\n");
		fclose(fp);
		return 0;
	}
	fclose(fp);	
	
	printf("Reading meta data file...complete\n");	
							
	return 1;
}

static int read_raw_stimulus_current(Network *network, char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	char  line[1000];	
	int line_cntr = 0;
	
       	printf("Reading RawStimulusCurrent file...\n");							

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/RawStimulusCurrent");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line, "----------SpikePatternGenerator - RawStimulusCurrent File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - RawStimulusCurrent File\n");
		fclose(fp);
		return 0;
	}		
	for (k=0; k< network->layer_count; k++)
	{
		ptr_layer = network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns_info.pattern_lengths_ms[pattern_num]; j++)
				{		
					if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  						
					all_stimulus_currents.raw_stimulus_currents[pattern_num][k][m][n][j] = atof(line);						
				}
			}
		}
	}			

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - End of RawStimulusCurrent File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - RawStimulusCurrent File\n");
		fclose(fp);
		return 0;
	}		
			
	fclose(fp);
	
       	printf("Reading RawStimulusCurrent file...complete\n");								
	return 1;
}

static int read_noisy_stimulus_current(Network *network, char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	FILE *fp;
	int j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	char  line[1000];	
	int line_cntr = 0;
	
       	printf("Reading NoisyStimulusCurrent file...\n");								

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/NoisyStimulusCurrent");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - NoisyStimulusCurrent File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - NoisyStimulusCurrent File\n");
		fclose(fp);
		return 0;
	}		
	
	for (k=0; k< network->layer_count; k++)
	{
		ptr_layer = network->layers[k];			
		for (m=0; m<ptr_layer->neuron_group_count; m++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[m];
			for (n=0; n<ptr_neuron_group->neuron_count; n++)
			{
				for (j = 0; j < all_stimulus_patterns_info.pattern_lengths_ms[pattern_num]; j++)
				{
					if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  				
					all_stimulus_currents.noisy_stimulus_currents[pattern_num][k][m][n][j] = atof(line);				
				}
			}
		}
	}			

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - End of NoisyStimulusCurrent File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - NoisyStimulusCurrent File\n");
		fclose(fp);
		return 0;
	}			
	fclose(fp);
	
       	printf("Reading NoisyStimulusCurrent file...complete\n");									
	return 1;
}

int read_spike_timestamps(char *data_directory_path, int pattern_num)
{
	char  temp_path[600];
	char  *end_ptr;	
	FILE *fp;
	int i;
	char  line[1000];	
	int line_cntr = 0;
	char word[100];	
		
       	printf("Reading SpikeTimeStamp file...\n");								

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/SpikeTimeStamp");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - SpikeTimeStamp File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - SpikeTimeStamp File\n");
		fclose(fp);
		return 0;
	}		


	for (i=0; i<all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  	
		if(!get_word_in_line('\t', 0, word, line, TRUE)) { fclose(fp); return 0; }
		all_spike_patterns.pattern_time_stamps[pattern_num][i].peak_time = strtoull(word, &end_ptr, 10);	// tested with llu max: 18446744073709551615
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		all_spike_patterns.pattern_time_stamps[pattern_num][i].mwa_or_layer = atoi(word);	
		if(!get_word_in_line('\t', 2, word, line, TRUE)) { fclose(fp); return 0; }
		all_spike_patterns.pattern_time_stamps[pattern_num][i].channel_or_neuron_group = atoi(word);	
		if(!get_word_in_line('\t', 3, word, line, TRUE)) { fclose(fp); return 0; }
		all_spike_patterns.pattern_time_stamps[pattern_num][i].unit_or_neuron = atoi(word);									
	}			

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - End of SpikeTimeStamp File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - SpikeTimeStamp File\n");
		fclose(fp);
		return 0;
	}					
	fclose(fp);
	
       	printf("Reading SpikeTimeStamp file...complete\n");									
	return 1;
}

int spike_pattern_generator_data_get_num_of_layers_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int *num_of_layers (send &num_of_layers to update)

	char *path_chooser;
	int *num_of_layers;
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	char temp_path[600];	
	char  line[1000];
	int line_cntr = 0;
	char word[100];				
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   
    	num_of_layers = va_arg ( arguments, int *);      		
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        strcpy(temp_path, main_dir_path);
        strcat(temp_path, "/meta");
        
 	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}                
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	*num_of_layers = atoi(word);    
	fclose(fp);    		
	return 1;			

}

int spike_pattern_generator_data_get_num_of_neuron_groups_in_layer_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int layer, int *num_of_neuron_groups (send &num_of_neuron_groups to update)

	int i, j, num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	char *path_chooser;
	int layer;
	int *num_of_neuron_groups;	
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	char temp_path[600];
	char  line[1000];
	int line_cntr = 0;
	char word[100];					
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   
     	layer = va_arg ( arguments, int);    	
      	num_of_neuron_groups = va_arg ( arguments, int *);    	    		
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        strcpy(temp_path, main_dir_path);
        strcat(temp_path, "/meta");
        
 	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}                
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_layers = atoi(word);
	
	if (layer >= num_of_layers)
	{
		fclose(fp);    		
		printf("DataFormat_v0: spike_pattern_generator_data_get_num_of_neuron_groups_in_layer_v0: ERROR: Inconvenient layer number %d.\n", layer);		
		return 0;
	}
	
	for (i=0; i<num_of_layers; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n"
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		if (i == layer)
		{
			*num_of_neuron_groups = atoi(word);
			fclose(fp);    		
			return 1;
		}	
		num_of_neuron_groups_in_layer = atoi(word);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n"
			if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
			num_of_neurons_in_neuron_group = atoi(word);
		}			
	}
	fclose(fp);    		
	printf("DataFormat_v0: spike_pattern_generator_data_get_num_of_neuron_groups_in_layer_v0: ERROR: Couldn' t find the specified layer %d in meta file\n", layer);
	return 0;	

}
int spike_pattern_generator_data_get_num_of_neurons_in_neuron_group_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int layer, int nrn_grp, int *num_of_neurons (send &num_of_neurons to update)
	int i, j, num_of_layers, num_of_neuron_groups_in_layer, num_of_neurons_in_neuron_group;
	char *path_chooser;
	int layer, nrn_grp;
	int *num_of_neurons;	
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	char temp_path[600];
	char  line[1000];
	int line_cntr = 0;
	char word[100];					
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   
     	layer = va_arg ( arguments, int);    
      	nrn_grp = va_arg ( arguments, int);      		
      	num_of_neurons = va_arg ( arguments, int *);    	    		
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        strcpy(temp_path, main_dir_path);
        strcat(temp_path, "/meta");
        
 	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}                
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_layers = atoi(word);
	
	if (layer >= num_of_layers)
	{
		fclose(fp);    		
		printf("DataFormat_v0: spike_pattern_generator_data_get_num_of_neurons_in_neuron_group_v0: ERROR: Inconvenient layer number %d.\n", layer);		
		return 0;
	}
	
	for (i=0; i<num_of_layers; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n"
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		num_of_neuron_groups_in_layer = atoi(word);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n"
			if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
			if ((i == layer) && (j == nrn_grp))
			{
				*num_of_neurons = atoi(word);
				fclose(fp);    		
				return 1;
			}						
			num_of_neurons_in_neuron_group = atoi(word);
		}			
	}
	fclose(fp);    		
	printf("DataFormat_v0: spike_pattern_generator_data_get_num_of_neurons_in_neuron_group_v0: ERROR: Couldn' t find the specified neuron group %d in layer %d in meta file\n", nrn_grp, layer);
	return 0;	
}
int spike_pattern_generator_data_get_num_of_patterns_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int *num_of_patterns (send &num_of_patterns to update)

	int i, j, num_of_layers, num_of_neuron_groups_in_layer;
	char *path_chooser;
	int *num_of_patterns;	
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	char temp_path[600];
	char  line[1000];
	int line_cntr = 0;
	char word[100];					
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   
      	num_of_patterns = va_arg ( arguments, int *);    	    		
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        strcpy(temp_path, main_dir_path);
        strcat(temp_path, "/meta");
        
 	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}                
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_layers = atoi(word);
	
	for (i=0; i<num_of_layers; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n"
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		num_of_neuron_groups_in_layer = atoi(word);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n"
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	MAX_PATTERN_LENGTH	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	MIN_PATTERN_LENGTH 		
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	NUM_OF_PATTERNS
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	*num_of_patterns = atoi(word);	
	fclose(fp);    		
	return 1;
}
int spike_pattern_generator_data_get_pattern_length_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int pattern_num, TimeStampMs *pattern_length (send &pattern_length to update)

	int i, j, num_of_layers, num_of_neuron_groups_in_layer;
	char *path_chooser;
	int pattern_num;
	int num_of_patterns;	
	TimeStampMs *pattern_length;	
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	char temp_path[600];
	char  line[1000];
	int line_cntr = 0;
	char word[100];					
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);
    	pattern_num = va_arg ( arguments, int);   
       	pattern_length = va_arg ( arguments, TimeStampMs *);    	    		
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        strcpy(temp_path, main_dir_path);
        strcat(temp_path, "/meta");
        
 	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}                
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_layers = atoi(word);
	
	for (i=0; i<num_of_layers; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n"
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		num_of_neuron_groups_in_layer = atoi(word);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n"
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	MAX_PATTERN_LENGTH	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	MIN_PATTERN_LENGTH 		
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	NUM_OF_PATTERNS
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_patterns = atoi(word);		
	for (i=0; i<num_of_patterns; i++ )
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	PATTERN_LENGTH_MS
		if (i == pattern_num)
		{
			if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
			*pattern_length = (TimeStampMs)atof(word);
			fclose(fp);
			return 1;
		}		
	}
	printf("DataFormat_v0: spike_pattern_generator_data_get_pattern_length_v0: ERROR: Requested pattern_num(%d) is invalid.\n", pattern_num);	
	fclose(fp);    		
	return 0;
}
int spike_pattern_generator_data_get_num_of_spikes_in_pattern_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int pattern_num, int *num_of_spikes (send &num_of_spikes)

	int i, j, num_of_layers, num_of_neuron_groups_in_layer;
	char *path_chooser;
	int pattern_num;
	int num_of_patterns;
	int *num_of_spikes;		
	FILE *fp;	
	DIR	*dir_main_folder;
	char main_dir_path[600];
	char temp_path[600];
	char  line[1000];
	int line_cntr = 0;
	char word[100];					
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);
    	pattern_num = va_arg ( arguments, int);   
       	num_of_spikes = va_arg ( arguments, int *);    	    		
	va_end ( arguments );
	
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 
	if ((dir_main_folder = opendir(main_dir_path)) == NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s has no SpikePatternGeneratorData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder that includes SpikePatternGeneratorData directory.\n\n");		        		
                return 0;
        }
        
        strcpy(temp_path, main_dir_path);
        strcat(temp_path, "/meta");
        
 	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't read file: %s\n\n", temp_path); return 0; }

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------SpikePatternGenerator - Main Meta File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - Main Meta File\n");
		fclose(fp);
		return 0;
	}                
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"DATA_FORMAT_VERSION\t%d\n"	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	"CREATION_DATE\t%s" 	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_LAYERS\t%d\n",
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_layers = atoi(word);
	
	for (i=0; i<num_of_layers; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURON_GROUPS_IN_LAYER_%d\t%d\n"
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		num_of_neuron_groups_in_layer = atoi(word);
		for (j=0; j<num_of_neuron_groups_in_layer; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   //	"NUM_OF_NEURONS_IN_LAYER_%d_NEURON_GROUP_%d\t%d\n"
		}			
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	MAX_PATTERN_LENGTH	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	MIN_PATTERN_LENGTH 		
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	NUM_OF_PATTERNS
	if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
	num_of_patterns = atoi(word);		
	for (i=0; i<num_of_patterns; i++ )
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	PATTERN_LENGTH_MS
	}	
	for (i=0; i<num_of_patterns; i++ )
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}   // 	PATTERN_LENGTH_MS
		if (i == pattern_num)
		{
			if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
			*num_of_spikes = atoi(word);
			fclose(fp);
			return 1;
		}		
	}
	printf("DataFormat_v0: spike_pattern_generator_data_get_num_of_spikes_in_pattern_v0: ERROR: Requested pattern_num(%d) is invalid.\n", pattern_num);	
	fclose(fp);    		
	return 0;
}
int spike_pattern_generator_data_get_all_spike_time_stamps_in_pattern_v0(int num, ...)
{
//	Input Parameters   	char *path_chooser, int pattern_num, int num_of_spikes_in_pattern, SpikeTimeStampItem *spike_stime_stamps, (send spike_stime_stamps)

	int i;
	char  temp_path[600];
	char main_dir_path[600];	
	char  *end_ptr;	
	FILE *fp;   
	char  line[1000];	
	int line_cntr = 0;
	char word[100];	

	char data_directory_name[10];
	char data_directory_num[10];
	char  data_directory_path[600];	
	DIR	*dir_data_directory;	

	char *path_chooser;
	int pattern_num;
	int num_of_spikes_in_pattern;
	SpikeTimeStampItem *spike_time_stamps;

  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);
    	pattern_num = va_arg ( arguments, int);   
	num_of_spikes_in_pattern = va_arg ( arguments, int);   	
       	spike_time_stamps = va_arg ( arguments, SpikeTimeStampItem *); 
	va_end ( arguments );

	if (spike_time_stamps == NULL)
	{
		printf("DataFormat_v0: spike_pattern_generator_data_get_all_spike_time_stamps_in_pattern_v0: ERROR: spike_time_stamps == NULL\n");		
		return 0;
	}

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
	strcpy(main_dir_path, path_chooser);						// SpikePatternGeneratorData should be selected to save 	
	strcpy(data_directory_path, main_dir_path);	
	strcat(data_directory_path, "/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) == NULL)
       	{	
       		printf ("DataFormat_v0: ERROR: path: %s has no %s folder.\n", main_dir_path, data_directory_name);		
               	return 0;
       	}

	printf("Successful opendir for data directory: %s\n", data_directory_name);		

 	strcpy(temp_path, data_directory_path);
 	strcat(temp_path, "/SpikeTimeStamp");
	if ((fp = fopen(temp_path, "r")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't create file: %s\n\n", temp_path); return 0; }	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - SpikeTimeStamp File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - SpikeTimeStamp File\n");
		fclose(fp);
		return 0;
	}
	printf("Reading SpikeTimeStamp file : %s\n", temp_path);	
				
	for (i = 0; i < num_of_spikes_in_pattern; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
		if(!get_word_in_line('\t', 0, word, line, TRUE)) { fclose(fp); return 0; }
		spike_time_stamps[i].peak_time = strtoull(word, &end_ptr, 10);	// tested with llu max: 18446744073709551615
		if(!get_word_in_line('\t', 1, word, line, TRUE)) { fclose(fp); return 0; }
		spike_time_stamps[i].mwa_or_layer = atoi(word);	
		if(!get_word_in_line('\t', 2, word, line, TRUE)) { fclose(fp); return 0; }
		spike_time_stamps[i].channel_or_neuron_group = atoi(word);	
		if(!get_word_in_line('\t', 3, word, line, TRUE)) { fclose(fp); return 0; }
		spike_time_stamps[i].unit_or_neuron = atoi(word);
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, temp_path);  fclose(fp); return 0; } else {line_cntr++;}  
	if (strcmp(line,"----------SpikePatternGenerator - End of SpikeTimeStamp File----------\n") != 0)
	{
		printf("DataFormat_v0: ERROR: Not a valid SpikePatternGenerator - SpikeTimeStamp File\n");
		fclose(fp);
		return 0;
	}					
	fclose(fp);
	printf("Reading SpikeTimeStamp file...complete\n");	
	return 1;								
}

