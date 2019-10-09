#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */


/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map maps[2];
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    Map * m = get_active_map();
    return (m->w)*Y + X;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // TODO: Fix me!
    return key%5;
}

void maps_init(int h, int w, int buckets)
{
    Map * m = get_active_map();
    m->items = createHashTable(map_hash, buckets);
    m->w = w;
    m->h = h;
}

Map* get_active_map()
{
    
    return &(maps[active_map]);
}

Map* set_active_map(int m)
{
    active_map = m;
    return &(maps[active_map]);
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    Map * m = get_active_map();
    return m->w;
}

int map_height()
{
    Map * m = get_active_map();
    return m->h;
}

int map_area()
{
    Map * m = get_active_map();
    return (m->h)*(m->w);
}

MapItem* get_north(int x, int y)
{
    Map* map = get_active_map();
    //get key of item north of the location
    int index = XY_KEY(x, y-1);
    return (MapItem*)getItem(map->items, index);
}

MapItem* get_south(int x, int y)
{
    Map* map = get_active_map();
    int index = XY_KEY(x, y+1);
    return (MapItem*)getItem(map->items, index);
}

MapItem* get_east(int x, int y)
{
    Map* map = get_active_map();
    int index = XY_KEY(x-1, y); //wtf why does this work boi 
    return (MapItem*)getItem(map->items, index);
}

MapItem* get_west(int x, int y)
{
    Map* map = get_active_map();
    int index = XY_KEY(x+1, y); //shouldn't this be minus?
    return (MapItem*)getItem(map->items, index);
}

MapItem* get_here(int x, int y)
{
    Map* map = get_active_map();
    int index = XY_KEY(x, y);
    return (MapItem*)getItem(map->items, index);
}


void map_erase(int x, int y)
{
    Map* map = get_active_map();
    int index = XY_KEY(x, y);
    deleteItem(map->items, index);
}

void omni(){
    Map* map = get_active_map();
    int h = map -> h;
    int w = map -> w;
    for (int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            MapItem* object = (MapItem*)getItem(map->items, XY_KEY(i,j));
            if(object) object -> walkable = true; 
        }
    }
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_rock(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = ROCK;
    w1->draw = draw_rock;
    w1->walkable = false;
    Rock* r = (Rock*) malloc(sizeof(Rock));
    //r -> is_pushed = false;
    //r -> wall_touch = false;
    //r -> x = x;
    //r -> y = y;
    w1->data = r;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_npc(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NPC;
    w1->draw = draw_npc;
    w1->walkable = false;
    NonPlayer* npc = (NonPlayer*) malloc(sizeof(NonPlayer));
    npc->quest_requested = false;
    npc->quest_complete = false;
    npc->has_key = true;
    w1->data = npc;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_door(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = DOOR;
    w1->draw = draw_door;
    w1->walkable = false;
    int o = false;
    w1->data = &o;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_goal(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GOAL;
    w1->draw = draw_goal;
    w1->walkable = false;
    int o = false;
    w1->data = &o;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_spike(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SPIKE;
    w1->draw = draw_spike;
    w1->walkable = false;
    int o = false;
    w1->data = &o;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}


void add_cars(int x, int y, int num_cars, int x1, int y1, int x2, int y2){

typedef struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
} CarKey;

    //should cars be map items?? would make it easier to make them move...
    //CarKey car_keys[num_cars];
    // cars on road one
    for (i = 0; i < num_cars/3; i++){
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1 -> type = CAR;
        w1 -> draw = draw_car;
        w1 -> walkable = false;

        Carkey* key = (CarKey*)malloc(sizeof(CarKey));
        key -> dir = right1 //right1 means going right on road one
        key -> x = x + ... //add
        key -> y = y + ... // 


        w1 -> data = key;
        add_car(x, y); //create this function in map.cpp
    }

    // cars on road two
    for (i = 0; i < num_cars/3 i++){
        //get the 
        add_car(x, y);
    }

    // cars on road three
    for (i = 0; i < num_cars/3; i++){
        //get the 
        add_car(x, y);
    }
       
}
}