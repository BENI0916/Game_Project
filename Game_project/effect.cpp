#include "lib/var.h"
#include "lib/effect.h"

extern PIMAGE screen;

int fadeIn() {
    cleardevice();
    for (int i = 0;i<16;delay_fps(30)) {
		putimage_alphablend(NULL,screen,0,0,0x30,0,0,wid,hih);
		i++;
	}
    flushkey();
    flushmouse();
    return 0;
}

int fadeOut() {
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    putimage(0,0,screen);
    for (int i = 0;i<16;delay_fps(30)) {
		putimage_alphablend(NULL,blk,0,0,0x30,0,0,wid,hih);
		i++;
	}
    delimage(blk);
    flushkey();
    flushmouse();
    return 0;
}

int flashOut() {
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    for (int j = 0;j<2;j++) {
        putimage(0,0,screen);
        for (int i = 0;i<8;delay_fps(30)) {
		    putimage_alphablend(NULL,blk,0,0,0x60,0,0,wid,hih);
		    i++;
	    }
        cleardevice();
        for (int i = 0;i<8;delay_fps(30)) {
		    putimage_alphablend(NULL,screen,0,0,0x60,0,0,wid,hih);
		    i++;
	    }
    }
    fadeOut();
    delimage(blk);
    flushkey();
    flushmouse();
    return 0;
}