#include "lib/save_load.h"
#include "lib/var.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

extern Human player;
extern int bgX,bgY,enemy_num,bp[3][bpL],bpIdx[3][bpL],bpAmount[3],inMaz;
extern char BgName[]; 

//新遊戲 初始化數值
void newGame() {
	sprintf(BgName,"%s","images\\bg\\home2.png");//當前背景
	inMaz = 0;//是否在迷宮內
	bgX=20,bgY=-20;//背景位置
	//背包相關
	bpAmount[0] = 0;
	bpAmount[1] = 0;
	bpAmount[2] = 0;
	for (int i = 0;i<bpL;i++) {//清空背包
		bp[0][i] = 0;
		bp[1][i] = 0;
		bp[2][i] = 0;
		bpIdx[0][i] = 0;
		bpIdx[1][i] = 0;
		bpIdx[2][i] = 0;
	}
	player.output_idx = 27;//玩家圖片編號
	player.hp = 10;//血量
	player.fhp = 10;//最大血量
	player.damage = 5;//傷害
	enemy_num = -1;//BOSS數
}

//存檔用函式 
void save() 
{
	FILE *fptr = fopen("data\\save\\save1.dat","wb");
	if(fptr==NULL)
	{
		puts("ERROR: Open file failed.\n");
		assert(0);
	}
	if(fwrite(&player.hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_hp failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(&player.fhp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_fhp failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(&player.damage,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_damage failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(&player.output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_output_idx failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(&bgX,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write bgX failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(&bgY,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write bgY failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(&enemy_num,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy_num failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(BgName,sizeof(char)*strlen(BgName),1,fptr) != 1)
	{
		puts("ERROR: Write BgName failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(bp,sizeof(int)*(3*bpL),1,fptr) != 1)
	{
		puts("ERROR: Write bp failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(bpIdx,sizeof(int)*(3*bpL),1,fptr) != 1)
	{
		puts("ERROR: Write bpIdx failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fwrite(bpAmount,sizeof(int)*3,1,fptr) != 1)
	{
		puts("ERROR: Write bpAmount failed.\n");
		fclose(fptr);
		assert(0);
	}
	
	fclose(fptr);
	puts("Save successful\n");
    //只須完成寫檔及建檔功能，寫入內容先空著就好
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例 
}

//讀檔用函式 
void load() 
{
	FILE *fptr = fopen("data\\save\\save1.dat","rb");
	if(fptr == NULL)
	{
		puts("ERROR: The file does not exist.\n");
		assert(0);
	}
	if(fread(&player.hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_hp failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(&player.fhp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_fhp failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(&player.damage,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_damage failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(&player.output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_output_idx failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(&bgX,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load bgX failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(&bgY,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load bgY failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(&enemy_num,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy_num failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(BgName,sizeof(char)*strlen(BgName),1,fptr) != 1)
	{
		puts("ERROR: Load BgName failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(bp,sizeof(int)*(3*bpL),1,fptr) != 1)
	{
		puts("ERROR: Write bp failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(bpIdx,sizeof(int)*(3*bpL),1,fptr) != 1)
	{
		puts("ERROR: Write bpIdx failed.\n");
		fclose(fptr);
		assert(0);
	}
	if(fread(bpAmount,sizeof(int)*3,1,fptr) != 1)
	{
		puts("ERROR: Write bpAmount failed.\n");
		fclose(fptr);
		assert(0);
	}
	
	fclose(fptr);
	puts("Load successful\n");
    //只需進行開檔及讀檔，若檔案不存在須告知玩家
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例  
}