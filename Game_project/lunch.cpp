#include "lib/lunch.h"
#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_img.h"
#include "lib/player_move3D.h"

extern PIMAGE bg;
extern int enemy_atk_type, enemy_num, inFight, bgX, bgY;
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

		if (inFight) {//�P�_�O�_�b�԰���
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
		else {
			
			keyListener();
			putimage(abs(wid-getwidth(bg))/2 + bgX, abs(hih-getheight(bg))/2 + bgY, bg);
			putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
			putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
		}
		/*if(enemy[enemy_num].hp > 0) // �Y�ĤH��q���� 0 �h�|��� 
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
		}*/
	}
}

