#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int key, atk_cnt, player_walk_cnt;
extern Human player;

void player_walk(int);
void atk(int);// ���� 

void move(int speed)
{
	if (kbhit()) // �˴��O�_����L��J 
		key = getch();
	
	if(atk_cnt > -1) // atk_cnt  < 0 �N���i����� , ��L����ƫh�N���b���� 
	{
		if(player.dir == 'd')
			atk(0);
		else
			atk(1);
	}
	else
	{
		switch (key)
		{
			case 97:  // ��J a 
				player.dir = 'a';
				player_walk(1);
				player.x -= speed;
				
				break;
			case 100: // ��J d
				player.dir = 'd';
				player_walk(0);
				player.x += speed;
				
				break;
			case 106: // ��J j 
				atk_cnt = 9;  
			default:
				break;
		}
	}
	key = 0; // ����ʧ@��N key�k 0, �קK�@�����ưʧ@ 
}

void player_walk(int val)
{
	int table[4] = {0, 4, 0, 2};
	
	player.output_idx = table[player_walk_cnt / 3] + val;
	player_walk_cnt--;

	if(player_walk_cnt < 0)
		player_walk_cnt = 11;
}

void atk(int val)
{
	// �ھڧ����p�ƾ��H�έ��諸��V  
	// �x�s�n��X���Ϥ��s�� 
	int table[5] = {14, 12, 10, 8, 6};
	
	player.output_idx = table[atk_cnt / 2] + val;
	atk_cnt--;
}
