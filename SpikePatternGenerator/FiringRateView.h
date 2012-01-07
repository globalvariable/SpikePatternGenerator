#ifndef FIRING_RATE_VIEW_H
#define FIRING_RATE_VIEW_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../BlueSpike/Library/NeuroStats/FiringRate/FiringRateGraph.h"
#include "../../NeuroSim/Library/Network/Network.h"
#include "Gui.h"


bool create_firing_rate_view_gui(TimeStamp bin_size, int num_of_patterns, TimeStamp pattern_length);
void display_firing_rates_button_func(void);
void calculate_firing_rates_button_func(void);






#endif
