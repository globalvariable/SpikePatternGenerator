#include "Pattern.h"

double injected_current_noise_variance = 0;
int injected_current_noise_addition_interval_ms = 1;

double initial_neuron_membrane_voltage_mean = 0;
double initial_neuron_membrane_voltage_variance = 0;	

bool allocate_patterns(TimeStampMs min_pattern_length, TimeStampMs max_pattern_length, int num_of_patterns)
{
	int i, j, k,m;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	int cntr = 0;
	srand ( time(NULL) );

	printf("Pattern: INFO: Allocating patterns...\n");	
	if (min_pattern_length>max_pattern_length)
	{
		printf("Pattern: ERROR: Minimum pattern length cannot be smaller than maximum pattern length\n");
		return FALSE;
	}
	
	if (!is_network_allocated())
		return FALSE;

	all_stimulus_patterns.pattern_lengths_ms = g_new0(TimeStampMs, num_of_patterns);
	for (i = 0; i<num_of_patterns; i++)
	{
		all_stimulus_patterns.pattern_lengths_ms[i] = (TimeStampMs)((max_pattern_length - min_pattern_length)*(rand()/(double)RAND_MAX)) + min_pattern_length;
	}

	all_stimulus_patterns.raw_stimulus_currents = g_new0(double****, num_of_patterns);
	all_stimulus_patterns.noisy_stimulus_currents = g_new0(double****, num_of_patterns);
	neuron_dynamics.v = g_new0(double****, num_of_patterns);
	neuron_dynamics.u = g_new0(double****, num_of_patterns);
	initial_neuron_dynamics.v = g_new0(double***, num_of_patterns);
	initial_neuron_dynamics.u = g_new0(double***, num_of_patterns);		
	for (i=0; i<num_of_patterns; i++)
	{	
		all_stimulus_patterns.raw_stimulus_currents[i] = g_new0(double***, all_network->layer_count);
		all_stimulus_patterns.noisy_stimulus_currents[i] = g_new0(double***, all_network->layer_count);	
		neuron_dynamics.v[i] = g_new0(double***, all_network->layer_count);
		neuron_dynamics.u[i] = g_new0(double***, all_network->layer_count);	
		initial_neuron_dynamics.v[i] = g_new0(double**, all_network->layer_count);
		initial_neuron_dynamics.u[i] = g_new0(double**, all_network->layer_count);			
		for (j=0; j<all_network->layer_count; j++)
		{
			ptr_layer = all_network->layers[j];			
			all_stimulus_patterns.raw_stimulus_currents[i][j] = g_new0(double**, ptr_layer->neuron_group_count);
			all_stimulus_patterns.noisy_stimulus_currents[i][j] = g_new0(double**, ptr_layer->neuron_group_count);	
			neuron_dynamics.v[i][j] = g_new0(double**, ptr_layer->neuron_group_count);
			neuron_dynamics.u[i][j] = g_new0(double**, ptr_layer->neuron_group_count);
			initial_neuron_dynamics.v[i][j] = g_new0(double*, ptr_layer->neuron_group_count);
			initial_neuron_dynamics.u[i][j] = g_new0(double*, ptr_layer->neuron_group_count);				
			for (k=0; k<ptr_layer->neuron_group_count; k++)
			{
				ptr_neuron_group = ptr_layer->neuron_groups[k];
				all_stimulus_patterns.raw_stimulus_currents[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);
				all_stimulus_patterns.noisy_stimulus_currents[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);	
				neuron_dynamics.v[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);		
				neuron_dynamics.u[i][j][k] = g_new0(double*, ptr_neuron_group->neuron_count);
				initial_neuron_dynamics.v[i][j][k] = g_new0(double, ptr_neuron_group->neuron_count);		
				initial_neuron_dynamics.u[i][j][k] = g_new0(double, ptr_neuron_group->neuron_count);				
				for (m=0; m<ptr_neuron_group->neuron_count; m++)
				{
					all_stimulus_patterns.raw_stimulus_currents[i][j][k][m] = g_new0(double, all_stimulus_patterns.pattern_lengths_ms[i]);
					all_stimulus_patterns.noisy_stimulus_currents[i][j][k][m] = g_new0(double, all_stimulus_patterns.pattern_lengths_ms[i]);
					neuron_dynamics.v[i][j][k][m] = g_new0(double, all_stimulus_patterns.pattern_lengths_ms[i]);		
					neuron_dynamics.u[i][j][k][m] = g_new0(double, all_stimulus_patterns.pattern_lengths_ms[i]);		
					cntr ++;				
				}
			}
		}
	}
	

	all_stimulus_patterns.drawn_stimulus_currents = g_new0(double***, all_network->layer_count);	
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		all_stimulus_patterns.drawn_stimulus_currents[i] = g_new0(double**, ptr_layer->neuron_group_count);
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			all_stimulus_patterns.drawn_stimulus_currents[i][j] = g_new0(double*, ptr_neuron_group->neuron_count);
			for (k=0; k<ptr_neuron_group->neuron_count; k++)
			{
				all_stimulus_patterns.drawn_stimulus_currents[i][j][k] = g_new0(double, max_pattern_length);
			}
		}
	}

	all_stimulus_patterns.max_pattern_length = max_pattern_length;
	all_stimulus_patterns.min_pattern_length = min_pattern_length;	
	all_stimulus_patterns.num_of_patterns = num_of_patterns;	
	
	printf("Pattern: INFO: Allocated %d stimulus (raw and noisy) current patterns.\n", cntr);

	
	if (!parker_sochacki_set_order_tolerance(40, 0))
		return FALSE;

	gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	gtk_databox_set_total_limits (GTK_DATABOX (neuron_dynamics_box), 0,all_stimulus_patterns.max_pattern_length - 1, MAX_V_VALUE, MIN_V_VALUE);
	
	return TRUE;
}

