#include "lib/var.h"
#include "lib/enemy_move3D.h"
#include "lib/status.h"
#include "lib/event.h"

extern Monster monster;
extern Human player;
int cnt;

void enemyMove(int idx) {
    if (idx==1) {   //雜燴兔
        if (monster.x>player.x&&monster.x-player.x<=176&&player.dir=='d') {
            monster.dir='a';
            monster.x -= 20;
        } 
        else if (monster.x>player.x) {
            monster.dir='d';
            if (monster.x<1179) {
                monster.x += 10;
            }
        }
        else if (monster.x<=player.x&&player.x-monster.x<=201&&player.dir=='a') {
            monster.dir='d';
            monster.x += 20;
        } 
        else if (monster.x<=player.x) {
            monster.dir='a';
            if (monster.x>0) {
                monster.x -= 10;
            }
        }
        cnt++;
        if (monster.dir=='d') {
            if (cnt/10) {
                monster.output_idx = 2;
                cnt = 0;
            }
            else if (cnt/5) {
                monster.output_idx = 3;
            }
        }
        else {
            if (cnt/10) {
                monster.output_idx = 0;
                cnt = 0;
            }
            else if (cnt/5) {
                monster.output_idx = 1;
            }
        }
        if (monster.hp<=0) leaveFight();
    }
}

void putEnemy(int idx) {
    enemyMove(idx);
    putimage_withalpha(NULL,monster.enemy_img[monster.output_idx],monster.x,monster.y);
    monBlood(monster.hp,monster.fhp);
}