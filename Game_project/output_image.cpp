#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#define hih 720 
#define wid 1280 
extern PIMAGE new_bg;
extern struct human // ���a�����c  
{
	int x;	// x �y�� 
	int y;	// y �y�� 
	int hp;	// ��q 
	char dir;// �H�����ª���V 
	int output_idx; // �Ω��x�s�n��X���Ϥ��s�� 
	PIMAGE player_img[16], player_msk[16]; // �x�s��j�᪺�Ϥ� 
}player;

void output_image()
{
	// ��X�I�� 
	putimage(0, 0, new_bg);
	
	// ��X���a 
	putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
}
