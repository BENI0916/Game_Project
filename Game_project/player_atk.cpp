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

// 玩家攻擊 
int player_atk(int val)
{	
	if(player.dir == 'd')
	{	
		// 若敵人在玩家攻擊範圍 
		if(is_middle(enemy.x + enemy.width * 0.98, player.x + player.width, enemy.x + enemy.width * 0.02))
		{
			enemy.hp -= player.damage;
			enemy.x += player.power;// 敵人會被玩家擊退 
			player.atked = 1;// 若有造成傷害則會記錄 避免一次攻擊有多次傷害 
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
