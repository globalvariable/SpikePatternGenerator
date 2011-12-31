#include "Gui.h"


void create_gui(void)
{

	GtkWidget *window, *table, *vbox, *hbox, *lbl;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1020);
  	gtk_window_set_title(GTK_WINDOW(window), "StimGenerator");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);


	table = gtk_table_new(6,8,TRUE);
	gtk_container_add(GTK_CONTAINER(window), table);


///////////////////////////////////////////// FIRST COLUMN  ///////////////////////////////////////////////////////////////
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0,3);  
	
  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	combo_neuron_type = gtk_combo_box_new_text();
        gtk_box_pack_start(GTK_BOX(hbox),combo_neuron_type, TRUE,TRUE,0);
	gtk_widget_set_size_request(combo_neuron_type, 200, 25) ;
	
	int i; char neuron_type_str[50];
	for (i = 0; i < MAX_NUM_OF_NEURON_TYPES; i++)
	{
		gtk_combo_box_append_text(GTK_COMBO_BOX(combo_neuron_type), get_neuron_type_string(i, neuron_type_str));
	}
 	gtk_combo_box_set_active(GTK_COMBO_BOX(combo_neuron_type), 0);
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			v:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_v = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_v, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_v), "-65");
	gtk_widget_set_size_request(entry_v, 50, 25) ;
 
 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			a:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_a = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_a, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_a), "0.03");
	gtk_widget_set_size_request(entry_a, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			b:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_b = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_b, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_b), "-9.5");
	gtk_widget_set_size_request(entry_b, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			c:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_c = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_c, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_c), "-85");
	gtk_widget_set_size_request(entry_c, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			d:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_d = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_d, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_d), "0");
	gtk_widget_set_size_request(entry_d, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			k:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_k = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_k, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_k), "1.3");
	gtk_widget_set_size_request(entry_k, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("			C:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_C = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_C, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_C), "200");
	gtk_widget_set_size_request(entry_C, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	v thres	:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_v_threshold = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_v_threshold, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_v_threshold), "-50");
	gtk_widget_set_size_request(entry_v_threshold, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	v peak	:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_v_peak = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_v_peak, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_v_peak), "48");
	gtk_widget_set_size_request(entry_v_peak, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	v resting	:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_v_resting = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_v_resting, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_v_resting), "-65");
	gtk_widget_set_size_request(entry_v_resting, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	inhibit	:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_inhibitory = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_inhibitory, FALSE,FALSE,0);
	gtk_entry_set_max_length (GTK_ENTRY(entry_inhibitory), 1);
	gtk_entry_set_text(GTK_ENTRY(entry_inhibitory), "0");
	gtk_widget_set_size_request(entry_inhibitory, 50, 25) ;
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	E Excite	:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_E_excitatory = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_E_excitatory, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_E_excitatory), "-65");
	gtk_widget_set_size_request(entry_E_excitatory, 50, 25) ;	
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	E Inhibit	:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_E_inhibitory = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_E_inhibitory, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_E_inhibitory), "-65");
	gtk_widget_set_size_request(entry_E_inhibitory, 50, 25) ;	
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	Tau Excite:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_tau_excitatory = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_tau_excitatory, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_tau_excitatory), "5");
	gtk_widget_set_size_request(entry_tau_excitatory, 50, 25) ;	
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("	Tau Inhibit:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_tau_inhibitory = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_tau_inhibitory, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_tau_inhibitory), "10");
	gtk_widget_set_size_request(entry_tau_inhibitory, 50, 25) ;			

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Num of Neuron:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
       	entry_num_of_neuron_for_group = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_num_of_neuron_for_group, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_num_of_neuron_for_group), "1");
	gtk_widget_set_size_request(entry_num_of_neuron_for_group, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_add_neurons_to_layer = gtk_button_new_with_label("Add Neurons to Layer");
	gtk_box_pack_start (GTK_BOX (hbox), btn_add_neurons_to_layer, FALSE, FALSE, 0);

        entry_add_neurons_to_layer = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_add_neurons_to_layer, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_add_neurons_to_layer), "0");
	gtk_widget_set_size_request(entry_add_neurons_to_layer, 50, 25) ;	
	
