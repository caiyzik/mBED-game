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
void status();

//global variables
int view_status;
int inventory;
int view_status_color;
int inventory_color;
int current_item = 0;
Player p;

void status(int quest_complete){
    uLCD.filled_rectangle(0, 128, 128, 90, PINK1);
    uLCD.locate(1,10);
    uLCD.textbackground_color(YELLOW);
    uLCD.color(BLACK);
    
    if (quest_complete){
        uLCD.printf("Congradulations! You have completed your quest!");
    } else{
        uLCD.printf("Quest is not completed");
    }
    wait(2);
}



/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define MENU_BUTTON 4

int get_menu_action(GameInputs inputs)
{
    if (!inputs.b2){
        return MENU_BUTTON;
    }
    return NO_ACTION;
}


#define NO_RESULT 0
#define FULL_DRAW 2
int update_menu(int action)
{
    switch(action)
    {
        case MENU_BUTTON:
            if (current_item%2 == 0) {//Start game
                view_status = true;
                status(p.quest_complete);
            } else if (current_item%2 == 1){ //Quit (screen cut to black)
                inventory = true;
            } else { //screen go white
            
            }
            break;
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
       
    
    if (current_item%2 == 0){
        view_status_color = GREEN;
    } else if (current_item%2 == 1){
        inventory_color = GREEN;
    }
    
    
    uLCD.locate(1,11);
    uLCD.color(view_status_color);
    uLCD.printf("View Status");
    
    uLCD.locate(1,12);
    uLCD.color(inventory_color);
    uLCD.printf("Inventory");
    
    
    view_status_color = BLACK;
    inventory_color = BLACK;
    
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_start_menu()
{
    uLCD.locate(1,10);
    //draw pink rectangle on whole screen
    uLCD.filled_rectangle(0, 128, 128, 90, PINK1);
    // write title
    uLCD.textbackground_color(YELLOW);
    uLCD.color(BLACK);
    uLCD.printf("Game Paused");
    
    if (current_item%2 == 0){
        view_status = GREEN;
    } else if (current_item%2 == 1){
        inventory = GREEN;
    }
    
    uLCD.locate(1,11);
    uLCD.color(view_status_color);
    uLCD.printf("View Status");
    
    uLCD.locate(1,12);
    uLCD.color(inventory_color);
    uLCD.printf("Inventory");
    
    
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int ingamemenu(Player player)
{
    p = player;
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
