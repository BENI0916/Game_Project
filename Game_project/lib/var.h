#ifndef VAR_H
#define VAR_H

//�����`���x�s��
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#pragma comment(lib, "Winmm.lib")

const int hih = 720; //������
const int wid = 1280; //�����e

// ���a�����c 
typedef struct 
{
	int x;	// x �y�� 
	int y;	// y �y��  
	int hp;	// ��q
	int fhp;
	int damage; // ��ĤH�y�����ˮ`  
	int atked;// �P�w�O�_���y���ˮ` 
	char dir;// �H�����ª���V 
	int output_idx; // �Ω��x�s�n��X���Ϥ��s�� 
	PIMAGE *player_img, *player_msk;  //�����x�s�Ϥ� 
	int high;
	int width;
	int power;// ���h�ĤH���Z�� 
	int atk_type; // �������� 
}Human;

typedef struct 
{
	int x;
	int y;
	int hp;
	int fhp;
	int damage;
	char dir;
	int output_idx;
	PIMAGE *enemy_img, *enemy_msk;
	int high;
	int width;
	int power;
	int speed;
	int atk_0_cnt;
	int atk_1_cnt;
}Monster;

typedef struct 
{
	int cnt;
	int output_idx;
	int printed;
	PIMAGE *loading_img;
}Animate;


typedef struct 
{
	int x;
	int y;
	int output_idx;
	int status;
	PIMAGE *skill_img, *skill_msk;
	int high;
	int width;
	int power;
}Bullet;

#endif