///////////////////////////////////////////// SECOND COLUMN  ///////////////////////////////////////////////////////////////

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 1,2,0,6);     ///  Stimulus graph control

  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Num of Patterns:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_num_of_patterns = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_num_of_patterns, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_num_of_patterns), "100");
	gtk_widget_set_size_request(entry_num_of_patterns, 50, 25) ;

  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Min Patt Len(ms):");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_min_length_of_pattern = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_min_length_of_pattern, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_min_length_of_pattern), "500");
	gtk_widget_set_size_request(entry_min_length_of_pattern, 50, 25) ;

  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Max Patt Len(ms):");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_max_length_of_pattern = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_max_length_of_pattern, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_max_length_of_pattern), "500");
	gtk_widget_set_size_request(entry_max_length_of_pattern, 50, 25) ;

  	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_allocate_patterns = gtk_button_new_with_label("Allocate Patterns");
	gtk_box_pack_start (GTK_BOX (hbox), btn_allocate_patterns, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

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

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_interrogate_network = gtk_button_new_with_label("Interrogate Network");
	gtk_box_pack_start (GTK_BOX (hbox), btn_interrogate_network, TRUE, TRUE, 0);	

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_interrogate_neuron = gtk_button_new_with_label("Interrogate Neuron");
	gtk_box_pack_start (GTK_BOX (hbox), btn_interrogate_neuron, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_display_drawn_stimuli = gtk_button_new_with_label("Display Drawn Stimuli");
	gtk_box_pack_start (GTK_BOX (hbox), btn_display_drawn_stimuli, TRUE, TRUE, 0);

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

	btn_display_raw_stimuli = gtk_button_new_with_label("Display Raw Stimuli");
	gtk_box_pack_start (GTK_BOX (hbox), btn_display_raw_stimuli, TRUE, TRUE, 0);
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);	

	btn_display_noisy_stimuli = gtk_button_new_with_label("Display Noisy Stimuli");
	gtk_box_pack_start (GTK_BOX (hbox), btn_display_noisy_stimuli, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("amp:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_amplifier = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_amplifier, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_amplifier), "0");
	gtk_widget_set_size_request(entry_amplifier, 50, 25) ;

	lbl = gtk_label_new("freq:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_freq = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_freq, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_freq), "0");
	gtk_widget_set_size_request(entry_freq, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Start time (ms):	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_start_time = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_start_time, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_start_time), "0");
	gtk_widget_set_size_request(entry_start_time, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("End time (ms):	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_end_time = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_end_time, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_end_time), "0");
	gtk_widget_set_size_request(entry_end_time, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Initial Current:		");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_initial_current = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_initial_current, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_initial_current), "0");
	gtk_widget_set_size_request(entry_initial_current, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	combo_signal_type = gtk_combo_box_new_text();
        gtk_box_pack_start(GTK_BOX(hbox),combo_signal_type, TRUE,TRUE,0);
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_signal_type), "Line");
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_signal_type), "Sin");
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_signal_type), "Cos");
 	gtk_combo_box_set_active(GTK_COMBO_BOX(combo_signal_type), 0);
 	
	btn_draw_stimuli = gtk_button_new_with_label("Draw Stimuli");
	gtk_box_pack_start (GTK_BOX (hbox), btn_draw_stimuli, TRUE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_copy_drawn_to_raw_stimuli = gtk_button_new_with_label("Copy Drawn to Raw Stimuli");
	gtk_box_pack_start (GTK_BOX (hbox), btn_copy_drawn_to_raw_stimuli, TRUE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Noise Range:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_noise_range = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_noise_range, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_noise_range), "0");
	gtk_widget_set_size_request(entry_noise_range, 50, 25) ;

	lbl = gtk_label_new("Period:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_noise_period = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_noise_period, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_noise_period), "1");
	gtk_widget_set_size_request(entry_noise_period, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_add_noise = gtk_button_new_with_label("Add Noise");
	gtk_box_pack_start (GTK_BOX (hbox), btn_add_noise, TRUE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Initial Volt-");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        
  	lbl = gtk_label_new("Mean:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        
        entry_initial_neuron_voltage = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_initial_neuron_voltage , FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_initial_neuron_voltage ), "0");
	gtk_widget_set_size_request(entry_initial_neuron_voltage, 50, 25) ;

	lbl = gtk_label_new("Rng:");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_initial_neuron_voltage_range = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_initial_neuron_voltage_range , FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_initial_neuron_voltage_range ), "0");
	gtk_widget_set_size_request(entry_initial_neuron_voltage_range, 50, 25) ;

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_initial_neuron_voltage = gtk_button_new_with_label("Submit Initial Voltage");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_initial_neuron_voltage, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_simulate = gtk_button_new_with_label("Simulate");
	gtk_box_pack_start (GTK_BOX (hbox), btn_simulate, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);
	
	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
        
	btn_display_neuron_dynamics = gtk_button_new_with_label("Display Neuron Dynamics");
	gtk_box_pack_start (GTK_BOX (hbox), btn_display_neuron_dynamics, TRUE, TRUE, 0);   

	combo_dynamics_type = gtk_combo_box_new_text();
        gtk_box_pack_start(GTK_BOX(hbox),combo_dynamics_type, FALSE,FALSE,0);
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_dynamics_type), "v");
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_dynamics_type), "u");
 	gtk_combo_box_set_active(GTK_COMBO_BOX(combo_dynamics_type), 0);
 	gtk_widget_set_size_request(combo_dynamics_type, 45, 25) ;

