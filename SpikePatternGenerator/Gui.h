#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../NeuroSim/Library/Network/Network.h"
#include "../../NeuroSim/Library/IzNeuron/Neuron.h"
#include "../../NeuroSim/Library/IzNeuron/NeuronTypes.h"
#include "Graphs.h"
#include "../Pattern/Pattern.h"
#include "../Randn/Randn.h"

#define LINE 0
#define SIN 1
#define COS 2
#define pi 3.141592653589793

// FIRST COLUMN
GtkWidget *combo_neuron_type;
GtkWidget *entry_v;
GtkWidget *entry_a;
GtkWidget *entry_b;
GtkWidget *entry_c;
GtkWidget *entry_d;
GtkWidget *entry_k;
GtkWidget *entry_C;
GtkWidget *entry_v_threshold;
GtkWidget *entry_v_peak;	
GtkWidget *entry_v_resting;
GtkWidget *entry_inhibitory;
GtkWidget *entry_E_excitatory;
GtkWidget *entry_E_inhibitory;
GtkWidget *entry_tau_excitatory;  
GtkWidget *entry_tau_inhibitory;
GtkWidget *entry_num_of_neuron_for_group;
GtkWidget *btn_add_neurons_to_layer;
GtkWidget *entry_add_neurons_to_layer;


// SECOND COLUMN
GtkWidget *entry_num_of_patterns;
GtkWidget *entry_min_length_of_pattern;
GtkWidget *entry_max_length_of_pattern;
GtkWidget *btn_allocate_patterns;


// SECOND COLUMN
// First Row
GtkWidget *entry_layer_num;
GtkWidget *entry_neuron_group_num;
GtkWidget *entry_neuron_num;
GtkWidget *entry_pattern_num;
GtkWidget *btn_interrogate_network;
GtkWidget *btn_interrogate_neuron;
GtkWidget *btn_display_drawn_stimuli;
GtkWidget *btn_display_raw_stimuli;
GtkWidget *btn_display_noisy_stimuli;
GtkWidget *combo_signal_type;
GtkWidget *entry_amplifier;
GtkWidget *entry_freq;
GtkWidget *entry_start_time;
GtkWidget *entry_end_time;
GtkWidget *entry_initial_current;
GtkWidget *btn_draw_stimuli;
GtkWidget *btn_copy_drawn_to_raw_stimuli;
GtkWidget *btn_add_noise;
GtkWidget *entry_noise_variance;
GtkWidget *entry_noise_period;
GtkWidget *btn_submit_initial_neuron_voltage;
GtkWidget *entry_initial_neuron_voltage;
GtkWidget *entry_initial_neuron_voltage_variance;
GtkWidget *btn_simulate;
GtkWidget *btn_display_neuron_dynamics;
GtkWidget *combo_dynamics_type;


/// LAST COLUMN
GtkWidget *txv_notes;
GtkWidget *btn_submit_notes;
GtkWidget *txv_additional_notes;
GtkWidget *btn_submit_additional_notes;
GtkWidget *btn_select_directory_to_create;
GtkWidget *btn_create_directory;
GtkWidget *btn_save;
GtkWidget *btn_select_directory_to_load;
GtkWidget *btn_load;


// THIRD COLUMN
///   at graphs.h


// Functions
void create_gui(void);
void combo_neuron_type_func(void);
void add_neurons_to_layer_button_func(void);
void interrogate_network_button_func(void); 		
void interrogate_neuron_button_func(void);
void allocate_patterns_button_func(void);
void draw_stimuli_button_func(void);
void add_noise_button_func(void);
void display_drawn_stimuli_button_func(void);
void display_raw_stimuli_button_func(void);
void display_noisy_stimuli_button_func(void);
void copy_drawn_to_raw_stimuli_button_func(void);
void simulate_button_func(void);
void display_neuron_dynamics_button_func(void);
void display_neuron_dynamics(void);
void submit_notes_button_func(void);
void submit_additional_notes_button_func(void);
void create_directory_button_func(void);
void save_button_func(void);
void load_button_func(void);
#endif
