#include "lib/player_move3D.h"
#include "lib/var.h"

extern int player_walk_cnt3D,bgX,bgY;
extern Human player;
int speed = 2;
int fps = 5;
int table[] = {0,-1,0,1};

void keyListener() {
    if(GetAsyncKeyState(0x41) || GetAsyncKeyState('a'))  {
        player.output_idx = 29 + table[player_walk_cnt3D++/fps];
		bgX += speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    if(GetAsyncKeyState(0x44) || GetAsyncKeyState('d'))  {
        player.output_idx = 35 + table[player_walk_cnt3D++/fps];
		bgX -= speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    if(GetAsyncKeyState(0x53) || GetAsyncKeyState('s'))  {
        player.output_idx = 32 + table[player_walk_cnt3D++/fps];
		bgY -= speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    if(GetAsyncKeyState(0x57) || GetAsyncKeyState('w'))  {
        player.output_idx = 26 + table[player_walk_cnt3D++/fps];
		bgY += speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
}