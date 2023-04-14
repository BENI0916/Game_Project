#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h> 
#include "dirent.h"
#include "lib/var.h"
PIMAGE bg = newimage(wid, hih); //bg:儲存背景圖片之變數
extern int enemy_num;
extern Human player;
extern Monster enemy[2];
extern Bullet skill[3];
extern animate loading_animate;

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
		// 輸出背景 
		putimage(0, 0, bg);
		
		if(enemy[enemy_num].hp > 0)
		{
			putimage(enemy[enemy_num].x, enemy[enemy_num].y, enemy[enemy_num].enemy_msk[enemy[enemy_num].output_idx], NOTSRCERASE);
			putimage(enemy[enemy_num].x, enemy[enemy_num].y, enemy[enemy_num].enemy_img[enemy[enemy_num].output_idx], SRCINVERT);
			
			for(int i = 0; i < 2; i++)
			{
				// 若技能正在發動會印出 
				if(skill[i].status > 0)
				{
					putimage(skill[i].x, skill[i].y, skill[i].skill_msk[skill[i].output_idx], NOTSRCERASE);
					putimage(skill[i].x, skill[i].y, skill[i].skill_img[skill[i].output_idx], SRCINVERT);
				}
			}
		}
		//printf("enemy_num = %d\n", enemy_num);
		// 輸出玩家
		putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
		putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
	}
}	

//讀取背景圖片 filename:欲讀取背景之路徑及檔名
void loadBG(char filename[]) 
{
	PIMAGE oriBG = newimage(); //建立暫存之背景圖片
	getimage(oriBG, filename); //取得圖片
	putimage(bg, 0, 0, wid, hih, oriBG, 0, 0, getwidth(oriBG), getheight(oriBG)); //進行拉伸並儲存
	delimage(oriBG); //刪除暫存
}

//讀取角色圖片 filename:欲讀取圖片之路徑及檔名
//**ori_img:指向圖片將儲存之指標變數 **ori_msk:指向遮罩將儲存之指標變數
//w:圖片輸出後之寬 h: 圖片輸出後之高
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h) 
{
	PIMAGE *img = NULL,*msk = NULL; //暫存圖片及遮罩之指標變數
	DIR *img_dir = NULL, *msk_dir = NULL; //資料夾的位址
    struct dirent *img_entry, *msk_entry;

	char img_str[100], msk_str[100];
	sprintf(img_str, ".\\%s\\img", filename); //定位
	sprintf(msk_str, ".\\%s\\msk", filename); //定位
	if((img_dir = opendir(img_str)) == NULL || (msk_dir = opendir(msk_str)) == NULL) 
	{ //判斷是否成功開啟所指定之路徑
            printf("opendir failed!\n");   
    }
	else 
	{
		for (int i = 0;(img_entry = readdir(img_dir)), (msk_entry = readdir(msk_dir));) 
		{ //判斷是否含有未讀取之檔案，若無則離開迭代
			if (strstr(img_entry->d_name,".png") && strstr(msk_entry->d_name, ".png")) 
			{ //判斷讀取之檔案的副檔名
				//擴充陣列
				*ori_img = (PIMAGE *)realloc(*ori_img,sizeof(PIMAGE)*(i+1));
				*ori_msk = (PIMAGE *)realloc(*ori_msk,sizeof(PIMAGE)*(i+1));
				
				img = (PIMAGE *)realloc(img,sizeof(PIMAGE)*(i+1));
				msk = (PIMAGE *)realloc(msk,sizeof(PIMAGE)*(i+1));	
				
				//建立圖片
				(*ori_img)[i] = newimage(w,h);
				(*ori_msk)[i] = newimage(w,h);
				
				img[i] = newimage();
				msk[i] = newimage();

				//讀取圖片並拉伸至指定長高
				sprintf(img_str, "%s\\img\\%s",filename,img_entry->d_name);
				sprintf(msk_str, "%s\\msk\\%s",filename,msk_entry->d_name);
				
				getimage(img[i], img_str);
				getimage(msk[i], msk_str);
				
				putimage((*ori_img)[i], 0, 0, w, h, img[i], 0, 0, getwidth(img[i]), getheight(img[i]));
				putimage((*ori_msk)[i], 0, 0, w, h, msk[i], 0, 0, getwidth(msk[i]), getheight(msk[i]));
				
				delimage(img[i]); //刪除暫存
				delimage(msk[i++]); //刪除暫存
			}
		}
		closedir(img_dir);
		closedir(msk_dir);
	}

	free(img);
	free(msk);
}
