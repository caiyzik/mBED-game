#include "ingamemenu.h"

#include "globals.h"
#include "hardware.h"

/**
 * Draw the menu background.
 */
static void draw_ingame_menu();

/**
 * Erase the menu.
 */
static void erase_ingame_menu();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_ingame_option(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void ingame_menu_wait();

void draw_ingame_menu()
{
    uLCD.filled_rectangle(0, 128, 128, 90, 0xFFFFFF); //(x1, y1, x2, y2) where (x1, y1) is bottom left corner and (x2, y2) is upper right corner
}

void erase_ingame_menu()
{
    uLCD.filled_rectangle(0, 128, 128, 90, 0x000000);
    //uLCD.filled_rectangle(0, 128, 128, 90, 0x000000);
}

void draw_ingame_option(const char* line, int which)
{
    if (which == 1){
     uLCD.locate(1,11); //TO DO: the line overlaps with second line if too long
    } else if (which == 2){
         uLCD.locate(1,12);
    } else{
        uLCD.locate(1,13);
    }
     // basic printf demo = 16 by 18 characters on screen
    uLCD.text_mode(TRANSPARENT);
    uLCD.color(BLACK);
    uLCD.printf(line);
}

void ingame_menu_wait()
{
    wait(2);
}

void ingame_menu()
{
    while 
    draw_ingame_menu();
    draw_ingame_option("Game Paused", 1);
    draw_ingame_option("View Status", 2);
    draw_ingame_option("Inventory", 3);
    ingame_menu_wait();
    erase_ingame_menu();
}

void long_speech(const char* lines[], int n)
{
}
