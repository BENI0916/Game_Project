//�����`���x�s��
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <graphics.h> 

const int hih = 720; //������
const int wid = 1280; //�����e

// ���a�����c 
struct Human 
{
	int x;	// x �y�� 
	int y;	// y �y��  
	int hp;	// ��q
	int damage;
	int atked;
	char dir;// �H�����ª���V 
	int output_idx; // �Ω��x�s�n��X���Ϥ��s�� 
	PIMAGE *player_img, *player_msk;  //�����x�s�Ϥ� 
};

struct Monster
{
	int x;
	int y;
	int hp;
	int damage;
	char dir;
	int output_idx;
	PIMAGE *enemy_img, *enemy_msk;
};

struct Bullet
{
	int x;
	int y;
	int output_idx;
	int status;
	int space_cal[6];
	PIMAGE *skill_img, *skill_msk;
};
