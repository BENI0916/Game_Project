#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"" 

int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir;
double start, end;
// key : ��L��J���x�s��m
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ� 

Human player;
Monster enemy;
Bullet skill;

void initialization();
void move(int speed);
void output_image();
void loadBG(char filename[]);
void enemy_move();
void enemy_atk();

int main(void)
{
	initgraph(wid, hih);	// ��l�ƿ�X���f 
	initialization();
	
	// is_run �˵��{�ǬO�_������������, ���쪺�ܷ|��^false, �Y�h�X�{�� 
	// delay_fps ����V�v, 60 ���"��������"��1000/60�@�� 
	for (; is_run() && player.hp > 0; delay_fps(60))
	{
		cleardevice(); // ���X�����f�M�� 
		
		if(enemy.hp > 0)
		{
			if(enemy_atk_type == -1)
				enemy_move();
			enemy_atk();
		}
		
		move(5);
		output_image();
	}

	return 0;
}
