#include "DataFormat_v0.h"


int create_main_directory_v0(int num, ...)
{
	FILE *fp;
	char *path_chooser;
	DIR	*dir_main_folder;
	char temp_dir_path[600];
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *);   	
	va_end ( arguments );
	
	strcpy(temp_dir_path, path_chooser);	
	strcat(temp_dir_path, "/SpikePatternGeneratorData");
	if ((dir_main_folder = opendir(temp_dir_path)) != NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s already has BlueSpikeData folder.\n", path_chooser);		
        	printf ("DataFormat_v0: ERROR: Select another folder or delete SpikeGeneratorData directory.\n\n");		        		
                return 0;
        }
 	strcpy(main_directory_path, temp_dir_path);	
	mkdir(main_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

        printf ("DataFormat_v0: Created SpikePatternGeneratorData folder in: %s.\n", path_chooser);
        printf ("DataFormat_v0: SpikePatternGeneratorData path is: %s.\n\n", main_directory_path); 
        
	if (!create_main_meta_file())
		return 0;

	if (!create_main_logs_file())
		return 0;
		
	if ((fp = fopen("./path_initial_directory", "w")) == NULL)  { printf ("ERROR: DataFormat_v0: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", path_chooser);
	fclose (fp);		

	return 1;
}

int create_main_meta_file(void)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;
	int i,j,k;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	Neuron		*ptr_neuron;
		
 	strcpy(temp_path, main_directory_path);
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
	fprintf(fp,"INJECTED_CURRENT_NOISE_ADDITION_INTERVAL_MS\t%f\n", injected_current_noise_addition_interval_ms;
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_MEAN\t%f\n", initial_neuron_membrane_voltage_mean);
	fprintf(fp,"INITIAL_NEURON_MEMBRANE_VOLTAGE_VARIANCE\t%f\n", initial_neuron_membrane_voltage_variance);	
	fprintf(fp,"----------SpikeGenerator - End of Main Meta File----------\n");
	fclose(fp);
	return 1;
}

int create_data_directory_v0(int num, ...)
{
	char data_directory_name[10];
	char data_directory_num[10];
	DIR	*dir_data_directory;	
	
	TimeStamp rec_start;
	
  	va_list arguments;
	va_start ( arguments, num );   
    	rec_start = va_arg ( arguments, TimeStamp);   	
	va_end ( arguments );	
	
	if (data_directory_cntr <10)
	{
		strcpy(data_directory_name, "dat0000");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);
	}
	else if (data_directory_cntr <100)
	{
		strcpy(data_directory_name, "dat000");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}
	else if (data_directory_cntr <1000)
	{
		strcpy(data_directory_name, "dat00");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (data_directory_cntr <10000)
	{
		strcpy(data_directory_name, "dat0");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (data_directory_cntr <100000)
	{
		strcpy(data_directory_name, "dat");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);			
	}	
	else
	{
		printf("DataFormat_v0: ERROR: data directory counter is %d.\n", data_directory_cntr);
		printf("DataFormat_v0: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, main_directory_path);	
	strcat(data_directory_path, "/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) != NULL)
        {
        	printf ("DataFormat_v0: ERROR: path: %s already has %s folder.\n", main_directory_path, data_directory_name);		
                return 0;
        }
	mkdir(data_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);	

	if (create_data_files(rec_start))
		data_directory_cntr++;

	return 1;
}

int create_data_files(TimeStamp rec_start)
{
	file_ptr_arr = g_new0(FILE*, NUM_OF_DATA_FILE_PER_RECORDING);    
	
	int time_prev = rt_get_cpu_time_ns();
	int time_curr;

	if (!create_recording_data())
		return 0;
	if (!create_blue_spike_time_stamp_data())
		return 0;
	if (!create_spike_time_stamp_data())
		return 0;		
	if (!create_exp_envi_event_data())
		return 0;		
	if (!create_exp_envi_command_data())
		return 0;			
	if (!create_mov_obj_event_data())
		return 0;		
	if (!create_mov_obj_command_data())
		return 0;
	if (!create_meta_data(rec_start))
		return 0;		
	time_curr = rt_get_cpu_time_ns();
	if ((time_curr - time_prev) > 100000000)		// if writing exceeds x milliseconds, there might be buffer reading error. (buffer might be overwrited before reading it.)
	{								
		printf ("Recorder: ERROR: Recording data files creation lasted longer than 50 msec\n");
		printf ("Recorder: ERROR: It lasted %d nanoseconds\n", time_curr - time_prev);
		printf ("Recorder: ERROR: It might lead to missing of data during buffer-reading\n");		
		printf("Recorder: Recording interrupted.\n\n");
		// delete_last_recorded_file();
		return 0;
	}					
		
	time_prev = time_curr;		
		
	return 1;
}

int create_recording_data(void)
{
	char temp[600];
	FILE *fp;
	char char_mwa_num[10], char_chan_num[10];
	int i,j;
	
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			strcpy(temp, data_directory_path);	
			if (i<10)
			{
				strcat(temp, "/Rec_mwa_0");
				sprintf(char_mwa_num, "%d" , i);
				strcat(temp, char_mwa_num);
			}
			else if (i<100)
			{
				strcat(temp, "/Rec_mwa_");
				sprintf(char_mwa_num, "%d" , i);
				strcat(temp, char_mwa_num);				
			}
			else
			{
				printf ("ERROR: Recorder: MAX MWA NUM is larger than 99\n\n");
				printf ("ERROR: Recorder: Couldn't create all recording files requested\n\n");
				return 0; 
			}
			strcat(temp, "_");
			if (j<10)
			{
				strcat(temp, "chan_00");
				sprintf(char_chan_num, "%d" , j);
				strcat(temp, char_chan_num);
			}
			else if (j<100)
			{
				strcat(temp, "chan_0");
				sprintf(char_chan_num, "%d" , j);
				strcat(temp, char_chan_num);				
			}
			else if (j<1000)
			{
				strcat(temp, "chan_");
				sprintf(char_chan_num, "%d" , j);
				strcat(temp, char_chan_num);			
			}
			else
			{
				printf ("ERROR: Recorder: MAX NUM OF CHAN PER MWA is larger than 999\n\n");
				printf ("ERROR: Recorder: Couldn't create all recording files requested\n\n");
				return 0; 
			}			
			if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
			file_ptr_arr[RECORDING_DATA_FILE_IDX + (i*MAX_NUM_OF_CHAN_PER_MWA)+j] =  fp;
			fprintf(fp,"----------BlueSpike - Recording Data File ( MWA #%s\tChannel #%s )----------\n", char_mwa_num, char_chan_num);						
		}
	}

	return 1;
}
int create_blue_spike_time_stamp_data(void)
{
	char temp[600];
	FILE *fp;
	
	strcpy(temp, data_directory_path);	
	strcat(temp, "/BlueSpikeTimeStamp");
	if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
	file_ptr_arr[BLUE_SPIKE_TIME_STAMP_DATA_FILE_IDX] =  fp;		
	fprintf(fp,"----------BlueSpike - Blue Spike Time Stamps File----------\n");						
	return 1;
}
int create_spike_time_stamp_data(void)
{
	char temp[600];
	FILE *fp;
	
	strcpy(temp, data_directory_path);	
	strcat(temp, "/SpikeTimeStamp");
	if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
	file_ptr_arr[SPIKE_TIME_STAMP_DATA_FILE_IDX] =  fp;		
	fprintf(fp,"----------BlueSpike - Spike Time Stamps File----------\n");						
	return 1;
}
int create_exp_envi_event_data(void)
{
	char temp[600];
	FILE *fp;
	char char_exp_envi_item[10];
	int i;	
		
	for (i=0; i < MAX_NUM_OF_EXP_ENVI_ITEMS; i++)
	{
		strcpy(temp, data_directory_path);	
		if (i<10)
		{
			strcat(temp, "/ExpEnvi_Event_item_");
			sprintf(char_exp_envi_item, "%d" , i);
			strcat(temp, char_exp_envi_item);
		}
		else
		{
			printf ("ERROR: Recorder: MAX EXPERIMETAL ENVIRONMENT ITEM is larger than 9\n\n");
			printf ("ERROR: Recorder: Couldn't create all recording files requested\n\n");
			return 0; 
		}
		if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
		file_ptr_arr[EXP_ENVI_EVENT_DATA_FILE_IDX+i] =  fp;		
		fprintf(fp,"----------BlueSpike - Experimental Environment Item #%s Event TimeStamps File----------\n", char_exp_envi_item);						
	}
	return 1;
}	
int create_exp_envi_command_data(void)
{
	char temp[600];
	FILE *fp;
	char char_exp_envi_item[10];
	int i;
	
	for (i=0; i < MAX_NUM_OF_EXP_ENVI_ITEMS; i++)
	{
		strcpy(temp, data_directory_path);	
		if (i<10)
		{
			strcat(temp, "/ExpEnvi_Comnd_item_");
			sprintf(char_exp_envi_item, "%d" , i);
			strcat(temp, char_exp_envi_item);
		}
		else
		{
			printf ("ERROR: Recorder: MAX EXPERIMETAL ENVIRONMENT ITEM is larger than 9\n\n");
			printf ("ERROR: Recorder: Couldn't create all recording files requested\n\n");
			return 0; 
		}
		if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
		file_ptr_arr[EXP_ENVI_COMMAND_DATA_FILE_IDX+i] = fp;
		fprintf(fp,"----------BlueSpike - Experimental Environment Item #%s Command TimeStamps File----------\n", char_exp_envi_item);				
	}	
	
	return 1;
}		
int create_mov_obj_event_data(void)
{
	char temp[600];
	FILE *fp;
	char char_mov_obj_num[10];	
	int i;
	
	for (i=0; i < MAX_NUM_OF_MOVING_OBJECTS; i++)
	{
		strcpy(temp, data_directory_path);	
		if (i<10)
		{
			strcat(temp, "/MovObj_Event_obj_");
			sprintf(char_mov_obj_num, "%d" , i);
			strcat(temp, char_mov_obj_num);
		}
		else
		{
			printf ("ERROR: Recorder: MAX MOVING OBJECT NUM is larger than 9\n\n");
			printf ("ERROR: Recorder: Couldn't create all recording files requested\n\n");
			return 0; 
		}
		if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
		file_ptr_arr[MOV_OBJ_EVENT_DATA_FILE_IDX + i] =  fp;
		fprintf(fp,"----------BlueSpike - Moving Object #%s Event TimeStamps File----------\n", char_mov_obj_num);
	}
	return 1;
}	

int create_mov_obj_command_data(void)
{
	char temp[600];
	FILE *fp;
	char char_mov_obj_num[10];	
	int i;
	
	for (i=0; i < MAX_NUM_OF_MOVING_OBJECTS; i++)
	{
		strcpy(temp, data_directory_path);	
		if (i<10)
		{
			strcat(temp, "/MovObj_Comnd_obj_");
			sprintf(char_mov_obj_num, "%d" , i);
			strcat(temp, char_mov_obj_num);
		}
		else
		{
			printf ("ERROR: Recorder: MAX MOVING OBJECT NUM is larger than 9\n\n");
			printf ("ERROR: Recorder: Couldn't create all recording files requested\n\n");
			return 0; 
		}
		if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
		file_ptr_arr[MOV_OBJ_COMMAND_DATA_FILE_IDX + i] =  fp;
		fprintf(fp,"----------BlueSpike - Moving Object #%s Command TimeStamps File----------\n", char_mov_obj_num);		
	}
	return 1;
}

int write_data_in_buffer_v0(int num, ...)
{
	int time_prev = rt_get_cpu_time_ns();
	int time_curr;
	int part_num;
	int finalize = 0;
  	va_list arguments;
	va_start ( arguments, num );   
    	part_num = va_arg ( arguments, int);   	
	if (num == 2)	// it is last part to write. write end of recording time into meta
	{
		end_meta_data(va_arg ( arguments, TimeStamp));
		finalize = 1;		
	}
	va_end ( arguments );
	
	write_recording_data(finalize);
	write_blue_spike_time_stamp_data(finalize);
	write_spike_time_stamp_data(finalize);	
	write_exp_envi_event_data(finalize);
	write_exp_envi_command_data(finalize);
	write_mov_obj_event_data(finalize);
	write_mov_obj_command_data(finalize);

	time_curr = rt_get_cpu_time_ns();
	if ((time_curr - time_prev) > 100000000)		// if writing exceeds x milliseconds, there might be buffer reading error. (buffer might be overwrited before reading it.)
	{								
		printf ("Recorder: ERROR: Recording data files (Part: %d) writing process lasted longer than 50 msec\n", part_num);
		printf ("Recorder: ERROR: It lasted %d nanoseconds\n", time_curr - time_prev);
		printf ("Recorder: ERROR: It might lead to missing of data during buffer-reading\n");		
		printf("Recorder: Recording interrupted.\n\n");
		// delete_last_recorded_file();
		return 0;
	}					
		
	time_prev = time_curr;	
	
	
	return 1;
}

int write_recording_data(bool finalize)
{
	int i, j, idx, end_idx;
	int file_ptr_arr_start_idx = RECORDING_DATA_FILE_IDX;
	RecordingDataChanBuff	*recording_data_chan_buff;
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			recording_data_chan_buff = &(recording_data->recording_data_buff[i][j]);
			idx = recording_data_buff_prev_idx[i][j];
			end_idx = recording_data_buff_end_idx[i][j];
			while (idx != end_idx)
			{
				fprintf(file_ptr_arr[(file_ptr_arr_start_idx+(i*MAX_NUM_OF_CHAN_PER_MWA))+j],"%.15f\n", (*recording_data_chan_buff)[idx] );
				idx++;	
				if (idx ==	RECORDING_DATA_BUFF_SIZE)
					idx = 0;	
			}
			if (finalize)
			{
				fprintf(file_ptr_arr[(file_ptr_arr_start_idx+(i*MAX_NUM_OF_CHAN_PER_MWA))+j],"----------BlueSpike - End of Recording Data File----------\n");						
			}
		}
	}		
	return 1;
}

