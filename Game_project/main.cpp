#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp" 

int key, atk_cnt, player_walk_cnt;
// key : ��L��J���x�s��m
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ� 

Human player = {.player_img=NULL,.player_msk=NULL};

void initialization();
void move(int speed);
void output_image();
void loadBG(char filename[]);

int main(void)
{
	initgraph(wid, hih);	// ��l�ƿ�X���f 
	initialization();
	
	// is_run �˵��{�ǬO�_������������, ���쪺�ܷ|��^false, �Y�h�X�{�� 
	// delay_fps ����V�v, 60 ���"��������"��1000/60�@�� 
	for (; is_run(); delay_fps(60))
	{
		cleardevice(); // ���X�����f�M�� 
		move(3);
		output_image();
	}

	return 0;
}
