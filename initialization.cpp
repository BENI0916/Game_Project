#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "var.cpp"
extern PIMAGE new_bg;
PIMAGE ori_bg;
// ori_bg : ��l�I��	new_bh : ��j�᪺�I�� 
extern int left_walk_cnt, right_walk_cnt, atk_cnt;
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ�

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
	
	left_walk_cnt = 0;
	right_walk_cnt = 0;
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
	
	getimage(player_ori_msk[0], "images\\main_char\\0_d_stand_msk.png");
	getimage(player_ori_img[0], "images\\main_char\\0_d_stand_img.png");
	
	getimage(player_ori_msk[1], "images\\main_char\\1_a_stand_msk.png");
	getimage(player_ori_img[1], "images\\main_char\\1_a_stand_img.png");
	
	getimage(player_ori_msk[2], "images\\main_char\\2_d_walk_1_msk.png");
	getimage(player_ori_img[2], "images\\main_char\\2_d_walk_1_img.png");
	
	getimage(player_ori_msk[3], "images\\main_char\\3_a_walk_1_msk.png");
	getimage(player_ori_img[3], "images\\main_char\\3_a_walk_1_img.png");
	
	getimage(player_ori_msk[4], "images\\main_char\\4_d_walk_2_msk.png");
	getimage(player_ori_img[4], "images\\main_char\\4_d_walk_2_img.png");
	
	getimage(player_ori_msk[5], "images\\main_char\\5_a_walk_2_msk.png");
	getimage(player_ori_img[5], "images\\main_char\\5_a_walk_2_img.png");
	
	getimage(player_ori_msk[6], "images\\main_char\\6_d_atk_1_msk.png");
	getimage(player_ori_img[6], "images\\main_char\\6_d_atk_1_img.png");
	
	getimage(player_ori_msk[7], "images\\main_char\\7_a_atk_1_msk.png");
	getimage(player_ori_img[7], "images\\main_char\\7_a_atk_1_img.png");
	
	getimage(player_ori_msk[8], "images\\main_char\\8_d_atk_2_msk.png");
	getimage(player_ori_img[8], "images\\main_char\\8_d_atk_2_img.png");
	
	getimage(player_ori_msk[9], "images\\main_char\\9_a_atk_2_msk.png");
	getimage(player_ori_img[9], "images\\main_char\\9_a_atk_2_img.png");
	
	getimage(player_ori_msk[10], "images\\main_char\\10_d_atk_3_msk.png");
	getimage(player_ori_img[10], "images\\main_char\\10_d_atk_3_img.png");
	
	getimage(player_ori_msk[11], "images\\main_char\\11_a_atk_3_msk.png");
	getimage(player_ori_img[11], "images\\main_char\\11_a_atk_3_img.png");
	
	getimage(player_ori_msk[12], "images\\main_char\\12_d_atk_4_msk.png");
	getimage(player_ori_img[12], "images\\main_char\\12_d_atk_4_img.png");
	
	getimage(player_ori_msk[13], "images\\main_char\\13_a_atk_4_msk.png");
	getimage(player_ori_img[13], "images\\main_char\\13_a_atk_4_img.png");
	
	getimage(player_ori_msk[14], "images\\main_char\\14_d_atk_5_msk.png");
	getimage(player_ori_img[14], "images\\main_char\\14_d_atk_5_img.png");
	
	getimage(player_ori_msk[15], "images\\main_char\\15_a_atk_5_msk.png");
	getimage(player_ori_img[15], "images\\main_char\\15_a_atk_5_img.png");
	
	// �N���J�᪺�Ϥ��i���Y�� 
	putimage(new_bg, 0, 0, wid, hih, ori_bg, 0, 0, 1000, 740);
	
	for(int i = 0; i < 16; i++)
	{	
		putimage(player.player_msk[i], 0, 0, 76, 66, player_ori_msk[i], 0, 0, 38, 33);
		putimage(player.player_img[i], 0, 0, 76, 66, player_ori_img[i], 0, 0, 38, 33);
	}
	
}
