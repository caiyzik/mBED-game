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
    if (which == TOP){
     uLCD.locate(1,12); //TO DO: the line overlaps with second line if too long
    } else if (which == BOTTOM){
         uLCD.locate(1,13);
    } 
     // basic printf demo = 16 by 18 characters on screen
    uLCD.text_mode(TRANSPARENT);
    uLCD.color(BLACK);
    uLCD.printf(line);
}

void speech_bubble_wait()
{
    wait(2);
}

void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    speech_bubble_wait();
    erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{
}
