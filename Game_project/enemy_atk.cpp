#include "lib/var.h" 
#include "lib/enemy_atk.h"
#include "lib/enemy_give_dmg.h"
#include "lib/initialization.h"

extern int enemy_atk_cnt, enemy_atk_type, enemy_num;
extern double start, end;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[2];

// ���禡�����ܼĤH���ʧ@ �Ȱw����� 
void enemy_atk()
{
	end = fclock(); // �������j�p�ɾ� 
	
	// �Y�Z���W�������w�W�L5�� �B �ĤH�P���a���Z�� �a�� �B �ĤH���i��������� 
	if(((end - start) > 5) && abs(enemy[enemy_num].x - player.x) < enemy[enemy_num].width * 2 && enemy_atk_type == -1)
	{
		enemy_atk_type = random(2) + enemy_num * 2; // �ĤH�ϥΧޯ઺��ܬ��H�� 
		
		if(enemy_num == 1)
			enemy_atk_type = -1;
		
		// �N�����s�����ޯ�ᤩ�p�ɾ� 
		switch(enemy_atk_type)
		{
			case 0:
				enemy_atk_cnt = enemy[enemy_num].atk_0_cnt;
				break;
			
			case 1:
				enemy_atk_cnt = enemy[enemy_num].atk_1_cnt;
				break;
			
			default :
				break;
		}
		
		start = fclock(); // ��s�������j���ɶ��_�I 
	}
	//printf("skill[0].status = %d output_index = %d\n", skill[0].status, skill[0].output_idx);
	if(enemy_atk_type == 0)
	{
		// �ھڪ��a��m�I��ޯ� 
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
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
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_second_atk(0);
		else
			enemy_second_atk(1);
		
		if(enemy_atk_cnt == -1)
			enemy_atk_type = -1;
	}
	
	// ���禡���y���ˮ` 
	enemy_give_dmg();
}
 
void enemy_first_atk(int val)
{
	int table[5] = {0, 2, 4, 2};
	
	// �ھڭp�ɾ���X�ʧ@ 
	enemy[enemy_num].output_idx = table[enemy_atk_cnt / 50] + val;
	
	// �Y�b�p�ɾ����S�w�ɶ����j�� �|��X�������ޯ�S�� 
	if(enemy[enemy_num].output_idx == 4 || enemy[enemy_num].output_idx == 5)
	{
		skill[0].status = 1; // 1 �N��ޯ�S�ķ|�L�X�A 0 �h�N���| 
		
		if(enemy[0].dir == 'a')
		{
			skill[0].x = enemy[enemy_num].x - skill[0].width * 0.9; // �վ�ޯ�L�X����m 
			skill[0].output_idx = 1;
		}
		else
		{
			skill[0].x = enemy[enemy_num].x + enemy[enemy_num].width * 0.9;
			skill[0].output_idx = 0;
		}
		
		skill[0].y = enemy[enemy_num].y + 50;
	}
	else
		skill[0].status = 0; // �Y���b�p�ɾ����S�w�ɶ����j���A�h���|��X�ޯ�S�� 
	
	enemy_atk_cnt -= 1; // �p�ɾ��˼� 
}

void enemy_second_atk(int val)
{
	int table[4] = {10, 6, 8, 6};
	
	enemy[enemy_num].output_idx = table[(enemy_atk_cnt - 40) / 15] + val;
	enemy_atk_cnt -= 1;
	
	// ���ޯ�����S�� �I��ޯ৹���� ���B�~���O��_���`���A 
	if(enemy_atk_cnt == -1)
		enemy[enemy_num].output_idx = 0 + val;
	
	// ���ޯ�t�����D�ʧ@ �H�U�h�������� y �b�첾 
	switch(enemy_atk_cnt)
	{
		case 98 :
			enemy[enemy_num].y -= 60;
			break;
		case 90 :
			enemy[enemy_num].y -= 35;
			break;
		case 82 :
			enemy[enemy_num].y -= 15;
			break;
		case 70 :
			enemy[enemy_num].y += 15;
			break;
		case 62 :
			enemy[enemy_num].y += 35;
			break;
		case 56 : 
			enemy[enemy_num].y += 60;
			break;
		default : 
			break;
	}
	
	// �b�S�w�ɶ����j�� ��X�ޯ�S�� 
	if(is_middle(56, enemy_atk_cnt, 0))
	{
		skill[1].status = 1;
		skill[1].x = enemy[enemy_num].x - skill[1].width / 3;
		
		skill[1].output_idx = 0;
		
		skill[1].y = hih * 0.6 + player.high - skill[1].high;
	}
	else
		skill[1].status = 0;
}
