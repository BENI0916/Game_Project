#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key;
extern Human player;

void player_walk(int);
void atk(int);
int player_move_check(char, int);
void jump(void);
void player_atk(int val);

void move(int speed)
{
	if (kbhit()) // �˴��O�_����L��J 
		key = getch();
	
	if(player_jump_cnt > -1)
		jump();
	if(atk_cnt > -1) // atk_cnt  < 0 �N���i����� , ��L����ƫh�N���b���� 
	{
		if(player.dir == 'd')
		{
			atk(0);
			
			if(!player.atked)
				player_atk(1);
		}
		else
		{
			atk(1);
			
			if(!player.atked)
				player_atk(-1);
		}
	}
	else 
	{
			if(GetAsyncKeyState(0x41) || GetAsyncKeyState('a'))  // ��J a 
			{
				player.dir = 'a';
				if(player_move_check(player.dir, speed))
				{
					player_walk(1);
					player.x -= speed;
				}
			}
			
			if(GetAsyncKeyState(0x44) || GetAsyncKeyState('d')) // ��J d
			{	
				player.dir = 'd';
				if(player_move_check(player.dir, speed))
				{
					player_walk(0);
					player.x += speed;
				}
	 	    }
			
			if(GetAsyncKeyState(0x4A) || GetAsyncKeyState('j'))// ��J j 
			{
				atk_cnt = 9;  
				player.atked = 0;
			}
			
			if(GetAsyncKeyState(0x20) || GetAsyncKeyState(' ')) // ��J�ť���
				if(player_jump_cnt < 0)
					player_jump_cnt = 15;
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

// �p����� 
void atk(int val)
{
	// �ھڧ����p�ƾ��H�έ��諸��V  
	// �x�s�n��X���Ϥ��s�� 
	int table[5] = {14, 12, 10, 8, 6};
	
	player.output_idx = table[atk_cnt / 2] + val;
	atk_cnt--;
}

// �p����D 
void jump()// 2 4 8 -> 16, 12, 10, 8, 4, 2
{			// 1 2 3 4 5 6
	int move_distance[4] = {6, 18, 40, 75};
	
	if(player_jump_cnt & 1)
	{
		if(player_jump_cnt > 7)
			player.y -= move_distance[player_jump_cnt / 2 - 4];
		else
			player.y += move_distance[3 - player_jump_cnt / 2];
	}
	
	player_jump_cnt--;
}

// ����a���X��� ������ 
int player_move_check(char dir, int speed)
{
	if(dir == 'a')
	{
		if(player.x - speed > 0)
			return 1;
		else 
			return 0;
	}
	else
	{
		if(player.x + player.width + speed < wid)
			return 1;
		else
			return 0;
	}
}
