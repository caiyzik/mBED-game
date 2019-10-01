// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include "startmenu.h"

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map();
void init_house_map();
int main ();

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    int quest_complete;
} Player;

int house_enabled = false;
int door_open = false;
int game_over = false;
int health = 0;

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
int get_action(GameInputs inputs)
{
    if(!inputs.b1){
        return BUTTON1;
    }
    if(!inputs.b2){
        return BUTTON2;
    }
    if (!inputs.b3){
        return MENU_BUTTON;
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
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action) //have a function called for each type of object. Pass a pointer to the object to the interact function
    {
        case GO_UP: 
            if (MapItem* object = get_north(Player.x, Player.y)){
                if (object -> type == NPC){
                     NonPlayer* n = (NonPlayer*)object -> data;
                    if(n -> quest_requested == false){
                        speech("Get dat money", "its dat way");
                        n -> quest_requested = true;
                    } else if (Player.quest_complete == false){ //should quest complete be in the player struct?
                        speech("What are u waitin for?", "get it boi");
                    } else if (n -> has_key == true) {
                        speech("Congrats!", "Here's the keyyyy");
                        n -> has_key = false;
                        Player.has_key = true;
                    } else if(n -> has_key == false){
                        speech("Congrats!", "Quest complete.");
                    }
               // else if (object -> type == DOOR){
                 //   bool o = object -> data;
                   // if (Player.has_key == true){
                     //   o = true;
                   // }
                //}
            
                    return NO_RESULT;
                }
                else if (object -> walkable == false){
                    return NO_RESULT;
                }
            }
            Player.y = Player.y - 1;
            return FULL_DRAW;
        case GO_LEFT:   
            if (MapItem* object = get_west(Player.x, Player.y)){
                if (object -> type == ROCK){
                    add_rock(Player.x + 2, Player.y);
                    map_erase(Player.x+1, Player.y);
                    Player.x = Player.x + 1;
                    Player.quest_complete = true;
                    return FULL_DRAW;
                    
                } else if(object -> type == SPIKE){
                    //lower health bar
                    health++;
                    return NO_RESULT;
                    
                }
                if (object -> walkable == false){
                     return NO_RESULT;
                }
            }
            Player.x = Player.x + 1;
            return FULL_DRAW; 
        case GO_DOWN:   
            if (MapItem* object = get_south(Player.x, Player.y)){
                if (object -> type == DOOR){
                    if (Player.has_key == true){
                        map_erase(Player.x, Player.y + 1);
                        Player.y = Player.y + 1;
                        door_open = true;
                        return FULL_DRAW;
                    }
                    return NO_RESULT;
                }
                if (object -> walkable == false){
                    return NO_RESULT;
                }    
            }
            Player.y = Player.y + 1;
            return FULL_DRAW;
            
        case GO_RIGHT:  
            if (MapItem* object = get_east(Player.x, Player.y)){
                if (object -> type == GOAL){
                    if(door_open == true){
                        game_over = true;
                        return NO_RESULT;
                    }
                    
                } else if(object -> type == DOOR){
                    init_house_map();  //add a bit of a wait here to simulate going into the house
                    }
                if (object -> walkable == false){
                    return NO_RESULT;
                }
            }
            Player.x = Player.x - 1;
            return FULL_DRAW;
           
        case BUTTON1: 
            omni();
            break;
        case BUTTON2: 
            break;
        case MENU_BUTTON:
            int result = ingamemenu();
            
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
void draw_game(int init)
{
   // int param1;
    //int param2; 
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init (this is when the loop hits the center of the screen)
            {
                draw_player(u, v, Player.has_key);
            
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        //if (curr_item -> type == ROCK){
                            //set parameters
                          //  Rock* r = (Rock*) curr_item -> data;
                            //param1 = r -> x;
                            //param2 = r -> y;
                            //}
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        if (house_enabled){
                            draw = draw_house_floor;
                        }
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            //MapItem* curr_item = get_here(x, y);
            //MapItem* prev_item = get_here(px, py);
            if (draw){
               // if(curr_item){
                 //   if(curr_item -> type == ROCK){
                   // draw(param1, param2);
                    //}
                //}
                draw(u,v);
            }
        }
    }

    // Draw status bars    
    draw_upper_status(health);
    draw_lower_status(Player.x, Player.y);
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    
    maps_init(50, 50, 5);
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }
    
    srand(time(NULL));
    for(int i = 0; i < 30; i++)
    {
        int x = rand()%((map_width()+1)-1) + 1;
        int y = rand()%((map_height()+1)-1) + 1;
        add_spike(x, y);
    }
    
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    add_wall(20, 20, HORIZONTAL, 15);
    add_npc(13, 13);
    add_rock(6, 42);
    add_door(7, 48);
    add_goal(43, 5);
    pc.printf("Walls done!\r\n");

    print_map();
}

void init_house_map()
{
    
    Map* map = set_active_map(1); //one is a house map
    maps_init(20, 20, 5);
    Player.x = Player.y = 5;
    
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
 
    add_npc(5, 15); //place NPC in the house
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    Map* map = set_active_map(0);
    int start = menu();
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    
    init_main_map();
    
    
    // Initialize game state
    //set_active_map(0); //this doesn't need to be here twice
    Player.x = Player.y = 5;
    Player.quest_complete = false;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actually do the game update:
        // 1. Read inputs  
            GameInputs in = read_inputs();
        // 2. Determine action (get_action) 
            int a = get_action(in);       
        // 3. Update game (update_game)
            int u = update_game(a);
        // 3b. Check for game over
        if (game_over == true){
            draw_game_over();
        }//else if(house_enabled == true){
            
            //Player.x = Player.y = 5; //idk if this should be here...
        //}
        // 4. Draw frame (draw_game)
        draw_game(u);
        
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}
