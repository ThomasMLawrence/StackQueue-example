//Michael Lawrence

//useful general functions.

//useful peripheral functions
#include "help.h"

void char_new(char * & to_build)
{
	//allocates and reads an array of 1000
	char temp[MAX];
	cin.get(temp, MAX, '\n'); cin.clear(); cin.ignore(MAX, '\n');
	to_build = new char[strlen(temp) + 1];
	strcpy(to_build, temp);
}

void char_new(char *& to_build, int size)
{
	//allocates and reads an array of given size
	char temp[size];
	cin.get(temp, size, '\n'); cin.clear(); cin.ignore(MAX, '\n');
	to_build = new char[strlen(temp) + 1];
	strcpy(to_build, temp);
}

void copy_array(char * & to_build, const char * to_copy)
{
	//copies array.
	if(to_copy)
	{
		to_build = new char[strlen(to_copy) + 1];
		strcpy(to_build, to_copy);
	}

}
