#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 480
#define wid 640
PIMAGE ori_bg = newimage(), new_bg = newimage(wid, hih);
int k, left_walk_cnt, right_walk_cnt;
struct human
{
	int x;
	int y;
	int hp;
	char dir;
	int output_idx;
	PIMAGE player_origin_img[6], player_origin_mask[6];
	PIMAGE player_new_img[6], player_new_mask[6];
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
		cleardevice();
		move(4);
		output_image();
	}

	return 0;
}
