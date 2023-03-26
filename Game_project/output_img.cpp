#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "dirent.h"
#include "var.cpp"
PIMAGE bg = newimage(wid, hih); //bg:�x�s�I���Ϥ����ܼ�
extern Human player;

void output_image()
{
	// ��X�I�� 
	putimage(0, 0, bg);
	
	// ��X���a
	putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
}

//Ū���I���Ϥ� filename:��Ū���I�������|���ɦW
void loadBG(char filename[]) {
	PIMAGE oriBG = newimage(); //�إ߼Ȧs���I���Ϥ�
	getimage(oriBG, filename); //���o�Ϥ�
	putimage(bg,0, 0, wid, hih, bg, 0, 0, getwidth(oriBG), getheight(oriBG)); //�i��Ԧ����x�s
	delimage(oriBG); //�R���Ȧs
}

//Ū������Ϥ� filename:��Ū���Ϥ������|���ɦW
//**ori_img:���V�Ϥ��N�x�s�������ܼ� **ori_msk:���V�B�n�N�x�s�������ܼ�
//w:�Ϥ���X�ᤧ�e h: �Ϥ���X�ᤧ��
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h) {
	PIMAGE *img = NULL,*msk = NULL; //�Ȧs�Ϥ��ξB�n�������ܼ�
	DIR *dir = NULL; //��Ƨ�����}
    struct dirent *entry;

	char s[100];
	sprintf(s, ".\\%s\\img", filename); //�w��
	if((dir = opendir(s))==NULL) { //�P�_�O�_���\�}�ҩҫ��w�����|
            printf("opendir failed!\n");   
    }
	else {
		for (int i = 0;(entry=readdir(dir));) { //�P�_�O�_�t����Ū�����ɮסA�Y�L�h���}���N
			if (strstr(entry->d_name,".png")) { //�P�_Ū�����ɮת����ɦW
				//�X�R�}�C
				*ori_img = (PIMAGE *)realloc(*ori_img,sizeof(PIMAGE)*(i+1));
				img = (PIMAGE *)realloc(img,sizeof(PIMAGE)*(i+1));

				//�إ߹Ϥ�
				(*ori_img)[i] = newimage(w,h);
				img[i] = newimage();

				//Ū���Ϥ��éԦ��ܫ��w����
				sprintf(s, "%s\\img\\%s",filename,entry->d_name);
				getimage(img[i], s);
				putimage((*ori_img)[i], 0, 0, w, h, img[i], 0, 0, getwidth(img[i]), getheight(img[i]));
				delimage(img[i++]); //�R���Ȧs
			}
		}
		closedir(dir);
	}

	sprintf(s, ".\\%s\\msk", filename); //�w��
	if((dir = opendir(s))==NULL) { //�P�_�O�_���\�}�ҩҫ��w�����|
            printf("opendir failed!\n");   
    }
	else {
		for (int i = 0;(entry=readdir(dir));) { //�P�_�O�_�t����Ū�����ɮסA�Y�L�h���}���N
			if (strstr(entry->d_name,".png")) { //�P�_Ū�����ɮת����ɦW
				//�X�R�}�C
				*ori_msk = (PIMAGE *)realloc(*ori_msk,sizeof(PIMAGE)*(i+1));
				msk = (PIMAGE *)realloc(msk,sizeof(PIMAGE)*(i+1));

				//�إ߹Ϥ�
				(*ori_msk)[i] = newimage(w,h);
				msk[i] = newimage();

				//Ū���Ϥ��éԦ��ܫ��w����
				sprintf(s, "%s\\msk\\%s",filename,entry->d_name);
				getimage(msk[i], s);
				putimage((*ori_msk)[i], 0, 0, w, h, msk[i], 0, 0, getwidth(msk[i]), getheight(msk[i]));
				delimage(msk[i++]); //�R���Ȧs
			}
		}
		closedir(dir); //������Ƨ�
	}
	//����O����귽
	free(img);
	free(msk);
}
