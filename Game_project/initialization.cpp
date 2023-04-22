#include "dirent.h"
#include "lib/var.h"
#include "lib/initialization.h"
#include "lib/output_img.h"
#include "lib/enemy_atk.h"

extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked, enemy_num,player_walk_cnt3D,bgX,bgY, inFight, get_dmg_cnt; // player_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�
extern double start;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[5], tp_door;
extern Animate loading_animate;
extern char BgName[50];

void initialization()
{
	sprintf(BgName,"%s","images\\bg\\home2.png");
	loadBG(BgName,1587/2,1300/2); //讀取背景
	
	printf("load background succes\n");
	char s[50];
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++無法將字串常數直接轉成char pointer，故有此行
	loadCHAR(s,&player.player_img,&player.player_msk,76,66, 0); //讀取主角圖片
	sprintf(s,"%s","images\\3D\\player");
	loadCHAR(s,&player.player_img,&player.player_msk,38*3.5,33*3.5,26);
	printf("load player image succes\n");
	
	// 設定初始值 
	player.x = (wid-28*3.5) / 2;
	player.y = (hih-33*3.5) / 2 + 80;
	player.hp = 10;
	player.damage = 25; // 對敵人造成的傷害 
	player.atked = 0;   // 判定是否有造成傷害  
	player.dir = 'd';   // 方向 
	player.output_idx = 27;// 輸出圖片編號 
	player.high = 28*3.5;   // 人物圖片的高 
	player.width = 33*3.5;  // 人物圖片的寬 
	player.power = 30;  // 擊退敵人的距離 
	player.atk_type = 0;
	/*player.x = wid / 4; // 暫定 
	player.y = hih * 0.6; // 暫定 
	player.hp = 10;
	player.damage = 25; // 對敵人造成的傷害 
	player.atked = 0;   // 判定是否有造成傷害 
	player.dir = 'd';   // 方向 
	player.output_idx = 0;// 輸出圖片編號 
	player.high = 66;   // 人物圖片的高 
	player.width = 76;  // 人物圖片的寬 
	player.power = 30;  // 擊退敵人的距離 
	player.atk_type = 0;*/
	
	player_walk_cnt = 11; // 走路計時器 
	player_walk_cnt3D = 0,bgX=20,bgY=-20;
	
	printf("player setting succes\n");
	
	enemy_ini(); // 初始化敵人 
	
	printf("enemy ini succes\n");
	flag = 10;
	
	enemy_ini_01();
	printf("enemy_ini_01 succes\n");
	
	skill_ini_00();
	printf("skill_ini_00 succes\n");
	
	skill_ini_01(); // 初始化敵人的技能 
	printf("skill_ini_01 succes\n");
	
	skill_ini_02();
	printf("skill_ini_02 succes\n");
	
	skill_ini_03();
	printf("skill_ini_03 succes\n");

	skill_ini_04();
	printf("skill_ini_04 succes\n");
	
	tp_door_ini();
	printf("tp_door_ini succes\n");

	start = fclock(); // 用於計時敵人的攻擊時間間隔 
	enemy_atk_type = -1; // 敵人使用的技能編號 
	player_jump_cnt = -1;// 人物跳躍計時器
	
	enemy_num = -1;
	
	loading_img_ini();
	printf("loading_img_ini succes\n");
	
	inFight = 0;
	get_dmg_cnt = 0;
}

void enemy_ini()
{
	char s[100];
	
	enemy[0].enemy_img = NULL;
	enemy[0].enemy_msk = NULL;
	
	sprintf(s,"%s","images\\enemy_0");
	loadCHAR(s, &enemy[0].enemy_img, &enemy[0].enemy_msk, 165, 165, 0);
	
	enemy[0].x = 900;
	enemy[0].y = hih * 0.6 - 165 + 66;
	enemy[0].dir = 'a';
	enemy[0].hp = 100;
	enemy[0].damage = 0; // 敵人造成的傷害 
	enemy[0].output_idx = 1;
	enemy[0].high = 165;
	enemy[0].width = 165;
	enemy[0].power = 100; // 敵人擊退玩家的距離 
	enemy[0].speed = 5;    
	enemy[0].atk_0_cnt = 199; // 敵人的技能計數器 
	enemy[0].atk_1_cnt = 99;  
}

