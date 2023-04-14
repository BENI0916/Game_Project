#include "lib/var.h" 
#include "lib/enemy_atk.h"
#include "lib/enemy_give_dmg.h"
#include "lib/initialization.h"

extern int enemy_atk_cnt, enemy_atk_type, enemy_num;
extern double start, end;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[4];

// 此函式為改變敵人的動作 僅針對攻擊 
void enemy_atk()
{
	end = fclock(); // 攻擊間隔計時器 
	
	// 若距離上次攻擊已超過5秒 且 敵人與玩家的距離 靠近 且 敵人未進行攻擊移動 
	if(((end - start) > 5) && abs(enemy[enemy_num].x - player.x) < enemy[enemy_num].width * 3 && enemy_atk_type <= -1)
	{
		enemy_atk_type = random(3) + enemy_num * 3; // 敵人使用技能的選擇為隨機 
		//if(enemy_num == 1)
		//	enemy_atk_type = -1;
		
		// 將對應編號的技能賦予計時器 
		switch(enemy_atk_type)
		{
			case 0:
				enemy_atk_cnt = enemy[enemy_num].atk_0_cnt;
				break;
			
			case 1:
				enemy_atk_cnt = enemy[enemy_num].atk_1_cnt;
				break;
			
			case 2 :
				enemy_atk_cnt = 60;
				break;
			
			case 3 :
				enemy_atk_cnt = 149;
				break;
			
			default :
				enemy_atk_type = -1;
				break;
		}
		start = fclock(); // 刷新攻擊間隔的時間起點 
	}
	//printf("skill[0].status = %d output_index = %d\n", skill[0].status, skill[0].output_idx);
	if(enemy_atk_type == 0)
	{
		// 根據玩家位置施放技能 
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_00_atk(0);
		else
			enemy_00_atk(1);
		
		//若攻擊計時器為-1 代表攻擊完畢 則紀錄已攻擊完畢 
		if(enemy_atk_cnt == -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 1)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_01_atk(0);
		else
			enemy_01_atk(1);
		
		if(enemy_atk_cnt == -1)
			enemy_atk_type = -1;
	}
	else if(enemy_atk_type == 2)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_02_atk(0);
		else 
			enemy_02_atk(1);
		
		if(enemy_atk_cnt <= -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 3)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_03_atk(0);
		else 
			enemy_03_atk(1);
		
		if(enemy_atk_cnt <= -1)
		{
			enemy_atk_type = -1;
		}
	}
	
	// 此函式為造成傷害 
	enemy_give_dmg();
}
 
void enemy_00_atk(int val)
{
	int table[5] = {0, 2, 4, 2};
	
	// 根據計時器輸出動作 
	enemy[enemy_num].output_idx = table[enemy_atk_cnt / 50] + val;
	
	// 若在計時器的特定時間間隔內 會輸出對應的技能特效 
	if(enemy[enemy_num].output_idx == 4 || enemy[enemy_num].output_idx == 5)
	{
		skill[0].status = 1; // 1 代表技能特效會印出， 0 則代表不會 
		
		if(enemy[0].dir == 'a')
		{
			skill[0].x = enemy[enemy_num].x - skill[0].width * 0.9; // 調整技能印出的位置 
			skill[0].output_idx = 1;
		}
		else
		{
			skill[0].x = enemy[enemy_num].x + enemy[enemy_num].width * 0.9;
			skill[0].output_idx = 0;
		}
		
		skill[0].y = enemy[enemy_num].y + 50;
	}
	else
		skill[0].status = 0; // 若不在計時器的特定時間間隔內，則不會輸出技能特效 
	
	enemy_atk_cnt -= 1; // 計時器倒數 
}

