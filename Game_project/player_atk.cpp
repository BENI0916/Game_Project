#include "lib/var.h"
#include "lib/player_atk.h"
#include "lib/enemy_give_dmg.h"

extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked, enemy_num;
extern double start, end;
extern Human player;
extern Monster enemy[2];

// 玩家攻擊 
void player_atk(int val)
{	
	switch(enemy_num)
	{
		case 0:
			if(player.dir == 'd')
			{	
				// 若敵人在玩家攻擊範圍 
				if(is_middle(enemy[0].x + enemy[0].width * 0.98, player.x + player.width, enemy[0].x + enemy[0].width * 0.02))
				{
					enemy[0].hp -= player.damage;
					enemy[0].x += player.power;// 敵人會被玩家擊退 
					player.atked = 1;// 若有造成傷害則會記錄 避免一次攻擊有多次傷害 
				}
			}
			else
			{
				if(is_middle(enemy[0].x + enemy[0].width * 0.98, player.x, enemy[0].x + enemy[0].width * 0.02))
				{
					enemy[0].hp -= player.damage;
					enemy[0].x -= player.power;	
					player.atked = 1;
				}
			}
			break;
		
		default :
			break;
	}
}