/////// LAST COLUMN

 	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 7,8, 0,6);  

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
        
 	lbl = gtk_label_new("Folder : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	btn_select_directory_to_load = gtk_file_chooser_button_new ("Select Folder to Load", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
        gtk_box_pack_start(GTK_BOX(hbox),btn_select_directory_to_load, TRUE,TRUE,0);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_load),"/home/kocaturk/PATTERNS");

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_load = gtk_button_new_with_label("Load");
	gtk_box_pack_start (GTK_BOX (hbox), btn_load, TRUE, TRUE, 0);   
	
	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);
        
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);       	
     	  	
  	lbl = gtk_label_new("Notes:");
	gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE, 0);
	 	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	      
 	gtk_widget_set_size_request(hbox, 50, 450);
 	
	txv_notes = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(hbox),txv_notes, TRUE,TRUE, 0);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,5);
        
	btn_submit_notes = gtk_button_new_with_label("Submit Notes");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_notes, TRUE, TRUE, 0);   
	
 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);	

  	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);
        	
  	lbl = gtk_label_new("Additional Notes:");
	gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE, 0);
	 	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	      
 	gtk_widget_set_size_request(hbox, 50, 300);
 	
	txv_additional_notes = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(hbox), txv_additional_notes, TRUE,TRUE, 0);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,5);
        
	btn_submit_additional_notes = gtk_button_new_with_label("Submit Additional Notes");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_additional_notes, TRUE, TRUE, 0); 
	
	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);  	

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Folder : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	btn_select_directory_to_load= gtk_file_chooser_button_new ("Select Folder to Create", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
        gtk_box_pack_start(GTK_BOX(hbox),btn_select_directory_to_load, TRUE,TRUE,0);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_load),"/home/kocaturk/PATTERNS");

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_create_directory = gtk_button_new_with_label("Create Data Directory");
	gtk_box_pack_start (GTK_BOX (hbox), btn_create_directory, TRUE, TRUE, 0);
	
  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_save= gtk_button_new_with_label("Save");
	gtk_box_pack_start (GTK_BOX (hbox), btn_save, TRUE, TRUE, 0);	
	
	gtk_widget_set_sensitive(btn_allocate_patterns, FALSE);
	gtk_widget_set_sensitive(btn_display_raw_stimuli, FALSE);
	gtk_widget_set_sensitive(btn_display_noisy_stimuli, FALSE);
	gtk_widget_set_sensitive(btn_draw_stimuli, FALSE);
	gtk_widget_set_sensitive(btn_simulate, FALSE);
	gtk_widget_set_sensitive(btn_add_noise, FALSE);
	gtk_widget_set_sensitive(btn_submit_initial_neuron_voltage, FALSE);

	initialize_graphs(table);
	
	gtk_widget_show_all(window);

  	g_signal_connect (GTK_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  	g_signal_connect_swapped(G_OBJECT(combo_neuron_type), "changed", G_CALLBACK(combo_neuron_type_func), G_OBJECT(window));	
     	g_signal_connect_swapped(G_OBJECT(btn_add_neurons_to_layer), "clicked", G_CALLBACK(add_neurons_to_layer_button_func), G_OBJECT(window));		  	
    	g_signal_connect_swapped(G_OBJECT(btn_interrogate_network), "clicked", G_CALLBACK(interrogate_network_button_func), G_OBJECT(window));		
      	g_signal_connect_swapped(G_OBJECT(btn_interrogate_neuron), "clicked", G_CALLBACK(interrogate_neuron_button_func), G_OBJECT(window));   
      	g_signal_connect_swapped(G_OBJECT(btn_allocate_patterns), "clicked", G_CALLBACK(allocate_patterns_button_func ), G_OBJECT(window));       	
	g_signal_connect_swapped(G_OBJECT(btn_draw_stimuli), "clicked", G_CALLBACK(draw_stimuli_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_copy_drawn_to_raw_stimuli), "clicked", G_CALLBACK(copy_drawn_to_raw_stimuli_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_add_noise), "clicked", G_CALLBACK(add_noise_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_display_drawn_stimuli), "clicked", G_CALLBACK(display_drawn_stimuli_button_func), G_OBJECT(window));	
	g_signal_connect_swapped(G_OBJECT(btn_display_raw_stimuli), "clicked", G_CALLBACK(display_raw_stimuli_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_display_noisy_stimuli), "clicked", G_CALLBACK(display_noisy_stimuli_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_simulate), "clicked", G_CALLBACK(simulate_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_display_neuron_dynamics), "clicked", G_CALLBACK(display_neuron_dynamics_button_func), G_OBJECT(window));		
	g_signal_connect_swapped(G_OBJECT(btn_submit_notes), "clicked", G_CALLBACK(submit_notes_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_submit_additional_notes), "clicked", G_CALLBACK(submit_additional_notes_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_create_directory), "clicked", G_CALLBACK(create_directory_button_func), G_OBJECT(window));
	g_signal_connect_swapped(G_OBJECT(btn_save), "clicked", G_CALLBACK(load_button_func), G_OBJECT(window));		
	g_signal_connect_swapped(G_OBJECT(btn_load), "clicked", G_CALLBACK(load_button_func), G_OBJECT(window));		     	   				
	return;
}

