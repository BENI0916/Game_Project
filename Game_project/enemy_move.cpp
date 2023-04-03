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
	
	// �Y�ĤH�P���a�Z���j��ĤH����Ө���
	// �h�|�����a��V���� 
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
	
	// ���ĤH�����|���B�� 
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
