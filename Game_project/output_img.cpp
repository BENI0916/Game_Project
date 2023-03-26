#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#include "dirent.h"
#include "var.cpp"
PIMAGE bg = newimage(wid, hih); //bg:儲存背景圖片之變數
extern Human player;

void output_image()
{
	// 輸出背景 
	putimage(0, 0, bg);
	
	// 輸出玩家
	putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
	putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
}

//讀取背景圖片 filename:欲讀取背景之路徑及檔名
void loadBG(char filename[]) {
	PIMAGE oriBG = newimage(); //建立暫存之背景圖片
	getimage(oriBG, filename); //取得圖片
	putimage(bg,0, 0, wid, hih, bg, 0, 0, getwidth(oriBG), getheight(oriBG)); //進行拉伸並儲存
	delimage(oriBG); //刪除暫存
}

//讀取角色圖片 filename:欲讀取圖片之路徑及檔名
//**ori_img:指向圖片將儲存之指標變數 **ori_msk:指向遮罩將儲存之指標變數
//w:圖片輸出後之寬 h: 圖片輸出後之高
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h) {
	PIMAGE *img = NULL,*msk = NULL; //暫存圖片及遮罩之指標變數
	DIR *dir = NULL; //資料夾的位址
    struct dirent *entry;

	char s[100];
	sprintf(s, ".\\%s\\img", filename); //定位
	if((dir = opendir(s))==NULL) { //判斷是否成功開啟所指定之路徑
            printf("opendir failed!\n");   
    }
	else {
		for (int i = 0;(entry=readdir(dir));) { //判斷是否含有未讀取之檔案，若無則離開迭代
			if (strstr(entry->d_name,".png")) { //判斷讀取之檔案的副檔名
				//擴充陣列
				*ori_img = (PIMAGE *)realloc(*ori_img,sizeof(PIMAGE)*(i+1));
				img = (PIMAGE *)realloc(img,sizeof(PIMAGE)*(i+1));

				//建立圖片
				(*ori_img)[i] = newimage(w,h);
				img[i] = newimage();

				//讀取圖片並拉伸至指定長高
				sprintf(s, "%s\\img\\%s",filename,entry->d_name);
				getimage(img[i], s);
				putimage((*ori_img)[i], 0, 0, w, h, img[i], 0, 0, getwidth(img[i]), getheight(img[i]));
				delimage(img[i++]); //刪除暫存
			}
		}
		closedir(dir);
	}

	sprintf(s, ".\\%s\\msk", filename); //定位
	if((dir = opendir(s))==NULL) { //判斷是否成功開啟所指定之路徑
            printf("opendir failed!\n");   
    }
	else {
		for (int i = 0;(entry=readdir(dir));) { //判斷是否含有未讀取之檔案，若無則離開迭代
			if (strstr(entry->d_name,".png")) { //判斷讀取之檔案的副檔名
				//擴充陣列
				*ori_msk = (PIMAGE *)realloc(*ori_msk,sizeof(PIMAGE)*(i+1));
				msk = (PIMAGE *)realloc(msk,sizeof(PIMAGE)*(i+1));

				//建立圖片
				(*ori_msk)[i] = newimage(w,h);
				msk[i] = newimage();

				//讀取圖片並拉伸至指定長高
				sprintf(s, "%s\\msk\\%s",filename,entry->d_name);
				getimage(msk[i], s);
				putimage((*ori_msk)[i], 0, 0, w, h, msk[i], 0, 0, getwidth(msk[i]), getheight(msk[i]));
				delimage(msk[i++]); //刪除暫存
			}
		}
		closedir(dir); //關閉資料夾
	}
	//釋放記憶體資源
	free(img);
	free(msk);
}