void combo_neuron_type_func (void)
{
	char str[20];
	
	double v;
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

	int neuron_type = gtk_combo_box_get_active (GTK_COMBO_BOX(combo_neuron_type));
	
	get_neuron_type_parameters(neuron_type, &v, &a, &b, &c, &d, &k, &C, &v_resting, &v_threshold, &v_peak, &inhibitory, &E_excitatory, &E_inhibitory, &tau_excitatory, &tau_inhibitory);

	sprintf(str, "%.2f", v);	
	gtk_entry_set_text(GTK_ENTRY(entry_v), str);
	sprintf(str, "%.2f", a);	
	gtk_entry_set_text(GTK_ENTRY(entry_a), str);
	sprintf(str, "%.2f", b);		
	gtk_entry_set_text(GTK_ENTRY(entry_b), str);
	sprintf(str, "%.2f", c);	
	gtk_entry_set_text(GTK_ENTRY(entry_c), str);
	sprintf(str, "%.2f", d);
	gtk_entry_set_text(GTK_ENTRY(entry_d), str);
	sprintf(str, "%.2f", C);
	gtk_entry_set_text(GTK_ENTRY(entry_C), str);
	sprintf(str, "%.2f", k);
	gtk_entry_set_text(GTK_ENTRY(entry_k), str);
	sprintf(str, "%.2f", v_resting);
	gtk_entry_set_text(GTK_ENTRY(entry_v_resting), str);
	sprintf(str, "%.2f", v_threshold);
	gtk_entry_set_text(GTK_ENTRY(entry_v_threshold), str);
	sprintf(str, "%.2f", v_peak);
	gtk_entry_set_text(GTK_ENTRY(entry_v_peak), str);
	sprintf(str, "%d", inhibitory);
	gtk_entry_set_text(GTK_ENTRY(entry_inhibitory), str);
	sprintf(str, "%.2f", E_excitatory);
	gtk_entry_set_text(GTK_ENTRY(entry_E_excitatory), str);
	sprintf(str, "%.2f", E_inhibitory);
	gtk_entry_set_text(GTK_ENTRY(entry_E_inhibitory), str);
	sprintf(str, "%.2f", tau_excitatory);
	gtk_entry_set_text(GTK_ENTRY(entry_tau_excitatory), str);
	sprintf(str, "%.2f", tau_inhibitory);
	gtk_entry_set_text(GTK_ENTRY(entry_tau_inhibitory), str);	
}

