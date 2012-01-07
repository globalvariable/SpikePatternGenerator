#include "FiringRateView.h"

static GtkWidget *entry_layer_num;
static GtkWidget *entry_neuron_group_num;
static GtkWidget *entry_neuron_num;
static GtkWidget *entry_pattern_num;
static GtkWidget *btn_display_firing_rates;
static GtkWidget *btn_calculate_firing_rates;

static GtkWidget *lbl_num_of_spikes_in_pattern;
static GtkWidget *lbl_mean_num_of_spikes_per_neuron;
static GtkWidget *lbl_variance_of_num_of_spikes_per_neuron;

bool create_firing_rate_view_gui(TimeStamp bin_size, int num_of_patterns, TimeStamp pattern_length)
{
	int i, j;
	GtkWidget *frame;
	GtkWidget *frame_label;
	
	GtkWidget *table, *hbox, *vbox, *lbl; 
	
        frame = gtk_frame_new ("Firing Rate");
        frame_label = gtk_label_new ("Firing Rate");      
        
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  	
  
 	hbox = gtk_hbox_new(TRUE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);  	


	table = gtk_table_new(6,8,TRUE);
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);
	
	///////////////////////////////////////////// FIRST COLUMN  ///////////////////////////////////////////////////////////////
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 6);  
	
  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	
	lbl = gtk_label_new("Layer #:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_layer_num = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_layer_num, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_layer_num), "0");
	gtk_widget_set_size_request(entry_layer_num, 50, 25) ;	
	
  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Group #:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_neuron_group_num = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_neuron_group_num, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_neuron_group_num), "0");
	gtk_widget_set_size_request(entry_neuron_group_num, 50, 25) ;	

  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Neuron #:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_neuron_num = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_neuron_num, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_neuron_num), "0");
	gtk_widget_set_size_request(entry_neuron_num, 50, 25) ;	

  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Pattern #:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_pattern_num = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_pattern_num, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_pattern_num), "0");
	gtk_widget_set_size_request(entry_pattern_num, 50, 25) ;	
	
 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_display_firing_rates = gtk_button_new_with_label("Display Firing Rates");
	gtk_box_pack_start (GTK_BOX (hbox), btn_display_firing_rates, TRUE, TRUE, 0);	

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,10);	

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_calculate_firing_rates = gtk_button_new_with_label("Calculate Firing Rates");
	gtk_box_pack_start (GTK_BOX (hbox), btn_calculate_firing_rates, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,10);	
	
 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);		

	lbl = gtk_label_new("Num of Spikes in Patt	: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

 	lbl_num_of_spikes_in_pattern = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_spikes_in_pattern, FALSE,FALSE,0);       
        	
 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);		

	lbl = gtk_label_new("Mean of Neuron Spikes	: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

 	lbl_mean_num_of_spikes_per_neuron = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_mean_num_of_spikes_per_neuron, FALSE,FALSE,0);      
        
 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);		

	lbl = gtk_label_new("Var of Neuron Spikes	: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

 	lbl_variance_of_num_of_spikes_per_neuron = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_variance_of_num_of_spikes_per_neuron, FALSE,FALSE,0);     
        
	///////////////////////////// GRAPHS /////////////////////////////////////////
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;

	firing_rate_submit_number_of_mwas(all_network->layer_count);
	for (i=0; i<all_network->layer_count; i++)
	{
		ptr_layer = all_network->layers[i];			
		firing_rate_submit_number_of_channels_in_mwa(i, ptr_layer->neuron_group_count);		
		for (j=0; j<ptr_layer->neuron_group_count; j++)
		{
			ptr_neuron_group = ptr_layer->neuron_groups[j];
			firing_rate_submit_number_of_units_in_mwa_channel(i, j, ptr_neuron_group->neuron_count);		
		}
	}
  	        
	firing_rate_submit_number_of_patterns (num_of_patterns);
	
	firing_rate_allocate_bins(pattern_length, bin_size);

	hbox = gtk_hbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), hbox, 1,6, 0, 3);  
 	create_firing_rate_bin_means_boxes_and_graphs(hbox, pattern_length, bin_size);  
 	  
	hbox = gtk_hbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), hbox, 1,6, 3, 6);  
	create_firing_rate_bin_variances_boxes_and_graphs(hbox, pattern_length, bin_size);
	 	   
	gtk_widget_show_all(window);

     	g_signal_connect(G_OBJECT(btn_display_firing_rates), "clicked", G_CALLBACK(display_firing_rates_button_func), NULL);	
     	g_signal_connect(G_OBJECT(btn_calculate_firing_rates), "clicked", G_CALLBACK(calculate_firing_rates_button_func), NULL);	
     	
	return TRUE;
}


void display_firing_rates_button_func(void)
{
	int pattern, layer, group, neuron_num;
	char str[20];
	NeuronFiringRate* stats;

	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	pattern = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_pattern_num)));

	refresh_neuron_firing_rate_means_graph(layer, group, neuron_num );
	refresh_neuron_firing_rate_variances_graph(layer, group, neuron_num );
	
	stats = get_neuron_firing_rate_statistics(layer, group, neuron_num );	
	
	sprintf(str, "%d" , (int)stats->num_of_spikes_in_pattern[pattern]);
	gtk_label_set_text(GTK_LABEL(lbl_num_of_spikes_in_pattern), str);
	sprintf(str, "%d" , (int)stats->mean_num_of_spikes_per_neuron);
	gtk_label_set_text(GTK_LABEL(lbl_mean_num_of_spikes_per_neuron), str);
	sprintf(str, "%d" , (int)stats->variance_of_num_of_spikes_per_neuron);
	gtk_label_set_text(GTK_LABEL(lbl_variance_of_num_of_spikes_per_neuron), str);		
}

void calculate_firing_rates_button_func(void)
{
	int i, j;
	int pattern, layer, group, neuron_num;
	char str[20];
	NeuronFiringRate* stats;
	int num_of_patt = firing_rate_get_num_of_patterns();
	TimeStamp patt_len = firing_rate_get_pattern_length_ns();
		
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	pattern = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_pattern_num)));

	firing_rate_clear_all_statistics();
	
	for (i = 0; i < num_of_patt; i++)
	{
		for (j = 0; j< all_spike_patterns.num_of_time_stamps_in_pattern[i]; j++)
		{
			firing_rate_add_spike_to_statistics(0, patt_len, all_spike_patterns.pattern_time_stamps[i][j], i);
		}
	} 	
	
	calculate_firing_rate_statistics();

	refresh_neuron_firing_rate_means_graph(layer, group, neuron_num);
	refresh_neuron_firing_rate_variances_graph(layer, group, neuron_num);
	
	stats = get_neuron_firing_rate_statistics(layer, group, neuron_num );	
	
	sprintf(str, "%d" , (int)stats->num_of_spikes_in_pattern[pattern]);
	gtk_label_set_text(GTK_LABEL(lbl_num_of_spikes_in_pattern), str);
	sprintf(str, "%d" , (int)stats->mean_num_of_spikes_per_neuron);
	gtk_label_set_text(GTK_LABEL(lbl_mean_num_of_spikes_per_neuron), str);
	sprintf(str, "%d" , (int)stats->variance_of_num_of_spikes_per_neuron);
	gtk_label_set_text(GTK_LABEL(lbl_variance_of_num_of_spikes_per_neuron), str);			
}

