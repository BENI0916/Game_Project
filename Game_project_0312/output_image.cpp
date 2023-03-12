#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#define hih 480
#define wid 640
extern PIMAGE ori_bg, new_bg;
extern struct human
{
	int x;
	int y;
	int hp;
	char dir;
	int output_idx;
	PIMAGE player_origin_img[6], player_origin_mask[6];
	PIMAGE player_new_img[6], player_new_mask[6];
}player;

void output_image()
{
	putimage(0, 0, new_bg);
	
	putimage(player.x, player.y, player.player_new_mask[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_new_img[player.output_idx], SRCINVERT);
}