void add_neurons_to_layer_button_func(void)
{
	int num_of_neuron;
	int layer; 
	double v;
	double a;
	double b;
	double c;
	double d;
	double k;
	double C;
	double v_resting;
	double v_threshold;
	double v_peak;
	double I_inject;
	bool inhibitory;
	double E_excitatory;
	double E_inhibitory;
	double tau_excitatory;
	double tau_inhibitory;
	int randomize_params;

 	num_of_neuron = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_num_of_neuron_for_group)));
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_add_neurons_to_layer))); 
	v = atof(gtk_entry_get_text(GTK_ENTRY(entry_v)));
	a = atof(gtk_entry_get_text(GTK_ENTRY(entry_a)));
	b = atof(gtk_entry_get_text(GTK_ENTRY(entry_b)));
	c = atof(gtk_entry_get_text(GTK_ENTRY(entry_c)));
	d = atof(gtk_entry_get_text(GTK_ENTRY(entry_d)));
	k = atof(gtk_entry_get_text(GTK_ENTRY(entry_k)));
	C = atof(gtk_entry_get_text(GTK_ENTRY(entry_C)));
	v_resting = atof(gtk_entry_get_text(GTK_ENTRY(entry_v_resting)));
	v_threshold = atof(gtk_entry_get_text(GTK_ENTRY(entry_v_threshold)));
	v_peak = atof(gtk_entry_get_text(GTK_ENTRY(entry_v_peak)));
	I_inject = 0;		// injection is done by stimulus
	inhibitory = (bool)atof(gtk_entry_get_text(GTK_ENTRY(entry_inhibitory)));
	E_excitatory = atof(gtk_entry_get_text(GTK_ENTRY(entry_E_excitatory)));
	E_inhibitory = atof(gtk_entry_get_text(GTK_ENTRY(entry_E_inhibitory)));
	tau_excitatory = atof(gtk_entry_get_text(GTK_ENTRY(entry_tau_excitatory)));
	tau_inhibitory = atof(gtk_entry_get_text(GTK_ENTRY(entry_tau_inhibitory)));
	randomize_params = 0;
							
	if (add_neurons_to_layer(num_of_neuron, layer, v, a, b, c, d, k, C, v_resting, v_threshold, v_peak, I_inject, inhibitory, E_excitatory, E_inhibitory, tau_excitatory, tau_inhibitory, randomize_params))
	{
		gtk_widget_set_sensitive(btn_allocate_patterns, TRUE);
	
	}
	return;
}

void interrogate_network_button_func(void)
{
	interrogate_network();
} 		

void interrogate_neuron_button_func(void)
{
	interrogate_neuron((int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num))), (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num))), (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num))));
}

void allocate_patterns_button_func(void)
{
	int patterns;
	int min_len, max_len;
	min_len = (TimeStampMs)atof(gtk_entry_get_text(GTK_ENTRY(entry_min_length_of_pattern)));
	max_len = (TimeStampMs)atof(gtk_entry_get_text(GTK_ENTRY(entry_max_length_of_pattern)));

	patterns = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_num_of_patterns)));	

	if (allocate_patterns(max_len, min_len,patterns))
	{
		allocate_graphs(max_len);
		gtk_widget_set_sensitive(btn_add_neurons_to_layer, FALSE);
		gtk_widget_set_sensitive(btn_allocate_patterns, FALSE);
		gtk_widget_set_sensitive(btn_display_raw_stimuli, TRUE);
		gtk_widget_set_sensitive(btn_display_noisy_stimuli, TRUE);
		gtk_widget_set_sensitive(btn_draw_stimuli, TRUE);
		gtk_widget_set_sensitive(btn_simulate, TRUE);
		gtk_widget_set_sensitive(btn_add_noise, TRUE);
		gtk_widget_set_sensitive(btn_submit_initial_neuron_voltage, TRUE);		
	}
}

