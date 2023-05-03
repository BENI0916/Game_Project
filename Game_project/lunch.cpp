#include "lib/lunch.h"
#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_img.h"
#include "lib/player_move3D.h"
#include "lib/esc.h"
#include "lib/effect.h"
#include "lib/status.h"

extern PIMAGE bg;
extern int enemy_atk_type, enemy_num, inFight, bgX, bgY;
extern Human player;
extern Monster enemy[3];
extern Animate loading_animate;
extern double end;

int esc,fade,mazFight;
PIMAGE escBG;
PIMAGE screen;
PIMAGE pauseImg;

void lunch()
{
	initialization();
	printf("initialization succes\n"); 
	randomize();
	inFight = 0;
	esc = 0;
	fade = 1;
	mazFight = 0;
	escBG = newimage();
	screen = newimage();
	pauseImg = newimage();
	getimage(escBG,"images\\bg\\black.png",0,0);
	getimage(pauseImg,"images\\menu\\pause.png",0,0);
	
	PlaySound(TEXT("audio\\bgm\\home.wav"),NULL,SND_LOOP | SND_ASYNC);

	flushkey();
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run() && player.hp > 0 && enemy_num < 3; delay_fps(60))
	{
		cleardevice(); // 把輸出的窗口清空 

		if (esc) {
			escListener();
			escScreen();
		}
		else {
			if (inFight) {//判斷是否在戰鬥中
				if(enemy[enemy_num].hp > 0) // 若敵人血量不為 0 則會行動 
				{
					if(enemy_atk_type == -1) // -1 代表 敵人未開始攻擊  
						enemy_move();		 // 則敵人會開始移動 
					enemy_atk();			 // 否則會進行攻擊  
				}
		
				move(5);
				output_image();
			}
			else if (!mazFight){
				keyListener();
				putimage(abs(wid-getwidth(bg))/2 + bgX, abs(hih-getheight(bg))/2 + bgY, bg);
				putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
				putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
			}
			if (mazFight) {
				move(5);
				putimage(0,0,bg);
				putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
				putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
				playerBlood(player.hp,player.fhp);
			}
			getimage(screen,0,0,wid,hih);
			if (fade) {
				fade = fadeIn();
			}
		}
	}
}

