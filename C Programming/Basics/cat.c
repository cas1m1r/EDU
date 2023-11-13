#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>

#define CHUNK 1024 /* read 1024 bytes at a time */

void usage()
{
	printf("Incorrect Usage\n");
	printf("$ cat <arg>\n");
}

/*function to get size of the file.*/
long int findSize(const char *file_name)
{
    struct stat st; /*declare stat variable*/
     
    /*get the size using stat()*/
    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
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
	if(argc < 2){
		usage();
		exit(0);
	}
	// Make sure the file exists first!
	if(fileExists(argv[1])){

   		char buf[CHUNK];
		FILE *file;
		size_t nread;

		// Read through file in chunks
		file = fopen(argv[1], "r");
		if (file) {
		    while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
		        fwrite(buf, 1, nread, stdout);
		    if (ferror(file)) {
		        // deal with error 
		        printf("Error reading %s\n", argv[1]);
		    }
   			// close the file
		    fclose(file);
		}

	} else {
		printf("Cannot find Symbol: %s\n", argv[1]);
		exit(0);
	}
}