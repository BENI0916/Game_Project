#include "lib/var.h"
#include "lib/esc.h"
#include "lib/setting.h"
#include "lib/status.h"
#include "lib/event.h"

extern int key;
extern int esc,victory;
extern PIMAGE screen,escBG;
extern LOGFONT title,text;
extern Human player;
extern PIMAGE pauseImg,SetImg;

int mX,mY;

void escScreen() {
    putimage(0, 0, screen);
    putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
    putimage_withalpha(NULL,pauseImg,593,300);
    putimage_withalpha(NULL,SetImg,1170,35);
    playerBlood(player.hp,player.fhp);
}

void escListener() {
    if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
        if (key == key_esc) {
            key = 0;
            esc = 0;
        }
    }
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