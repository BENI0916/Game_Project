#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#include "dirent.h" 
#include "var.cpp" 
extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked; // player_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�
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
	char s[] = "images\\bg\\back_ground_01.png"; //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadBG(s); //Ū���I��
	
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadCHAR(s,&player.player_img,&player.player_msk,76,66); //Ū���D���Ϥ�

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
	
	player_walk_cnt = 11; // �����p�ɾ� 
	
	enemy_ini(); // ��l�ƼĤH 
	flag = 10;
	
	skill_ini_00(); // ��l�ƼĤH���ޯ� 
	skill_ini_01();
	
	start = fclock(); // �Ω�p�ɼĤH�������ɶ����j 
	enemy_atk_type = -1; // �ĤH�ϥΪ��ޯ�s�� 
	player_jump_cnt = -1;// �H�����D�p�ɾ� 
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
}

// �ޯ�1 
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

// �ޯ�2 
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
