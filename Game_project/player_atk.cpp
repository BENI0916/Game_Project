//player_atk
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp" 

extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked;
extern double start, end;
extern Human player;
extern Monster enemy;

int is_middle(int up, int pos, int down);

// ���a���� 
int player_atk(int val)
{	
	if(player.dir == 'd')
	{	
		// �Y�ĤH�b���a�����d�� 
		if(is_middle(enemy.x + enemy.width * 0.98, player.x + player.width, enemy.x + enemy.width * 0.02))
		{
			enemy.hp -= player.damage;
			enemy.x += player.power;// �ĤH�|�Q���a���h 
			player.atked = 1;// �Y���y���ˮ`�h�|�O�� �קK�@���������h���ˮ` 
		}
	}
	else
	{
		if(is_middle(enemy.x + enemy.width * 0.98, player.x, enemy.x + enemy.width * 0.02))
		{
			enemy.hp -= player.damage;
			enemy.x -= player.power;	
			player.atked = 1;
		}
	}
}