void enemy_ini_01()
{
	char s[100];
	
	enemy[1].enemy_img = NULL;
	enemy[1].enemy_msk = NULL;
	
	sprintf(s,"%s","images\\enemy_1");
	loadCHAR(s, &enemy[1].enemy_img, &enemy[1].enemy_msk, 136, 150, 0);
	//508
	enemy[1].x = 900;
	enemy[1].y = hih * 0.6 - 150 + 66;
	enemy[1].dir = 'a';
	enemy[1].hp = 100;
	enemy[1].damage = 0; // 敵人造成的傷害 
	enemy[1].output_idx = 1;
	enemy[1].high = 150;
	enemy[1].width = 136;
	enemy[1].power = 100; // 敵人擊退玩家的距離 
	enemy[1].speed = 5;    
	enemy[1].atk_0_cnt = -1; // 敵人的技能計數器 
	enemy[1].atk_1_cnt = -1;  
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
	loadCHAR(s, &skill[0].skill_img, &skill[0].skill_msk, 250, 126, 0);
	
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
	loadCHAR(s, &skill[1].skill_img, &skill[1].skill_msk, 608, 256, 0);
	
	skill[1].high = 256;
	skill[1].width = 608;
	skill[1].power = 200;
}

void loading_img_ini()
{
	char s[100];
	
	loading_animate.loading_img = (PIMAGE *)malloc(sizeof(PIMAGE) * 8);
	
	for(int i = 0; i < 9; i++)
	{
		loading_animate.loading_img[i] = newimage();
		sprintf(s, "images\\loading\\0%d_loading_img.png", i);
		getimage(loading_animate.loading_img[i], s);
	}
	
	loading_animate.cnt = 0;
	loading_animate.output_idx = 0;
	loading_animate.printed = 1;
}

void skill_ini_02()
{
	char s[100];
	
	skill[2].x = 0;
	skill[2].y = 0;
	skill[2].status = 0;
	skill[2].output_idx = 0;
	skill[2].skill_img = NULL;
	skill[2].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_0_2_skill"); // 34 21
	loadCHAR(s, &skill[2].skill_img, &skill[2].skill_msk, 170, 105, 0);
	
	skill[2].high = 105;
	skill[2].width = 170;
	skill[2].power = 100;
}

void skill_ini_03()
{
	char s[100];
	
	skill[3].x = 0;
	skill[3].y = 0;
	skill[3].status = 0;
	skill[3].output_idx = 0;
	skill[3].skill_img = NULL;
	skill[3].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_1_0_skill");
	loadCHAR(s, &skill[3].skill_img, &skill[3].skill_msk, 125, 125, 0);
	
	skill[3].high = 125;
	skill[3].width = 125;
	skill[3].power = 50;
}

void skill_ini_04()
{
	char s[100];
	skill[4].x = 0;
	skill[4].y = 0;
	skill[4].status = 0;
	skill[4].output_idx = 0;
	skill[4].skill_img = NULL;
	skill[4].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_1_1_skill");
	loadCHAR(s, &skill[4].skill_img, &skill[4].skill_msk, 336, 296, 0);
	
	skill[4].high = 336;
	skill[4].width = 296;
	skill[4].power = 5;
}

// 用來存放傳送門
// .power當作輸出的計數器
void tp_door_ini()
{
	char s[100];
	tp_door.x = wid - 77;
	tp_door.y = hih * 0.6 -11;
	tp_door.status = 0;
	tp_door.output_idx = 0;
	tp_door.skill_img = NULL;
	tp_door.skill_msk = NULL;
	sprintf(s, "%s", "images\\tp_door");
	loadCHAR(s, &tp_door.skill_img, &tp_door.skill_msk, 77, 77, 0);
	
	tp_door.high = 77;
	tp_door.width = 77;
	tp_door.power = 0;
}

