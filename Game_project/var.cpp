//�����`���x�s��
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>

const int hih = 720; //������
const int wid = 1280; //�����e

// ���a�����c 
struct Human {
	int x;	// x �y�� 
	int y;	// y �y��  
	int hp;	// ��q
	char dir;// �H�����ª���V 
	int output_idx; // �Ω��x�s�n��X���Ϥ��s�� 
	PIMAGE *player_img, *player_msk;  //�����x�s�Ϥ� 
};
