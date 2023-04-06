#include "dirent.h"
#include "lib/var.h"
#include "lib/initialization.h"
#include "lib/output_image.h"
#include "lib/enemy_atk.h"

extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked; // player_walk_cnt : 走路計數器 用於計算走路時輸出的圖片
extern double start;
extern Human player;
extern Monster enemy;
extern Bullet skill[2];
extern animate loading_animate;

void enemy_ini();
void skill_ini_00();
void skill_ini_01();
void loading_img_ini();

void initialization()
{
	char s[] = "images\\bg\\back_ground_01.png"; //C++無法將字串常數直接轉成char pointer，故有此行
	loadBG(s); //讀取背景
	
	printf("load background succes\n");
	
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++無法將字串常數直接轉成char pointer，故有此行
	loadCHAR(s,&player.player_img,&player.player_msk,76,66); //讀取主角圖片
	
	printf("load player image succes\n");
	
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
	player.atk_type = 0;
	
	player_walk_cnt = 11; // 走路計時器 
	
	printf("player setting succes\n");
	
	enemy_ini(); // 初始化敵人 
	
	printf("enemy ini succes\n");
	flag = 10;
	
	skill_ini_01();
	printf("skill_ini_01 succes\n");
	
	skill_ini_00(); // 初始化敵人的技能 
	printf("skill_ini_00 succes\n");
	
	start = fclock(); // 用於計時敵人的攻擊時間間隔 
	enemy_atk_type = -1; // 敵人使用的技能編號 
	player_jump_cnt = -1;// 人物跳躍計時器
	
	loading_img_ini();
	printf("loading_img_ini succes\n");
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
	enemy.use_skill = (atk_func *) malloc(sizeof(atk_func));
	enemy.use_skill[0] = enemy_first_atk;
	enemy.use_skill[1] = enemy_second_atk;
}

// 技能1 
void skill_ini_00()
{
	char s[100];
	
	skill[0].x = 0;
	skill[0].y = 0;
	skill[0].output_idx = 0;
	skill[0].status = 0;
	skill[0].skill_img = NULL;
	skill[0].skill_msk = NULL;
	
	sprintf(s, "%s", "images\\enemy_0_0_skill");
	loadCHAR(s, &skill[0].skill_img, &skill[0].skill_msk, 250, 126);
	
	skill[0].high = 126;
	skill[0].width = 250;
	skill[0].power = 200;
}

// 技能2 
void skill_ini_01()
{
	char s[100];
	
	skill[1].x = 0;
	skill[1].y = 0;
	skill[1].status = 0;
	skill[1].output_idx = 0;
	skill[1].skill_img = NULL;
	skill[1].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_0_1_skill");
	loadCHAR(s, &skill[1].skill_img, &skill[1].skill_msk, 608, 256);
	
	skill[1].high = 256;
	skill[1].width = 608;
	skill[1].power = 200;
}

void loading_img_ini()
{
	char s[100];
	
	loading_animate.loading_img = (PIMAGE *)malloc(sizeof(PIMAGE) * 8);
	
	for(int i = 0; i < 8; i++)
	{
		loading_animate.loading_img[i] = newimage();
		sprintf(s, "images\\loading\\0%d_loading_img.png", i);
		getimage(loading_animate.loading_img[i], s);
	}
	
	loading_animate.cnt = 0;
	loading_animate.output_idx = 0;
}
