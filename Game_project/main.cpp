#include "lib/var.h"
#include "lib/game_start.h"

int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, enemy_num;
double start, end;
// key : ��L��J���x�s��m
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ� 

Human player;
Monster enemy[2];
Bullet skill[2];
Animate loading_animate;

int main(void)
{
	//�}�l�B��
	gameStart();

	return 0;
}

//                                 |~~~~~~~|
//                                 |       |
//                                 |       |
//                                 |       |
//                                 |       |
//                                 |       |
//      |~.\\\_\~~~~~~~~~~~~~~xx~~~         ~~~~~~~~~~~~~~~~~~~~~/_//;~|
//      |  \  o \_         ,XXXXX),                         _..-~ o /  |
//      |    ~~\  ~-.     XXXXX`)))),                 _.--~~   .-~~~   |
//       ~~~~~~~`\   ~\~~~XXX' _/ ';))     |~~~~~~..-~     _.-~ ~~~~~~~
//                `\   ~~--`_\~\, ;;;\)__.---.~~~      _.-~
//                  ~-.       `:;;/;; \          _..-~~
//                     ~-._      `''        /-~-~
//                         `\              /  /
//                           |         ,   | |
//                            |  '        /  |
//                             \/;          |
//                              ;;          |
//                              `;   .       |
//                              |~~~-----.....|
//                             | \             \
//                            | /\~~--...__    |
//                            (|  `\       __-\|
//                            ||    \_   /~    |
//                            |)     \~-'      |
//                             |      | \      '
//                             |      |  \    :
//                              \     |  |    |
//                               |    )  (    )
//                                \  /;  /\  |
//                                |    |/   |
//                                |    |   |
//                                 \  .'  ||
//                                 |  |  | |
//                                 (  | |  |
//                                 |   \ \ |
//                                 || o `.)|
//                                 |`\\\\) |
//                                 |       |
//                                 |       |
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//                      �C�q�O��                �õL BUG
