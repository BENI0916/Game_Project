#include "lib/var.h"
#include "lib/player_atk.h"
#include "lib/enemy_give_dmg.h"

extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked, enemy_num;
extern double start, end;
extern Human player;
extern Monster enemy[2];

//玩家攻擊敵人
void atk_enemy(Monster &e, int power, int damage, char dir){
	if(is_middle(e.x + e.width * 0.98, player.x + player.width, e.x + e.width * 0.02))
	{
		e.hp -= damage;
		e.x += (dir == 'd' ? power : -power);// 敵人會被玩家擊退 
		player.atked = 1;// 若有造成傷害則會記錄 避免一次攻擊有多次傷害 
	}
}

// 玩家攻擊 
void player_atk(int val)
{	
	switch(enemy_num)
	{
		case 0:
			atk_enemy(enemy[0], player.power, player.damage, player.dir);
			break;
		default :
			break;
	}
}
