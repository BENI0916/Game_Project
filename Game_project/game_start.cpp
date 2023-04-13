#include "lib/var.h"
#include "lib/game_start.h"
#include "lib/lunch.h"
#include "lib/save_load.h"
#include "lib/setting.h"

//遊戲開始執行會先跳來這裡
void gameStart() {
    initgraph(wid, hih);	// 初始化輸出窗口 
	printf("inigraph succes\n");

    /*
    遊戲的開始畫面
    畫面需要有四顆按鈕，分別是:開始遊戲 讀/存檔 設定 結束遊戲
    以下說明各按鈕功能

    開始遊戲:
        按下後執行 lunch.cpp 的 lunch()
        lunch()內的內容無需更動，執行它就好
    讀/存檔:
        按下後進行畫面切換，展示出三個存檔格，按下各存檔格後將跳出兩個按鈕，分別是: 存檔 讀檔
            存檔: 執行 save_load.cpp 的 save()
            讀檔: 執行 save_load.cpp 的 load()
    設定:
        按下後執行 setting.cpp 的 setting()
    結束遊戲:
        按下後終止程式

    各用到之函式詳細內容請至各cpp檔內查看



    */
    lunch();
}