#include "lib/var.h"
#include "lib/esc.h"

extern int key;
extern int esc,lock;
extern PIMAGE screen;
extern LOGFONT title,text;
extern Human player;

void escScreen() {
    putimage(0, 0, screen);
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
}