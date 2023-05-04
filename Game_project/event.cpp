#include "lib/var.h"
#include "lib/event.h"
#include "lib/output_img.h"
#include "lib/effect.h"

Monster monster;
extern int fade,cnt;
extern Human player;
extern char BgName[];

int event() {
    int r = random(100);
    if (r<100) {
        PlaySound(TEXT("audio\\bgm\\battle.wav"),NULL,SND_LOOP|SND_ASYNC);
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
    sprintf(BgName,"%s","images\\bg\\back_ground_01.png");
    loadBG(BgName);
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