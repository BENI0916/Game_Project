#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_image.h"

int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, enemy_num;
double start, end;
// key : 鍵盤輸入的儲存位置
// left_walk_cnt, right_walk_cnt : 走路計數器 用於計算走路時輸出的圖片 

Human player;
Monster enemy[2];
Bullet skill[2];
animate loading_animate;

int main(void)
{
	initgraph(wid, hih);	// 初始化輸出窗口 
	printf("inigraph succes\n");
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

	return 0;
}

//                                 |~~~~~~~|
//                                 |       |
//                                 |       |
//                                 |       |
//                                 |       |
//                                 |       |
//      |~.\\\_\~~~~~~~~~~~~~~xx~~~         ~~~~~~~~~~~~~~~~~~~~~/_//;~|
//      |  \  o \_         ,XXXXX),                         _..-~ o /  |
//      |    ~~\  ~-.     XXXXX`)))),                 _.--~~   .-~~~   |
//       ~~~~~~~`\   ~\~~~XXX' _/ ';))     |~~~~~~..-~     _.-~ ~~~~~~~
//                `\   ~~--`_\~\, ;;;\)__.---.~~~      _.-~
//                  ~-.       `:;;/;; \          _..-~~
//                     ~-._      `''        /-~-~
//                         `\              /  /
//                           |         ,   | |
//                            |  '        /  |
//                             \/;          |
//                              ;;          |
//                              `;   .       |
//                              |~~~-----.....|
//                             | \             \
//                            | /\~~--...__    |
//                            (|  `\       __-\|
//                            ||    \_   /~    |
//                            |)     \~-'      |
//                             |      | \      '
//                             |      |  \    :
//                              \     |  |    |
//                               |    )  (    )
//                                \  /;  /\  |
//                                |    |/   |
//                                |    |   |
//                                 \  .'  ||
//                                 |  |  | |
//                                 (  | |  |
//                                 |   \ \ |
//                                 || o `.)|
//                                 |`\\\\) |
//                                 |       |
//                                 |       |
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//                      耶穌保佑                永無 BUG
