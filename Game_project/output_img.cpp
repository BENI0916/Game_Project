#include "dirent.h"
#include "lib/var.h" 
#include "lib/output_img.h"

extern PIMAGE bg;
extern int enemy_num;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[4];
extern Animate loading_animate;

void output_image()
{
	if(loading_animate.cnt < 72)
	{
		loading_animate.output_idx = loading_animate.cnt / 8;
		putimage(0, 0, loading_animate.loading_img[loading_animate.output_idx]);
		loading_animate.cnt++;
	}
	else
	{
		// ��X�I�� 
		putimage(0, 0, bg);
		
		if(enemy[enemy_num].hp > 0)
		{
			putimage(enemy[enemy_num].x, enemy[enemy_num].y, enemy[enemy_num].enemy_msk[enemy[enemy_num].output_idx], NOTSRCERASE);
			putimage(enemy[enemy_num].x, enemy[enemy_num].y, enemy[enemy_num].enemy_img[enemy[enemy_num].output_idx], SRCINVERT);
			
			for(int i = 0; i < 4; i++)
			{
				// �Y�ޯॿ�b�o�ʷ|�L�X 
				if(skill[i].status > 0)
				{
					putimage(skill[i].x, skill[i].y, skill[i].skill_msk[skill[i].output_idx], NOTSRCERASE);
					putimage(skill[i].x, skill[i].y, skill[i].skill_img[skill[i].output_idx], SRCINVERT);
				}
			}
		}
		
		// ��X���a
		putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
		putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
	}
}	

//Ū���I���Ϥ� filename:��Ū���I�������|���ɦW
void loadBG(char filename[]) 
{	
	delimage(bg);
	bg = newimage(wid,hih);
	PIMAGE oriBG = newimage(); //�إ߼Ȧs���I���Ϥ�
	getimage(oriBG, filename); //���o�Ϥ�
	putimage(bg, 0, 0, wid, hih, oriBG, 0, 0, getwidth(oriBG), getheight(oriBG)); //�i��Ԧ����x�s
	delimage(oriBG); //�R���Ȧs
}

//Ū���I���Ϥ� filename:��Ū���I�������|���ɦW w:���Y��e h:���Y�ᰪ
void loadBG(char filename[],int w,int h) 
{	
	delimage(bg);
	bg = newimage(w,h);
	PIMAGE oriBG = newimage(); //�إ߼Ȧs���I���Ϥ�
	getimage(oriBG, filename); //���o�Ϥ�
	putimage(bg, 0, 0, w, h, oriBG, 0, 0, getwidth(oriBG), getheight(oriBG)); //�i��Ԧ����x�s
	delimage(oriBG); //�R���Ȧs
}

//Ū������Ϥ� filename:��Ū���Ϥ������|���ɦW
//**ori_img:���V�Ϥ��N�x�s�������ܼ� **ori_msk:���V�B�n�N�x�s�������ܼ�
//w:�Ϥ���X�ᤧ�e h: �Ϥ���X�ᤧ��
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h,int index) 
{
	PIMAGE *img = NULL,*msk = NULL; //�Ȧs�Ϥ��ξB�n�������ܼ�
	DIR *img_dir = NULL, *msk_dir = NULL; //��Ƨ�����}
    struct dirent *img_entry, *msk_entry;

	char img_str[100], msk_str[100];
	sprintf(img_str, ".\\%s\\img", filename); //�w��
	sprintf(msk_str, ".\\%s\\msk", filename); //�w��
	if((img_dir = opendir(img_str)) == NULL || (msk_dir = opendir(msk_str)) == NULL) 
	{ //�P�_�O�_���\�}�ҩҫ��w�����|
            printf("opendir failed!\n");   
    }
	else 
	{
		for (int i = index;(img_entry = readdir(img_dir)), (msk_entry = readdir(msk_dir));) 
		{ //�P�_�O�_�t����Ū�����ɮסA�Y�L�h���}���N
			if (strstr(img_entry->d_name,".png") && strstr(msk_entry->d_name, ".png")) 
			{ //�P�_Ū�����ɮת����ɦW
				//�X�R�}�C
				*ori_img = (PIMAGE *)realloc(*ori_img,sizeof(PIMAGE)*(i+1));
				*ori_msk = (PIMAGE *)realloc(*ori_msk,sizeof(PIMAGE)*(i+1));
				
				img = (PIMAGE *)realloc(img,sizeof(PIMAGE)*(i+1));
				msk = (PIMAGE *)realloc(msk,sizeof(PIMAGE)*(i+1));	
				
				//�إ߹Ϥ�
				(*ori_img)[i] = newimage(w,h);
				(*ori_msk)[i] = newimage(w,h);
				
				img[i] = newimage();
				msk[i] = newimage();

				//Ū���Ϥ��éԦ��ܫ��w����
				sprintf(img_str, "%s\\img\\%s",filename,img_entry->d_name);
				sprintf(msk_str, "%s\\msk\\%s",filename,msk_entry->d_name);
				
				getimage(img[i], img_str);
				getimage(msk[i], msk_str);
				
				putimage((*ori_img)[i], 0, 0, w, h, img[i], 0, 0, getwidth(img[i]), getheight(img[i]));
				putimage((*ori_msk)[i], 0, 0, w, h, msk[i], 0, 0, getwidth(msk[i]), getheight(msk[i]));
				
				delimage(img[i]); //�R���Ȧs
				delimage(msk[i++]); //�R���Ȧs
			}
		}
		closedir(img_dir);
		closedir(msk_dir);
	}

	free(img);
	free(msk);
}
