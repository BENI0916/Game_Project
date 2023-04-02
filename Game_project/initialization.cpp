#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h>
#include "dirent.h" 
#include "var.cpp" 
extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked; // player_walk_cnt : 走路計數器 用於計算走路時輸出的圖片
extern double start;
extern Human player;
extern Monster enemy;
extern Bullet skill;

void loadBG(char filename[]);
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h);
void enemy_ini(void);
void skill_ini(void);

void initialization()
{
	char s[] = "images\\bg\\back_ground_01.png"; //C++無法將字串常數直接轉成char pointer，故有此行
	loadBG(s); //讀取背景
	
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++無法將字串常數直接轉成char pointer，故有此行
	loadCHAR(s,&player.player_img,&player.player_msk,76,66); //讀取主角圖片

	// 設定初始值 
	player.x = wid / 4; // 暫定 
	player.y = hih * 0.6; // 暫定
	player.hp = 100;
	player.damage = 25;
	player.atked = 0;
	player.dir = 'd';
	player.output_idx = 0;
	
	player_walk_cnt = 11;
	
	enemy_ini();
	flag = 10;
	
	skill_ini();
	
	start = fclock();
	enemy_atk_type = -1;
	player_jump_cnt = -1;
}

void enemy_ini()
{
	char s[100];
	
	enemy.enemy_img = NULL;
	enemy.enemy_msk = NULL;
	
	sprintf(s,"%s","images\\enemy_0");
	loadCHAR(s, &enemy.enemy_img, &enemy.enemy_msk, 165, 165);
	
	enemy.x = 900;
	enemy.y = hih * 0.6 - 165 + 66;
	enemy.dir = 'a';
	enemy.hp = 100;
	enemy.damage = 0;
	enemy.output_idx = 1;
}

void skill_ini()
{
	char s[100];
	
	skill.skill_img = NULL;
	skill.skill_msk = NULL;
	skill.status = 0;
	
	skill.space_cal[0] = 10; // a_left
	skill.space_cal[1] = 240;  // a_right
	skill.space_cal[2] = -240;   // d_left
	skill.space_cal[3] = -10;  // d_right
	skill.space_cal[4] = 10;   // up
	skill.space_cal[5] = 116;  // down
	
	sprintf(s, "%s", "images\\enemy_0_skill");
	loadCHAR(s, &skill.skill_img, &skill.skill_msk, 250, 126);
	
	skill.output_idx = 0;
}
