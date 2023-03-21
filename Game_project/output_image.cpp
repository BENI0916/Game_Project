#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#define hih 720 
#define wid 1280 
extern PIMAGE new_bg;
extern struct human // 玩家的結構  
{
	int x;	// x 座標 
	int y;	// y 座標 
	int hp;	// 血量 
	char dir;// 人物面朝的方向 
	int output_idx; // 用於儲存要輸出的圖片編號 
	PIMAGE player_img[16], player_msk[16]; // 儲存放大後的圖片 
}player;

void output_image()
{
	// 輸出背景 
	putimage(0, 0, new_bg);
	
	// 輸出玩家 
	putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
}
