#ifndef SIMULATION_GRAPHS_H
#define SIMULATION_GRAPHS_H

#include <gtkdatabox.h>
#include <gtkdatabox_ruler.h>
#include <gtkdatabox_lines.h>
#include <gtkdatabox_grid.h>
#include <gtk/gtk.h>
#include "../Pattern/Pattern.h"

GtkWidget *stimulus_box;
GtkWidget *stimulus_databox;
GtkDataboxGraph *stimulus_graph;

GtkWidget *neuron_dynamics_box;
GtkWidget *neuron_dynamics_databox;
GtkDataboxGraph *neuron_dynamics_graph;

float *stimulus_graph_y_axis;
float *stimulus_graph_x_axis;

float *neuron_dynamics_graph_y_axis;
float *neuron_dynamics_graph_x_axis;

GdkColor color_bg_neuron_dynamics;
GdkColor color_neuron_dynamics_line;
GdkColor color_neuron_dynamics_grid;


// Functions

void initialize_graphs(GtkWidget * table);
void allocate_graphs(TimeStampMs arg_max_patt_len);
#endif
