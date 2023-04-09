#include "lib/var.h"
#include "lib/enemy_move.h"

extern int key, atk_cnt, player_walk_cnt, flag, enemy_num;
extern Human player;
extern Monster enemy[2];

void enemy_move()
{
	switch(enemy_num)
	{
		case 0:
			if((enemy[enemy_num].x + enemy[enemy_num].width / 2) > (player.x + player.width / 2))
				enemy[enemy_num].dir = 'a';
			else
				enemy[enemy_num].dir = 'd';
				
			// 若敵人與玩家距離大於敵人的兩個身位
			// 則會往玩家方向移動 
			if(abs(enemy[enemy_num].x - player.x) >= enemy[enemy_num].width * 2)
			{
				if(enemy[enemy_num].x > player.x)
				{	
					enemy[enemy_num].x -= enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 1;
				}
				else
				{
					enemy[enemy_num].x += enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 0;
				}
			}
			
			// 讓敵人走路會有浮動 
			if(flag == 40)
			{
				enemy[enemy_num].y -= 3;
			}
			else if(flag == 0)
			{
				enemy[enemy_num].y += 3;
				flag = 81;
			}
			
			flag--;
			break;
		
		case 1:
			if((enemy[enemy_num].x + enemy[enemy_num].width / 2) > (player.x + player.width / 2))
				enemy[enemy_num].dir = 'a';
			else
				enemy[enemy_num].dir = 'd';
			
			if(abs(enemy[enemy_num].x - player.x) >= 300)
			{
				if(enemy[enemy_num].x > player.x)
				{	
					enemy[enemy_num].x -= enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 1;
				}
				else
				{
					enemy[enemy_num].x += enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 0;
				}
			}
			else
			{
				if(flag <= 0)
					flag = 80;
				flag--;
				
				int table[2] = {0, 2};
				
				if(enemy[enemy_num].dir == 'a')
				{
					enemy[enemy_num].output_idx = table[flag / 40 ] + 1;
				}
				else
				{
					enemy[enemy_num].output_idx = table[flag / 40 ];
				}
			}
			break;
			
		default :
			break;
	}
}
