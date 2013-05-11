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

void nation_selection_changed();
char* get_selected_nation();
int refresh_saves();
void on_new_nation();
void toggle_infobox(GtkWidget *hide_info, gpointer infobox);
void on_update();
void on_help();
void on_about();
void about_window_close(GtkWidget *widget, gpointer window);

void get_nation_data(const char* nation);
void get_file(char* file, char* url);

GtkListStore *nationstore;
GtkListStore *savestore;
GtkWidget *nationview;
GtkWidget *saveview;
GtkTreeIter nation_row, save_row;
GtkTreeSelection *selection;
GtkCellRenderer *renderer;

void on_new_nation();
GtkWidget *newnation_entry;
GtkWidget *newnation_button;
void on_newnation_button_clicked();
void newnation_close(GtkWidget *widget, gpointer window){


int i;
