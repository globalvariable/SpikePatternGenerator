#include "Pattern.h"

bool allocate_patterns(TimeStampMs min_pattern_length, TimeStampMs max_pattern_length, int num_of_patterns)
{
	int i;

	srand ( time(NULL) );

	printf("Pattern: INFO: Allocating patterns...\n");	
	if (min_pattern_length>max_pattern_length)
	{
		printf("Pattern: ERROR: Minimum pattern length cannot be larger than maximum pattern length\n");
		return FALSE;
	}
	if ((min_pattern_length <= 0) || (max_pattern_length <= 0) )
	{
		printf("Pattern: ERROR: Any pattern length cannot be smaller than or equal to zero\n");
		return FALSE;
	}
		
	if (!is_network_allocated())
		return FALSE;

	all_stimulus_patterns_info.pattern_lengths_ms = g_new0(TimeStampMs, num_of_patterns);
	for (i = 0; i<num_of_patterns; i++)
	{
		all_stimulus_patterns_info.pattern_lengths_ms[i] = (TimeStampMs)((max_pattern_length - min_pattern_length)*(rand()/(double)RAND_MAX)) + min_pattern_length;
	}
	all_stimulus_patterns_info.max_pattern_length = max_pattern_length;
	all_stimulus_patterns_info.min_pattern_length = min_pattern_length;	
	all_stimulus_patterns_info.num_of_patterns = num_of_patterns;	

	printf("Pattern: INFO: Allocated all stimulus pattern info struct.\n");

	if (!allocate_stimulus_currents())
		return FALSE;
		
	if (!allocate_neuron_dynamics())	
		return FALSE;
		
	if (!allocate_spike_patterns())		
		return FALSE;
					
	gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, all_stimulus_patterns_info.max_pattern_length - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	gtk_databox_set_total_limits (GTK_DATABOX (neuron_dynamics_box), 0,all_stimulus_patterns_info.max_pattern_length - 1, MAX_V_VALUE, MIN_V_VALUE);
	
	return TRUE;
}

bool deallocate_patterns(void)
{
	if (!is_network_allocated())
		return FALSE;
		
	if (!deallocate_stimulus_currents())
		return FALSE;
		
	if (!deallocate_neuron_dynamics())	
		return FALSE;
		
	if (!deallocate_spike_patterns())		
		return FALSE;		
		
	g_free(all_stimulus_patterns_info.pattern_lengths_ms);
	all_stimulus_patterns_info.pattern_lengths_ms = NULL;		
	all_stimulus_patterns_info.max_pattern_length = 0;
	all_stimulus_patterns_info.min_pattern_length = 0;	
	all_stimulus_patterns_info.num_of_patterns = 0;		

	return TRUE;	
}


bool increment_time_stamp_number_of_pattern(int pattern_num)
{
	int i;
	SpikeTimeStampItem* local_pattern_time_stamps = NULL; 

	local_pattern_time_stamps = g_new0(SpikeTimeStampItem, all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num] +1);	
	if (local_pattern_time_stamps == NULL)
	{
		printf("Pattern: ERROR: Couldn't allocate new spike pattern for pattern number: %d\n", pattern_num);
		return FALSE;		
	}
	for (i=0; i< all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]; i++)
	{
		local_pattern_time_stamps[i] = all_spike_patterns.pattern_time_stamps[pattern_num][i];
	}
	g_free(all_spike_patterns.pattern_time_stamps[pattern_num]);
	all_spike_patterns.pattern_time_stamps[pattern_num] = local_pattern_time_stamps;
	all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]++;
	
	return TRUE;
}

bool add_time_stamp_to_spike_pattern_time_stamps(int pattern_num, int layer, int neuron_group, int neuron_num, TimeStamp spike_time)
{

	 if (increment_time_stamp_number_of_pattern(pattern_num))
	{
		all_spike_patterns.pattern_time_stamps[pattern_num][all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]-1].peak_time = spike_time;
		all_spike_patterns.pattern_time_stamps[pattern_num][all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]-1].mwa_or_layer = layer;
		all_spike_patterns.pattern_time_stamps[pattern_num][all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]-1].channel_or_neuron_group = neuron_group;	
		all_spike_patterns.pattern_time_stamps[pattern_num][all_spike_patterns.num_of_time_stamps_in_pattern[pattern_num]-1].unit_or_neuron = neuron_num;	
		return TRUE;					
	}
	return FALSE;
}

