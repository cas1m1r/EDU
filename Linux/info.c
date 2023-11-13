#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <stdio.h>

// struct sysinfo {
// 		long uptime;             /* Seconds since boot */
// 		unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
// 		unsigned long totalram;  /* Total usable main memory size */
// 		unsigned long freeram;   /* Available memory size */
// 	    unsigned long sharedram; /* Amount of shared memory  */
// 		unsigned long bufferram; /* Memory used by buffers */
// 		unsigned long totalswap; /* Total swap space size */
// 		unsigned long freeswap;  /* Swap space still available */
// 		unsigned short procs;    /* Number of current processes */
// 		char _f[22];             /* Pads structure to 64 bytes */
// };

void displayInfo(struct sysinfo s){
	const double megabyte = 1024 * 1024;
	const double gigabyte = megabyte * 1024;
	printf ("Total RAM: \t%5.1f GB\n", s.totalram / gigabyte);
	printf ("Free RAM: \t%5.1f MB\n", s.freeram / megabyte);
	printf("Free Swap: \t%5.1f MB\n", s.freeswap / megabyte);
	printf("Total Swap: \t%5.1f MB\n", s.totalswap / megabyte);
	printf ("Process Count: \t%d\n", s.procs);
}

void showUptime(struct sysinfo s){
	const long min = 60;
	const long hr = 3600;
	const long day = 3600* 24;

	printf ("Uptime:\t %ld days, %ld:%02ld:%02ld\n", 
    		 s.uptime / day, (s.uptime % day) / hr, 
 	        (s.uptime % hr) / min, s.uptime % min);
}

void main(int argc, char* argv[]){
	 /* Obtain system statistics. */
	 struct sysinfo si;
	 sysinfo (&si);
	 showUptime(si);
	 displayInfo(si);
}