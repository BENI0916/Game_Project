#include "lib/var.h"
#include "lib/enemy_give_dmg.h"
 
extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked;
extern double start, end;
extern Human player;
extern Monster enemy;
extern Bullet skill[2];

void enemy_give_dmg()
{
	if(enemy_atk_type == 0)
	{
		// 敵人本體與技能均會造成傷害與擊退效果 
		if(enemy.dir == 'a')
		{
			// 判定玩家是否在敵人的攻擊範圍內 
			if(is_middle(enemy.x + enemy.width * 1.1, player.x + player.width / 2, enemy.x - enemy.width / 10))
			{
				player.hp -= enemy.damage;
				player.x -= enemy.power;
			}
			
			// 判定玩家是否在敵人的技能範圍內 
			if(skill[0].status && is_middle(skill[0].x + skill[0].width, player.x + player.width / 2, skill[0].x))
			{
				player.hp -= enemy.damage;
				player.x -= skill[0].power;
				//skill[0].status = 0;
			}
		}
		else
		{
			// player.x > enemy.x + 64 && enemy.x + 165 > player.x
			if(is_middle(enemy.x + enemy.width, player.x + player.width / 2, enemy.x))
			{
				player.hp -= enemy.damage;
				player.x += enemy.power;
			}
			
			if(skill[0].status && is_middle(skill[0].x + skill[0].width, player.x + player.width / 2, skill[0].x))
			{
				player.hp -= enemy.damage;
				player.x += skill[0].power;
				//skill[0].status = 0;
			}
		}
	}
	else if(enemy_atk_type == 1)
	{
		// 判定玩家是否在敵人的攻擊範圍內 
		if(is_middle(62, enemy_atk_cnt, 56))
		{
			//player.x >= enemy.x && player.x <= enemy.x + 165
			if(is_middle(enemy.x + enemy.width, player.x + player.width / 2, enemy.x))
			{
				//player.y - 10 > enemy.y - 165
				if(is_middle(enemy.y + enemy.high * 1.5, player.y + player.high / 2, enemy.y))
				{
					player.hp -= enemy.damage;
					
					if(enemy.dir == 'a')
						player.x -= enemy.power;
					else
						player.x += enemy.power;	
				}	
			}	
		}
		
		//printf("%d %d %d %d\n", skill[1].x, player.x + player.width / 2, skill[1].x + skill[1].width / 10, is_middle(skill[1].x, player.x + player.width / 2, skill[1].x + skill[1].width / 10));
		// 此技能較為特殊 一次共有四個範圍造成傷害 故分成左右兩組 
		if(is_middle(56, enemy_atk_cnt, 0))
		{
			// 左 
			if(is_middle(skill[1].x + skill[1].width / 10, player.x + player.width / 2, skill[1].x) == 1
			|| is_middle(skill[1].x + skill[1].width * 30 / 100, player.x + player.width / 2, skill[1].x + skill[1].width * 21 / 100) == 1)
			{
				player.hp -= enemy.damage;
				player.x -= skill[1].power;
				skill[1].status = 0;
			}
			// 右 
			else if(is_middle(skill[1].x + skill[1].width * 84 / 100, player.x + player.width / 2, skill[1].x + skill[1].width * 74 / 100) == 1
				 || is_middle(skill[1].x + skill[1].width, player.x + player.width / 2, skill[1].x + skill[1].width * 9 / 10) == 1)
			{
				player.hp -= enemy.damage;
				player.x += skill[1].power;
				skill[1].status = 0;
			}
		}	
	}
}

// 用於判斷 pos 是否在 up 和 down 中間 
int is_middle(int up, int pos, int down)
{
	if(up >= pos && pos >= down)
		return 1;
	return 0;
}