void clear_spike_pattern_time_stamps(void)
{
	int i;
	for (i = 0; i < all_stimulus_patterns_info.num_of_patterns; i++)
	{
		g_free(all_spike_patterns.pattern_time_stamps[i]);	
		all_spike_patterns.pattern_time_stamps[i] = NULL;	// g_free does not make this register null 
		all_spike_patterns.num_of_time_stamps_in_pattern[i] = 0;
	}
	printf("Pattern: INFO: Cleared spike timestamps in memory.\n");
}

bool allocate_stimulus_currents(void)
{
	int i, j, k,m;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	if (!is_network_allocated())
		return FALSE;
	
	all_stimulus_currents.drawn_stimulus_currents = g_new0(double***, all_network->layer_count);
	all_stimulus_currents.noise_variances = g_new0(double**, all_network->layer_count);	
	all_stimulus_currents.noise_addition_ms_intervals = g_new0(TimeStampMs**, all_network->layer_count);			
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		all_stimulus_currents.drawn_stimulus_currents[i] = g_new0(double**, ptr_layer->neuron_group_count);
		all_stimulus_currents.noise_variances[i] = g_new0(double*,  ptr_layer->neuron_group_count);	
		all_stimulus_currents.noise_addition_ms_intervals[i] = g_new0(TimeStampMs*,  ptr_layer->neuron_group_count);				
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			all_stimulus_currents.drawn_stimulus_currents[i][j] = g_new0(double*, ptr_neuron_group->neuron_count);
			all_stimulus_currents.noise_variances[i][j] = g_new0(double, ptr_neuron_group->neuron_count);		
			all_stimulus_currents.noise_addition_ms_intervals[i][j] = g_new0(TimeStampMs, ptr_neuron_group->neuron_count);		
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				all_stimulus_currents.drawn_stimulus_currents[i][j][k] = g_new0(double, all_stimulus_patterns_info.max_pattern_length);
			}
		}
	}

	all_stimulus_currents.raw_stimulus_currents = g_new0(double****, all_stimulus_patterns_info.num_of_patterns);
	all_stimulus_currents.noisy_stimulus_currents = g_new0(double****, all_stimulus_patterns_info.num_of_patterns);
	for (i=0; i<all_stimulus_patterns_info.num_of_patterns; i++)
	{
		all_stimulus_currents.raw_stimulus_currents[i] = g_new0(double***, all_network->layer_count);
		all_stimulus_currents.noisy_stimulus_currents[i] = g_new0(double***, all_network->layer_count);
		for (j=0; j<all_network->layer_count; j++)
		{			
			ptr_layer = all_network->layers[j];			
			all_stimulus_currents.raw_stimulus_currents[i][j] = g_new0(double**, ptr_layer->neuron_group_count);
			all_stimulus_currents.noisy_stimulus_currents[i][j] = g_new0(double**, ptr_layer->neuron_group_count);	
			for (k=0; k<ptr_layer->neuron_group_count; k++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[k];
				all_stimulus_currents.raw_stimulus_currents[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);
				all_stimulus_currents.noisy_stimulus_currents[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);	
				for (m=0; m<ptr_neuron_group->neuron_count; m++)
				{
					all_stimulus_currents.raw_stimulus_currents[i][j][k][m] = g_new0(double, all_stimulus_patterns_info.pattern_lengths_ms[i]);
					all_stimulus_currents.noisy_stimulus_currents[i][j][k][m] = g_new0(double, all_stimulus_patterns_info.pattern_lengths_ms[i]);
				}
			}
		}
	}
	printf ("Pattern: INFO: Allocated stimulus current struct\n");
	return TRUE;
}

