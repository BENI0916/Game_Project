#include "lib/var.h"
#include "lib/game_start.h"
#include "lib/lunch.h"
#include "lib/save_load.h"
#include "lib/setting.h"

//�C���}�l����|�����ӳo�� 
void gameStart() 
{
    initgraph(wid, hih);	// ��l�Ƶ��f 
	printf("inigraph succes\n");

    /*
    �C�����}�l�e��
	�e���ݭn���|�����s�A���O�O:�}�l�C�� Ū/�s�� �]�w �����C��
	�H�U�����U���s�\��
	
	�}�l�C�� :
		���U����� lunch.cpp �� lunch() 
		lunch()�������e�L����ʡA���楦�N�n
	Ū/�s��:
		���U��i��e�������A�i�ܥX�T�Ӧs�ɮ�A���U�Ӧs�ɮ��N���X��ӫ��s�A���O�O: �s�� Ū�� 
			�s��: ���� save_load.cpp �� save()
			Ū��: ���� save_load.cpp �� load()
	�]�w:
		���U����� setting.cpp �� setting()
	�����C��:
		���U��פ�{��
		
	�U�Ψ줧�禡�ԲӤ��e�ЦܦUcpp�ɤ��d�� 


    */
    lunch();
}
