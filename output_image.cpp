#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "var.cpp"
extern PIMAGE new_bg;
extern Human player;

void output_image()
{
	// ��X�I�� 
	putimage(0, 0, new_bg);
	
	// ��X���a 
	putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
}
