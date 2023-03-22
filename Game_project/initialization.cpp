#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "var.cpp" 
extern PIMAGE new_bg;
PIMAGE ori_bg;
// ori_bg : ��l�I��	new_bg : ��j�᪺�I�� 
extern int atk_cnt, player_walk_cnt;
// player_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�

extern Human player;

PIMAGE player_ori_img[16], player_ori_msk[16];
// ��l�Ϥ� 

void loading(); // ���J�Ϥ� 

void initialization()
{
	ori_bg = newimage();
	
	for(int i = 0; i < 16; i++)
	{
		player_ori_img[i] = newimage(); // �ЫعϤ� 
		player_ori_msk[i] = newimage();
		
		player.player_img[i] = newimage(76, 66); // �Ы� 76 * 66 �j�p���Ϥ� 
		player.player_msk[i] = newimage(76, 66);
	}
	
	loading(); // ���J�Ϥ�
	// �]�w��l�� 
	player.x = wid / 2; // �ȩw 
	player.y = hih / 2; // �ȩw
	player.hp = 5;
	player.dir = 'd';
	player.output_idx = 0;
	
	player_walk_cnt = 11;
	atk_cnt = 0;
	
	// �Y��᪺�Ϥ��x�s�b��L��m��
	// �N�쥻���Ϥ��R�� 
	delimage(ori_bg);
	
	for(int i = 0; i < 16; i++)
	{
		delimage(player_ori_img[i]);
		delimage(player_ori_msk[i]);
	}
}

void loading() // ���J�Ϥ� 
{
	getimage(ori_bg, "images\\back_ground_01.png");
	
	char img[100];
	char msk[100];
	
	for(int i = 0; i < 16; i++)
	{
		sprintf(img, "images\\main_char\\img_%d.png", i);
		sprintf(msk, "images\\main_char\\msk_%d.png", i);
		
		getimage(player_ori_img[i], img);
		getimage(player_ori_msk[i], msk);
	}
	
	// �N���J�᪺�Ϥ��i���Y�� 
	putimage(new_bg, 0, 0, wid, hih, ori_bg, 0, 0, 1000, 740);
	
	for(int i = 0; i < 16; i++)
	{	
		putimage(player.player_msk[i], 0, 0, 76, 66, player_ori_msk[i], 0, 0, 38, 33);
		putimage(player.player_img[i], 0, 0, 76, 66, player_ori_img[i], 0, 0, 38, 33);
	}
	
}
