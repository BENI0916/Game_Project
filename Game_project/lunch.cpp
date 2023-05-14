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
#include "lib/enemy_move3D.h"
#include "lib/event.h"
#include "lib/bebao.h"

extern PIMAGE bg, dropImg[bpL], win_screen;
extern int enemy_atk_type, enemy_num, inFight, bgX, bgY, win_screen_cnt;
extern Human player;
extern Monster enemy[3];
extern Animate loading_animate;
extern double end;

int esc,fade,metEvent,victory,inBp;
PIMAGE escBG,screen,pauseImg,bgF,victoryUI,dropImg[bpL],gray,bpImg[3];

void lunch()
{
	initialization();
	printf("initialization succes\n"); 
	randomize();
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	setfont(16,0,"number");
	settextjustify(1,1);

	inBp = 0;
	inFight = 0;
	esc = 0;
	fade = 1;
	metEvent = 0;
	victory = 0;
	escBG = newimage();
	screen = newimage();
	pauseImg = newimage();
	victoryUI = newimage();
	gray = newimage();
	getimage(escBG,"images\\bg\\black.png",0,0);
	getimage(pauseImg,"images\\menu\\pause.png",0,0);
	getimage(victoryUI,"images\\menu\\victoryUI.png",0,0);
	getimage(gray,"images\\menu\\bk.png",0,0);
	
	mciSendString (TEXT("open audio\\bgm\\home.mp3 alias homemusic"), NULL,0,NULL);
	mciSendString (TEXT("play homemusic repeat"), NULL,0,NULL);
	flushkey();
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run() && player.hp > 0 && enemy_num < 3; delay_fps(60))
	{
		cleardevice(); // 把輸出的窗口清空 

		if (inBp) {
			bpScreen();
			bpListener();
		}
		else if (victory) {
			if (victory==1) {
				putimage(0,0,screen);
				putimage_withalpha(NULL,victoryUI,0,0);
				putDrop();
				vicListener();
			}
		}
		else if (esc) {
			escListener();
			escScreen();
		}
		else {
			if (inFight) 
			{//判斷是否在戰鬥中
				if(enemy[enemy_num].hp > 0) // 若敵人血量不為 0 則會行動 
				{
					if(enemy_atk_type == -1) // -1 代表 敵人未開始攻擊  
						enemy_move();		 // 則敵人會開始移動 
					enemy_atk();			 // 否則會進行攻擊  
				}
		
				move(5);
				output_image();

				if (enemy_num >= 3)
				{
					inFight = 0;
				}
				
			}
			else if (!metEvent){
				keyListener();
				putimage(abs(wid-getwidth(bg))/2 + bgX, abs(hih-getheight(bg))/2 + bgY, bg);
				putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
				putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
			}
			if (metEvent) {
				if (metEvent<10) {
					move(5);
					putimage(0,0,bgF);
					putEnemy(metEvent);
					if (victory==0) {
						putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
						putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
						playerBlood(player.hp,player.fhp);
					}
				}
			}
			getimage(screen,0,0,wid,hih);
			if (fade) {
				fade = fadeIn();
			}
		}
	}
}