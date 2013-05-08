/*
	This file is part of nationstates-gtk.

    nationstates-gtk is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    nationstates-linux is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with nationstates-gtk.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <gtk/gtk.h>
#include "reading.h"

static GtkWidget* create_window(void){

	/// Create the main window and set its title
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Nationstates-linux");

	/// Declare the main_box and make a temp left_box where the treeview should be
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	/// Tabs for the notebook
	GtkWidget *save_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *description_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *region_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *graph_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *event_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	/// Declare a new notebook
	GtkWidget *notebook = gtk_notebook_new();

	/// Append the pages with appropriate labels to the notebook
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), save_tab, gtk_label_new("Saved Data"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), description_tab, gtk_label_new("Description"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), region_tab, gtk_label_new("Region"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), graph_tab, gtk_label_new("Census Graph"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), event_tab, gtk_label_new("Events"));

	/// Add the main box to the window then add the left_box and notebook ( should be right box ) to the main_box
	gtk_container_add(GTK_CONTAINER(window), main_box);
	gtk_box_pack_start(GTK_BOX(main_box), left_box, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), notebook, TRUE, TRUE, 0);

	/// Set up signal handlers for events
	g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	return window;
}

int main(int argc, char **argv){

	gtk_init (&argc, &argv);

	/// Create a reference for the window and put our window in it.
	GtkWidget *main_window = create_window();

	/// Show all the widgets that exist in the main_window
	gtk_widget_show_all (main_window);

	/// Start the wait for event loop
	gtk_main();
	return 0;
}
