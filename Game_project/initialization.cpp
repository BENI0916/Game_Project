#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "var.cpp" 
extern PIMAGE new_bg;
PIMAGE ori_bg;
// ori_bg : 原始背景	new_bg : 放大後的背景 
extern int atk_cnt, player_walk_cnt;
// player_walk_cnt : 走路計數器 用於計算走路時輸出的圖片

extern Human player;

PIMAGE player_ori_img[16], player_ori_msk[16];
// 原始圖片 

void loading(); // 載入圖片 

void initialization()
{
	ori_bg = newimage();
	
	for(int i = 0; i < 16; i++)
	{
		player_ori_img[i] = newimage(); // 創建圖片 
		player_ori_msk[i] = newimage();
		
		player.player_img[i] = newimage(76, 66); // 創建 76 * 66 大小的圖片 
		player.player_msk[i] = newimage(76, 66);
	}
	
	loading(); // 載入圖片
	// 設定初始值 
	player.x = wid / 2; // 暫定 
	player.y = hih / 2; // 暫定
	player.hp = 5;
	player.dir = 'd';
	player.output_idx = 0;
	
	player_walk_cnt = 11;
	atk_cnt = 0;
	
	// 縮放後的圖片儲存在其他位置後
	// 將原本的圖片刪除 
	delimage(ori_bg);
	
	for(int i = 0; i < 16; i++)
	{
		delimage(player_ori_img[i]);
		delimage(player_ori_msk[i]);
	}
}

void loading() // 載入圖片 
{
	getimage(ori_bg, "images\\back_ground_01.png");
	
	char img[100];
	char msk[100];
	
	for(int i = 0; i < 16; i++)
	{
		sprintf(img, "images\\main_char\\img_%d.png", i);
		sprintf(msk, "images\\main_char\\msk_%d.png", i);
		
		getimage(player_ori_img[i], img);
		getimage(player_ori_msk[i], msk);
	}
	
	// 將載入後的圖片進行縮放 
	putimage(new_bg, 0, 0, wid, hih, ori_bg, 0, 0, 1000, 740);
	
	for(int i = 0; i < 16; i++)
	{	
		putimage(player.player_msk[i], 0, 0, 76, 66, player_ori_msk[i], 0, 0, 38, 33);
		putimage(player.player_img[i], 0, 0, 76, 66, player_ori_img[i], 0, 0, 38, 33);
	}
	
}
