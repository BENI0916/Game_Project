#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 720  // �� 
#define wid 1280 // �e 
PIMAGE new_bg = newimage(wid, hih);
// new_bh : ��j�᪺�I�� 
int key, left_walk_cnt, right_walk_cnt, atk_cnt;
// key : ��L��J���x�s��m
// left_walk_cnt, right_walk_cnt : �����p�ƾ� �Ω�p�⨫���ɿ�X���Ϥ� 

struct human // ���a�����c 
{
	int x;	// x �y�� 
	int y;	// y �y�� 
	int hp;	// ��q 
	char dir;// �H�����ª���V 
	int output_idx; // �Ω��x�s�n��X���Ϥ��s�� 
	PIMAGE player_img[16], player_msk[16]; // �x�s�Ϥ� 
}player;

void initialization();  // ��l�� 
void move(int speed);	// ���a���� speed: ���ʤ@�����Z��  
void output_image();	// ��X�Ϥ� 


int main(void)
{
	initgraph(wid, hih);	// ��l�ƿ�X���f 
	initialization();
	
	// is_run �˵��{�ǬO�_������������, ���쪺�ܷ|��^false, �Y�h�X�{�� 
	// delay_fps ����V�v, 60 ���"��������"��1000/60�@�� 
	for (; is_run(); delay_fps(60))
	{
		cleardevice(); // ���X�����f�M�� 
		move(3); 
		output_image();  
	}

	return 0;
}