void enemy_01_atk(int val)
{
	int table[4] = {10, 6, 8, 6};
	
	enemy[enemy_num].output_idx = table[(enemy_atk_cnt - 40) / 15] + val;
	enemy_atk_cnt -= 1;
	
	// 此技能較為特殊 施放技能完畢後 需額外指令恢復正常型態 
	if(enemy_atk_cnt == -1)
		enemy[enemy_num].output_idx = 0 + val;
	
	// 此技能含有跳躍動作 以下則為對應的 y 軸位移 
	switch(enemy_atk_cnt)
	{
		case 98 :
			enemy[enemy_num].y -= 60;
			break;
		case 90 :
			enemy[enemy_num].y -= 35;
			break;
		case 82 :
			enemy[enemy_num].y -= 15;
			break;
		case 70 :
			enemy[enemy_num].y += 15;
			break;
		case 62 :
			enemy[enemy_num].y += 35;
			break;
		case 56 : 
			enemy[enemy_num].y += 60;
			break;
		default : 
			break;
	}
	
	// 在特定時間間隔內 輸出技能特效 
	if(is_middle(56, enemy_atk_cnt, 0))
	{
		skill[1].status = 1;
		skill[1].x = enemy[enemy_num].x - skill[1].width / 3;
		
		skill[1].output_idx = 0;
		
		skill[1].y = hih * 0.6 + player.high - skill[1].high;
	}
	else
		skill[1].status = 0;
}

void enemy_02_atk(int val)
{
	enemy_atk_cnt--;
	if(enemy_atk_cnt > -1)
	{
		skill[2].status = 1;
		skill[2].output_idx = val;
		
		if(enemy[enemy_num].dir == 'a')
		{
			skill[2].x = enemy[enemy_num].x - ((60 - enemy_atk_cnt) * 15);
		}
		else
		{
			skill[2].x = enemy[enemy_num].x + enemy[enemy_num].width + ((59 - enemy_atk_cnt) * 15);
		}
		
		skill[2].y = hih * 0.6 + player.high - skill[2].high;
	}	
	else
		skill[2].status = 0;
}

void enemy_03_atk(int val)
{
	int table[5] = {6, 6, 4};
	
	enemy[enemy_num].output_idx = table[enemy_atk_cnt / 50] + val;
	enemy_atk_cnt -= 1;
	
	if(enemy_atk_cnt == -1)
		enemy[enemy_num].output_idx = 0 + val;
	
	skill[3].status = 1;
	skill[3].y = enemy[enemy_num].y + skill[3].high * 0.2;
	
	if(enemy_atk_cnt > 99)
	{
		switch(enemy_atk_cnt)
		{
			case 149:
				skill[3].output_idx = 0;
				break;
				
			case 132:
				skill[3].output_idx = 1;
				break;
			
			case 115:
				skill[3].output_idx = 2;
				break;
			
			default:
				break;
		}
		
		if(enemy[enemy_num].dir == 'a')
		{
			skill[3].x = enemy[enemy_num].x - skill[3].width;
		}
		else
		{
			skill[3].x = enemy[enemy_num].x + enemy[enemy_num].width * 0.6;
		}
	}
	else
	{
		if(enemy[enemy_num].dir == 'a')
		{
			skill[3].x = enemy[enemy_num].x - ((99 - enemy_atk_cnt) * 10) - skill[3].width;
		}
		else
		{
			skill[3].x = enemy[enemy_num].x + enemy[enemy_num].width * 0.6 + ((99 - enemy_atk_cnt) * 10);
		}
		
		switch(enemy_atk_cnt)
		{
			case 90:
				skill[3].output_idx = 4 - val;
				break;
				
			case 88:
				skill[3].output_idx = 6 - val;
				break;
			
			case 70:
				skill[3].output_idx = 4 - val;
				break;
				
			case 60:
				skill[3].output_idx = 6 - val;
				break;
				
			case 50:
				skill[3].output_idx = 4 - val;
				break;
				
			case 40:
				skill[3].output_idx = 6 - val;
				break;
				
			case 30:
				skill[3].output_idx = 4 - val;
				break;
				
			case 20:
				skill[3].output_idx = 6 - val;
				break;
			
			case 10:
				skill[3].output_idx = 4 - val;
				break;
			
			case -1:
				skill[3].status = 0;
				break;
			
			default :
				break;
		}
	}
}