void draw_stimuli_button_func(void)
{
	int layer, group, neuron_num;
	int start_time, end_time;
	int combo_idx;
	float amplifier, initial_current, freq, starting_curr_val; 
	int i;

	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));

	amplifier= atof(gtk_entry_get_text(GTK_ENTRY(entry_amplifier)));
	freq= atof(gtk_entry_get_text(GTK_ENTRY(entry_freq)));
	start_time = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_start_time)));
	end_time = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_end_time)));
	initial_current = atof(gtk_entry_get_text(GTK_ENTRY(entry_initial_current)));

	starting_curr_val = all_stimulus_patterns.drawn_stimulus_currents[layer][group][neuron_num][start_time];

	combo_idx=gtk_combo_box_get_active (GTK_COMBO_BOX(combo_signal_type));

	if ((start_time <= end_time) && (start_time >= 0) && (end_time >= 0) && (start_time < all_stimulus_patterns.max_pattern_length))
	{
		if (end_time >= all_stimulus_patterns.max_pattern_length )
		{
			printf("WARNING: End time entered is larger than maximum stimuli length %d\n", all_stimulus_patterns.max_pattern_length);
			end_time = all_stimulus_patterns.max_pattern_length-1;
		}
		if (combo_idx == LINE)
		{
			for (i=start_time; i<end_time; i++)
			{
				all_stimulus_patterns.drawn_stimulus_currents[layer][group][neuron_num][i] = amplifier * ((i-start_time)/1000.0) + initial_current+ starting_curr_val;
			}
		}
		else if (combo_idx == SIN)
		{
			for (i=start_time; i<end_time; i++)
			{
				all_stimulus_patterns.drawn_stimulus_currents[layer][group][neuron_num][i] = amplifier * sin (2*pi*freq* ((i-start_time)/1000.0)) + initial_current + starting_curr_val;
			}
		}	
		else if (combo_idx == COS)
		{
			for (i=start_time; i<end_time; i++)
			{
				all_stimulus_patterns.drawn_stimulus_currents[layer][group][neuron_num][i] = amplifier * cos (2*pi*freq* ((i-start_time)/1000.0) ) + initial_current + starting_curr_val;
			}
		}
		for (i=0; i<all_stimulus_patterns.max_pattern_length; i++)
		{
			stimulus_graph_y_axis[i] = (float)all_stimulus_patterns.drawn_stimulus_currents[layer][group][neuron_num][i];
		}
		gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	}
	else
	{
		printf ("ERROR: Submitted Start/End time is invalid to draw stimuli\n");
	}

}

void add_noise_button_func(void)
{

	int layer, group, neuron_num;
	float noise_range, noise;
	int noise_period, noise_period_cntr; 
	int i,j;
	
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	
	noise_range = atof(gtk_entry_get_text(GTK_ENTRY(entry_noise_range)));
	noise_period = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_noise_period)));

	if (noise_period<1)
	{
		printf("ERROR: Noise insertion period cannot be smaller than 1 ms\n");
		return;
	}
	
	srand ( time(NULL) );
	
	noise_period_cntr = 0;
	noise = noise_range*(rand()/(double)RAND_MAX) - (noise_range/2);
	
	for (i = 0; i< all_stimulus_patterns.num_of_patterns; i++)
	{
		for (j = 0; j < all_stimulus_patterns.pattern_lengths_ms[i]; j++)
		{
			if (noise_period_cntr == noise_period)
			{
				noise = noise_range*(rand()/(double)RAND_MAX) - (noise_range/2);			
				noise_period_cntr = 0;		
			}
			noise_period_cntr++;				
			all_stimulus_patterns.noisy_stimulus_currents[i][layer][group][neuron_num][j] = all_stimulus_patterns.raw_stimulus_currents[i][layer][group][neuron_num][j] + noise;
			if (all_stimulus_patterns.noisy_stimulus_currents[i][layer][group][neuron_num][j] < MIN_CURRENT_VALUE)
				all_stimulus_patterns.noisy_stimulus_currents[i][layer][group][neuron_num][j] = MIN_CURRENT_VALUE;			
		}			
	}	
}


