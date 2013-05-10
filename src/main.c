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
#include <gdk/gdkkeysyms.h>
#include <curl/curl.h>
#include "reading.h"
#include "main.h"

static GtkWidget* create_window(void){

	/// Create the main window and set its title
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Nation States");

	/// Label for the flag and nation information
	GtkWidget *infobox = gtk_label_new("test");

	/// Declare the boxes
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *menu_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *lr_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	/// Tabs for the notebook
	GtkWidget *save_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *description_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *region_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *graph_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *event_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	/// Append the pages with appropriate labels to the notebook
	GtkWidget* tabs[] = {save_tab, description_tab, region_tab, graph_tab, event_tab};
	char* tab_labels[] = {"Saved Data", "Desription", "Region", "Census Graph", "Events"};
	GtkWidget *notebook = gtk_notebook_new();
	for(i=0; i<sizeof(tabs)/sizeof(tabs[0]); i++)
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tabs[i], gtk_label_new(tab_labels[i]));

	/// Treeview declarations
	GtkWidget *treeview = gtk_tree_view_new();
	GtkTreeViewColumn *nation_stat = gtk_tree_view_column_new();
	GtkTreeViewColumn *column_a = gtk_tree_view_column_new();
	GtkTreeViewColumn *column_b = gtk_tree_view_column_new();
	GtkTreeViewColumn *plus_minus = gtk_tree_view_column_new();

	/// Treeview formation
	GtkTreeViewColumn* columns[] = {nation_stat, column_a, column_b, plus_minus};
	char* column_labels[] = {"Nation Statistics", "a", "b", "+/-"};
	for(i=0; i<sizeof(columns)/sizeof(columns[0]); i++){
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), columns[i]);
		gtk_tree_view_column_set_title(columns[i], column_labels[i]);
	}

	/// Nationview formation
	nationview = gtk_tree_view_new();
	renderer = gtk_cell_renderer_text_new();
	GtkTreeViewColumn *nationlist = gtk_tree_view_column_new_with_attributes("Nations", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(nationview), nationlist);

	/// Saveview formation
	saveview = gtk_tree_view_new();
	GtkTreeViewColumn *savelist = gtk_tree_view_column_new_with_attributes("Saves", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(saveview), savelist);
	gtk_tree_view_column_set_title(savelist, "Saves");

	/// Make and attach liststores to savelists
	nationstore = gtk_list_store_new(1, G_TYPE_STRING);
	savestore = gtk_list_store_new(1, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(nationview), GTK_TREE_MODEL(nationstore));
	gtk_tree_view_set_model(GTK_TREE_VIEW(saveview), GTK_TREE_MODEL(savestore));

	/// Menu stuff
	GtkAccelGroup *accel_group = gtk_accel_group_new();
	GtkWidget *menubar = gtk_menu_bar_new();
	GtkWidget *file_menu  = gtk_menu_new();
	GtkWidget *view_menu = gtk_menu_new();
	GtkWidget *tools_menu = gtk_menu_new();
	GtkWidget *help_menu = gtk_menu_new();

	GtkWidget *file = gtk_menu_item_new_with_label("File");
	GtkWidget *new_nation = gtk_menu_item_new_with_label("Add Nation");
	GtkWidget *file_sep = gtk_separator_menu_item_new();
	GtkWidget *quit = gtk_menu_item_new_with_label("Quit");

	GtkWidget *view = gtk_menu_item_new_with_label("View");
	GtkWidget *hide_info = gtk_check_menu_item_new_with_label("Hide Info/Flag Box");

	GtkWidget *tools = gtk_menu_item_new_with_label("Tools");
	GtkWidget *update = gtk_menu_item_new_with_label("Update All");

	GtkWidget *help = gtk_menu_item_new_with_label("Help");
	GtkWidget *help_option = gtk_menu_item_new_with_label("Help");
	GtkWidget *about = gtk_menu_item_new_with_label("About");


	/// Menu organizing
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_nation);
	gtk_widget_add_accelerator(new_nation, "activate", accel_group, GDK_KEY_N, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit);
	gtk_widget_add_accelerator(quit, "activate", accel_group, GDK_KEY_Q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), view_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view);
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(hide_info), FALSE	);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), hide_info);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(tools), tools_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), tools);
	gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), update);
	gtk_widget_add_accelerator(update, "activate", accel_group, GDK_KEY_U, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), help_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_option);
	gtk_widget_add_accelerator(help_option, "activate", accel_group, GDK_KEY_F1, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about);

	/// Menu events
	g_signal_connect (G_OBJECT(new_nation), "activate", G_CALLBACK(on_new_nation), NULL);
	g_signal_connect (G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect (G_OBJECT(hide_info), "activate", G_CALLBACK(toggle_infobox), infobox);

	g_signal_connect (G_OBJECT(update), "activate", G_CALLBACK(on_update), NULL);

	g_signal_connect (G_OBJECT(help_option), "activate", G_CALLBACK(on_help), NULL);
	g_signal_connect (G_OBJECT(about), "activate", G_CALLBACK(on_about), NULL);

	/// Main box starting
	gtk_container_add(GTK_CONTAINER(window), main_box);
	gtk_box_pack_start(GTK_BOX(main_box), menu_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), lr_box, TRUE, TRUE, 0);

	/// Menu box starting
	gtk_box_pack_start(GTK_BOX(menu_box), menubar, FALSE, FALSE, 0);

	/// LR box starting
	gtk_box_pack_start(GTK_BOX(lr_box), left_box, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(lr_box), right_box, TRUE, TRUE, 1);


	/// Left box starting
	gtk_box_pack_start(GTK_BOX(left_box), treeview, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(save_tab), nationview, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(save_tab), saveview, TRUE, TRUE, 1);

	/// Right box starting
	gtk_box_pack_start(GTK_BOX(right_box), infobox, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(right_box), notebook, TRUE, TRUE, 1);

	/// Set up signal handlers for events
	g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/// Signal to update a nation. Button should be the right menu click for update data
	//g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(get_nation_data), NULL);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(nationview));
	g_signal_connect(selection, "changed", G_CALLBACK(nation_selection_changed), "");

	return window;
}

