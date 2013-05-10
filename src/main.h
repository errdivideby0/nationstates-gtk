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
void get_selected_nation();
void refresh_saves();
void on_new_nation();
void on_update();
void on_help();
void on_about();

GtkListStore *nationstore;
GtkListStore *savestore;
GtkWidget *nationview;
GtkWidget *saveview;
GtkTreeIter nation_row;
GtkTreeSelection *selection;
GtkCellRenderer *renderer;

int i;
char* selected_nation;