void display_drawn_stimuli_button_func(void)
{
	int layer, group, neuron_num;
	int i;	
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));

	if (is_neuron(layer, group, neuron_num))
	{
		for (i=0; i<all_stimulus_patterns.max_pattern_length; i++)
		{
			stimulus_graph_y_axis[i] = (float)all_stimulus_patterns.drawn_stimulus_currents[layer][group][neuron_num][i];
		}
		gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	}
}

void display_raw_stimuli_button_func(void)
{
	int pattern, layer, group, neuron_num;
	int i;	
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	pattern = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_pattern_num)));

	if ((pattern < all_stimulus_patterns.num_of_patterns) && (is_neuron(layer, group, neuron_num)))
	{
		for (i=0; i<all_stimulus_patterns.pattern_lengths_ms[pattern]; i++)
		{
			stimulus_graph_y_axis[i] = (float)all_stimulus_patterns.raw_stimulus_currents[pattern][layer][group][neuron_num][i];
		}
		gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	}
}

void display_noisy_stimuli_button_func(void)
{
	int pattern, layer, group, neuron_num;
	int i;	
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	pattern = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_pattern_num)));

	if ((pattern < all_stimulus_patterns.num_of_patterns) && (is_neuron(layer, group, neuron_num)))
	{
		for (i=0; i<all_stimulus_patterns.pattern_lengths_ms[pattern]; i++)
		{
			stimulus_graph_y_axis[i] = (float)all_stimulus_patterns.noisy_stimulus_currents[pattern][layer][group][neuron_num][i];
		}
		gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	}
}

void copy_drawn_to_raw_stimuli_button_func(void)
{

	int i,j, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
		
	for (i = 0; i< all_stimulus_patterns.num_of_patterns; i++)
	{
		for (j = 0; j < all_stimulus_patterns.pattern_lengths_ms[i]; j++)
		{
			for (k=0; k<all_network->layer_count; k++)
			{
				ptr_layer = all_network->layers[k];			
				for (m=0; m<ptr_layer->neuron_group_count; m++)
				{
					ptr_neuron_group = ptr_layer->neuron_groups[m];
					for (n=0; n<ptr_neuron_group->neuron_count; n++)
					{
						all_stimulus_patterns.raw_stimulus_currents[i][k][m][n][j] = all_stimulus_patterns.drawn_stimulus_currents[k][m][n][j];   // directly uses drawn stimulus to generate raw. squeezing, or modifications can be reflected to raw stimuli in the future. 
					}
				}
			}
		}			
	}

}


void submit_initial_neuron_voltage_button_func(void)
{
	int layer, group, neuron_num;
	double initial_neuron_voltage, initial_neuron_voltage_range, voltage;
	Neuron* nrn;
	int i;

	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	
	initial_neuron_voltage = atof(gtk_entry_get_text(GTK_ENTRY(entry_initial_neuron_voltage)));
	initial_neuron_voltage_range = atof(gtk_entry_get_text(GTK_ENTRY(entry_initial_neuron_voltage_range)));

	nrn = get_neuron_address(layer, group, neuron_num);
	if (nrn == NULL)
		return;

	if (initial_neuron_voltage > nrn->v_peak)
	{
		printf("Initial neuron voltage cannot be larger than peak voltage %f\n",  nrn->v_peak);
		return;
	}
			
	for (i = 0; i< all_stimulus_patterns.num_of_patterns; i++)
	{
		voltage = initial_neuron_voltage_range*(rand()/(double)RAND_MAX) - (initial_neuron_voltage_range/2) + initial_neuron_voltage;
		if (voltage < 0)
			voltage = 0;
		if (voltage > nrn->v_peak)	
			voltage = nrn->v_peak;
		initial_neuron_dynamics.v[i][layer][group][neuron_num] = voltage;
		initial_neuron_dynamics.u[i][layer][group][neuron_num] = nrn->b * voltage;
	}
}


