#include "lib/var.h" 
#include "lib/enemy_atk.h"
#include "lib/enemy_give_dmg.h"
#include "lib/initialization.h"

extern int enemy_atk_cnt, enemy_atk_type, enemy_num, get_dmg_cnt, skill_dir;
extern double start, end;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[6];

// 此函式為改變敵人的動作 僅針對攻擊 
void enemy_atk()
{
	end = fclock(); // 攻擊間隔計時器 
	
	// 若距離上次攻擊已超過5秒 且 敵人與玩家的距離 靠近 且 敵人未進行攻擊移動 
	if(((end - start) > 4) && abs(enemy[enemy_num].x - player.x) < enemy[enemy_num].width * 3 && enemy_atk_type <= -1)
	{
		enemy_atk_type = random(3) + enemy_num * 3; // 敵人使用技能的選擇為隨機 
		//if(enemy_num == 1)
		//	enemy_atk_type = -1;
		get_dmg_cnt = 0;
		
		// 將對應編號的技能賦予計時器 
		switch(enemy_atk_type)
		{
			case 0:
				enemy_atk_cnt = enemy[enemy_num].atk_0_cnt;
				break;
			
			case 1:
				enemy_atk_cnt = enemy[enemy_num].atk_1_cnt;
				break;
			
			case 2 :
				enemy_atk_cnt = 60;
				break;
			
			case 3 :
				enemy_atk_cnt = 149;
				break;
			
			case 4 :
				enemy_atk_cnt = 120;
				break;

			case 5 :
				enemy_atk_cnt = 56;
				break;

			default :
				enemy_atk_type = -1;
				break;
		}
		start = fclock(); // 刷新攻擊間隔的時間起點 
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			skill_dir = 0;
		else	
			skill_dir = 1;
	}
	//printf("skill[0].status = %d output_index = %d\n", skill[0].status, skill[0].output_idx);
	if(enemy_atk_type == 0)
	{
		// 根據玩家位置施放技能 
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_00_atk(skill_dir);
		else
			enemy_00_atk(skill_dir);
		
		//若攻擊計時器為-1 代表攻擊完畢 則紀錄已攻擊完畢 
		if(enemy_atk_cnt == -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 1)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_01_atk(skill_dir);
		else
			enemy_01_atk(skill_dir);
		
		if(enemy_atk_cnt == -1)
			enemy_atk_type = -1;
	}
	else if(enemy_atk_type == 2)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_02_atk(skill_dir);
		else 
			enemy_02_atk(skill_dir);
		
		if(enemy_atk_cnt <= -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 3)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_03_atk(skill_dir);
		else 
			enemy_03_atk(skill_dir);
		
		if(enemy_atk_cnt <= -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 4)
	{
		if(player.x + player.width / 2 > enemy[enemy_num].x + enemy[enemy_num].width / 2)
			enemy_04_atk(skill_dir);
		else 
			enemy_04_atk(skill_dir);
		
		if(enemy_atk_cnt <= -1)
		{
			enemy_atk_type = -1;
		}
	}
	else if(enemy_atk_type == 5)
	{
		enemy_05_atk(0);

		if(enemy_atk_cnt <= -1)
			enemy_atk_type = -1;
	}
	
	// 此函式為造成傷害 
	if(get_dmg_cnt == 0 && enemy[enemy_num].hp > 0)
		enemy_give_dmg();
}
 
