#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int key, atk_cnt, player_walk_cnt;
extern Human player;

void player_walk(int);
void atk(int);// 攻擊 

void move(int speed)
{
	if (kbhit()) // 檢測是否有鍵盤輸入 
		key = getch();
	
	if(atk_cnt > -1) // atk_cnt  < 0 代表未進行攻擊 , 其他正整數則代表正在攻擊 
	{
		if(player.dir == 'd')
			atk(0);
		else
			atk(1);
	}
	else
	{
		switch (key)
		{
			case 97:  // 輸入 a 
				player.dir = 'a';
				player_walk(1);
				player.x -= speed;
				
				break;
			case 100: // 輸入 d
				player.dir = 'd';
				player_walk(0);
				player.x += speed;
				
				break;
			case 106: // 輸入 j 
				atk_cnt = 9;  
			default:
				break;
		}
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

void atk(int val)
{
	// 根據攻擊計數器以及面對的方向  
	// 儲存要輸出的圖片編號 
	int table[5] = {14, 12, 10, 8, 6};
	
	player.output_idx = table[atk_cnt / 2] + val;
	atk_cnt--;
}