void on_new_nation(){
	char nation_name[40];
	///Declaring new nation stuff
	GtkWidget *newnation_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(newnation_window), "Add New Nation");
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *newnation_entry = gtk_entry_new();
	GtkWidget *newnation_button = gtk_button_new_with_label("Add Nation");

	///Placing objects in window
	gtk_container_add(GTK_CONTAINER(newnation_window), main_box);
	gtk_box_pack_start(GTK_BOX(main_box), newnation_entry, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(main_box), newnation_button, TRUE, TRUE, 1);

	///Make Window Show
	gtk_widget_show_all(newnation_window);

	///Gets info and adds new nation
	//nation_name = gtk_entry_get_text(newnation_entry);

	/// Form the url
	char url_new[2048];
	const char* base = "http://www.nationstates.net/cgi-bin/api.cgi?nation=";
	const char* rest = "&q=censusscore-0+censusscore-1+censusscore-2+censusscore-3+censusscore-4+censusscore-5+censusscore-6+censusscore-7+censusscore-8+censusscore-9+censusscore-10+censusscore-11+censusscore-12+censusscore-13+censusscore-14+censusscore-15+censusscore-16+censusscore-17+censusscore-18+censusscore-19+censusscore-20+censusscore-21+censusscore-22+censusscore-23+censusscore-24+censusscore-25+censusscore-26+censusscore-27+censusscore-28+censusscore-29+censusscore-30+censusscore-31+censusscore-32+censusscore-33+censusscore-34+censusscore-35+censusscore-36+censusscore-37+censusscore-38+censusscore-39+censusscore-40+censusscore-41+censusscore-42+censusscore-43+censusscore-44+censusscore-45+censusscore-46+censusscore-47+censusscore-48+censusscore-49+censusscore-50+censusscore-51+censusscore-52+censusscore-53+censusscore-54+censusscore-55+censusscore-56+censusscore-57+censusscore-58+censusscore-59+censusscore-60+censusscore-61+censusscore-62+censusscore-63+censusscore-64+censusscore-65+censusscore-66+censusscore-67+censusscore-68+fullname+motto+category+freedom+region+tax+animal+animaltrait+currency+flag+crime+sensibilities+govt+govtdesc+industrydesc+notable+admirable+founded+lastactivity+influence+publicsector+deaths+legislation+happenings";
	strcat(url_new, base);
	strcat(url_new, nation_name);
	strcat(url_new, rest);
	/// Download the file
	get_file("./nation.xml", url_new);
	//save_census_median();

	///Signal Handlers
}

void toggle_infobox(GtkWidget *hide_info, gpointer infobox){
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(hide_info)))
		gtk_widget_hide(infobox);
	else
		gtk_widget_show(infobox);
}

void on_update(){

}

void on_help(){

}

void on_about(){
	///Declaring about stuff
	GtkWidget *about_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(about_window), "About");
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *label = gtk_label_new("Nationstates-linux is free software: you can redistribute it and/or modify\n"
						"it under the terms of the GNU General Public License as published by\n"
						"the Free Software Foundation, either version 3 of the License, or\n"
						"(at your option) any later version.\n"
						"\n"
						"Nationstates-linux is distributed in the hope that it will be useful,\n"
						"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
						"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
						"GNU General Public License for more details.\n");
	GtkWidget *close_button = gtk_button_new_with_label("close");

	///Object Placement in window
	gtk_container_add(GTK_CONTAINER(about_window), main_box);
	gtk_box_pack_start(GTK_BOX(main_box), label, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(main_box), close_button, FALSE, FALSE, 1);

	///Make window show
	gtk_widget_show_all(about_window);

	///Close Button
	g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(about_window_close), G_OBJECT (about_window));
}

