#include "lib/var.h"
#include "lib/bebao.h"
#include "lib/status.h"

int bp[3][bpL],bpIdx[3][bpL],bpAmount[3];
extern int key,inBp;
extern PIMAGE screen,bpImg[],escBG,gray,dropImg[];
extern Human player;

int extern mX,mY;

void bpScreen() {
    putimage(0, 0, screen);
    putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
    putimage_withalpha(NULL,bpImg[inBp-1],0,0);
    putBpItem(inBp-1);
    playerBlood(player.hp,player.fhp);
    putMoney();
}

void bpListener() {
    if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
        if (key == 101||key_esc) {
            key = 0;
            inBp = 0;
        }
    }
    mousepos(&mX,&mY);
	if((mX >= 1144 && mX <= 1263) && (mY >= 141 && mY <= 250) && keystate(key_mouse_l)) {
        //第一層背包
        flushmouse();
        inBp = 1;
	}
    if((mX >= 1144 && mX <= 1263) && (mY >= 251 && mY <= 361) && keystate(key_mouse_l)) {
        //第二層背包
        flushmouse();
        inBp = 2;
	}
    if((mX >= 1144 && mX <= 1263) && (mY >= 362 && mY <= 473) && keystate(key_mouse_l)) {
        //第三層背包
        flushmouse();
        inBp = 3;
	}
}

void updateBp(int type,int idx) {
    printf("%d ",bpAmount[type]);
    bpIdx[type][bpAmount[type]++] = idx;
    printf("%d ",bpAmount[type]);
    for (int i = 0;i<bpAmount[type]-1;i++) {
        for (int j = 0;j<bpAmount[type]-1-i;j++) {
            if (bpIdx[type][j]>bpIdx[type][j+1]) {
                int tem = bpIdx[type][j];
                bpIdx[type][j] = bpIdx[type][j+1];
                bpIdx[type][j+1] = tem;
            }
        }
    }
    printf("%d\n",bpAmount[type]);
}

void putBpItem(int idx) {
    for (int i = 0;i<bpAmount[idx];i++) {
        int x,y;
        i > 4 ? x = 477 : x = 0;
        i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
        putimage_alphablend(NULL,gray,180+x,y-6,0x70,0,0,442,45);
        putimage_withalpha(NULL,dropImg[bpIdx[idx][i]],216+x-getwidth(dropImg[bpIdx[idx][i]])/2,y);
        xyprintf(401+x,y+getheight(dropImg[bpIdx[idx][i]])/2,"%s",dropName[bpIdx[idx][i]]);
        xyprintf(586+x,y+getheight(dropImg[bpIdx[idx][i]])/2,"%d",bp[idx][bpIdx[idx][i]]);
    }
}