int write_blue_spike_time_stamp_data(bool finalize)
{
	int idx, end_idx;
	int file_ptr_start_idx = BLUE_SPIKE_TIME_STAMP_DATA_FILE_IDX;
	int buff_size = BLUE_SPIKE_TIME_STAMP_BUFF_SIZE;

	idx = blue_spike_time_stamp_buff_prev_idx;
	end_idx = blue_spike_time_stamp_buff_end_idx;
	while (idx != end_idx)
	{
		fprintf(file_ptr_arr[file_ptr_start_idx],"%llu\t", blue_spike_time_stamp->blue_spike_time_stamp_buff[idx].peak_time);
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\t", blue_spike_time_stamp->blue_spike_time_stamp_buff[idx].mwa);	
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\t", blue_spike_time_stamp->blue_spike_time_stamp_buff[idx].channel);
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\t", blue_spike_time_stamp->blue_spike_time_stamp_buff[idx].unit);
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\n", blue_spike_time_stamp->blue_spike_time_stamp_buff[idx].include_unit);						
		idx++;	
		if (idx ==	buff_size)
			idx = 0;	
	}
	if (finalize)
	{
		fprintf(file_ptr_arr[file_ptr_start_idx],"----------BlueSpike - End of Blue Spike TimeStamps File----------\n");						
	}
	return 1;
}
int write_spike_time_stamp_data(bool finalize)
{
	int idx, end_idx;
	int file_ptr_start_idx = SPIKE_TIME_STAMP_DATA_FILE_IDX;
	int buff_size = SPIKE_TIME_STAMP_BUFF_SIZE;

	idx = spike_time_stamp_buff_prev_idx;
	end_idx = spike_time_stamp_buff_end_idx;
	while (idx != end_idx)
	{
		fprintf(file_ptr_arr[file_ptr_start_idx],"%llu\t", spike_time_stamp->spike_time_stamp_buff[idx].peak_time);
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\t", spike_time_stamp->spike_time_stamp_buff[idx].mwa);	
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\t", spike_time_stamp->spike_time_stamp_buff[idx].channel);
		fprintf(file_ptr_arr[file_ptr_start_idx],"%d\t", spike_time_stamp->spike_time_stamp_buff[idx].unit);
		idx++;	
		if (idx ==	buff_size)
			idx = 0;	
	}
	if (finalize)
	{
		fprintf(file_ptr_arr[file_ptr_start_idx],"----------BlueSpike - End of Spike TimeStamps File----------\n");						
	}
	return 1;
}
int write_exp_envi_event_data(bool finalize)
{
	int idx, end_idx;
	int file_ptr_start_idx = EXP_ENVI_EVENT_DATA_FILE_IDX;
	int buff_size = EXP_ENVI_EVENT_TIMESTAMP_BUFF_SIZE;
	int i;
	
	for (i=0; i < MAX_NUM_OF_EXP_ENVI_ITEMS; i++)
	{
		idx = exp_envi_event_buff_prev_idx[i];
		end_idx = exp_envi_event_buff_end_idx[i];
		while (idx != end_idx)
		{
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"%llu\t", exp_envi_event_time_stamp->timestamp_buff[i][idx].time);			
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"%u\t", exp_envi_event_time_stamp->timestamp_buff[i][idx].type);
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"%f\n", exp_envi_event_time_stamp->timestamp_buff[i][idx].value);											
			idx++;	
			if (idx ==	buff_size)
				idx = 0;	
		}
		if (finalize)
		{
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"----------BlueSpike - End of Experimental Environment Event TimeStamps File----------\n");						
		}
	}		
	return 1;
}	
	