void about_window_close(GtkWidget *widget, gpointer window){
	/// destroys the about window
	gtk_widget_destroy(GTK_WIDGET(window));
}

void refresh_nations(){
	FILE *fp = fopen("./name-store/nation_list.txt", "r");
	int count = count_lines(fp);
	char* nations[count];
	read_to_array(fp, &nations[0], count);
	fclose(fp);

	if(count>0){
		gtk_list_store_clear(nationstore);
		for(i=0; i<count; i++){
			gtk_list_store_append(nationstore, &nation_row);
			gtk_list_store_set(nationstore, &nation_row, 0, nations[i], -1);
		}
	}
}


void nation_selection_changed(){
	refresh_saves();
}

/// This should be called everytime a change happens to the nationview (new data was retrieved, a nation added, deleted, etc);
int refresh_saves(){
	char* selected_nat = get_selected_nation();
	char filepath[128];
	filepath[0] = '\0';
	const char* start = "./nations-store/";
	const char* end = "/datelog.txt";
	strcat(filepath, start);
	strcat(filepath, selected_nat);
	strcat(filepath, end);
	FILE *fp = fopen(filepath, "r");
	if(fp == NULL){
		printf("Could not find file: %s\n", filepath);
		return 1;
	}

	int count = count_lines(fp);
	char* saves[count];
	read_to_array(fp, &saves[0], count);
	fclose(fp);

	if(count>0){
		gtk_list_store_clear(savestore);
		for(i=0; i<count; i++){
			int end = strlen(saves[i]) - 1;
			if (saves[i][end] == '\n')
				saves[i][end] = '\0';
			gtk_list_store_append(savestore, &save_row);
			gtk_list_store_set(savestore, &save_row, 0, saves[i], -1);
		}
	}
	return 0;
}

/// When this is called, gets the currently selected nation in nationview and sets the global variable selected_nation to the name of the nation.
char* get_selected_nation(){
	GtkTreeIter iter;
	GtkTreeModel *model;
	char* selected_nation = NULL;
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(nationview));
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)){
		gtk_tree_model_get(model, &iter, 0, &selected_nation,  -1);
		int end = strlen(selected_nation) - 1;
		if (selected_nation[end] == '\n')
			selected_nation[end] = '\0';
		return selected_nation;
	}
	return "";
}

void get_nation_data(const char* nation){
	/// Get selected nation from treeview
	// const char* nation = get_selected_nation();
	/// Form the url
	char url[2048];
	const char* base = "http://www.nationstates.net/cgi-bin/api.cgi?nation=";
	const char* rest = "&q=censusscore-0+censusscore-1+censusscore-2+censusscore-3+censusscore-4+censusscore-5+censusscore-6+censusscore-7+censusscore-8+censusscore-9+censusscore-10+censusscore-11+censusscore-12+censusscore-13+censusscore-14+censusscore-15+censusscore-16+censusscore-17+censusscore-18+censusscore-19+censusscore-20+censusscore-21+censusscore-22+censusscore-23+censusscore-24+censusscore-25+censusscore-26+censusscore-27+censusscore-28+censusscore-29+censusscore-30+censusscore-31+censusscore-32+censusscore-33+censusscore-34+censusscore-35+censusscore-36+censusscore-37+censusscore-38+censusscore-39+censusscore-40+censusscore-41+censusscore-42+censusscore-43+censusscore-44+censusscore-45+censusscore-46+censusscore-47+censusscore-48+censusscore-49+censusscore-50+censusscore-51+censusscore-52+censusscore-53+censusscore-54+censusscore-55+censusscore-56+censusscore-57+censusscore-58+censusscore-59+censusscore-60+censusscore-61+censusscore-62+censusscore-63+censusscore-64+censusscore-65+censusscore-66+censusscore-67+censusscore-68+fullname+motto+category+freedom+region+tax+animal+animaltrait+currency+flag+crime+sensibilities+govt+govtdesc+industrydesc+notable+admirable+founded+lastactivity+influence+publicsector+deaths+legislation+happenings";
	strcat(url, base);
	strcat(url, nation);
	strcat(url, rest);
	/// Download the file
	get_file("./nation.xml", url);
	//save_census_median();
}

void get_file(char* file, char* url){
	CURL *curl = curl_easy_init();
	if (curl) {
		FILE *fp = fopen(file,"wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}

int main(int argc, char **argv){

	gtk_init (&argc, &argv);

	/// Create a reference for the window and put our window in it.
	GtkWidget *main_window = create_window();

	/// Show all the widgets that exist in the main_window
	gtk_widget_show_all (main_window);

	/// Load the saves
	refresh_nations();

	/// Start the wait for event loop
	gtk_main();
	return 0;
}
