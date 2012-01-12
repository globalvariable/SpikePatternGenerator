#include "Gui.h"


void create_gui(void)
{

	GtkWidget *vbox;


 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1020);
  	gtk_window_set_title(GTK_WINDOW(window), "SpikePatternGenerator");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	tabs = gtk_notebook_new ();
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (tabs), GTK_POS_TOP);
        gtk_box_pack_start(GTK_BOX(vbox),tabs, TRUE, TRUE, 0);

  	if (!create_simulation_view_gui())
		return;      	
//	if (!create_firing_rate_view_gui(window, tabs))
//		return;

	gtk_widget_show_all(window);

	initialize_spike_pattern_generator_data_read_write_handlers();
	
  	g_signal_connect (GTK_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  		   				
	return;
}


