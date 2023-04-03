#include "lib/var.h"
#include "lib/enemy_move.h"

extern int key, atk_cnt, player_walk_cnt, flag;
extern Human player;
extern Monster enemy;

void enemy_move()
{
	if((enemy.x + enemy.width / 2) > (player.x + player.width / 2))
		enemy.dir = 'a';
	else
		enemy.dir = 'd';
	
	// 若敵人與玩家距離大於敵人的兩個身位
	// 則會往玩家方向移動 
	if(abs(enemy.x - player.x) >= enemy.width * 2)
	{
		if(enemy.x > player.x)
		{	
			enemy.x -= enemy.speed;
			enemy.output_idx = 1;
		}
		else
		{
			enemy.x += enemy.speed;
			enemy.output_idx = 0;
		}
	}
	
	// 讓敵人走路會有浮動 
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
