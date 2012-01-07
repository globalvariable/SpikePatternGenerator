#ifndef SIMULATION_VIEW_H
#define SIMULATION_VIEW_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../NeuroSim/Library/Network/Network.h"
#include "../../NeuroSim/Library/IzNeuron/Neuron.h"
#include "../../NeuroSim/Library/IzNeuron/NeuronTypes.h"
#include "SimulationGraphs.h"
#include "../Pattern/Pattern.h"
#include "../Randn/Randn.h"
#include "../DataHandling/DataHandling.h"
#include "../DataHandling/DataHandling.h"
#include "FiringRateView.h"
#include "Gui.h"

#define LINE 0
#define SIN 1
#define COS 2
#define CLEAR 3
#define pi 3.141592653589793





bool create_simulation_view_gui(void);
void combo_neuron_type_func(void);
void add_neurons_to_layer_button_func(void);
void create_firing_rate_view_button_func(void);

void interrogate_network_button_func(void); 		
void interrogate_neuron_button_func(void);
void submit_parker_sochacki_params_button_func(void);
void allocate_patterns_button_func(void);
void draw_stimuli_button_func(void);
void clear_stimuli_button_func(void);
void add_noise_button_func(void);
void display_drawn_stimuli_button_func(void);
void display_raw_stimuli_button_func(void);
void display_noisy_stimuli_button_func(void);
void copy_drawn_to_raw_stimuli_button_func(void);
void simulate_button_func(void);
void display_neuron_dynamics_button_func(void);
void display_neuron_dynamics(void);
void create_directory_button_func(void);
void save_button_func(void);
void load_button_func(void);
void fill_notes_text_view(void);
void set_directory_btn_select_directory(void);
void set_neuron_param_entries(int neuron_type);







#endif
