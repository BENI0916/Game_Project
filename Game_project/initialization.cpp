#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#include "dirent.h" 
#include "var.cpp" 
extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked; // player_walk_cnt : 走路計數器 用於計算走路時輸出的圖片
extern double start;
extern Human player;
extern Monster enemy;
extern Bullet skill[2];

void loadBG(char filename[]);
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h);
void enemy_ini(void);
void skill_ini_00(void);
void skill_ini_01(void);

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
	player.hp = 10;
	player.damage = 25; // 對敵人造成的傷害 
	player.atked = 0;   // 判定是否有造成傷害 
	player.dir = 'd';   // 方向 
	player.output_idx = 0;// 輸出圖片編號 
	player.high = 66;   // 人物圖片的高 
	player.width = 76;  // 人物圖片的寬 
	player.power = 30;  // 擊退敵人的距離 
	
	player_walk_cnt = 11; // 走路計時器 
	
	enemy_ini(); // 初始化敵人 
	flag = 10;
	
	skill_ini_00(); // 初始化敵人的技能 
	skill_ini_01();
	
	start = fclock(); // 用於計時敵人的攻擊時間間隔 
	enemy_atk_type = -1; // 敵人使用的技能編號 
	player_jump_cnt = -1;// 人物跳躍計時器 
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
	enemy.damage = 0; // 敵人造成的傷害 
	enemy.output_idx = 1;
	enemy.high = 165;
	enemy.width = 165;
	enemy.power = 100; // 敵人擊退玩家的距離 
	enemy.speed = 5;    
	enemy.atk_0_cnt = 199; // 敵人的技能計數器 
	enemy.atk_1_cnt = 99;  
}

// 技能1 
void skill_ini_00()
{
	char s[100];
	
	skill[0].skill_img = NULL;
	skill[0].skill_msk = NULL;
	skill[0].status = 0;
	
	sprintf(s, "%s", "images\\enemy_0_0_skill");
	loadCHAR(s, &skill[0].skill_img, &skill[0].skill_msk, 250, 126);
	
	skill[0].output_idx = 0;
	skill[0].high = 126;
	skill[0].width = 250;
	skill[0].power = 200;
}

// 技能2 
void skill_ini_01()
{
	char s[100];
	
	skill[1].skill_img = NULL;
	skill[1].skill_msk = NULL;
	skill[1].status = 0;
	
	sprintf(s, "%s", "images\\enemy_0_1_skill");
	loadCHAR(s, &skill[1].skill_img, &skill[1].skill_msk, 608, 256);
	
	skill[1].output_idx = 0;
	skill[1].high = 256;
	skill[1].width = 608;
	skill[1].power = 200;
}
