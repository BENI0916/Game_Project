#include "lib/var.h"
#include "lib/event.h"
#include "lib/output_img.h"
#include "lib/effect.h"

Monster monster;
extern int mazFight,fade;
extern Human player;
extern char BgName[];

void event() {
    int r = random(100);
    if (r<100) {
        PlaySound(TEXT("audio\\bgm\\battle.wav"),NULL,SND_LOOP|SND_ASYNC);
        choMon();
    }
}

void choMon() {
    int r = random(100);
    //雜燴兔
    if (r<100) {
        
    }

    mazFight = 1;
    player.x = 20;
	player.y = hih * 0.6;
    player.output_idx = 0;
	player.high = 66;
	player.width = 76;
    sprintf(BgName,"%s","images\\bg\\back_ground_01.png");
    loadBG(BgName);
    flashOut();
    fade = 1;
}