#include "spice_file_io.h"
#include <stdio.h>
#include <stdlib.h>

static int file_verify_not_empty(FILE * fp)
{
    fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	
    // file is empty
    if (0 == size) {
        return 0;
    }

    else if(0 < size) {
        return 1;
    }
    return 0;
}

FILE * file_open_and_verify(char * file_name) {
    // ABCs 
    if (!file_name) {
        return NULL;
    }

    FILE *  file = fopen(file_name, "r");
    if(!file) {
        printf("Unable to open %s\n", file_name);
        return NULL;
    }

    int file_size = file_verify_not_empty(file);
    
    if (0 == file_size) {
        return NULL;
    }
    else {
        return file;
    }
}

/* end of file */