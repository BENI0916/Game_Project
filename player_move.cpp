#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int key, left_walk_cnt, right_walk_cnt, atk_cnt;
extern Human player;

void walk_left(); // ������ 
void walk_right();// ���k�� 
void atk();// ���� 

void move(int speed)
{
	if (kbhit()) // �˴��O�_����L��J 
		key = getch();
	
	if(atk_cnt) // atk_cnt : 0 �N�����i�����? , ��L����?h�N�����b���� 
	{
		atk();
	}
	else
	{
		switch (key)
		{
			case 97:  // ��J a 
				walk_left();
				player.x -= speed;
				
				break;
			case 100: // ��J d
				walk_right();
				player.x += speed;
				
				break;
			case 106: // ��J j 
				atk_cnt = 10;  
			default:
				break;
		}
	}
	key = 0; // ����ʧ@��N key�k 0, �קK�@�����ưʧ@ 
}

void walk_left()
{
	// �Y�n���ʪ���V�P���a���諸��V���P , �h����V
	// �_�h�ھڨ����p�ƾ� �x�s�n��X���Ϥ��s�� 
	if(player.dir != 'a')  
	{
		player.output_idx = 1;
		player.dir = 'a';
	}
	else if(left_walk_cnt < 3)
	{
		player.output_idx = 3;
		left_walk_cnt++;
	}
	else if(left_walk_cnt < 6)
	{
		player.output_idx = 1;
		left_walk_cnt++;
	}
	else if(left_walk_cnt < 9)
	{
		player.output_idx = 5;
		left_walk_cnt++;
	}
	else if(left_walk_cnt == 9)
	{
		player.output_idx = 1;
		left_walk_cnt = 0;
	}
}

void walk_right()
{
	// �Y�n���ʪ���V�P���a���諸��V���P , �h����V
	// �_�h�ھڨ����p�ƾ� �x�s�n��X���Ϥ��s�� 
	if(player.dir != 'd')
	{
		player.output_idx = 0;
		player.dir = 'd';
	}
	else if(right_walk_cnt < 3)
	{
		player.output_idx = 2;
		right_walk_cnt++;
	}
	else if(right_walk_cnt < 6)
	{
		player.output_idx = 0;
		right_walk_cnt++;
	}
	else if(right_walk_cnt < 9)
	{
		player.output_idx = 4;
		right_walk_cnt++;
	}
	else if(right_walk_cnt == 9)
	{
		player.output_idx = 0;
		right_walk_cnt = 0;
	}
}

void atk()
{
	// �ھڧ����p�ƾ��H�έ��諸��V  
	// �x�s�n��X���Ϥ��s�� 
	if(atk_cnt > 8)
	{
		if(player.dir == 'd')
			player.output_idx = 6;
		else
			player.output_idx = 7;
	}
	else if(atk_cnt > 6)
	{
		if(player.dir == 'd')
			player.output_idx = 8;
		else
			player.output_idx = 9;
	}
	else if(atk_cnt > 4)	
	{
		if(player.dir == 'd')
			player.output_idx = 10;
		else
			player.output_idx = 11;
	}
	else if(atk_cnt > 2)
	{
		if(player.dir == 'd')
			player.output_idx = 12;
		else
			player.output_idx = 13;
	}
	else if(atk_cnt > 0)
	{
		if(player.dir == 'd')
			player.output_idx = 14;
		else
			player.output_idx = 15;
	}
	atk_cnt--;
}
