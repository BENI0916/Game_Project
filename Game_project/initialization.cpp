#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "dirent.h"
#include "var.cpp" 
extern int atk_cnt, player_walk_cnt; // player_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�
extern Human player;
void loadBG(char filename[]);
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h);

void initialization()
{
	char s[] = "images\\bg\\back_ground_01.png"; //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadBG(s); //Ū���I��
	
	sprintf(s,"%s","images\\main_char"); //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadCHAR(s,&player.player_img,&player.player_msk,76,66); //Ū���D���Ϥ�

	// �]�w��l�� 
	player.x = wid / 2; // �ȩw 
	player.y = hih / 2; // �ȩw
	player.hp = 5;
	player.dir = 'd';
	player.output_idx = 0;
	
	player_walk_cnt = 11;
	atk_cnt = 0;
}