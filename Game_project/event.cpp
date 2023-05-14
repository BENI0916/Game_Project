#include "lib/var.h"
#include "lib/event.h"
#include "lib/output_img.h"
#include "lib/effect.h"
#include "lib/bebao.h"

Monster monster;
extern int fade,cnt,metEvent,bp[3][bpL];
extern Human player;
extern PIMAGE bgF,dropImg[],gray;
int type,dropIdx[bpL],dropAmount[bpL];

int event() {
    int r = random(150);
    if (r<1) {
        mciSendString (TEXT("open audio\\bgm\\battle.mp3 alias battlemusic"), NULL,0,NULL);
	    mciSendString (TEXT("play battlemusic"), NULL,0,NULL);
        return choMon();
    }
    return 0;
}

int choMon() {
    int r = random(100);

    player.x = 20;
	player.y = hih * 0.6;
    player.output_idx = 0;
	player.high = 66;
	player.width = 76;
    bgF = newimage(wid,hih);
    PIMAGE oriBG = newimage();
	getimage(oriBG, "images\\bg\\back_ground_01.png");
	putimage(bgF, 0, 0, wid, hih, oriBG, 0, 0, getwidth(oriBG), getheight(oriBG));
	delimage(oriBG);
    flashOut();
    fade = 1;
    cnt = 0;
    type = 0;
    for (int i = 0;i<bpL;i++) {
		dropAmount[i] = 0;
        dropIdx[i] = 0;
	}
    //雜燴兔
    if (r<100) {
        char s[100];
	    monster.enemy_img = NULL;
	    sprintf(s,"%s","images\\3D\\monster\\rabbit");
	    loadCHAR(s, &monster.enemy_img, 101, 66, 0);
        monster.x = 960;
        monster.y = 425;
        monster.hp = 20;
        monster.fhp = 20;
        monster.dir = 'd';
        monster.output_idx = 2;
        monster.width = 101;
        monster.high = 66;
        return 1;
    }
    return 0;
}

void leaveFight() {
    player.x = (wid-28*3.5) / 2;
	player.y = (hih-33*3.5) / 2 + 80;
    player.output_idx = 33;// 輸出圖片編號 
	player.high = 28*3.5;   // 人物圖片的高 
	player.width = 33*3.5;  // 人物圖片的寬
    delimage(bgF);
    metEvent = 0;
    fadeOut();
    fade = 1;
}

void drop(int idx) {
    if (idx==1) {
        dropAmount[0] = random(10)*100+100;
        dropAmount[1] = random(3);
        bp[0][0] += dropAmount[0];
        bp[0][1] += dropAmount[1];
        if ((dropAmount[1])&&(!bp[0][1]-dropAmount[1])) updateBp(0,1);
    }
}

void putDrop() {
    if (type==0) {
        for (int i = 0;i<bpL;i++) {
            if (dropAmount[i]) dropIdx[type++] = i;
        }
    }
    for (int i = 0;i<type;i++) {
        int y = 60*i+300;
        putimage_alphablend(NULL,gray,190,y-6,0x70,0,0,442,45);
        putimage_withalpha(NULL,dropImg[dropIdx[i]],226-getwidth(dropImg[dropIdx[i]])/2,y);
        xyprintf(411,y+getheight(dropImg[dropIdx[i]])/2,"%s",dropName[dropIdx[i]]);
        xyprintf(596,y+getheight(dropImg[dropIdx[i]])/2,"%d",dropAmount[dropIdx[i]]);
    }
}