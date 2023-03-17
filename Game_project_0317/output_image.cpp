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
	int std_x;
	int std_y;
	int atk_x;
	int atk_y;
	int hp;
	char dir;
	int output_idx;
	PIMAGE player_origin_img[12], player_origin_mask[12];
	PIMAGE player_new_img[12], player_new_mask[12];
}player;

void output_image()
{
	putimage(0, 0, new_bg);
	
	putimage(player.x, player.y, player.player_new_mask[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_new_img[player.output_idx], SRCINVERT);
}
