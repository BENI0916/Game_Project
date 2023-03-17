#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 480
#define wid 640
extern int k, left_walk_cnt, right_walk_cnt, atk_cnt;
extern struct human
{
	int x;
	int y;
	int std_x;
	int std_y;
	int atk_x;
	int atk_y;
	int hp;
	char dir;
	int output_idx;
	PIMAGE player_origin_img[12], player_origin_mask[12];
	PIMAGE player_new_img[12], player_new_mask[12];
}player;

void walk_left();
void walk_right();
void atk();

void move(int speed)
{
	if (kbhit()) 
		k = getch();
	
	if(atk_cnt)
	{
		if(atk_cnt == 10)
			player.atk_x = player.std_y - 5;
		
		atk();
		
		player.y = player.atk_y;
	}
	else
	{
		//player.std_x = player.atk_x + 2;
		player.std_y = player.atk_y + 5;
		//player.x = player.std_x;
		player.y = player.std_y;
		
		switch (k)
		{
			case 97:
				walk_left();
				player.x -= speed;
				player.std_x = player.x;
				
				break;
			case 100:
				walk_right();
				player.x += speed;
				player.std_x = player.x;
				
				break;
			case 106:
				atk_cnt = 10;
			default:
				break;
		}
	}
	k = 0;
}

void walk_left()
{
	if(player.dir != 'a')
	{
		player.output_idx = 1;
		player.dir = 'a';
	}
	else if(left_walk_cnt < 2)
	{
		player.output_idx = 2;
		left_walk_cnt++;
	}
	else if(left_walk_cnt < 4)
	{
		player.output_idx = 1;
		left_walk_cnt++;
	}
	else if(left_walk_cnt < 6)
	{
		player.output_idx = 4;
		left_walk_cnt++;
	}
	else if(left_walk_cnt == 6)
	{
		player.output_idx = 1;
		left_walk_cnt = 0;
	}
}

void walk_right()
{
	if(player.dir != 'd')
	{
		player.output_idx = 0;
		player.dir = 'd';
	}
	else if(right_walk_cnt < 2)
	{
		player.output_idx = 3;
		right_walk_cnt++;
	}
	else if(right_walk_cnt < 4)
	{
		player.output_idx = 0;
		right_walk_cnt++;
	}
	else if(right_walk_cnt < 6)
	{
		player.output_idx = 5;
		right_walk_cnt++;
	}
	else if(right_walk_cnt == 6)
	{
		player.output_idx = 0;
		right_walk_cnt = 0;
	}
}

void atk()
{
	if(atk_cnt > 7)
	{
		if(player.dir == 'a')
			player.output_idx = 6;
		else
			player.output_idx = 9;
	}
	else if(atk_cnt > 4)
	{
		if(player.dir == 'a')
			player.output_idx = 7;
		else
			player.output_idx = 10;
	}
	else if(atk_cnt > 1)	
	{
		if(player.dir == 'a')
			player.output_idx = 8;
		else
			player.output_idx = 11;
	}
	else
	{
		if(player.dir == 'a')
			player.output_idx = 1;
		else
			player.output_idx = 0;
	}
	
	atk_cnt--;
}