void enemy_00_atk(int val)
{
	int table[5] = {0, 2, 4, 2};
	
	// �ھڭp�ɾ���X�ʧ@ 
	enemy[enemy_num].output_idx = table[enemy_atk_cnt / 50] + val;
	
	// �Y�b�p�ɾ����S�w�ɶ����j�� �|��X�������ޯ�S�� 
	if(enemy[enemy_num].output_idx == 4 || enemy[enemy_num].output_idx == 5)
	{
		skill[0].status = 1; // 1 �N���ޯ�S�ķ|�L�X�A 0 �h�N�����| 
		
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

void enemy_01_atk(int val)
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

void enemy_02_atk(int val)
{
	enemy_atk_cnt--;
	if(enemy_atk_cnt > -1)
	{
		skill[2].status = 1;
		skill[2].output_idx = val;
		
		if(enemy[enemy_num].dir == 'a')
		{
			skill[2].x = enemy[enemy_num].x - ((60 - enemy_atk_cnt) * 15);
		}
		else
		{
			skill[2].x = enemy[enemy_num].x + enemy[enemy_num].width + ((59 - enemy_atk_cnt) * 15);
		}
		
		skill[2].y = hih * 0.6 + player.high - skill[2].high;
	}	
	else
		skill[2].status = 0;
}

void enemy_03_atk(int val)
{
	int table[5] = {6, 6, 4};
	
	enemy[enemy_num].output_idx = table[enemy_atk_cnt / 50] + val;
	enemy_atk_cnt -= 1;
	
	if(enemy_atk_cnt == -1)
		enemy[enemy_num].output_idx = 0 + val;
	
	skill[3].status = 1;
	skill[3].y = enemy[enemy_num].y + skill[3].high * 0.2;
	
	if(enemy_atk_cnt > 99)
	{
		switch(enemy_atk_cnt)
		{
			case 149:
				skill[3].output_idx = 0;
				break;
				
			case 132:
				skill[3].output_idx = 1;
				break;
			
			case 115:
				skill[3].output_idx = 2;
				break;
			
			default:
				break;
		}
		
		if(enemy[enemy_num].dir == 'a')
		{
			skill[3].x = enemy[enemy_num].x - skill[3].width;
		}
		else
		{
			skill[3].x = enemy[enemy_num].x + enemy[enemy_num].width * 0.6;
		}
	}
	else
	{
		if(enemy[enemy_num].dir == 'a')
		{
			skill[3].x = enemy[enemy_num].x - ((99 - enemy_atk_cnt) * 10) - skill[3].width;
		}
		else
		{
			skill[3].x = enemy[enemy_num].x + enemy[enemy_num].width * 0.6 + ((99 - enemy_atk_cnt) * 10);
		}
		
		switch(enemy_atk_cnt)
		{
			case 90:
				skill[3].output_idx = 4 - val;
				break;
				
			case 88:
				skill[3].output_idx = 6 - val;
				break;
			
			case 70:
				skill[3].output_idx = 4 - val;
				break;
				
			case 60:
				skill[3].output_idx = 6 - val;
				break;
				
			case 50:
				skill[3].output_idx = 4 - val;
				break;
				
			case 40:
				skill[3].output_idx = 6 - val;
				break;
				
			case 30:
				skill[3].output_idx = 4 - val;
				break;
				
			case 20:
				skill[3].output_idx = 6 - val;
				break;
			
			case 10:
				skill[3].output_idx = 4 - val;
				break;
			
			case -1:
				skill[3].status = 0;
				break;
			
			default :
				break;
		}
	}
}

void enemy_04_atk(int val)
{
	int table[9] = {10, 8, 6, 4, 4, 2, 2, 0, 0};
	enemy_atk_cnt--;

	if(enemy_atk_cnt % 30 == 0)
		get_dmg_cnt = 0;

	if(enemy_atk_cnt < 70)
		enemy[enemy_num].output_idx = 12 + val;
	else if(enemy_atk_cnt < 90)
		enemy[enemy_num].output_idx = 10 + val;
	else if(enemy_atk_cnt < 120)
		enemy[enemy_num].output_idx = 8 + val;

	if(enemy_atk_cnt < 90)
	{
		if(enemy_atk_cnt > -1)
		{
			skill[4].output_idx = table[enemy_atk_cnt / 10] + val;
			
			if(!skill[4].status)
			{
				skill[4].x = player.x + player.width / 2 - skill[4].width / 2;
			}
			skill[4].status = 1;
			skill[4].y = hih * 0.6 + 130 - skill[4].high;
		}	
		else
			skill[4].status = 0;
	}
}

void enemy_05_atk(int val)
{
	if(!skill[5].status)
		skill[5].x = player.x + player.width / 2 - skill[5].width / 2;

	skill[5].status = 1;
	enemy_atk_cnt--;


	switch(enemy_atk_cnt)
	{
		case 55:
			skill[5].output_idx = 0;
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.7;
			break;
		
		case 50:
			skill[5].output_idx = 1;
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.7;
			break;
		
		case 45:
			skill[5].output_idx = 2;
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.8;
			break;
		
		case 40:
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.7;
			break;
		
		case 29:
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.5;
			break;

		case 20:
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.3;
			break;
		
		case 13:
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 1.1;
			break;

		case 8:
			skill[5].output_idx = 3;
			skill[5].y = hih * 0.6 + 66 - skill[5].high * 0.9;
			break;
		
		case -1:
			skill[5].status = 0;
			break;

		default:
			break;
	}


}

