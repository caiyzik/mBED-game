// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file
int get_menu_action (GameInputs inputs);
int update_menu (int action);
void draw_menu (int init);
void init_start_menu ();
int menu ();

int b2presses = 0;
int start;
int quit;
int start_color;
int quit_color;
int third_color;
int current_item = 0;

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */


/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define MENU_BUTTON 4
#define GO_LEFT 5
#define GO_RIGHT 6
#define GO_UP 7
#define GO_DOWN 8
int get_menu_action(GameInputs inputs)
{
    if(!inputs.b1){
        return BUTTON1;
    }
    if(!inputs.b2){
        return BUTTON2;
    }
    if (!inputs.b3){
        return BUTTON3;
    }
    if ((inputs.ay > 0.05 && inputs.ay < 0.5) && abs(inputs.ax) < .5){
        return GO_LEFT;    
    } else if ((inputs.ay < -0.05 && inputs.ay > -0.5) && abs(inputs.ax) < .5){
        return GO_RIGHT;
    }else if (inputs.ax > 0.05 && inputs.ax < 0.5){
        return GO_DOWN;
    }else if (inputs.ax < -0.05 && inputs.ax > -0.5){
        return GO_UP;
    }
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_menu(int action)
{
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action) //have a function called for each type of object. Pass a pointer to the object to the interact function
    {           
        case BUTTON1: 
            //if button 1 pressed move to next menu item
            current_item = current_item++;
            break;
        case BUTTON2: 
            //if button 2 pressed select menu item
            //b2presses++;
            if (current_item%3 == 0) {//Start game
                start = true;
            } else if (current_item%3 == 1){ //Quit (screen cut to black)
                quit = true;
            } else { //screen go white
            
            }
            break;
        case MENU_BUTTON:
        break;
        default:        break;
    }
    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_menu(int init)
{
       
    
    if (current_item%3 == 0){
        start_color = GREEN;
    } else if (current_item%3 == 1){
        quit_color = GREEN;
    } else{
        third_color = GREEN;
    }
    
    
    
    uLCD.locate(1,4);
    uLCD.color(start_color);
    uLCD.printf("Start");
    
    uLCD.locate(1,6);
    uLCD.color(quit_color);
    uLCD.printf("Quit");
    
    uLCD.locate(1,8);
    uLCD.color(third_color);
    uLCD.printf("Thrid Option");
    
    start_color = BLACK;
    quit_color = BLACK;
    third_color = BLACK;
    
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_start_menu()
{
    uLCD.locate(1,2);
    //draw pink rectangle on whole screen
    uLCD.filled_rectangle(0, 127, 127, 0, PINK1);
    // write title
    uLCD.textbackground_color(YELLOW);
    uLCD.color(BLACK);
    uLCD.printf("Issa Quest");
    
    if (current_item%3 == 0){
        start_color = GREEN;
    } else if (current_item%3 == 1){
        quit_color = GREEN;
    } else{
        third_color = GREEN;
    }
    
    uLCD.locate(1,4);
    uLCD.color(start_color);
    uLCD.printf("Start da game");
    
    uLCD.locate(1,6);
    uLCD.color(quit_color);
    uLCD.printf("Quit?");
    
    uLCD.locate(1,8);
    uLCD.color(third_color);
    uLCD.printf("Ayyyyee lmao");
    
    
    
    
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int menu()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    init_start_menu();

    // Initial drawing
    draw_menu(true);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actually do the game update:
        // 1. Read inputs  
            GameInputs in = read_inputs();
        // 2. Determine action (get_action) 
            int a = get_menu_action(in);       
        // 3. Update game (update_game)
            int u = update_menu(a);
        
        // 4. Draw frame (draw_game)
        draw_menu(u);
        
        //check for start
        if (start){
            return start;
        }
        
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 500) wait_ms(500 - dt);
    }
}
