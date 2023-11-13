#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>

#define CHUNK 1024 /* read/write 1024 bytes at a time */

void usage()
{
	printf("Incorrect Usage\n");
	printf("$ copy <original_file> <new_file>\n");
}

/* function go check whether a file exists. */
bool fileExists(const char *path)
{
    // Try to open file
    FILE *fptr = fopen(path, "r");

    // If file does not exists 
    if (fptr == NULL)
        return false;

    // File exists hence close file and return true.
    fclose(fptr);

    return true;
}

int main(int argc, char *argv[])
{
	// check args
	if(argc < 3){
		usage();
		exit(0);
	}
	// Make sure the file doesnt already exist first!
	if(!fileExists(argv[2]) && fileExists(argv[1])){
   		char buf[CHUNK];
		FILE *file;
		FILE *fcopy;
		size_t nread;

		// copy file in chunks
		file = fopen(argv[1], "r");
		fcopy = fopen(argv[2], "w");
		if (file) {
		    while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
		        fwrite(buf, 1, nread, fcopy);
		    if (ferror(file)) {
		        // deal with error 
		        printf("Error reading %s\n", argv[1]);
		    }
   			// close the file
		    fclose(file);
		    fclose(fcopy);
		}

	} else {
		printf("Cannot Copy File: %s\n", argv[1]);
		exit(0);
	}
}