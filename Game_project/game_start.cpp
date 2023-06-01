#include "lib/var.h"
#include "lib/game_start.h"
#include "lib/lunch.h"
#include "lib/save_load.h"
#include "lib/setting.h"
#include "lib/effect.h"

PIMAGE SetImg,FolderImg,screen;

//遊戲開始執行會先跳來這邊 
void gameStart() 
{
    initgraph(wid, hih);	// 初始化窗口 
	printf("inigraph succes\n");
	screen = newimage();
	putLogo(); //播放LOGO
	
	mciSendString (TEXT("open audio\\bgm\\title.mp3 alias titlemusic"), NULL,0,NULL);
	mciSendString (TEXT("play titlemusic repeat"), NULL,0,NULL);
	
	PIMAGE MenubgImg = newimage(wid,hih);
	
    //創建臨時圖像
    PIMAGE tmp = newimage();
    getimage(tmp,"images\\menu\\menubg.png");
    //獲取圖像的寬高
	int tmpWidth = getwidth(tmp);
    int tmpHeight = getheight(tmp);
    //將背景圖像繪製成指定大小
    putimage(MenubgImg, 0, 0, wid, hih, tmp, 0, 0, tmpWidth, tmpHeight);
    //銷毀臨時圖像
    delimage(tmp);
    tmp = NULL;
    //繪製背景圖像

    //battle beast logo
    PIMAGE BattleImg = newimage();
    getimage(BattleImg,"images\\menu\\battle.png");
    
    //start button
    PIMAGE StartImg = newimage();
    getimage(StartImg,"images\\menu\\start.png");
    
    //quit button
    PIMAGE QuitImg = newimage();
    getimage(QuitImg,"images\\menu\\quit.png");
    
    //setting button
    SetImg = newimage();
    getimage(SetImg,"images\\menu\\setting.png");
    
    //foler button
    FolderImg = newimage();
    getimage(FolderImg,"images\\menu\\white_folder.png");
    
    
    mouse_msg msg = {0};
	
	// 新增 enemy_num < 2 : 用來結束程式
    for(;is_run();delay_fps(60))
    {
    	//char str[32];
        //int x, y;
        //mousepos(&x, &y);
        //sprintf(str, "%4d %4d", x, y);
        //outtextxy(0, 0, str);
		putimage(0,0,MenubgImg);
		putimage_withalpha(NULL,BattleImg,50,20);
		putimage_withalpha(NULL,StartImg,300,550);
		putimage_withalpha(NULL,QuitImg,820,550);
		putimage_withalpha(NULL,SetImg,1170,35);
		putimage_withalpha(NULL,FolderImg,1170,580);
        
    	//獲取鼠標訊息
    	while (mousemsg())
    	{
    		msg = getmouse();
		}
		if((msg.x >= 299 && msg.x <= 515) && (msg.y >= 555 && msg.y <= 603) && msg.is_left())
		{
			//點擊開始
			flushkey();
			flushmouse();
			getimage(screen,0,0,wid,hih);
			fadeOut();
			mciSendString(TEXT("stop titlemusic"),NULL,0,NULL);
			mciSendString(TEXT("close titlemusic"),NULL,0,NULL);
			newGame();
			lunch();
			msg = {0};
			mciSendString (TEXT("open audio\\bgm\\title.mp3 alias titlemusic"), NULL,0,NULL);
			mciSendString (TEXT("play titlemusic repeat"), NULL,0,NULL);
		}
		else if((msg.x >= 825 && msg.x <= 991) && (msg.y >= 552 && msg.y <= 603) && msg.is_left())
		{
			//點擊結束
			flushkey();
			flushmouse();
			fadeOut();
			mciSendString(TEXT("stop titlemusic"),NULL,0,NULL);
			mciSendString(TEXT("close titlemusic"),NULL,0,NULL);
			delimage(MenubgImg);
			delimage(StartImg);
			delimage(QuitImg);
			delimage(BattleImg);
			closegraph();
			exit(0);
		}
		else if((msg.x >= 1177 && msg.x <= 1229) && (msg.y >= 46 && msg.y <= 86) && msg.is_left())
		{
			//點擊設定
			flushkey();
			flushmouse();
			setting();
		}
		else if((msg.x >= 1176 && msg.x <= 1238) && (msg.y >= 595 && msg.y <= 638) && msg.is_left())
		{
			//點擊資料夾
			flushkey();
			flushmouse();
			SaveLoadSystem();
		}
	}
    /*
    遊戲的開始畫面
	畫面需要有四顆按鈕，分別是:開始遊戲 讀/存檔 設定 結束遊戲
	以下說明各按鈕功能
	
	開始遊戲 :
		按下後執行 lunch.cpp 的 lunch() 
		lunch()內的內容無須更動，執行它就好
	讀/存檔:
		按下後進行畫面切換，展示出三個存檔格，按下個存檔格後將跳出兩個按鈕，分別是: 存檔 讀檔 
			存檔: 執行 save_load.cpp 的 save()
			讀檔: 執行 save_load.cpp 的 load()
	設定:
		按下後執行 setting.cpp 的 setting()
	結束遊戲:
		按下後終止程式
		
	各用到之函式詳細內容請至各cpp檔內查看 


    */
    //lunch();
}