#include "keyboard.h"  
#include "source.h"
#include <unistd.h>
#include <sys/io.h>

int canSend;

unsigned char get_scancode(){
    return inb(0x60);
}



int keyboard_handler(){
    unsigned char scancode;
    
    // Get element in console buffer
    scancode = get_scancode();
    canSend = 0;
    int cleared = 0;
    char character;
    switch(scancode){
        case 0x0f:
            canSend = 0;
            cleared = 1;
            clear_screen();
            break;
        case 0x01:
            break;
        case 0x1E:
            character = 'a';
            canSend = 1;
            break;
        case 0x30:
            canSend = 1;
            character = 'b';
        case 0x2E:
            canSend = 1;
            character = 'c';
            break;
        case 0x20:
            canSend = 1;
            character = 'd';
            break;
        case 0x12:
            canSend = 1;
            character = 'e';
            break;
        case 0x21:
            canSend = 1;
            character = 'f';
            break;
        case 0x22:
            canSend = 1;
            character = 'g';
            break;
        case 0x17:
            canSend = 1;
            character = 'i';
            break;
        case 0x24:
            canSend = 1;
            character = 'j';
            break;
        case 0x25:
            canSend = 1;
            character = 'k';
            break;
        case 0x26:
            canSend = 1;
            character = 'l';
            break;
        case 0x32:
            canSend = 1;
            character = 'm';
            break;
        case 0x31:
            canSend = 1;
            character = 'n';
            break;
        case 0x18:
            canSend = 1;
            character = 'o';
            break;
        case 0x19:
            canSend = 1;
            character = 'p';
            break;
        case 0x10:
            canSend = 1;
            character = 'q';
            break;
        case 0x13:
            canSend = 1;
            character = 'r';
            break;
        case 0x1F:
            canSend = 1;
            character = 's';
            break;
        case 0x14:
            canSend = 1;
            character = 't';
            break;
        case 0x16:
            canSend = 1;
            character = 'u';
            break;
        case 0x2F:
            canSend = 1;
            character = 'v';
            break;
        case 0x11:
            canSend = 1;
            character = 'w';
            break;
        case 0x2D:
            canSend = 1;
            character = 'x';
            break;
        case 0x15:
            canSend = 1;
            character = 'y';
            break;
        case 0x2C:
            canSend = 1;
            character = 'z';
            break;
    }

    // check if theres a character to send
    if (canSend) {
        // vga_index += 1;
        print_char(character, 15); // Make terminal text white
    }
    // Return location for cursor
    return vga_index;

}

