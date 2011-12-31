#include "Graphs.h"


void initialize_graphs(GtkWidget * table)
{


	gtk_databox_create_box_with_scrollbars_and_rulers (&stimulus_box, &stimulus_databox,TRUE, TRUE, TRUE, TRUE);
	gtk_databox_create_box_with_scrollbars_and_rulers (&neuron_dynamics_box, &neuron_dynamics_databox,TRUE, TRUE, TRUE, TRUE);
	
	color_bg_neuron_dynamics.red = 65535;
	color_bg_neuron_dynamics.green = 65535;
	color_bg_neuron_dynamics.blue = 65535;

  	gtk_widget_modify_bg (stimulus_box, GTK_STATE_NORMAL, &color_bg_neuron_dynamics);
  	gtk_widget_modify_bg (neuron_dynamics_box, GTK_STATE_NORMAL, &color_bg_neuron_dynamics);

	color_neuron_dynamics_grid.red = 50000;
	color_neuron_dynamics_grid.green = 50000;
	color_neuron_dynamics_grid.blue = 50000;

	gtk_databox_graph_add (GTK_DATABOX (stimulus_box), gtk_databox_grid_new (21, 21, &color_neuron_dynamics_grid, 0));
	gtk_databox_graph_add (GTK_DATABOX (neuron_dynamics_box), gtk_databox_grid_new (21, 21, &color_neuron_dynamics_grid, 0));

	color_neuron_dynamics_line.red = 0;
	color_neuron_dynamics_line.green = 0;
	color_neuron_dynamics_line.blue = 0;

   	gtk_table_attach_defaults(GTK_TABLE(table), stimulus_databox, 2,7,0,3);     
   	gtk_table_attach_defaults(GTK_TABLE(table), neuron_dynamics_databox, 2,7,3,6);     

	gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, 1000, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);
	gtk_databox_set_total_limits (GTK_DATABOX (neuron_dynamics_box), 0, 1000, MAX_V_VALUE, MIN_V_VALUE);


}

void allocate_graphs(TimeStampMs arg_max_patt_len)
{
	int i;
	stimulus_graph_y_axis = g_new0(float, arg_max_patt_len);    
	stimulus_graph_x_axis = g_new0(float, arg_max_patt_len);    

	neuron_dynamics_graph_y_axis = g_new0(float, arg_max_patt_len);   
	neuron_dynamics_graph_x_axis = g_new0(float, arg_max_patt_len);   // to include dynamics value when t = 0

	for (i=0;i<arg_max_patt_len; i++)
	{
		stimulus_graph_x_axis[i] = i;
	}
	for (i=0;i<arg_max_patt_len; i++)
	{
		neuron_dynamics_graph_x_axis[i] =  i;
	}

	stimulus_graph = GTK_DATABOX_GRAPH(gtk_databox_lines_new (arg_max_patt_len, stimulus_graph_x_axis, stimulus_graph_y_axis, &color_neuron_dynamics_line, 0));
	gtk_databox_graph_add (GTK_DATABOX (stimulus_box), stimulus_graph);
	
	neuron_dynamics_graph = GTK_DATABOX_GRAPH(gtk_databox_lines_new (arg_max_patt_len, neuron_dynamics_graph_x_axis, neuron_dynamics_graph_y_axis, &color_neuron_dynamics_line, 0));
	gtk_databox_graph_add (GTK_DATABOX (neuron_dynamics_box), neuron_dynamics_graph);
	
	gtk_databox_set_total_limits (GTK_DATABOX (stimulus_box), 0, arg_max_patt_len - 1, MAX_CURRENT_VALUE, MIN_CURRENT_VALUE);		
	gtk_databox_set_total_limits (GTK_DATABOX (neuron_dynamics_box), 0,arg_max_patt_len - 1, MAX_V_VALUE, MIN_V_VALUE);	
}
