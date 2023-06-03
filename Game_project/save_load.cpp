#include "lib/save_load.h"
#include "lib/var.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern Human player;
extern int bgX,bgY,enemy_num,bp[3][bpL],bpIdx[3][bpL],bpAmount[3],inMaz,folder,mX,mY;
extern char BgName[];
extern PIMAGE CellImg, ButtonImg;
int IsEmpty1,IsEmpty2,IsEmpty3,IsPrint1,IsPrint2,IsPrint3,IsButton;
FILE *fptr;

//概念:
//右下角資料夾圖案
//點進去會顯示三個儲存格(顯示 empty or 有存檔)，且有 delete,back 按鈕(分別執行delete,back)
//點儲存格，會出現 save,load 按鈕(分別執行save,load)

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

void SaveLoadScreen()
{
    putimage_withalpha(NULL,CellImg,200,160);
	PrintCellinfo();
}

void PrintCellinfo()
{
	if(IsEmpty1 == 0)
	{
  		outtextxy(393,366,"EMPTY");
	}
	else if(IsEmpty1 == 1)
	{
		outtextxy(393,366,"SAVED");
	}
	
	if(IsEmpty2 == 0)
	{
  		outtextxy(645,366,"EMPTY");
	}
	else if(IsEmpty2 == 1)
	{
		outtextxy(645,366,"SAVED");
	}
	
	if(IsEmpty3 == 0)
	{
  		outtextxy(895,366,"EMPTY");
	}
	else if(IsEmpty3 == 1)
	{
		outtextxy(895,366,"SAVED");
	}
	
}

void SaveLoadlistener()
{
	mousepos(&mX,&mY);
	
	//save:305 538 491 590
	//load:555 543 741 593
	//delete:808 545 991 585
	
	if(IsButton){
		if((mX >= 305 && mX <= 491) && (mY >= 538 && mY <= 590) && keystate(key_mouse_l)){
			flushmouse();
			save();
		}
		else if((mX >= 555 && mX <= 741) && (mY >= 543 && mY <= 593) && keystate(key_mouse_l)){
			flushmouse();
			load();
		}
		else if((mX >= 808 && mX <= 991) && (mY >= 545 && mY <= 590) && keystate(key_mouse_l)){
			flushmouse();
			del();
		}
	}
	if((mX >= 294 && mX <= 490) && (mY >= 276 && mY <= 447) && keystate(key_mouse_l))
	{
		//按第一個處存格
		flushmouse();
		IsPrint1 = 1;
		IsPrint2 = 0;
		IsPrint3 = 0;
	}
	else if((mX >= 546 && mX <= 740) && (mY >= 276 && mY <= 447) && keystate(key_mouse_l))
	{
		//按第二個處存格
		flushmouse();
		IsPrint1 = 0;
		IsPrint2 = 1;
		IsPrint3 = 0;
	}
	else if((mX >= 801 && mX <= 995) && (mY >= 276 && mY <= 447) && keystate(key_mouse_l))
	{
		//按第三個處存格
		flushmouse();
		IsPrint1 = 0;
		IsPrint2 = 0;
		IsPrint3 = 1;
	}
	else if((mX >= 1176 && mX <= 1238) && (mY >= 595 && mY <= 638) && keystate(key_mouse_l))
	{
		//按第二次資料夾消除畫面
		flushmouse();
		folder = 0;
	}
	else if(IsPrint1==1 || IsPrint2==1 || IsPrint3==1){
		//點了其中一個處存格，顯示按鈕
		putimage_withalpha(NULL,ButtonImg,185,160);
		IsButton = 1;
	}
	
}

//存檔用函式 
void save() 
{
	if(IsPrint1){
		fptr = fopen("data\\save\\save1.dat", "wb");
	}
	else if (IsPrint2){
		fptr = fopen("data\\save\\save2.dat", "wb");
	}
	else if (IsPrint3){
		fptr = fopen("data\\save\\save3.dat", "wb");
	}
	
	if(fptr == NULL)
	{
		puts("ERROR: Open file failed.");
		assert(0);
	}
	else if(fwrite(&player.hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&player.fhp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_fhp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&player.damage,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_damage failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&player.output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&bgX,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write bgX failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&bgY,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write bgY failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy_num,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy_num failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(BgName,sizeof(char),strlen(BgName),fptr))
	{
		puts("ERROR: Write BgName failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(bp,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Write bp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(bpIdx,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Write bpIdx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(bpAmount,sizeof(int),3,fptr))
	{
		puts("ERROR: Write bpAmount failed.");
		fclose(fptr);
		assert(0);
	}
	else{
		fclose(fptr);
		puts("Save successfully");
		if(IsPrint1) IsEmpty1 = 1;
		else if(IsPrint2) IsEmpty2 = 1;
		else if(IsPrint3) IsEmpty3 = 1;
	}
    //只須完成寫檔及建檔功能，寫入內容先空著就好
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例 
}

//讀檔用函式 
void load() 
{
	FILE *fptr;
	if(IsPrint1){
		fptr = fopen("data\\save\\save1.dat", "rb");
	}
	else if (IsPrint2){
		fptr = fopen("data\\save\\save2.dat", "rb");
	}
	else if (IsPrint3){
		fptr = fopen("data\\save\\save3.dat", "rb");
	}
	
	if(fptr == NULL)
	{
		puts("ERROR: The file does not exist.");
		assert(0);
	}
	else if(fread(&player.hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&player.fhp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_fhp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&player.damage,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_damage failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&player.output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&bgX,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load bgX failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&bgY,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load bgY failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy_num,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy_num failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(BgName,sizeof(char),strlen(BgName),fptr))
	{
		puts("ERROR: Load BgName failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(bp,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Load bp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(bpIdx,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Load bpIdx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(bpAmount,sizeof(int),3,fptr))
	{
		puts("ERROR: Load bpAmount failed.");
		fclose(fptr);
		assert(0);
	}
	else{
		fclose(fptr);
		puts("Load successfully");
	}
	
	
    //只需進行開檔及讀檔，若檔案不存在須告知玩家
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例  
}

void del(){
	//檔案清空
	//print empty
	
	if(IsPrint1){
		fptr = fopen("data\\save\\save1.dat", "wb");
		IsEmpty1 = 0;
	}
	else if (IsPrint2){
		fptr = fopen("data\\save\\save2.dat", "wb");
		IsEmpty2 = 0;
	}
	else if (IsPrint3){
		fptr = fopen("data\\save\\save3.dat", "wb");
		IsEmpty3 = 0;
	}
	
	if(fptr == NULL){
		puts("ERROR: clean file failed.");
		assert(0);
	}
	else{
		puts("clean file successfully");
		fclose(fptr);
	}
}