bool allocate_neuron_dynamics(void)
{
	int i, j, k,m;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	if (!is_network_allocated())
		return FALSE;

	neuron_dynamics.v = g_new0(double****, all_stimulus_patterns_info.num_of_patterns);
	neuron_dynamics.u = g_new0(double****, all_stimulus_patterns_info.num_of_patterns);
	neuron_dynamics.initial_v = g_new0(double***, all_stimulus_patterns_info.num_of_patterns);
	neuron_dynamics.initial_u = g_new0(double***,all_stimulus_patterns_info.num_of_patterns);		
	for (i=0; i<all_stimulus_patterns_info.num_of_patterns; i++)
	{	
		neuron_dynamics.v[i] = g_new0(double***, all_network->layer_count);
		neuron_dynamics.u[i] = g_new0(double***, all_network->layer_count);	
		neuron_dynamics.initial_v[i] = g_new0(double**, all_network->layer_count);
		neuron_dynamics.initial_u[i] = g_new0(double**, all_network->layer_count);			
		for (j=0; j<all_network->layer_count; j++)
		{
			ptr_layer = all_network->layers[j];			
			neuron_dynamics.v[i][j] = g_new0(double**, ptr_layer->neuron_group_count);
			neuron_dynamics.u[i][j] = g_new0(double**, ptr_layer->neuron_group_count);
			neuron_dynamics.initial_v[i][j] = g_new0(double*, ptr_layer->neuron_group_count);
			neuron_dynamics.initial_u[i][j] = g_new0(double*, ptr_layer->neuron_group_count);				
			for (k=0; k<ptr_layer->neuron_group_count; k++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[k];
				neuron_dynamics.v[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);		
				neuron_dynamics.u[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);
				neuron_dynamics.initial_v[i][j][k] = g_new0(double, ptr_neuron_group->neuron_count);		
				neuron_dynamics.initial_u[i][j][k] = g_new0(double, ptr_neuron_group->neuron_count);				
				for (m=0; m<ptr_neuron_group->neuron_count; m++)
				{
					neuron_dynamics.v[i][j][k][m] = g_new0(double, all_stimulus_patterns_info.pattern_lengths_ms[i]);		
					neuron_dynamics.u[i][j][k][m] = g_new0(double, all_stimulus_patterns_info.pattern_lengths_ms[i]);		
				}
			}
		}
	}
	
	neuron_dynamics.initial_v_means = g_new0(double**, all_network->layer_count);
	neuron_dynamics.initial_v_variances = g_new0(double**, all_network->layer_count);	
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		neuron_dynamics.initial_v_means[i] = g_new0(double*, ptr_layer->neuron_group_count);
		neuron_dynamics.initial_v_variances[i] = g_new0(double*, ptr_layer->neuron_group_count);
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			neuron_dynamics.initial_v_means[i][j] = g_new0(double, ptr_neuron_group->neuron_count);		
			neuron_dynamics.initial_v_variances[i][j] = g_new0(double, ptr_neuron_group->neuron_count);
		}
	}	
	printf ("Pattern: INFO: Allocated neuron dynamics struct\n");	
	return TRUE;	
}

bool allocate_spike_patterns(void)
{
	if (!is_network_allocated())
		return FALSE;

	all_spike_patterns.pattern_time_stamps = g_new0(SpikeTimeStampItem*, all_stimulus_patterns_info.num_of_patterns);		// num_of_pattern * num_of_time_stamps_in_pattern
	all_spike_patterns.num_of_time_stamps_in_pattern = g_new0(int, all_stimulus_patterns_info.num_of_patterns);
	printf ("Pattern: INFO: Allocated spike time stamps struct for each pattern - not allocated for each spike\n");		
	return TRUE;	
}


bool deallocate_stimulus_currents(void)
{
	int i, j, k,m;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	if (!is_network_allocated())
		return FALSE;
	
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				g_free(all_stimulus_currents.drawn_stimulus_currents[i][j][k]);
			}
			g_free(all_stimulus_currents.drawn_stimulus_currents[i][j]);
			g_free(all_stimulus_currents.noise_variances[i][j]);
			g_free(all_stimulus_currents.noise_addition_ms_intervals[i][j]);	
		}
		g_free(all_stimulus_currents.drawn_stimulus_currents[i]);
		g_free(all_stimulus_currents.noise_variances[i]);
		g_free(all_stimulus_currents.noise_addition_ms_intervals[i]);			
	}
	g_free(all_stimulus_currents.drawn_stimulus_currents);
	g_free(all_stimulus_currents.noise_variances);
	g_free(all_stimulus_currents.noise_addition_ms_intervals);		
	all_stimulus_currents.drawn_stimulus_currents = NULL;
	all_stimulus_currents.noise_variances = NULL;
	all_stimulus_currents.noise_addition_ms_intervals = NULL;		

	for (i=0; i<all_stimulus_patterns_info.num_of_patterns; i++)
	{
		for (j=0; j<all_network->layer_count; j++)
		{			
			ptr_layer = all_network->layers[j];			

			for (k=0; k<ptr_layer->neuron_group_count; k++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[k];

				for (m=0; m<ptr_neuron_group->neuron_count; m++)
				{
					g_free(all_stimulus_currents.raw_stimulus_currents[i][j][k][m]);
					g_free(all_stimulus_currents.noisy_stimulus_currents[i][j][k][m]);
				}
				g_free(all_stimulus_currents.raw_stimulus_currents[i][j][k]);
				g_free(all_stimulus_currents.noisy_stimulus_currents[i][j][k]);					
			}
			g_free(all_stimulus_currents.raw_stimulus_currents[i][j]);
			g_free(all_stimulus_currents.noisy_stimulus_currents[i][j]);				
		}
		g_free(all_stimulus_currents.raw_stimulus_currents[i]);
		g_free(all_stimulus_currents.noisy_stimulus_currents[i]);	
	}
	g_free(all_stimulus_currents.raw_stimulus_currents);
	g_free(all_stimulus_currents.noisy_stimulus_currents);	
	all_stimulus_currents.raw_stimulus_currents = NULL;
	all_stimulus_currents.noisy_stimulus_currents = NULL;
			
	printf ("Pattern: INFO: De-Allocated stimulus current struct\n");
	return TRUE;
}

