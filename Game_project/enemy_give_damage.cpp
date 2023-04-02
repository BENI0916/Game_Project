// enemy_give_damage
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
extern Bullet skill;
bool is_middle(int up, int pos, int down);

void enemy_give_damage()
{
	if(enemy_atk_type == 0)
	{
		if(enemy.dir == 'a')
		{
			if(player.x + 40 > enemy.x && enemy.x + 100 > player.x)
			{
				player.hp -= enemy.damage;
				player.x -= 100;
			}
			
			//player.x >= skill.x + skill.space_cal[0] && player.x <= skill.space_cal[1]
			if(skill.status && is_middle(skill.x + skill.space_cal[1], player.x, skill.x + skill.space_cal[0]))
			{
				player.hp -= enemy.damage;
				player.x -= 300;
				skill.status = 0;
			}
		}
		else
		{
			if(player.x > enemy.x + 64 && enemy.x + 165 > player.x)
			{
				player.hp -= enemy.damage;
				player.x += 100;
			}
		}
	}
	else if(enemy_atk_type == 1)
	{
		if(enemy_atk_cnt <= 16)
		{
			if(player.x >= enemy.x && player.x <= enemy.x + 165)
			{
				if(player.y - 10 > enemy.y - 165)
				{
					player.hp -= enemy.damage;
					
					if(enemy.dir == 'a')
						player.x -= 150;
					else
						player.x += 150;	
				}	
			}	
		}	
	}
}

bool is_middle(int up, int pos, int down)
{
	if(up >= pos && pos >= down)
		return true;
	return false;
}
