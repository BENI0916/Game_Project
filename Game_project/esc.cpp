#include "lib/var.h"
#include "lib/esc.h"
#include "lib/setting.h"
#include "lib/status.h"
#include "lib/event.h"
#include "lib/effect.h"

extern int key,esc,victory,fade,inHelp,mX,mY,folder;
extern PIMAGE screen,escBG,pauseImg,SetImg,helpImg,keyHelp,FolderImg;
extern Human player;


void escScreen() {
    putimage(0, 0, screen);
    putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
    putimage_withalpha(NULL,pauseImg,593,300);
    putimage_withalpha(NULL,SetImg,1170,35);
    putimage_withalpha(NULL,helpImg,1070,35);
    putimage_withalpha(NULL,FolderImg,1170,580);
    playerBlood(player.hp,player.fhp);
    putMoney();
}

void escListener() {
    if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
        if (key == key_esc) {
            key = 0;
            esc = 0;
            inHelp = 0;
        }
    }
    if (!inHelp) {
        mousepos(&mX,&mY);
	    if((mX >= 600 && mX <= 710) && (mY >= 320 && mY <= 410) && keystate(key_mouse_l)) {
            //結束esc
            flushmouse();
            esc = 0;
	    }
        if((mX >= 1177 && mX <= 1229) && (mY >= 46 && mY <= 86) && keystate(key_mouse_l)) {
		    //點擊設定
		    setting();
	    }
        if((mX >= 1070 && mX <= 1140) && (mY >= 35 && mY <= 105) && keystate(key_mouse_l)) {
		    //點擊幫助
		    inHelp = 1;
	    }
	    if((mX >= 1176 && mX <= 1238) && (mY >= 595 && mY <= 638) && keystate(key_mouse_l))
		{
			//點擊資料夾
			for(;is_run();delay_fps(60)){
				if(keystate(key_mouse_l) == 0) break;
			}
			flushmouse();
			folder = 1;
		}
    }
}

void vicListener() {
    mousepos(&mX,&mY);
	if((mX >= 1000 && mX <= 1187) && (mY >= 649 && mY <= 702) && keystate(key_mouse_l)) {
        //結束勝利UI
        flushmouse();
        victory = 0;
        leaveFight();
	}
}

void goListener() {
    mousepos(&mX,&mY);
	if((mX >= 511 && mX <= 767) && (mY >= 432 && mY <= 478) && keystate(key_mouse_l)) {
        //結束勝利UI
        flushmouse();
        victory = 0;
        mciSendString (TEXT("stop gameover"), NULL,0,NULL);
        mciSendString (TEXT("close gameover"), NULL,0,NULL);
        getimage(screen,0,0,wid,hih);
        fadeOut();
        fade = 1;
        mciSendString (TEXT("open audio\\bgm\\home.mp3 alias homemusic"), NULL,0,NULL);
	    mciSendString (TEXT("play homemusic repeat"), NULL,0,NULL);
	}
}