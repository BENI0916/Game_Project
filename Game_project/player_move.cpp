#include "lib/var.h"
#include "lib/player_move.h"
#include "lib/player_atk.h"

extern int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key, enemy_num;
extern Human player;
extern Monster enemy[2];
extern Animate loading_animate;

void move(int speed)
{
	if (kbhit()) // 檢測是否有鍵盤輸入 
		key = getch();
	
	if(player_jump_cnt > -1)
		jump();
	if(atk_cnt > -1) // atk_cnt  < 0 代表未進行攻擊 , 其他正整數則代表正在攻擊 
	{
		if(player.dir == 'd')
		{
			atk(0);
			
			if(!player.atked)
				player_atk(1);
		}
		else
		{
			atk(1);
			
			if(!player.atked)
				player_atk(-1);
		}
	}
	else 
	{
			if(GetAsyncKeyState(0x41) || GetAsyncKeyState('a'))  // 輸入 a 
			{
				player.dir = 'a';
				if(player_move_check(player.dir, speed))
				{
					player_walk(1);
					player.x -= speed;
				}
			}
			
			if(GetAsyncKeyState(0x44) || GetAsyncKeyState('d')) // 輸入 d
			{	
				player.dir = 'd';
				if(player_move_check(player.dir, speed))
				{
					player_walk(0);
					player.x += speed;
				}
	 	    }
			
			if(GetAsyncKeyState(0x4A) || GetAsyncKeyState('j'))// 輸入 j 
			{
				atk_cnt = 9;  
				player.atked = 0;
				
				if(player.atk_type == 0)
					player.atk_type = 1;
				else
					player.atk_type = 0;
			}
			
			if(GetAsyncKeyState(0x20) || GetAsyncKeyState(' ')) // 輸入空白鍵
				if(player_jump_cnt < 0)
					player_jump_cnt = 15;
		}
	
	key = 0; // 執行動作後將 key歸 0, 避免一直重複動作 
}

void player_walk(int val)
{
	int table[4] = {0, 4, 0, 2};
	
	player.output_idx = table[player_walk_cnt / 3] + val;
	player_walk_cnt--;

	if(player_walk_cnt < 0)
		player_walk_cnt = 11;
}

// 計算攻擊 
void atk(int val)
{
	// 根據攻擊計數器以及面對的方向  
	// 儲存要輸出的圖片編號 
	int table[5] = {14, 12, 10, 8, 6};
	//printf("val = %d player.atk_type = %d\n", val, player.atk_type);
	switch(player.atk_type)
	{
		case 0:
			player.output_idx = table[atk_cnt / 2] + val;
			break;
		
		case 1:
			player.output_idx = table[atk_cnt / 2] + 10 + val;
			break;
		
		default:
			break;
	}
	atk_cnt--;
}

// 計算跳躍 
void jump()// 2 4 8 -> 16, 12, 10, 8, 4, 2
{			// 1 2 3 4 5 6
	int move_distance[4] = {10, 30, 50, 80};
	
	if(player_jump_cnt & 1)
	{
		if(player_jump_cnt > 7)
			player.y -= move_distance[player_jump_cnt / 2 - 4];
		else
			player.y += move_distance[3 - player_jump_cnt / 2];
	}
	
	player_jump_cnt--;
}

// 防止玩家走出邊界 
int player_move_check(char dir, int speed)
{
	// 如果敵人被打敗 且 玩家走到傳送門所在 則 開啟loading的動畫
	if(enemy[enemy_num].hp <= 0 && (player.x + player.width) >= (wid - 77))
	{
		loading_animate.printed = 1;
		loading_animate.cnt = 0;
	}

	if(dir == 'a')
	{
		if(player.x - speed > 0)
			return 1;
		else 
			return 0;
	}
	else
	{
		if(player.x + player.width + speed < wid)
			return 1;
		else
			return 0;
	}
}
