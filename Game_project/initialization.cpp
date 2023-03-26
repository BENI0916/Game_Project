#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "dirent.h"
#include "var.cpp" 
extern int atk_cnt, player_walk_cnt; // player_walk_cnt : 走路計數器 用於計算走路時輸出的圖片
extern Human player;
void loadBG(char filename[]);
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h);

void initialization()
{
	char s[] = "images\\bg\\back_ground_01.png"; //C++無法將字串常數直接轉成char pointer，故有此行
	loadBG(s); //讀取背景
	
	sprintf(s,"%s","images\\main_char"); //C++無法將字串常數直接轉成char pointer，故有此行
	loadCHAR(s,&player.player_img,&player.player_msk,76,66); //讀取主角圖片

	// 設定初始值 
	player.x = wid / 2; // 暫定 
	player.y = hih / 2; // 暫定
	player.hp = 5;
	player.dir = 'd';
	player.output_idx = 0;
	
	player_walk_cnt = 11;
	atk_cnt = 0;
}