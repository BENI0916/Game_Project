//此為常數儲存區
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h> 

const int hih = 720; //視窗長
const int wid = 1280; //視窗寬

// 玩家的結構 
struct Human 
{
	int x;	// x 座標 
	int y;	// y 座標  
	int hp;	// 血量
	int damage;
	int atked;
	char dir;// 人物面朝的方向 
	int output_idx; // 用於儲存要輸出的圖片編號 
	PIMAGE *player_img, *player_msk;  //角色儲存圖片 
};

struct Monster
{
	int x;
	int y;
	int hp;
	int damage;
	char dir;
	int output_idx;
	PIMAGE *enemy_img, *enemy_msk;
};

struct Bullet
{
	int x;
	int y;
	int output_idx;
	int status;
	int space_cal[6];
	PIMAGE *skill_img, *skill_msk;
};
