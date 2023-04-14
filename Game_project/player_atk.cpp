#include "lib/var.h"
#include "lib/player_atk.h"
#include "lib/enemy_give_dmg.h"

extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked, enemy_num;
extern double start, end;
extern Human player;
extern Monster enemy[2];

// 玩家攻擊 
int player_atk(int val)
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
		
		case 1:
			if(player.dir == 'd')
			{
				if((is_middle(enemy[1].x + enemy[1].width * 0.64, player.x + player.width, enemy[1].x + enemy[1].width * 0.36)
				|| is_middle(enemy[1].x + enemy[1].width * 0.64, player.x + player.width * 0.6, enemy[1].x + enemy[1].width * 0.36))
				&& is_middle(enemy[1].y + enemy[1].high, player.y + player.high / 2, enemy[1].y + enemy[1].high * 0.17))
				{
					enemy[1].hp -= player.damage;
					enemy[1].x += player.power;	
					player.atked = 1;
				}
			}
			else
			{
				if((is_middle(enemy[1].x + enemy[1].width * 0.64, player.x, enemy[1].x + enemy[1].width * 0.36)
				||  is_middle(enemy[1].x + enemy[1].width * 0.64, player.x + player.width * 0.4, enemy[1].x + enemy[1].width * 0.36))
				&& is_middle(enemy[1].y + enemy[1].high, player.y + player.high / 2, enemy[1].y + enemy[1].high * 0.17))
				{
					enemy[1].hp -= player.damage;
					enemy[1].x -= player.power;	
					player.atked = 1;
				}
			}
			
			break;
			
		default :
			break;
	}
}
