#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 720 
#define wid 1280 
extern int key, left_walk_cnt, right_walk_cnt, atk_cnt;
extern struct human // 玩家的結構  
{
	int x;	// x 座標 
	int y;	// y 座標 
	int hp;	// 血量 
	char dir;// 人物面朝的方向 
	int output_idx; // 用於儲存要輸出的圖片編號 
	PIMAGE player_img[16], player_msk[16]; // 儲存放大後的圖片 
}player;

void walk_left(); // 往左走 
void walk_right();// 往右走 
void atk();// 攻擊 

void move(int speed)
{
	if (kbhit()) // 檢測是否有鍵盤輸入 
		key = getch();
	
	if(atk_cnt) // atk_cnt : 0 代表未進行攻擊 , 其他正整數則代表正在攻擊 
	{
		atk();
	}
	else
	{
		switch (key)
		{
			case 97:  // 輸入 a 
				walk_left();
				player.x -= speed;
				
				break;
			case 100: // 輸入 d
				walk_right();
				player.x += speed;
				
				break;
			case 106: // 輸入 j 
				atk_cnt = 10;  
			default:
				break;
		}
	}
	key = 0; // 執行動作後將 key歸 0, 避免一直重複動作 
}

void walk_left()
{
	// 若要移動的方向與玩家面對的方向不同 , 則先轉向
	// 否則根據走路計數器 儲存要輸出的圖片編號 
	if(player.dir != 'a')  
	{
		player.output_idx = 1;
		player.dir = 'a';
	}
	else if(left_walk_cnt < 3)
	{
		player.output_idx = 3;
		left_walk_cnt++;
	}
	else if(left_walk_cnt < 6)
	{
		player.output_idx = 1;
		left_walk_cnt++;
	}
	else if(left_walk_cnt < 9)
	{
		player.output_idx = 5;
		left_walk_cnt++;
	}
	else if(left_walk_cnt == 9)
	{
		player.output_idx = 1;
		left_walk_cnt = 0;
	}
}

void walk_right()
{
	// 若要移動的方向與玩家面對的方向不同 , 則先轉向
	// 否則根據走路計數器 儲存要輸出的圖片編號 
	if(player.dir != 'd')
	{
		player.output_idx = 0;
		player.dir = 'd';
	}
	else if(right_walk_cnt < 3)
	{
		player.output_idx = 2;
		right_walk_cnt++;
	}
	else if(right_walk_cnt < 6)
	{
		player.output_idx = 0;
		right_walk_cnt++;
	}
	else if(right_walk_cnt < 9)
	{
		player.output_idx = 4;
		right_walk_cnt++;
	}
	else if(right_walk_cnt == 9)
	{
		player.output_idx = 0;
		right_walk_cnt = 0;
	}
}

void atk()
{
	// 根據攻擊計數器以及面對的方向  
	// 儲存要輸出的圖片編號 
	if(atk_cnt > 8)
	{
		if(player.dir == 'd')
			player.output_idx = 6;
		else
			player.output_idx = 7;
	}
	else if(atk_cnt > 6)
	{
		if(player.dir == 'd')
			player.output_idx = 8;
		else
			player.output_idx = 9;
	}
	else if(atk_cnt > 4)	
	{
		if(player.dir == 'd')
			player.output_idx = 10;
		else
			player.output_idx = 11;
	}
	else if(atk_cnt > 2)
	{
		if(player.dir == 'd')
			player.output_idx = 12;
		else
			player.output_idx = 13;
	}
	else if(atk_cnt > 0)
	{
		if(player.dir == 'd')
			player.output_idx = 14;
		else
			player.output_idx = 15;
	}
	atk_cnt--;
}
