//Michael Lawrence

//these are useful general functions.

//this is the header for some helpful functions.

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX = 1000;

//builds a new array. max size 1000.
void char_new(char * & to_build);
//builds an array of given size.
void char_new(char * & to_build, int size);
//copies an array.
void copy_array(char * & to_build, const char * to_copy);

