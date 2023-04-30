#include "lib/player_move3D.h"
#include "lib/var.h"
#include "lib/output_img.h"
#include "lib/initialization.h"
#include <iostream>
#include <string>
using namespace std;

extern int player_walk_cnt3D,bgX,bgY, inFight;
extern Human player;
extern char BgName[50];
extern Bullet tp_door;
int speed = 3;
int fps = 10;
int table[] = {0,-1,0,1};

void itemwall(int xl, int xr, int yu, int yd) {
    if(bgX <= xl && bgX >= xr && bgY <= yu &bgY >= yd) {
        if(GetAsyncKeyState(0x41) || GetAsyncKeyState('a'))  bgX -= speed;
        if(GetAsyncKeyState(0x44) || GetAsyncKeyState('d'))  bgX += speed;
        if(GetAsyncKeyState(0x53) || GetAsyncKeyState('s'))  bgY += speed;
        if(GetAsyncKeyState(0x57) || GetAsyncKeyState('w'))  bgY -= speed;
    }
}

void keyListener() {
    if(GetAsyncKeyState(0x41) || GetAsyncKeyState('a'))  {
        player.output_idx = 30 + table[player_walk_cnt3D++/fps];
		bgX += speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    if(GetAsyncKeyState(0x44) || GetAsyncKeyState('d'))  {
        player.output_idx = 36 + table[player_walk_cnt3D++/fps];
		bgX -= speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    if(GetAsyncKeyState(0x53) || GetAsyncKeyState('s'))  {
        player.output_idx = 33 + table[player_walk_cnt3D++/fps];
		bgY -= speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    if(GetAsyncKeyState(0x57) || GetAsyncKeyState('w'))  {
        player.output_idx = 27 + table[player_walk_cnt3D++/fps];
		bgY += speed;
        if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
	}
    //home2樓設定
    if (strcmp(BgName, "images\\bg\\home2.png")==0) {
        //地圖牆
        if(bgX  <-360) bgX = -360;
        if(bgX > 375) bgX = 375;
        if(bgY  <-192) bgY = -192;
        if(bgY > 285) bgY = 285;
        //物件牆
        itemwall(75,-39, 180, 54); //電視
        itemwall(370,237,105,-48); //床
        //itemwall(375,313,250,210);
        //itemwall(370,211,98,-75);
        itemwall(-78,-168,285,174);
        itemwall(-78,-246,219,180);
        //背景轉換
        if(bgX >= -214 && bgX <= -169&& bgY >=220 && bgY <=285) {
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2); //讀取背景
        }
    }
    //home1樓設定
    if (strcmp(BgName, "images\\bg\\home1.png")==0) {
        //地圖牆
        if(bgX  <-360) bgX = -360;
        if(bgX > 375) bgX = 375;
        if(bgY  <-192) bgY = -192;
        if(bgY > 285) bgY = 285;
        //物件牆
        itemwall(-231,-360,225,192);
        itemwall(189,-360,-177,-220);
        itemwall(375,273,-177,-220);
        itemwall(375,165,285,264);
        itemwall(135,24,285,264);
        itemwall(138,-30,174,27); //桌子
        //背景轉換
        //上樓
        if(bgX <= -270 && bgY >=228 && bgY <=285) {
            sprintf(BgName,"%s","images\\bg\\home2.png");
            loadBG(BgName,1587/2,1300/2);
        }
        //出門
        if(bgX > 189 && bgX < 270 && bgY <= -186) {
            sprintf(BgName,"%s","images\\bg\\village.png");
            loadBG(BgName, 1859*1.2, 1542*1.3);
            bgX = -483;
            bgY = -1077;
        }
    }
    //村莊設定
    if (strcmp(BgName, "images\\bg\\village.png")==0) {
        //地圖牆
        if(bgX < -2028) bgX = -2028;
        if(bgX > -126) bgX = -126;
        if(bgY < -2016) bgY = -2016;
        if(bgY > -288) bgY = -288;
        //物件牆
        itemwall(-333,-816,-603,-1035); //左上房
        itemwall(-252,-333,-903,-1035); //郵箱
        itemwall(-1137,-1623,-603,-1035); //右上房
        itemwall(-1056,-1137,-903,-1035); //郵箱
        itemwall(-1047,-1713,-1179,-1614); //右下房
        itemwall(-126,-1011,-288,-483); //左上樹
        itemwall(-1122,-1854,-288,-483); //右上樹
        itemwall(-1839,-1959,-480,-1068);
        itemwall(-1839,-1959,-1269,-2016); //右下樹
        itemwall(-126,-912,-1908,-2016); //左下湖
        itemwall(-330,-819,-1326,-1419); //左下柵欄
        itemwall(-336,-456,-1617,-1710);
        itemwall(-1044,-1629,-1809,-1905); //右下柵欄
        //背景轉換
        //回家
        if(bgX >= -510 && bgX <=-459 && bgY >=-1041 && bgY <=-1023) {
            bgX=219;
            bgY=-171;
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2);
        }
        //雜貨店
        if(bgX >= -1311 && bgX <=-1269 && bgY >=-1041 && bgY <=-1023) {
            bgX=219;
            bgY=-171;
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2);
        }
        //賭場
        if(bgX >= -1404 && bgX <=-1359 && bgY >=-1620 && bgY <=-1596) {
            bgX=219;
            bgY=-171;
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2);
        }
        //村子右邊BOSS傳送門
        if(bgX < -1956) {
            inFight=1;
            tp_door_ini();
            player.x = wid / 4; // 暫定 
	        player.y = hih * 0.6; // 暫定 
            player.output_idx = 0;// 輸出圖片編號 
	        player.high = 66;   // 人物圖片的高 
	        player.width = 76;  // 人物圖片的寬
            sprintf(BgName,"%s","images\\bg\\back_ground_01.png");
            loadBG(BgName);
        }
        //村子上方刷怪副本
        if(bgY > -342) {
            //還沒做
            /*inFight=1;
            tp_door_ini();
            player.x = wid / 4; // 暫定 
	        player.y = hih * 0.6; // 暫定 
            player.output_idx = 0;// 輸出圖片編號 
	        player.high = 66;   // 人物圖片的高 
	        player.width = 76;  // 人物圖片的寬
            sprintf(BgName,"%s","images\\bg\\back_ground_01.png");
            loadBG(BgName);*/
        }
    }
    cout << bgX << " " << bgY << "       \r";
}

//g++ *.cpp -o test.exe -lgraphics64 -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lgdiplus