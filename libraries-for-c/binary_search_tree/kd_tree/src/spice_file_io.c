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

	else if (0 < size) {
		return 1;
	}
	return 0;
}

FILE *file_open_and_verify(char *file_name)
{
	// ABCs 
	if (!file_name) {
		return NULL;
	}

	FILE *file = fopen(file_name, "r");
	if (!file) {
		printf("Unable to open %s\n", file_name);
		return NULL;
	}

	int file_size = file_verify_not_empty(file);

	if (0 == file_size) {
		return NULL;
	} else {
		return file;
	}
}

void display_usage_statement(void)
{
	const char *message = "\n---------- Program Help Menu ----------\n"
	    "\nUsage: ./exe [-f] <file> [-arg...] <argument(s)>\n"
	    "\nMandatory Arguments:\n"
	    "\t-f | --file     : input file to use with program.\n"
	    "\t-x | --lat 	: provide x coordinate for use in program.\n"
	    "\t-y | --lon 	: provide y coordinate for use in program.\n"
	    "\t-d | --distance : provide radius to conduct search.\n"
	    "\nOptional Arguments: \n"
	    "\t-k | --nodes   : returns number of closest nodes to coordinates provided.\n"
	    "\t-h | --help	: displays all options and usage of program.\n"
	    "\nExample Usage:\n"
	    "\tShort Options: \n"
	    "\t\t./myprog -f file.txt -x 2.5 -y 3.0 -d 10\n"
	    "\t\t./myprog -f file.txt -x 2.5 -y 3.0 -d 10 -n 3\n"
	    "\n\tLong Options :\n"
	    "\t\t./myprog --file file.txt --lat 2.5 --lon 3.0 --distance 10\n"
	    "\t\t./myprog --file file.txt --lat 2.5 --lon 3.0 --distance 10 --number 3\n\n"
	    "------------ End Help Menu ------------\n\n";

	printf("%s", message);
}

/* end of file */
