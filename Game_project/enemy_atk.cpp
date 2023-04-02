// enemy_atk
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "var.cpp"
extern int enemy_atk_cnt, enemy_atk_type;
extern double start, end;
extern Human player;
extern Monster enemy;
extern Bullet skill[2];

void enemy_first_atk(int val);
void enemy_second_atk(int val);
void enemy_give_damage();
int is_middle(int up, int pos, int down);

// ���禡�����ܼĤH���ʧ@ �Ȱw����� 
void enemy_atk()
{
	end = fclock(); // �������j�p�ɾ� 
	
	// �Y�Z���W�������w�W�L5�� �B �ĤH�P���a���Z�� �a�� �B �ĤH���i��������� 
	if(((end - start) > 5) && abs(enemy.x - player.x) < enemy.width * 2 && enemy_atk_type == -1)
	{
		enemy_atk_type = random(2); // �ĤH�ϥΧޯ઺��ܬ��H�� 
		
		// �N�����s�����ޯ�ᤩ�p�ɾ� 
		switch(enemy_atk_type)
		{
			case 0:
				enemy_atk_cnt = enemy.atk_0_cnt;
				break;
			
			case 1:
				enemy_atk_cnt = enemy.atk_1_cnt;
				break;
			
			default :
				break;
		}
		
		start = fclock(); // ��s�������j���ɶ��_�I 
	}
	
	if(enemy_atk_type == 0)
	{
		// �ھڪ��a��m�I��ޯ� 
		if(player.x + player.width / 2 > enemy.x + enemy.width / 2)
			enemy_first_atk(0);
		else
			enemy_first_atk(1);
		
		//�Y�����p�ɾ���-1 �N��������� �h�����w�������� 
		if(enemy_atk_cnt == -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 1)
	{
		if(player.x + player.width / 2 > enemy.x + enemy.width / 2)
			enemy_second_atk(0);
		else
			enemy_second_atk(1);
		
		if(enemy_atk_cnt == -1)
			enemy_atk_type = -1;
	}
	
	// ���禡���y���ˮ` 
	enemy_give_damage();
}
 
void enemy_first_atk(int val)
{
	int table[5] = {0, 2, 4, 2};
	
	// �ھڭp�ɾ���X�ʧ@ 
	enemy.output_idx = table[enemy_atk_cnt / 50] + val;
	
	// �Y�b�p�ɾ����S�w�ɶ����j�� �|��X�������ޯ�S�� 
	if(enemy.output_idx == 4 || enemy.output_idx == 5)
	{
		skill[0].status = 1; // 1 �N��ޯ�S�ķ|�L�X�A 0 �h�N���| 
		
		if(enemy.dir == 'a')
		{
			skill[0].x = enemy.x - skill[0].width * 0.9; // �վ�ޯ�L�X����m 
			skill[0].output_idx = 1;
		}
		else
		{
			skill[0].x = enemy.x + enemy.width * 0.9;
			skill[0].output_idx = 0;
		}
		
		skill[0].y = enemy.y + 50;
	}
	else
		skill[0].status = 0; // �Y���b�p�ɾ����S�w�ɶ����j���A�h���|��X�ޯ�S�� 
	
	enemy_atk_cnt -= 1; // �p�ɾ��˼� 
}

void enemy_second_atk(int val)
{
	int table[4] = {10, 6, 8, 6};
	
	enemy.output_idx = table[(enemy_atk_cnt - 40) / 15] + val;
	enemy_atk_cnt -= 1;
	
	// ���ޯ�����S�� �I��ޯ৹���� ���B�~���O��_���`���A 
	if(enemy_atk_cnt == -1)
		enemy.output_idx = 0 + val;
	
	// ���ޯ�t�����D�ʧ@ �H�U�h�������� y �b�첾 
	switch(enemy_atk_cnt)
	{
		case 98 :
			enemy.y -= 60;
			break;
		case 90 :
			enemy.y -= 35;
			break;
		case 82 :
			enemy.y -= 15;
			break;
		case 70 :
			enemy.y += 15;
			break;
		case 62 :
			enemy.y += 35;
			break;
		case 56 : 
			enemy.y += 60;
			break;
		default : 
			break;
	}
	
	// �b�S�w�ɶ����j�� ��X�ޯ�S�� 
	if(is_middle(56, enemy_atk_cnt, 0))
	{
		skill[1].status = 1;
		skill[1].x = enemy.x - skill[1].width / 3;
		
		skill[1].output_idx = 0;
		
		skill[1].y = hih * 0.6 + player.high - skill[1].high;
	}
	else
		skill[1].status = 0;
}
