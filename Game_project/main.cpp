#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_image.h"

int key, atk_cnt, player_walk_cnt, player_jump_cnt, last_key, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, enemy_num;
double start, end;
// key : ��L��J���x�s��m
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ� 

Human player;
Monster enemy[2];
Bullet skill[2];
animate loading_animate;

int main(void)
{
	initgraph(wid, hih);	// ��l�ƿ�X���f 
	printf("inigraph succes\n");
	initialization();
	printf("initialization succes\n"); 
	
	// is_run �˵��{�ǬO�_������������, ���쪺�ܷ|��^false, �Y�h�X�{�� 
	// delay_fps ����V�v, 60 ���"��������"��1000/60�@�� 
	for (; is_run() && player.hp > 0 && enemy_num < 2; delay_fps(60))
	{
		cleardevice(); // ���X�����f�M�� 
		
		if(enemy[enemy_num].hp > 0) // �Y�ĤH��q���� 0 �h�|��� 
		{
			if(enemy_atk_type == -1) // -1 �N�� �ĤH���}�l���� 
				enemy_move();		 // �h�ĤH�|�}�l���� 
			enemy_atk();			 // �_�h�|�i����� 
			//printf("enemy_atk_cnt = %d\n", enemy_atk_cnt);
		}
		else if(loading_animate.cnt == 72)
		{
			loading_animate.cnt = 0;
		}
		
		move(5);
		output_image();
		
		if(enemy[enemy_num].hp <= 0)
		{
			printf("active\n");
			enemy_num++;
		}
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
