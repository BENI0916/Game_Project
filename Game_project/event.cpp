#include "lib/var.h"
#include "lib/event.h"
#include "lib/output_img.h"
#include "lib/effect.h"

Monster monster;
extern int fade,cnt,metEvent;
extern Human player;
extern PIMAGE bgF;

int event() {
    int r = random(400);
    if (r<1) {
        //PlaySound(TEXT("audio\\bgm\\battle.wav"),NULL,SND_LOOP|SND_ASYNC);
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
    //雜燴兔
    if (r<100) {
        char s[100];
	    monster.enemy_img = NULL;
	    sprintf(s,"%s","images\\3D\\monster\\rabbit");
	    loadCHAR(s, &monster.enemy_img, 101, 66, 0);
        monster.x = 960;
        monster.y = 425;
        monster.hp = 100;
        monster.fhp = 100;
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
    //PlaySound(NULL,NULL,0);
    mciSendString (TEXT("stop battlemusic"), NULL,0,NULL);
    mciSendString (TEXT("close battlemusic"), NULL,0,NULL);
    delimage(bgF);
    metEvent = 0;
}