#include "FiringRateView.h"



bool create_firing_rate_view_gui(GtkWidget *tabs)
{

	GtkWidget *frame_firing_rate;
	GtkWidget *frame_label_firing_rate;

        frame_firing_rate = gtk_frame_new ("Firing Rate");
        frame_label_firing_rate = gtk_label_new ("Firing Rate");      
        
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame_firing_rate, frame_label_firing_rate);  		
        
	return TRUE;
}
