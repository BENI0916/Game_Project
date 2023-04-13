#ifndef VAR_H
#define VAR_H

//此為常數儲存區
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>

const int hih = 720; //視窗長
const int wid = 1280; //視窗寬

// 玩家的結構 
typedef struct 
{
	int x;	// x 座標 
	int y;	// y 座標  
	int hp;	// 血量
	int damage; // 對敵人造成的傷害  
	int atked;// 判定是否有造成傷害 
	char dir;// 人物面朝的方向 
	int output_idx; // 用於儲存要輸出的圖片編號 
	PIMAGE *player_img, *player_msk;  //角色儲存圖片 
	int high;
	int width;
	int power;// 擊退敵人的距離 
	int atk_type; // 攻擊的型 
}Human;

typedef struct 
{
	int x;
	int y;
	int hp;
	int damage;
	char dir;
	int output_idx;
	PIMAGE *enemy_img, *enemy_msk;
	int high;
	int width;
	int power;
	int speed;
	int atk_0_cnt;
	int atk_1_cnt;
}Monster;

typedef struct 
{
	int cnt;
	int output_idx;
	PIMAGE *loading_img;
}Animate;


typedef struct 
{
	int x;
	int y;
	int output_idx;
	int status;
	PIMAGE *skill_img, *skill_msk;
	int high;
	int width;
	int power;
}Bullet;

#endif
