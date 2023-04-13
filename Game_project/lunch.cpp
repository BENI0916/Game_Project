#include "lib/var.h"
#include "lib/lunch.h"
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_img.h"

extern int enemy_atk_type, enemy_num;
extern Human player;
extern Monster enemy[2];
extern Animate loading_animate;

void lunch() {
	initialization();
	printf("initialization succes\n"); 
	
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run() && player.hp > 0 && enemy_num < 2; delay_fps(60))
	{
		cleardevice(); // 把輸出的窗口清空 
		
		if(enemy[enemy_num].hp > 0) // 若敵人血量不為 0 則會行動 
		{
			if(enemy_atk_type == -1) // -1 代表 敵人未開始攻擊 
				enemy_move();		 // 則敵人會開始移動 
			enemy_atk();			 // 否則會進行攻擊 
			//printf("enemy_atk_cnt = %d\n", enemy_atk_cnt);
		}
		else if(loading_animate.cnt == 72)
		{
			loading_animate.cnt = 0;
		}
		
		move(5);
		output_image();
		
		if(enemy[enemy_num].hp <= 0)
		{
			printf("active\n");
			enemy_num++;
		}
	}
}