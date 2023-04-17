#include "dirent.h"
#include "lib/var.h"
#include "lib/initialization.h"
#include "lib/output_img.h"
#include "lib/enemy_atk.h"

extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked, enemy_num; // player_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�
extern double start;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[4];
extern Animate loading_animate;

void initialization()
{
	char s[] = "images\\bg\\back_ground_01.png"; //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadBG(s); //Ū���I��
	
	printf("load background succes\n");
	
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadCHAR(s,&player.player_img,&player.player_msk,76,66, 0); //Ū���D���Ϥ�
	
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
	
	enemy_ini_01();
	printf("enemy_ini_01 succes\n");
	
	skill_ini_00();
	printf("skill_ini_00 succes\n");
	
	skill_ini_01(); // ��l�ƼĤH���ޯ� 
	printf("skill_ini_01 succes\n");
	
	skill_ini_02();
	printf("skill_ini_02 succes\n");
	
	skill_ini_03();
	printf("skill_ini_03 succes\n");
	
	start = fclock(); // �Ω�p�ɼĤH�������ɶ����j 
	enemy_atk_type = -1; // �ĤH�ϥΪ��ޯ�s�� 
	player_jump_cnt = -1;// �H�����D�p�ɾ�
	
	enemy_num = 0;
	
	loading_img_ini();
	printf("loading_img_ini succes\n");
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
	enemy[0].damage = 0; // �ĤH�y�����ˮ` 
	enemy[0].output_idx = 1;
	enemy[0].high = 165;
	enemy[0].width = 165;
	enemy[0].power = 100; // �ĤH���h���a���Z�� 
	enemy[0].speed = 5;    
	enemy[0].atk_0_cnt = 199; // �ĤH���ޯ�p�ƾ� 
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
	enemy[1].damage = 0; // �ĤH�y�����ˮ` 
	enemy[1].output_idx = 1;
	enemy[1].high = 150;
	enemy[1].width = 136;
	enemy[1].power = 100; // �ĤH���h���a���Z�� 
	enemy[1].speed = 5;    
	enemy[1].atk_0_cnt = -1; // �ĤH���ޯ�p�ƾ� 
	enemy[1].atk_1_cnt = -1;  
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
	loadCHAR(s, &skill[0].skill_img, &skill[0].skill_msk, 250, 126, 0);
	
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
	skill[3].power = 80;
}

