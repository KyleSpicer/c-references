
#include "c-spice-lib.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // for usleep function in string_slow_print

    
// prints string one char at a time for aesthetic. 
void string_slow_print(char the_string[], double delay_time)
{
    int str_size = strlen(the_string);

    for (int i = 0; i < str_size; i++)
    {
        printf("%c", the_string[i]);
        fflush(stdout);
        usleep(delay_time);
    }
}

// removes newline char from string
char * string_remove_newline(char * string)
{

    char buffer[];
}


/*** end of file ***/
