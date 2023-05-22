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
extern int enemy_atk_type, enemy_num, inFight, bgX, bgY, win_screen_cnt,inMaz,atk_cd,player_walk_cnt,player_jump_cnt,dash_cnt,atk_cnt;
extern Human player;
extern Monster enemy[3];
extern Animate loading_animate;
extern double end;
extern char BgName[];

int esc,fade,metEvent,victory,inBp,fOn;
PIMAGE escBG,screen,pauseImg,bgF,victoryUI,dropImg[bpL],gray,bpImg[3],gameover,fbt,swordImg[3],potionImg[2];

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
	gameover = newimage();
	fbt = newimage();
	getimage(escBG,"images\\bg\\black.png",0,0);
	getimage(pauseImg,"images\\menu\\pause.png",0,0);
	getimage(victoryUI,"images\\menu\\victoryUI.png",0,0);
	getimage(gray,"images\\menu\\bk.png",0,0);
	getimage(gameover,"images\\bg\\gameover.png",0,0);
	getimage(fbt,"images\\menu\\F.png",0,0);

	mciSendString (TEXT("open audio\\bgm\\home.mp3 alias homemusic"), NULL,0,NULL);
	mciSendString (TEXT("play homemusic repeat"), NULL,0,NULL);
	flushkey();
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run() && enemy_num < 3; delay_fps(60))
	{
		cleardevice(); // 把輸出的窗口清空 

		if (player.hp<=0) {
			if (inFight) {
				inFight=0;
				atk_cd = 4;
				enemy[enemy_num].hp = enemy[enemy_num].fhp;
				enemy[enemy_num].x = 900;
				enemy[enemy_num].output_idx = 1;
				enemy[enemy_num].dir = 'a';
				enemy[0].y = hih * 0.6 - 165 + 66;
				enemy[1].y = hih * 0.6 - 150 + 66;
				enemy[2].y = hih * 0.6 - 400 + 66;
				enemy_atk_type = -1;
			}
			else {
				mciSendString (TEXT("stop battlemusic"), NULL,0,NULL);
        		mciSendString (TEXT("close battlemusic"), NULL,0,NULL);
				delimage(bgF);
    			metEvent = 0;
				inMaz=0;
			}
			mciSendString (TEXT("open audio\\bgm\\gameover.mp3 alias gameover"), NULL,0,NULL);
	    	mciSendString (TEXT("play gameover"), NULL,0,NULL);
			putimage(0,0,screen);
			for (int i = 0;i<32;delay_fps(30)) {
				putimage_alphablend(NULL,gameover,0,0,0x18,0,0,wid,hih);
				i++;
			}
            player.x = (wid-28*3.5) / 2;
			player.y = (hih-33*3.5) / 2 + 80;
            player.output_idx = 27;// 輸出圖片編號 
	        player.high = 28*3.5;   // 人物圖片的高 
			player.width = 33*3.5;  // 人物圖片的寬
			player.atk_type = 0;
			player_walk_cnt = 11;
			player_jump_cnt = -1;
			atk_cnt = -1;
			dash_cnt = 0;
			sprintf(BgName,"%s","images\\bg\\home2.png");
            bgX=20;
            bgY=-20;
			loadBG(BgName,1587/2,1300/2);
    		flushkey();
    		flushmouse();
			victory = -1;
			player.hp = player.fhp;
		}
		else if (inBp) {
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
			if (victory==-1) {
				putimage(0,0,gameover);
				goListener();
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
				if(fOn) putimage(720,430,fbt);
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
