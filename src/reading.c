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

#include "reading.h"

char* dupe_str(const char* s){
    char* p = malloc(strlen(s)+1);
    if (p) strcpy(p, s);
    return p;
}

int count_lines(FILE *fp){
	int c, count = 0;
	/// Make c equal to the next character in the FILE and while it is not the End Of File
	while((c = getc(fp)) != EOF){
		/// If the character is a new line, add one to the count
		if(c == '\n')
			count++;
	}
	/// Rewind the FILE to the begining and return the number of lines.
	rewind(fp);
	return count;
}

void read_to_array(FILE *fp, char* (*arr), int count){
	int i;
	/// Get the first line from the FILE, write it to the char* buffer and make equal the array at i
	char buffer[1025];
	for(i=0; i<count; i++){
		fgets(buffer, 1024, fp);
		arr[i] = dupe_str(buffer);
	}
}


/// Open the file with a char*, and read mode
/*
FILE *fp = fopen(argv[1], "r");
if(fp == NULL){
	printf("Could not read file.\n");
	return 1;
}
*/

/// Count the number of lines and make a array of that size, then pass that into the read function
/*
int count = count_lines(fp);
char* arr[count];
read_to_array(fp, &arr[0], count);
	fclose(fp);
*/

/// Access the array values like usual
/*
int i;
for(i=0; i<count; i++)
	printf("%s", arr[i]);
*/
