#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#define hih 480
#define wid 640
PIMAGE ori_bg = newimage(), new_bg = newimage(wid, hih);
PIMAGE player_origin_img = newimage(), player_origin_mask = newimage();
PIMAGE player_new_img = newimage(28, 52), player_new_mask = newimage(28, 52);
int k;
struct human
{
	int x;
	int y;
	int hp;
}player;

void initialization(struct human *);
//void output_image(struct human*);

void move(int speed)
{
	if (kbhit()) 
		k = getch();
	switch (k)
	{
	case 97:
		player.x -= speed;
		break;
	case 100:
		player.x += speed;
		break;
	default:
		break;
	}
	k = 0;
}
void output_image(struct human*);


int main(void)
{
	initgraph(wid, hih);
	initialization(&player);
	
	//output_image(&player);
	
	// is_run �˴��{�ǬO�_�������������A���쪺�ܷ|��^false�A�Y���Ӱh�X�{��
	// delay_fps ����V�v�A60��ܡ��������ɡ���1000/60�@��
	for (; is_run(); delay_fps(60))
	{
		cleardevice();
		move(3);
		output_image(&player);
	}

	return 0;
}