bool deallocate_neuron_dynamics(void)
{
	int i, j, k,m;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	if (!is_network_allocated())
		return FALSE;

	for (i=0; i<all_stimulus_patterns_info.num_of_patterns; i++)
	{	
		for (j=0; j<all_network->layer_count; j++)
		{
			ptr_layer = all_network->layers[j];			
			for (k=0; k<ptr_layer->neuron_group_count; k++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[k];
				for (m=0; m<ptr_neuron_group->neuron_count; m++)
				{
					g_free(neuron_dynamics.v[i][j][k][m]);		
					g_free(neuron_dynamics.u[i][j][k][m]);		
				}
				g_free(neuron_dynamics.v[i][j][k]);		
				g_free(neuron_dynamics.u[i][j][k]);
				g_free(neuron_dynamics.initial_v[i][j][k]);		
				g_free(neuron_dynamics.initial_u[i][j][k]);					
			}
			g_free(neuron_dynamics.v[i][j]);
			g_free(neuron_dynamics.u[i][j]);
			g_free(neuron_dynamics.initial_v[i][j]);
			g_free(neuron_dynamics.initial_u[i][j]);			
		}
		g_free(neuron_dynamics.v[i]);
		g_free(neuron_dynamics.u[i]);	
		g_free(neuron_dynamics.initial_v[i]);
		g_free(neuron_dynamics.initial_u[i]);			
	}
	g_free(neuron_dynamics.v);
	g_free(neuron_dynamics.u);
	g_free(neuron_dynamics.initial_v);
	g_free(neuron_dynamics.initial_u);
	neuron_dynamics.v = NULL;
	neuron_dynamics.u = NULL;
	neuron_dynamics.initial_v = NULL;
	neuron_dynamics.initial_u = NULL;	

	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			g_free(neuron_dynamics.initial_v_means[i][j]);		
			g_free(neuron_dynamics.initial_v_variances[i][j]);
		}
		g_free(neuron_dynamics.initial_v_means[i]);
		g_free(neuron_dynamics.initial_v_variances[i]);		
	}	
	g_free(neuron_dynamics.initial_v_means);
	g_free(neuron_dynamics.initial_v_variances);	
	neuron_dynamics.initial_v_means = NULL;	
	neuron_dynamics.initial_v_variances = NULL;
	printf ("Pattern: INFO: De-Allocated neuron dynamics struct\n");	
	return TRUE;	
}

bool deallocate_spike_patterns(void)
{
	int i;

	if (!is_network_allocated())
		return FALSE;
	
	for (i = 0; i < all_stimulus_patterns_info.num_of_patterns; i++)
	{
		g_free(all_spike_patterns.pattern_time_stamps[i]);
	}
	g_free(all_spike_patterns.pattern_time_stamps);
	g_free(all_spike_patterns.num_of_time_stamps_in_pattern);
	all_spike_patterns.pattern_time_stamps = NULL;
	all_spike_patterns.num_of_time_stamps_in_pattern = NULL;
	printf ("Pattern: INFO: De-Allocated spike time stamps\n");		
	return TRUE;	
}
