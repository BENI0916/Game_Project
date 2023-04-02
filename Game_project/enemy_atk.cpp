// enemy_atk
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir;
extern double start, end;
extern Human player;
extern Monster enemy;
extern Bullet skill;

void enemy_first_atk(int val);
void enemy_second_atk(int val);
void enemy_give_damage();

void enemy_atk()
{
	end = fclock();
	
	if((end - start) > 5 && abs(enemy.x - player.x) < 300 && enemy_atk_type == -1)
	{
		enemy_atk_type = random(2);
		
		switch(enemy_atk_type)
		{
			case 0:
				enemy_atk_cnt = 199;
				break;
			
			case 1:
				enemy_atk_cnt = 59;
				break;
			
			default :
				break;
		}
		
		start = fclock();
		
		if(enemy.x > player.x)
			player_enemy_dir = 1;
		else
			player_enemy_dir = 0;
	}
	
	if(enemy_atk_type == 0)
	{
		enemy_first_atk(player_enemy_dir);
		
		if(enemy_atk_cnt == -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 1)
	{
		enemy_second_atk(player_enemy_dir);
		
		if(enemy_atk_cnt == -1)
			enemy_atk_type = -1;
	}
	
	enemy_give_damage();
}

void enemy_first_atk(int val)
{
	int table[5] = {0, 2, 4, 2};
	
	enemy.output_idx = table[enemy_atk_cnt / 50] + val;
	
	if(enemy.output_idx == 4 || enemy.output_idx == 5)
	
	{
		skill.status = 1;
		
		if(enemy.dir == 'a')
		{
			skill.x = enemy.x - 240;
			skill.output_idx = 1;
		}
		else
		{
			skill.x = enemy.x + 160;
			skill.output_idx = 0;
		}
		
		skill.y = enemy.y + 50;
	}
	else
		skill.status = 0;
	
	enemy_atk_cnt -= 1;
}

void enemy_second_atk(int val)
{
	int table[4] = {10, 6, 8, 6};
	
	enemy.output_idx = table[enemy_atk_cnt / 15] + val;
	enemy_atk_cnt -= 1;
	
	if(enemy_atk_cnt == -1)
		enemy.output_idx = 0 + val;
	
	switch(enemy_atk_cnt)
	{
		case 58 :
			enemy.y -= 60;
			break;
		case 50 :
			enemy.y -= 35;
			break;
		case 42 :
			enemy.y -= 15;
			break;
		case 30 :
			enemy.y += 15;
			break;
		case 22 :
			enemy.y += 35;
			break;
		case 16 : 
			enemy.y += 60;
			break;
		default : 
			break;
	}
}
