#include "lib/lunch.h"
#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_img.h"

extern int enemy_atk_type, enemy_num;
extern Human player;
extern Monster enemy[2];
extern Animate loading_animate;

void lunch()
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
			{
				enemy_move();		 // �h�ĤH�|�}�l���� 
			}
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
			loading_animate.cnt = 0;
		}
	}
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
