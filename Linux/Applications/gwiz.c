/**
 * GTK WIZ  
 * Can I hook functions essential to gnome applications and actually affect the way they run?
 * Maybe inserting or deleting words in gedit lol. 
 **/ 
#define _GNU_SOURCE 
#include <sys/socket.h>
#include <termios.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>

////// Declare hooks 
int (*strcmp_actual)(char*,char*);

long unsigned int(*strlen_actual)(char*);

char* (* strcpy_actual)(char *dest, const char *src);


/////////////////////////////-----{ H O O K S }-----/////////////////////////////

/* Hooks STRLEN  */
long unsigned int strlen(char *str){
    strlen_actual = dlsym(RTLD_NEXT, "strlen");
    // Change the Name of the window
    if (strcmp(str, "Untitled Document 1")==0)
        sprintf(str,"T Y L 3 R D U R D 3 N");
    
    // Prevent people from typing phrase
    if(strstr(str, "fightclub") != NULL)
        sprintf(str,"         ");
    if(strstr(str, "FightClub") != NULL)
        sprintf(str,"         ");
    if( strstr(str, "Fight Club") != NULL)
        sprintf(str,"          ");
    if( strstr(str, "fight club") != NULL)
        sprintf(str,"          ");
    
    // prevent light mode in gedit lol
    if(strcmp(str,"kate.xml") == 0)
        sprintf(str,"tango.xml");
    if( strstr(str, "light.xml") != NULL)
        sprintf(str,"cobalt.xml");

    // For Messing with gnome-calculator
    if(strcmp(str,"1+1")==0)
        sprintf(str,"42");    
    return strlen_actual(str);
}


/* gcc -Wall -fPIC -shared -ldl -Wl,--no-as-needed gwiz.c -o gwiz.so */
/* run using: LD_PRELOAD=gwiz.so gedit */
