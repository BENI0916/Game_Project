// enemy_atk
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int enemy_atk_cnt, enemy_atk_type;
extern double start, end;
extern Human player;
extern Monster enemy;
extern Bullet skill[2];

void enemy_first_atk(int val);
void enemy_second_atk(int val);
void enemy_give_damage();
int is_middle(int up, int pos, int down);

// 此函式為改變敵人的動作 僅針對攻擊 
void enemy_atk()
{
	end = fclock(); // 攻擊間隔計時器 
	
	// 若距離上次攻擊已超過5秒 且 敵人與玩家的距離 靠近 且 敵人未進行攻擊移動 
	if(((end - start) > 5) && abs(enemy.x - player.x) < enemy.width * 2 && enemy_atk_type == -1)
	{
		enemy_atk_type = random(2); // 敵人使用技能的選擇為隨機 
		
		// 將對應編號的技能賦予計時器 
		switch(enemy_atk_type)
		{
			case 0:
				enemy_atk_cnt = enemy.atk_0_cnt;
				break;
			
			case 1:
				enemy_atk_cnt = enemy.atk_1_cnt;
				break;
			
			default :
				break;
		}
		
		start = fclock(); // 刷新攻擊間隔的時間起點 
	}
	
	if(enemy_atk_type == 0)
	{
		// 根據玩家位置施放技能 
		if(player.x + player.width / 2 > enemy.x + enemy.width / 2)
			enemy_first_atk(0);
		else
			enemy_first_atk(1);
		
		//若攻擊計時器為-1 代表攻擊完畢 則紀錄已攻擊完畢 
		if(enemy_atk_cnt == -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 1)
	{
		if(player.x + player.width / 2 > enemy.x + enemy.width / 2)
			enemy_second_atk(0);
		else
			enemy_second_atk(1);
		
		if(enemy_atk_cnt == -1)
			enemy_atk_type = -1;
	}
	
	// 此函式為造成傷害 
	enemy_give_damage();
}
 
void enemy_first_atk(int val)
{
	int table[5] = {0, 2, 4, 2};
	
	// 根據計時器輸出動作 
	enemy.output_idx = table[enemy_atk_cnt / 50] + val;
	
	// 若在計時器的特定時間間隔內 會輸出對應的技能特效 
	if(enemy.output_idx == 4 || enemy.output_idx == 5)
	{
		skill[0].status = 1; // 1 代表技能特效會印出， 0 則代表不會 
		
		if(enemy.dir == 'a')
		{
			skill[0].x = enemy.x - skill[0].width * 0.9; // 調整技能印出的位置 
			skill[0].output_idx = 1;
		}
		else
		{
			skill[0].x = enemy.x + enemy.width * 0.9;
			skill[0].output_idx = 0;
		}
		
		skill[0].y = enemy.y + 50;
	}
	else
		skill[0].status = 0; // 若不在計時器的特定時間間隔內，則不會輸出技能特效 
	
	enemy_atk_cnt -= 1; // 計時器倒數 
}

void enemy_second_atk(int val)
{
	int table[4] = {10, 6, 8, 6};
	
	enemy.output_idx = table[(enemy_atk_cnt - 40) / 15] + val;
	enemy_atk_cnt -= 1;
	
	// 此技能較為特殊 施放技能完畢後 需額外指令恢復正常型態 
	if(enemy_atk_cnt == -1)
		enemy.output_idx = 0 + val;
	
	// 此技能含有跳躍動作 以下則為對應的 y 軸位移 
	switch(enemy_atk_cnt)
	{
		case 98 :
			enemy.y -= 60;
			break;
		case 90 :
			enemy.y -= 35;
			break;
		case 82 :
			enemy.y -= 15;
			break;
		case 70 :
			enemy.y += 15;
			break;
		case 62 :
			enemy.y += 35;
			break;
		case 56 : 
			enemy.y += 60;
			break;
		default : 
			break;
	}
	
	// 在特定時間間隔內 輸出技能特效 
	if(is_middle(56, enemy_atk_cnt, 0))
	{
		skill[1].status = 1;
		skill[1].x = enemy.x - skill[1].width / 3;
		
		skill[1].output_idx = 0;
		
		skill[1].y = hih * 0.6 + player.high - skill[1].high;
	}
	else
		skill[1].status = 0;
}
