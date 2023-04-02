//player_atk
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp" 
extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked;
extern double start, end;
extern Human player;
extern Monster enemy;

void player_atk(int val)
{	
	if(player.dir == 'd')
	{	
		if((player.x + 38) >= (enemy.x + 3)
		&& (player.x + 38) <= (enemy.x + 162))
		{
			enemy.hp -= player.damage;
			enemy.x += 20;	
			player.atked = 1;
		}
	}
	else
	{
		if((player.x <= enemy.x + 162)
		&& (player.x >= enemy.x + 3))
		{
			enemy.hp -= player.damage;
			enemy.x -= 20;	
			player.atked = 1;
		}
	}
}
