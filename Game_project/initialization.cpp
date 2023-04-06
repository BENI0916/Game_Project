#include "dirent.h"
#include "lib/var.h"
#include "lib/initialization.h"
#include "lib/output_image.h"
#include "lib/enemy_atk.h"

extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked; // player_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�
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
	char s[] = "images\\bg\\back_ground_01.png"; //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadBG(s); //Ū���I��
	
	printf("load background succes\n");
	
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadCHAR(s,&player.player_img,&player.player_msk,76,66); //Ū���D���Ϥ�
	
	printf("load player image succes\n");
	
	// �]�w��l�� 
	player.x = wid / 4; // �ȩw 
	player.y = hih * 0.6; // �ȩw 
	player.hp = 10;
	player.damage = 25; // ��ĤH�y�����ˮ` 
	player.atked = 0;   // �P�w�O�_���y���ˮ` 
	player.dir = 'd';   // ��V 
	player.output_idx = 0;// ��X�Ϥ��s�� 
	player.high = 66;   // �H���Ϥ����� 
	player.width = 76;  // �H���Ϥ����e 
	player.power = 30;  // ���h�ĤH���Z�� 
	player.atk_type = 0;
	
	player_walk_cnt = 11; // �����p�ɾ� 
	
	printf("player setting succes\n");
	
	enemy_ini(); // ��l�ƼĤH 
	
	printf("enemy ini succes\n");
	flag = 10;
	
	skill_ini_01();
	printf("skill_ini_01 succes\n");
	
	skill_ini_00(); // ��l�ƼĤH���ޯ� 
	printf("skill_ini_00 succes\n");
	
	start = fclock(); // �Ω�p�ɼĤH�������ɶ����j 
	enemy_atk_type = -1; // �ĤH�ϥΪ��ޯ�s�� 
	player_jump_cnt = -1;// �H�����D�p�ɾ�
	
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
	enemy.damage = 0; // �ĤH�y�����ˮ` 
	enemy.output_idx = 1;
	enemy.high = 165;
	enemy.width = 165;
	enemy.power = 100; // �ĤH���h���a���Z�� 
	enemy.speed = 5;    
	enemy.atk_0_cnt = 199; // �ĤH���ޯ�p�ƾ� 
	enemy.atk_1_cnt = 99;  
	enemy.use_skill = (atk_func *) malloc(sizeof(atk_func));
	enemy.use_skill[0] = enemy_first_atk;
	enemy.use_skill[1] = enemy_second_atk;
}

// �ޯ�1 
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

// �ޯ�2 
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
