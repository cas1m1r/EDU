#include "source.h"
#include "keyboard.h"

void main(void){

    terminal_buffer = (unsigned short*)VGA_ADDRESS;
    vga_index = 0;

    clear_screen();
    print_string("Welcome to ByteClub", GREEN);
    vga_index = 80;
    print_char(' ', GREEN);
    vga_index = 160;

    while (1) {
        int state = keyboard_handler();
        if (state==1){
            clear_screen();
            vga_index = 80;
        }
    }

    return;
}






