#include "graphics.h"

#include "globals.h"

#define DARKGREEN 0x154f08



char heart[122] = "BPPPVBBPPPV"
                  "PPPPPVPPPPP"
                  "PPPPPPPPPPP"
                  "PPPPPPPPPPP"
                  "PPPPPPPPPPP"
                  "PPPPPPPPPPP"
                  "PPPPPPPPPPP"
                  "PPPPPPPPPPP"
                  "BPPPPPPPPPV"
                  "BBBBBBBBBBB"
                  "BBBBBBBBBBB";
                  
char matt[122] = "BBB11111BBB"
                  "BBB1B1B1BBB"
                  "BBB11111BBB"
                  "BBWWWWWWWBB"
                  "BBW44W44WBB"
                  "BBW55W55WBB"
                  "BBW66W66WBB"
                  "BBW33W33WBB"
                  "BBB22222BBB"
                  "BBB22B22BBB"
                  "BBB22B22BBB";
                  
char shrub[122] = "BBBBBBBBBBB"
                  "BBBBBBBBBBB"
                  "BBBBBBBBBBB"
                  "BBBBBBBBBBB"
                  "BBBBBBBBBBB"
                  "BBBBBBBBBBB"
                  "BBBBBBBBBBB"
                  "BBGGBGBBGGG"
                  "GGGGGGGBGGB"
                  "BGGGGGGGGGB"
                  "BBGGGGGGGBB";

void draw_player(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    draw_img(u, v, matt);
}


void draw_npc(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+11, v+11, YELLOW);
}


#define BROWN  0xD2691E
#define DIRT   BROWN
#define CREAM 0xecd5c3   //1
#define M_BROWN 0x5a300f //2
#define M_BLUE 0x0834db  //3
#define M_RED 0xd92626   //4
#define M_YELLOW 0xfff700  //5
#define M_GREEN 0x2ddd03 //6
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'P') colors[i] = PINK1;
        else if (img[i] == 'V') colors[i] = LIGHTPINK;
        else if (img[i] == '1') colors[i] = CREAM;
        else if (img[i] == '2') colors[i] = M_BROWN;
        else if (img[i] == '3') colors[i] = M_BLUE;
        else if (img[i] == '4') colors[i] = M_RED;
        else if (img[i] == '5') colors[i] = M_YELLOW;
        else if (img[i] == '6') colors[i] = M_GREEN;
        else if (img[i] == 'W') colors[i] = 0xFFFFFF;
        else colors[i] = DARKGREEN;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}



void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, DARKGREEN);
}

void draw_house_floor(int u, int v)
{
    // Fill a tile with brown (wood)
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLUE);
}

#define GRAY2 0x9096B0
void draw_road(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GRAY2);
}

void draw_door(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+5, v+5, RED);
}

void draw_plant(int u, int v)
{
    draw_img(u, v, shrub);
}

void draw_spike(int u, int v)
{
    uLCD.triangle(u, v, u+10, v+10, u, v+10, PINK1);
}

#define GRAY 0x9096A0
void draw_rock(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GRAY);
}

void draw_goal(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_upper_status(int health)
{
    // Draw bottom border of status bar
    if (health == 0){
        uLCD.filled_rectangle(health, 9, 127, 0, GREEN);
    } else{
        uLCD.filled_rectangle(0, 9, health+10, 0, RED);
    }
    //draw_img(0, 0, heart);
    
    // Add other status info drawing code here
    
    
}

void draw_lower_status(int x, int y)
{
    //uLCD.filled_rectangle(0, 128, 128, 110, 0x000000);
    // Draw top border of status bar
    //uLCD.line(0, 118, 127, 118, GREEN);
    
    // Add other status info drawing code here
    char str[30];
    sprintf(str, "Coord: (%d, %d)", x, y);
    uLCD.text_mode(OPAQUE);
    uLCD.textbackground_color(BLACK);
    uLCD.text_string(str, 0, 15,  FONT_7X8, 0xFFFFFF);
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

void draw_game_over(){
    uLCD.filled_rectangle(0,  128, 128, 0, WHITE);
    uLCD.locate(1,5);
    uLCD.text_mode(TRANSPARENT);
    uLCD.color(BLACK);
    uLCD.printf("GAME OVER!");
}