int write_exp_envi_command_data(bool finalize)
{
	int idx, end_idx;
	int file_ptr_start_idx = EXP_ENVI_COMMAND_DATA_FILE_IDX;
	int buff_size = EXP_ENVI_COMMAND_TIMESTAMP_BUFF_SIZE;
	int i;
	
	for (i=0; i < MAX_NUM_OF_EXP_ENVI_ITEMS; i++)
	{
		idx = exp_envi_command_buff_prev_idx[i];
		end_idx = exp_envi_command_buff_end_idx[i];
		while (idx != end_idx)
		{
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"%llu\t", exp_envi_command_time_stamp->timestamp_buff[i][idx].time);			
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"%u\t", exp_envi_command_time_stamp->timestamp_buff[i][idx].type);
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"%f\n", exp_envi_command_time_stamp->timestamp_buff[i][idx].value);											
			idx++;	
			if (idx ==	buff_size)
				idx = 0;	
		}
		if (finalize)
		{
			fprintf(file_ptr_arr[file_ptr_start_idx+i],"----------BlueSpike - End of Experimental Environment Command TimeStamps File----------\n");						
		}
	}		
	return 1;
}	
		
int write_mov_obj_event_data(bool finalize)
{
	int i, j, idx, end_idx;
	int file_ptr_arr_start_idx = MOV_OBJ_EVENT_DATA_FILE_IDX;
	int buff_size = MOVING_OBJ_EVENT_TIMESTAMP_BUFF_SIZE;
	
	for (i=0; i < MAX_NUM_OF_MOVING_OBJECTS; i++)
	{
		idx = mov_obj_event_buff_prev_idx[i];
		end_idx = mov_obj_event_buff_end_idx[i];
		while (idx != end_idx)
		{
			fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"%llu", mov_obj_event_time_stamp->timestamp_buff[i][idx].time );
			for (j=0;j<MAX_NUM_OF_COMPONENT_PER_MOVING_OBJECT; j++)
			{
				fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\t%f", mov_obj_event_time_stamp->timestamp_buff[i][idx].Speed[j]);
				fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\t%d", mov_obj_event_time_stamp->timestamp_buff[i][idx].Direction[j]);	
				fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\t%f", mov_obj_event_time_stamp->timestamp_buff[i][idx].Location[j]);								
			}
			fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\n");
			idx++;	
			if (idx == buff_size)
				idx = 0;	
		}
		if (finalize)
		{
			fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"----------BlueSpike - End of Moving Object Event TimeStamps File----------\n");		
		}
	}
	return 1;
}	
	
