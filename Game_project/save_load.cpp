#include "lib/save_load.h"
#include <stdio.h>
#include <assert.h>

//存檔用函式 
void save() 
{
	FILE *fptr = fopen("data\\save\\save1.dat","wb");
	assert(fptr);
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
		puts("ERROR: The file doesn't exist.\n");
		assert(0);
	}
    //只需進行開檔及讀檔，若檔案不存在須告知玩家
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例  
}