#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 720  // 高 
#define wid 1280 // 寬 
PIMAGE new_bg = newimage(wid, hih);
// new_bh : 放大後的背景 
int key, left_walk_cnt, right_walk_cnt, atk_cnt;
// key : 鍵盤輸入的儲存位置
// left_walk_cnt, right_walk_cnt : 走路計數器 用於計算走路時輸出的圖片 

struct human // 玩家的結構 
{
	int x;	// x 座標 
	int y;	// y 座標 
	int hp;	// 血量 
	char dir;// 人物面朝的方向 
	int output_idx; // 用於儲存要輸出的圖片編號 
	PIMAGE player_img[16], player_msk[16]; // 儲存圖片 
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
		cleardevice(); // 把輸出的窗口清空 
		move(3); 
		output_image();  
	}

	return 0;
}