int write_mov_obj_command_data(bool finalize)
{
	int i, j, idx, end_idx;
	int file_ptr_arr_start_idx = MOV_OBJ_COMMAND_DATA_FILE_IDX;
	int buff_size = MOVING_OBJ_COMMAND_TIMESTAMP_BUFF_SIZE;
	
	for (i=0; i < MAX_NUM_OF_MOVING_OBJECTS; i++)
	{
		idx = mov_obj_command_buff_prev_idx[i];
		end_idx = mov_obj_command_buff_end_idx[i];
		while (idx != end_idx)
		{
			fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"%llu", mov_obj_command_time_stamp->timestamp_buff[i][idx].time );
			for (j=0;j<MAX_NUM_OF_COMPONENT_PER_MOVING_OBJECT; j++)
			{
				fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\t%f", mov_obj_command_time_stamp->timestamp_buff[i][idx].Speed[j]);
				fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\t%d", mov_obj_command_time_stamp->timestamp_buff[i][idx].Direction[j]);	
				fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\t%f", mov_obj_command_time_stamp->timestamp_buff[i][idx].Location[j]);								
			}
			fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"\n");
			idx++;	
			if (idx == buff_size)
				idx = 0;	
		}
		if (finalize)
		{
			fprintf(file_ptr_arr[file_ptr_arr_start_idx+i],"----------BlueSpike - End of Moving Object Command TimeStamps File----------\n");		
		}
	}
	return 1;
}

int create_meta_data(TimeStamp rec_start)
{
	char temp[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
		
	strcpy(temp, data_directory_path);
	strcat(temp, "/meta");
	if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp); return 0; }
	fprintf(fp,"----------BlueSpike - Meta File----------\n");
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"START\t%llu\n", rec_start);		
	fclose(fp);	
	return 1;	
}

