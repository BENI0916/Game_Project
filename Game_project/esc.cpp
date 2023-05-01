#include "lib/var.h"
#include "lib/esc.h"

extern int key;
extern int esc,lock;
extern PIMAGE screen;
extern LOGFONT title,text;
extern Human player;
extern PIMAGE pauseImg,SetImg;

int mX,mY;

void escScreen() {
    putimage(0, 0, screen);
    putimage_withalpha(NULL,pauseImg,593,300);
    putimage_withalpha(NULL,SetImg,1170,35);
}

void escListener() {
    if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
        if (key == key_esc) {
            key = 0;
            esc = 0;
            lock = 1;
        }
    }
    mousepos(&mX,&mY);
	if((mX >= 600 && mX <= 710) && (mY >= 320 && mY <= 410) && keystate(key_mouse_l)) {
        flushmouse();
        esc = 0;
        lock = 1;
	}
}