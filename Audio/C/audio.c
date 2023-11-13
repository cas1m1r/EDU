#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wave.h"
#define TRUE 1 
#define FALSE 0

 // WAV Headers
unsigned char wavHead4[4];
unsigned char wavHead2[2];

void usage(char *argv[]){printf("Usage: %s [wav file]\n",argv[0]);}

/* Get File Pointer */
FILE * getFilePtr(char const *filename){ 
	FILE *ptr = fopen(filename, "rb");
	if (ptr == NULL){
		printf("Error opening file\n");
		exit(1);
	}
	return ptr;
}

/* Check WAV Header Size */
void readHeaderSize(FILE *file, struct HEADER *head){
	int read = 0;
	read = fread(head->riff, sizeof(head->riff), 1, file);
	read = fread(wavHead4, sizeof(wavHead4), 1, file);
	// convert to big endian 4byte integer
	head->overall_size = wavHead4[0] | 
						 (wavHead4[1] << 8) |
						 (wavHead4[2] << 16)|
						 (wavHead4[3] << 24);
	
	printf("[-] Song Size: bytes: %uKb\n", head->overall_size/1024);
}

/* Read Format data from WAV Header */
void readHeaderFormat(FILE *file, struct HEADER *head){
	fread(head->wave, sizeof(head->wave),1,file);
	fread(head->fmt_chunk_marker, sizeof(head->fmt_chunk_marker),1,file);
	fread(wavHead4, sizeof(wavHead4), 1, file);
	// printf("%u %u %u %u\n", wavHead4[0], wavHead4[1], wavHead4[2], wavHead4[3]);
	// convert little endian to big endian 4 byte integer
 	head->length_of_fmt = wavHead4[0] |
						  (wavHead4[1] << 8) |
					      (wavHead4[2] << 16) |
						  (wavHead4[3] << 24);
	
	fread(wavHead2, sizeof(wavHead2), 1, file);
	// printf("%u %u \n", wavHead2[0], wavHead2[1]);
	head->format_type = wavHead2[0] | (wavHead2[1] << 8);
	char format_name[10];
	// determine format type 
	if (head->format_type == 1){
		strcpy(format_name, "PCM");
	}
	else if (head->format_type == 6){
		strcpy(format_name, "A-law");
	}
	else if (head->format_type == 7){
		strcpy(format_name, "Mu-law");
	}else{
		printf("Unrecognized Format %u\n", head->format_type);
		exit(1);
	}
	printf("\n[+] Wave Track Header Info:\n");
	printf("[-] Length of Fornat Header: %d bytes\n", head->length_of_fmt);
	printf("[-] Wave Marker: %s\n", head->wave);
	printf("[-] Format Marker: %s\n", head->fmt_chunk_marker);
	printf("[-] Format type: %u %s \n", head->format_type, format_name);
}

/* Read WAV Sampling Data  */
void readSampleData(FILE *file, struct HEADER *header){
	fread(wavHead2, sizeof(wavHead2), 1, file);
	// determine number of channels 
	header->channels = wavHead2[0] | (wavHead2[1] << 8);
	fread(wavHead4, sizeof(wavHead4), 1, file);
	// get sample rate 
	header->sample_rate = (wavHead4[0]) | 
						  (wavHead4[1] << 8)| 
						  (wavHead4[2] <<16)| 
						  (wavHead4[3] <<24);
	// get bitrate
	fread(wavHead4, sizeof(wavHead4), 1, file);
	header->byterate = wavHead4[0] | 
					  (wavHead4[1] << 8) |
					  (wavHead4[2] <<16) |
					  (wavHead4[3] <<24);
	// check header block alignment 
	fread(wavHead2, sizeof(wavHead2), 1, file);
	header->block_align = wavHead2[0] |
						  (wavHead2[1] << 8);
	// check bits per sample
	fread(wavHead2, sizeof(wavHead2), 1, file);
	header->bits_per_sample =  wavHead2[0] |
						      (wavHead2[1] << 8);
	// check start of data header
	fread(header->data_chunk_header, sizeof(header->data_chunk_header), 1, file);
	printf("\n[+] Audio Track Technical Info: \n");
	printf("[-] Audio uses %d channels\n", header->channels);
	printf("[-] Sample Rate: %uHz\n", header->sample_rate);
	printf("[-] BitRate: %uKb\n", (header->byterate*8)/1024);
	printf("[-] %u Bits per sample\n", header->bits_per_sample);
	
}


int main(int argc, char const *argv[]){
	/* check args */
	if (argc < 1){
		usage(argv);
		return 1;
	}

	// Load in WAV File 
	FILE *fp = getFilePtr(argv[1]);
	printf("[+] Opening %s\n", argv[1]);	

	struct HEADER header;
	// Populate wave header structure
	readHeaderSize(fp, &header);
	readHeaderFormat(fp, &header);
	readSampleData(fp, &header);

	return 0;
}