#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp" 

int key, atk_cnt, player_walk_cnt;
// key : 鍵盤輸入的儲存位置
// left_walk_cnt, right_walk_cnt : 走路計數器 用於計算走路時輸出的圖片 

Human player = {.player_img=NULL,.player_msk=NULL};

void initialization();
void move(int speed);
void output_image();
void loadBG(char filename[]);

int main(void)
{
	initgraph(wid, hih);	// 初始化輸出窗口 
	initialization();
	
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run(); delay_fps(60))
	{
		cleardevice(); // 把輸出的窗口清空 
		move(3);
		output_image();
	}

	return 0;
}