int end_meta_data(TimeStamp rec_end)
{
	char temp_path[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
		
	strcpy(temp_path, data_directory_path);
	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }
	fprintf(fp,"END\t%llu\n", rec_end);
	fprintf(fp,"----------BlueSpike - End of Meta File----------\n");	
	fclose(fp);	
		
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/logs");
	if ((fp = fopen(temp_path, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"%s\t\tFinished recording.\n", asctime (timeinfo)); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");
	fclose(fp);
	return 1;		
}


int fclose_all_data_files_v0(int num, ...)
{
	int i , num_of_data_files = NUM_OF_DATA_FILE_PER_RECORDING;
		
	for (i = 0; i<num_of_data_files; i++)
	{
		if (file_ptr_arr[i] != NULL)
			fclose(file_ptr_arr[i]);
	}
	g_free(file_ptr_arr);

	return 1;
}



int write_notes_to_files_v0(int num, ...)
{
	char *text_buffer;
	GtkTextIter start, end;
	int char_count;
	char  temp_path[600];
	int i;
	FILE *fp;
	GtkWidget *text_view; 
	time_t rawtime;
	struct tm * timeinfo;		
	
  	va_list arguments;
	va_start ( arguments, num );   
    	text_view = va_arg ( arguments, GtkWidget *);   	
	va_end ( arguments );
	
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));	
       	gtk_text_buffer_get_start_iter ( buffer, &start);
        gtk_text_buffer_get_end_iter ( buffer, &end);
        text_buffer = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
	char_count = gtk_text_buffer_get_char_count(buffer);

 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/notes");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }
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
	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);	
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/logs");
	if ((fp = fopen(temp_path, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }	
	fprintf(fp,"%s\t\tCreated /notes file and submitted notes.\n", asctime (timeinfo)); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");	 
	fclose(fp);
	
	return 1;
}

int write_additional_notes_to_files_v0(int num, ...)
{
	char *text_buffer;
	GtkTextIter start, end;
	int char_count;
	int i;
	GtkWidget *text_view; 
	FILE *fp;
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;	
	
  	va_list arguments;
	va_start ( arguments, num );   
    	text_view = va_arg ( arguments, GtkWidget *);   	
	va_end ( arguments );
	
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));	
       	gtk_text_buffer_get_start_iter ( buffer, &start);
        gtk_text_buffer_get_end_iter ( buffer, &end);
        text_buffer = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);
	char_count = gtk_text_buffer_get_char_count(buffer);

	time ( &rawtime );
	timeinfo = localtime (&rawtime);
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/notes");
	if ((fp = fopen(temp_path, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't append text to file: %s\n\n", temp_path); return 0; }		

	fprintf(fp,"\n---------------------------------------------------------------------------------\n");	
	fprintf(fp,"Additional Note:\n%s", asctime (timeinfo)); 		
	
	for (i = 0; i < char_count; i++)
	{
		fprintf(fp, "%c", text_buffer[i]);		
	}	
	fclose(fp);
		
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/logs");
	if ((fp = fopen(temp_path, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }	
	fprintf(fp,"%s\t\tSubmitted additonal note to /notes.\n", asctime (timeinfo)); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");	 
	fclose(fp);
				
	return 1;
}

int create_main_logs_file(void)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;
	
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/logs");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"---------BlueSpike - Logs File---------------\n"); 		
	fprintf(fp,"%s\t\tCreated BlueSpikeData folder.\n", asctime (timeinfo)); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");
	fprintf(fp,"%s\t\tCreated /logs file (this file).\n", asctime (timeinfo)); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");	
	fclose(fp);
	return 1; 		
}

int write_maps_templates_to_files_v0(int num, ...)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;

	if (!write_maps_to_files())
		return 0;
	if (!write_spike_thresholds_to_files())
		return 0;
	if (!write_templates_to_files())
		return 0;
		
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/logs");
	if ((fp = fopen(temp_path, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't append to file: %s\n\n", temp_path); return 0; }	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"%s\t\tSaved daq card mwa mappings and templates.\n", asctime (timeinfo)); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");	
	fclose(fp);	
	
	return 1;		
}

int write_maps_to_files(void)
{
	FILE *fp;	
	char  temp_path[600];
	int i, j;
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/maps");
 	
	if (!interrogate_mapping())
		return 0;
	 	
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }
	
	fprintf(fp, "BlueSpike - Data Acquisiton Cards vs Microwire Arrays Mapping File\n");	
	fprintf(fp,"MAX_NUM_OF_DAQ_CARD\t%d\n",MAX_NUM_OF_DAQ_CARD);
	fprintf(fp,"MAX_NUM_OF_CHANNEL_PER_DAQ_CARD\t%d\n",MAX_NUM_OF_CHANNEL_PER_DAQ_CARD);		
	fprintf(fp,"MAX_NUM_OF_MWA\t%d\n", MAX_NUM_OF_MWA);
	fprintf(fp,"MAX_NUM_OF_CHAN_PER_MWA\t%d\n",MAX_NUM_OF_CHAN_PER_MWA);
	for (i = 0; i<MAX_NUM_OF_DAQ_CARD; i++)
	{	
		for (j = 0; j<MAX_NUM_OF_CHANNEL_PER_DAQ_CARD; j++)
		{	
			fprintf(fp, "DAQ:\t%d\tChannel:\t%d\t---->\tMWA:\t%d\tChannel:\t%d\t\n", i, j, shared_memory->daq_mwa_map[i][j].mwa, shared_memory->daq_mwa_map[i][j].channel);	
		}
	}
	fprintf(fp, "BlueSpike - End of Data Acquisiton Cards vs Microwire Arrays Mapping File\n");				
	fclose(fp);

	if ((fp = fopen("../ConfigDaq/path_initial_directory", "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", temp_path); fclose (fp);		
	
	return 1;
}

int write_spike_thresholds_to_files(void)
{
	FILE *fp;	
	char  temp_path[600];
	int i,j;
	
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/spike_thres");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }	

	fprintf(fp, "----------------BlueSpike - Spike Thresholds File---------------\n");	
	fprintf(fp,"MAX_NUM_OF_MWA\t%d\n", MAX_NUM_OF_MWA);
	fprintf(fp,"MAX_NUM_OF_CHAN_PER_MWA\t%d\n",MAX_NUM_OF_CHAN_PER_MWA);	
	for (i=0; i<MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			fprintf(fp, "%.2f\t", shared_memory->spike_thresholding.amplitude_thres[i][j]);																			
		}
		fprintf(fp, "\n");																					
	}
	fprintf(fp, "----------------BlueSpike - End of Spike Thresholds File----------------\n");
	fclose(fp);

	if ((fp = fopen("../SpikeViewer/path_initial_directory", "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", temp_path); fclose (fp);
	
	return 1;
}

int write_templates_to_files(void)
{
	FILE *fp;	
	char  temp_path[600];
	int i,j,k,m,n;
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/templates");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't create file: %s\n\n", temp_path); return 0; }

	fprintf(fp, "----------------BlueSpike - Template Matching File---------------\n");
	fprintf(fp,"MAX_NUM_OF_MWA\t%d\n", MAX_NUM_OF_MWA);
	fprintf(fp,"MAX_NUM_OF_CHAN_PER_MWA\t%d\n",MAX_NUM_OF_CHAN_PER_MWA);
	fprintf(fp,"MAX_NUM_OF_UNIT_PER_CHAN\t%d\n",MAX_NUM_OF_UNIT_PER_CHAN);
	fprintf(fp,"NUM_OF_SAMP_PER_SPIKE\t%d\n",NUM_OF_SAMP_PER_SPIKE);		
	fprintf(fp, "--------- Inverted Covariance Matrix ------\n");																					
	for (i=0; i<MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			for (k=0; k<MAX_NUM_OF_UNIT_PER_CHAN; k++)
			{
				fprintf(fp, "---------\tMWA:\t%d\tChannel:\t%d\tUnit:\t%d\t------\n", i,j, k);																								
				for (m=0; m<NUM_OF_SAMP_PER_SPIKE; m++)
				{
					for (n=0; n<NUM_OF_SAMP_PER_SPIKE; n++)
					{				
						fprintf(fp, "%.20f\t", shared_memory->template_matching_data[i][j][k].inv_S[m][n]);
					}
					fprintf(fp, "\n");																										
				}
			}
		}
	}
	fprintf(fp, "--------- sqrt(det(S)) / log(det(S)) / probability_threshold / sorting_on_off / include_unit ------\n");																					
	for (i=0; i<MAX_NUM_OF_MWA; i++)
	{
		fprintf(fp, "--------- MWA: %d\n", i);																							
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			for (k=0; k<MAX_NUM_OF_UNIT_PER_CHAN; k++)
			{
				fprintf(fp, "%.20f\t", shared_memory->template_matching_data[i][j][k].sqrt_det_S);
				fprintf(fp, "%.20f\t", shared_memory->template_matching_data[i][j][k].log_det_S);	
				fprintf(fp, "%E\t", shared_memory->template_matching_data[i][j][k].probability_thres);
				fprintf(fp, "%d\t", shared_memory->template_matching_data[i][j][k].sorting_on);		
				fprintf(fp, "%d\t", shared_memory->template_matching_data[i][j][k].include_unit);																
			}
			fprintf(fp, "\n");																													
		}
	}

	fprintf(fp, "----------------BlueSpike - End of Template Matching File---------------\n");		
	fclose(fp);
	
	if ((fp = fopen("../SpikeSorter/path_initial_directory", "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", temp_path); fclose (fp);
		
	return 1;		
}

int delete_last_recording_v0(int num, ...)
{
 	char path_item[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
	DIR	*dir_data_directory;
        struct dirent   *dirent_item;
     	int status;
    	struct stat item_stat;
    	     	       	
	if ((dir_data_directory = opendir(data_directory_path)) == NULL)
        {
        	printf ("Recorder: ERROR: Couldn't opendir: %s\n\n", data_directory_path);		
                return 0;
        }

	while ((dirent_item = readdir(dir_data_directory)) !=NULL)
	{	
		if ((strcmp( dirent_item->d_name, "." ) == 0) || (strcmp(dirent_item->d_name, ".." ) == 0)) 	
			continue;
		strcpy(path_item, data_directory_path);
		strcat(path_item, "/");
		strcat(path_item, dirent_item->d_name);	
		if ((status = stat(path_item, &item_stat)) != 0)
		{
        		printf ("ERROR: Couldn' t retrieve item status (file or folder?): %s\n", path_item);
			return -1;
		} 
		if (S_ISREG (item_stat.st_mode))
		{
			remove(path_item);
		}			
	}
	closedir(dir_data_directory);		
	rmdir(data_directory_path);					
	data_directory_cntr--;	

 	strcpy(path_item, main_directory_path);
 	strcat(path_item, "/logs");
	if ((fp = fopen(path_item, "a+")) == NULL)  { printf ("ERROR: Recorder: Couldn't append to file: %s\n\n", path_item); return 0; }	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"%s\t\tDeleted last recording. Folder %s\n", asctime (timeinfo), data_directory_path); 	
	fprintf(fp,"---------------------------------------------------------------------------------\n");	
	fclose(fp);	
	
	return 1;
}

int read_mapping_v0(int num, ...)
{	
	char *path_maps;
	char line[1000];
	char word[100];
  	va_list arguments;
	va_start ( arguments, num );   
    	path_maps = va_arg ( arguments, char *);   	
	va_end ( arguments );	


	int i,j, line_cntr=0;
	int max_num_of_daq_card, max_num_of_channel_per_daq_card, max_num_of_mwa, max_num_of_channel_per_mwa;
	FILE *fp=NULL;
	int mwa, mwa_channel;

	printf("Loading maps file...\n");

	fp = fopen(path_maps, "r");
	if (fp == NULL)
	{
		printf("ERROR: Couldn't fopen the maps file\n");
		return 0;		
	}

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "BlueSpike - Data Acquisiton Cards vs Microwire Arrays Mapping File\n") != 0)
	{
		printf("ERROR: Not a valid DAQ Card - MWA Mapping Maps File\n");
		fclose(fp);
		return 0;
	}  	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;	
	max_num_of_daq_card = (int)atof(word);	
	if (MAX_NUM_OF_DAQ_CARD	< max_num_of_daq_card )
	{
		printf("ERROR: Maps file was saved when MAX_NUM_OF_DAQ_CARD = %d\n",max_num_of_daq_card);
		printf("ERROR: Now it is MAX_NUM_OF_DAQ_CARD = %d\n", MAX_NUM_OF_DAQ_CARD);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_DAQ_CARD	> max_num_of_daq_card )
	{
		printf("WARNING: Maps file was saved when MAX_NUM_OF_DAQ_CARD = %d\n",max_num_of_daq_card);
		printf("WARNING: Now it is MAX_NUM_OF_DAQ_CARD = %d\n", MAX_NUM_OF_DAQ_CARD);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;} 
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;		  
	max_num_of_channel_per_daq_card = (int)atof(word);
	if (MAX_NUM_OF_CHANNEL_PER_DAQ_CARD < max_num_of_channel_per_daq_card)
	{
		printf("ERROR: Maps file was saved when MAX_NUM_OF_DAQ_CARD = %d\n", max_num_of_channel_per_daq_card);
		printf("ERROR: Now it is MAX_NUM_OF_DAQ_CARD = %d\n", MAX_NUM_OF_CHANNEL_PER_DAQ_CARD);	
		fclose(fp);
		return 0; 
	}
	else if (MAX_NUM_OF_CHANNEL_PER_DAQ_CARD > max_num_of_channel_per_daq_card)
	{
		printf("WARNING: Maps file was saved when MAX_NUM_OF_DAQ_CARD = %d\n", max_num_of_channel_per_daq_card);
		printf("WARNING: Now it is MAX_NUM_OF_DAQ_CARD = %d\n", MAX_NUM_OF_CHANNEL_PER_DAQ_CARD);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}	
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;		
	max_num_of_mwa = (int)atof(word);
	if (MAX_NUM_OF_MWA < max_num_of_mwa)
	{
		printf("ERROR: Maps file was saved when MAX_NUM_OF_MWA = %d\n", max_num_of_mwa);
		printf("ERROR: Now it is MAX_NUM_OF_MWA = %d\n", MAX_NUM_OF_MWA);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_MWA > max_num_of_mwa)
	{
		printf("WARNING: Maps file was saved when MAX_NUM_OF_MWA = %d\n", max_num_of_mwa);
		printf("WARNING: Now it is MAX_NUM_OF_MWA= %d\n", MAX_NUM_OF_MWA);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;
	max_num_of_channel_per_mwa = (int)atof(word);	
	if (MAX_NUM_OF_CHAN_PER_MWA < max_num_of_channel_per_mwa)
	{
		printf("ERROR: Maps file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_channel_per_mwa);
		printf("ERROR: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_CHAN_PER_MWA);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_CHAN_PER_MWA > max_num_of_channel_per_mwa)
	{
		printf("WARNING: Maps file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_channel_per_mwa);
		printf("WARNING: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_CHAN_PER_MWA);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}	


	for (i = 0; i<max_num_of_daq_card; i++)    /// Only configure the ones written in config file even though max_num_of_daq_card != MAX_NUM_OF_DAQ_CARD
	{	
		for (j = 0; j<max_num_of_channel_per_daq_card; j++)
		{	
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;}  
			if(!get_word_in_line('\t', 6, word, line, TRUE))
				return 0; 
			mwa = (int)atof(word);
			if ((mwa > MAX_NUM_OF_MWA) || (mwa < 0))  { printf("ERROR: Incompatible value at %d th line of maps file\n", line_cntr);  fclose(fp); return 0;} 
			if(!get_word_in_line('\t', 8, word, line, TRUE))
				return 0; 
			mwa_channel = (int)atof(word);
			if ((mwa_channel > MAX_NUM_OF_CHAN_PER_MWA) || (mwa_channel < 0))  { printf("ERROR: Incompatible value at %d th line of maps file\n", line_cntr);  fclose(fp); return 0;} 
						
			while (!(shared_memory->kernel_task_ctrl.kernel_task_idle)) { usleep(1); }   // wait until rt_task_wait_period starts
			// First delete mwa to daq mapping			
			shared_memory->mwa_daq_map[shared_memory->daq_mwa_map[i][j].mwa][shared_memory->daq_mwa_map[i][j].channel].daq_card = MAX_NUM_OF_DAQ_CARD;
			shared_memory->mwa_daq_map[shared_memory->daq_mwa_map[i][j].mwa][shared_memory->daq_mwa_map[i][j].channel].daq_chan = MAX_NUM_OF_CHANNEL_PER_DAQ_CARD;
			shared_memory->daq_mwa_map[i][j].mwa = MAX_NUM_OF_MWA;
			shared_memory->daq_mwa_map[i][j].channel = MAX_NUM_OF_CHAN_PER_MWA;			
			// Now map daq to mwa	
			shared_memory->daq_mwa_map[i][j].mwa = mwa;
			shared_memory->daq_mwa_map[i][j].channel = mwa_channel;
			// Now map mwa to daq
			shared_memory->mwa_daq_map[mwa][mwa_channel].daq_card = i;
			shared_memory->mwa_daq_map[mwa][mwa_channel].daq_chan = j;				
		}
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_maps);  fclose(fp); return 0; } else {line_cntr++;} 
	if (strcmp(line, "BlueSpike - End of Data Acquisiton Cards vs Microwire Arrays Mapping File\n") != 0)
	{
		printf("ERROR: Not a valid DAQ Card - MWA Mapping Maps File\n");
		fclose(fp);
		for (i = 0; i<MAX_NUM_OF_DAQ_CARD; i++)    /// Only configure the ones written in config file even though max_num_of_daq_card != MAX_NUM_OF_DAQ_CARD
		{	
			for (j = 0; j<MAX_NUM_OF_CHANNEL_PER_DAQ_CARD; j++)
			{	
				while (!(shared_memory->kernel_task_ctrl.kernel_task_idle)) { usleep(1); }   // wait until rt_task_wait_period starts
				shared_memory->mwa_daq_map[shared_memory->daq_mwa_map[i][j].mwa][shared_memory->daq_mwa_map[i][j].channel].daq_card = MAX_NUM_OF_DAQ_CARD;
				shared_memory->mwa_daq_map[shared_memory->daq_mwa_map[i][j].mwa][shared_memory->daq_mwa_map[i][j].channel].daq_chan = MAX_NUM_OF_CHANNEL_PER_DAQ_CARD;
				shared_memory->daq_mwa_map[i][j].mwa = MAX_NUM_OF_MWA;
				shared_memory->daq_mwa_map[i][j].channel = MAX_NUM_OF_CHAN_PER_MWA;			
			}
		}
		return 0;
	}  		

	fclose(fp);

	if (!interrogate_mapping())
		return 0;
	
	return 1;	

}

int read_spike_thresholds_v0(int num, ...)
{	
	char *path_thres;
	char line[1000];
	char word[100];
  	va_list arguments;
	va_start ( arguments, num );   
    	path_thres = va_arg ( arguments, char *);   	
	va_end ( arguments );	
	
	int i,j, line_cntr=0;
	int max_num_of_mwa, max_num_of_channel_per_mwa;
	FILE *fp=NULL;

	printf("Loading spike thresholds file...\n");

	fp = fopen(path_thres, "r");
	if (fp == NULL)
	{
		printf("ERROR: Couldn't fopen /spike_thres file\n");
		return 0;		
	}
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_thres);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------------BlueSpike - Spike Thresholds File---------------\n") != 0)
	{
		printf("ERROR: Not a valid Spike Thresholds File\n");
		fclose(fp);
		return 0;
	}  	

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_thres);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;		
	max_num_of_mwa = (int)atof(word);
	if (MAX_NUM_OF_MWA < max_num_of_mwa)
	{
		printf("ERROR: Spike Thresholds file was saved when MAX_NUM_OF_MWA = %d\n", max_num_of_mwa);
		printf("ERROR: Now it is MAX_NUM_OF_MWA = %d\n", MAX_NUM_OF_MWA);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_MWA > max_num_of_mwa)
	{
		printf("WARNING: Spike Thresholds file was saved when MAX_NUM_OF_MWA = %d\n", max_num_of_mwa);
		printf("WARNING: Now it is MAX_NUM_OF_MWA= %d\n", MAX_NUM_OF_MWA);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_thres);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;
	max_num_of_channel_per_mwa = (int)atof(word);	
	if (MAX_NUM_OF_CHAN_PER_MWA < max_num_of_channel_per_mwa)
	{
		printf("ERROR: Spike Thresholds file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_channel_per_mwa);
		printf("ERROR: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_CHAN_PER_MWA);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_CHAN_PER_MWA > max_num_of_channel_per_mwa)
	{
		printf("WARNING: Spike Thresholds file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_channel_per_mwa);
		printf("WARNING: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_CHAN_PER_MWA);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}	

	for (i = 0; i<max_num_of_mwa; i++)    /// Only configure the ones written in config file even though max_num_of_daq_card != MAX_NUM_OF_DAQ_CARD
	{	
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_thres);  fclose(fp); return 0; } else {line_cntr++;}  
		for (j = 0; j < max_num_of_channel_per_mwa ; j++)
		{	
			if(!get_word_in_line('\t', j, word, line, TRUE))
				return 0; 
			if (atof(word) > 0)
			{
				printf("SpikeViewer: ERROR: Spike threshold cannot be smaller than zero.\n");
				printf("SpikeViewer: ERROR: Invalid value in Spike Threshold file.\n");
				return 0;
			} 				
			shared_memory->spike_thresholding.amplitude_thres[i][j]= atof(word);
		}
	}	

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_thres);  fclose(fp); return 0; } else {line_cntr++;} 
	if (strcmp(line, "----------------BlueSpike - End of Spike Thresholds File----------------\n") != 0)
	{
		printf("ERROR: Not a valid Spike Thresholds File\n");
		fclose(fp);
		for (i = 0; i<MAX_NUM_OF_MWA; i++)    /// Only configure the ones written in config file even though max_num_of_daq_card != MAX_NUM_OF_DAQ_CARD
		{	
			for (j = 0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
			{	
				shared_memory->spike_thresholding.amplitude_thres[i][j] = 0;			
			}
		}
		return 0;
	} 
	fclose(fp);	
	printf("Loading spike thresholds file...complete\n");	
	return 1; 	
}


int read_spike_templates_v0(int num, ...)
{	
	char *path_templates;
	char line[5000];
	char word[100];
  	va_list arguments;
	va_start ( arguments, num );   
    	path_templates = va_arg ( arguments, char *);   	
	va_end ( arguments );	
	
	int i,j, k,m ,n , line_cntr=0;
	int max_num_of_mwa, max_num_of_channel_per_mwa, max_num_of_unit_per_chan, num_samp_per_spike;
	FILE *fp=NULL;

	printf("Loading spike templates file...\n");

	fp = fopen(path_templates, "r");
	if (fp == NULL)
	{
		printf("ERROR: Couldn't fopen /templates file\n");
		return 0;		
	}
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   
	if (strcmp(line, "----------------BlueSpike - Template Matching File---------------\n") != 0)
	{
		printf("ERROR: Not a valid Spike Templates File\n");
		fclose(fp);
		return 0;
	}  	

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;		
	max_num_of_mwa = (int)atof(word);
	if (MAX_NUM_OF_MWA < max_num_of_mwa)
	{
		printf("ERROR: Spike Templates file was saved when MAX_NUM_OF_MWA = %d\n", max_num_of_mwa);
		printf("ERROR: Now it is MAX_NUM_OF_MWA = %d\n", MAX_NUM_OF_MWA);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_MWA > max_num_of_mwa)
	{
		printf("WARNING: Spike Templates file was saved when MAX_NUM_OF_MWA = %d\n", max_num_of_mwa);
		printf("WARNING: Now it is MAX_NUM_OF_MWA= %d\n", MAX_NUM_OF_MWA);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}
	
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;
	max_num_of_channel_per_mwa = (int)atof(word);	
	if (MAX_NUM_OF_CHAN_PER_MWA < max_num_of_channel_per_mwa)
	{
		printf("ERROR: Spike Templates file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_channel_per_mwa);
		printf("ERROR: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_CHAN_PER_MWA);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_CHAN_PER_MWA > max_num_of_channel_per_mwa)
	{
		printf("WARNING: Spike Templates file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_channel_per_mwa);
		printf("WARNING: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_CHAN_PER_MWA);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}		

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;
	max_num_of_unit_per_chan = (int)atof(word);	
	if (MAX_NUM_OF_UNIT_PER_CHAN < max_num_of_unit_per_chan)
	{
		printf("ERROR: Spike Templates file was saved when MAX_NUM_OF_UNIT_PER_CHAN = %d\n", max_num_of_unit_per_chan);
		printf("ERROR: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_UNIT_PER_CHAN);	
		fclose(fp);
		return 0;
	}
	else if (MAX_NUM_OF_UNIT_PER_CHAN > max_num_of_channel_per_mwa)
	{
		printf("WARNING: Spike Templates file was saved when MAX_NUM_OF_CHAN_PER_MWA = %d\n", max_num_of_unit_per_chan);
		printf("WARNING: Now it is MAX_NUM_OF_CHAN_PER_MWA = %d\n", MAX_NUM_OF_UNIT_PER_CHAN);		
		printf("WARNING: Configuration was done but you should check validity\n");	
	}

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   
	if(!get_word_in_line('\t', 1, word, line, TRUE))
		return 0;
	num_samp_per_spike = (int)atof(word);	
	if (NUM_OF_SAMP_PER_SPIKE != num_samp_per_spike)
	{
		printf("ERROR: Spike Templates file was saved when NUM_OF_SAMP_PER_SPIKE = %d\n", num_samp_per_spike);
		printf("ERROR: Now it is NUM_OF_SAMP_PER_SPIKE = %d\n", NUM_OF_SAMP_PER_SPIKE);	
		fclose(fp);
		return 0;
	}

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   // skip one line
	for (i=0; i<max_num_of_mwa; i++)
	{
		for (j=0; j<max_num_of_channel_per_mwa; j++)
		{
			for (k=0; k<max_num_of_unit_per_chan; k++)
			{
				if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   // skip one line		
				for (m=0; m<num_samp_per_spike; m++)
				{
					if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}  				
					for (n=0; n<num_samp_per_spike; n++)
					{				
						if(!get_word_in_line('\t', n, word, line, TRUE))
							return 0;
						shared_memory->template_matching_data[i][j][k].inv_S[m][n] = atof(word);						
					}
				}
			}
		}
	}

	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   // skip one line

	for (i=0; i<max_num_of_mwa; i++)
	{
		if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   // skip one line
		for (j=0; j<max_num_of_channel_per_mwa; j++)
		{
			if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;}   
			for (k=0; k<max_num_of_unit_per_chan; k++)
			{
				if(!get_word_in_line('\t', 0, word, line, TRUE))
					return 0;			
				shared_memory->template_matching_data[i][j][k].sqrt_det_S = atof(word);	
				if(!get_word_in_line('\t', 0, word, line, TRUE))
					return 0;			
				shared_memory->template_matching_data[i][j][k].log_det_S = atof(word);	
				if(!get_word_in_line('\t', 0, word, line, TRUE))
					return 0;			
				shared_memory->template_matching_data[i][j][k].probability_thres = atof(word);
				if(!get_word_in_line('\t', 0, word, line, TRUE))
					return 0;			
				shared_memory->template_matching_data[i][j][k].sorting_on = (bool)atof(word);
				if(!get_word_in_line('\t', 0, word, line, TRUE))
					return 0;			
				shared_memory->template_matching_data[i][j][k].include_unit = (bool)atof(word);
			}
		}
	}
	if (fgets(line, sizeof line, fp ) == NULL)   {  printf("ERROR: Couldn' t read %d th line of %s\n", line_cntr, path_templates);  fclose(fp); return 0; } else {line_cntr++;} 
	if (strcmp(line, "----------------BlueSpike - End of Template Matching File---------------\n") != 0)
	{
		printf("ERROR: Not a valid Spike Temnplates File\n");
		fclose(fp);
		for (i=0; i<MAX_NUM_OF_MWA; i++)
		{
			for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
			{
				for (k=0; k<MAX_NUM_OF_UNIT_PER_CHAN; k++)
				{
					for (m=0; m<NUM_OF_SAMP_PER_SPIKE; m++)
					{
						for (n=0; n<NUM_OF_SAMP_PER_SPIKE; n++)
						{				
							shared_memory->template_matching_data[i][j][k].inv_S[m][n] = 0;						
						}
					}
					shared_memory->template_matching_data[i][j][k].sqrt_det_S = 0;
					shared_memory->template_matching_data[i][j][k].log_det_S = 0;		
					shared_memory->template_matching_data[i][j][k].probability_thres = 0;	
					shared_memory->template_matching_data[i][j][k].sorting_on = 0;			
					shared_memory->template_matching_data[i][j][k].include_unit = 0;
				}
			}
		}
	} 
	fclose(fp);	
	printf("Loading spike templates file...complete\n");			

	return 1;
}
