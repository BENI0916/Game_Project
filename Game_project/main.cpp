#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_img.h"

int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir;
double start, end;
// key : ��L��J���x�s��m
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ� 

Human player;
Monster enemy;
Bullet skill[2];

int main(void)
{
	initgraph(wid, hih);	// ��l�ƿ�X���f 
	initialization();
	
	// is_run �˵��{�ǬO�_������������, ���쪺�ܷ|��^false, �Y�h�X�{�� 
	// delay_fps ����V�v, 60 ���"��������"��1000/60�@�� 
	for (; is_run() && player.hp > 0; delay_fps(60))
	{
		cleardevice(); // ���X�����f�M�� 
		
		if(enemy.hp > 0) // �Y�ĤH��q���� 0 �h�|��� 
		{
			if(enemy_atk_type == -1) // -1 �N�� �ĤH���}�l���� 
				enemy_move();		 // �h�ĤH�|�}�l���� 
			enemy_atk();			 // �_�h�|�i����� 
		}
		
		move(5);
		output_img();
	}

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