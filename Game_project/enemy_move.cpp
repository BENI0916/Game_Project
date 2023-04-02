#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int key, atk_cnt, player_walk_cnt, flag;
extern Human player;
extern Monster enemy;

void enemy_move()
{
	if(enemy.x > player.x)
		enemy.dir = 'a';
	else
		enemy.dir = 'd';
		
	if(abs(enemy.x - player.x) > 300)
	{
		if(enemy.x > player.x)
		{	
			enemy.x -= 5;
			enemy.output_idx = 1;
		}
		else
		{
			enemy.x += 5;
			enemy.output_idx = 0;
		}
	}
	
	if(flag == 40)
	{
		enemy.y -= 3;
	}
	else if(flag == 0)
	{
		enemy.y += 3;
		flag = 81;
	}
	
	flag--;
}