void simulate_button_func(void)
{
	int i, k, m, n;
	Layer		*ptr_layer;
	NeuronGroup	*ptr_neuron_group;
	Neuron		*ptr_neuron;		
	
	TimeStamp start_time_ns, end_time_ns, time_ns;
	ParkerSochackiStepSize step_size = 250000;
	TimeStampMs time_ms_idx;
	TimeStamp  spike_time;


	for (i = 0; i< all_stimulus_patterns.num_of_patterns; i++)
	{
		start_time_ns = 0;
		end_time_ns = all_stimulus_patterns.pattern_lengths_ms[i] * 1000000;
		for (time_ns = start_time_ns; time_ns < end_time_ns; time_ns+=step_size)
		{	
			time_ms_idx = (TimeStampMs)(time_ns/1000000); // milliseconds scale
			for (k=0; k<all_network->layer_count; k++)
			{
				ptr_layer = all_network->layers[k];			
				for (m=0; m<ptr_layer->neuron_group_count; m++)
				{
					ptr_neuron_group = ptr_layer->neuron_groups[m];
					for (n=0; n<ptr_neuron_group->neuron_count; n++)
					{
						ptr_neuron = &(ptr_neuron_group->neurons[n]);
						if (time_ns == start_time_ns)
						{
							ptr_neuron->v = initial_neuron_dynamics.v[i][k][m][n]; 
							ptr_neuron->u = initial_neuron_dynamics.u[i][k][m][n];
						} 
						ptr_neuron -> I_inject = all_stimulus_patterns.noisy_stimulus_currents[i][k][m][n][time_ms_idx];
						spike_time = evaluate_neuron_dyn(ptr_neuron, time_ns, time_ns+step_size);
						if (spike_time != 0)
							printf ("Spike time nano: %llu\n", spike_time);
						neuron_dynamics.v[i][k][m][n][time_ms_idx] = ptr_neuron->v;	
						neuron_dynamics.u[i][k][m][n][time_ms_idx] = ptr_neuron->u;								
					}
				}
			}
		}
	}
	display_neuron_dynamics();	
}

void display_neuron_dynamics_button_func(void)
{
	display_neuron_dynamics();
}

void display_neuron_dynamics(void)
{
	int pattern, layer, group, neuron_num;
	int i;
	int active_neuron_dyn_to_disp;	
	layer = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_layer_num)));
	group = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_group_num)));
	neuron_num = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_neuron_num)));
	pattern = (int)atof(gtk_entry_get_text(GTK_ENTRY(entry_pattern_num)));
	
	active_neuron_dyn_to_disp = gtk_combo_box_get_active (GTK_COMBO_BOX(combo_dynamics_type));
	if ((pattern < all_stimulus_patterns.num_of_patterns) && (is_neuron(layer, group, neuron_num)))
	{
		for (i=0; i<all_stimulus_patterns.pattern_lengths_ms[pattern]; i++)
		{
			if (active_neuron_dyn_to_disp == 0)	// display v 
			{
				neuron_dynamics_graph_y_axis[i] = (float)neuron_dynamics.v[pattern][layer][group][neuron_num][i];
				gtk_databox_set_total_limits (GTK_DATABOX (neuron_dynamics_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_V_VALUE, MIN_V_VALUE);		
			}
			else if  (active_neuron_dyn_to_disp == 1) // display u
			{
				neuron_dynamics_graph_y_axis[i] = (float)neuron_dynamics.u[pattern][layer][group][neuron_num][i];
				gtk_databox_set_total_limits (GTK_DATABOX (neuron_dynamics_box), 0, all_stimulus_patterns.max_pattern_length - 1, MAX_U_VALUE, MIN_U_VALUE);		
			}			
		}

	}
}

void create_directory_button_func(void)
{

}

void submit_notes_button_func(void)
{

}

void submit_additional_notes_button_func(void)
{

}

void save_button_func(void)
{

}

void load_button_func(void)
{

}
