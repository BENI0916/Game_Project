#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 480
#define wid 640
PIMAGE ori_bg = newimage(), new_bg = newimage(wid, hih);
int k, left_walk_cnt, right_walk_cnt, atk_cnt;
struct human
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

void initialization();  // 初始化 
void move(int speed);	// 玩家移動 speed: 移動一次的距離  
void output_image();	// 輸出圖片 


int main(void)
{
	initgraph(wid, hih);	// 初始化輸出窗口 
	initialization();
	
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run(); delay_fps(60))
	{
		cleardevice();
		move(4);
		output_image();
	}

	return 0;
}
