#include <ege.h>
#include <stdio.h>
#include <graphics.h> 
#define hih 720 
#define wid 1280 
extern PIMAGE new_bg;
PIMAGE ori_bg;
// ori_bg : 原始背景	new_bh : 放大後的背景 
extern int left_walk_cnt, right_walk_cnt, atk_cnt;
// left_walk_cnt, right_walk_cnt : 走路計數器 用於計算走路時輸出的圖片

extern struct human // 玩家的結構  
{
	int x;	// x 座標 
	int y;	// y 座標 
	int hp;	// 血量 
	char dir;// 人物面朝的方向 
	int output_idx; // 用於儲存要輸出的圖片編號 
	PIMAGE player_img[16], player_msk[16]; // 儲存放大後的圖片 
}player;

PIMAGE player_ori_img[16], player_ori_msk[16];
// 原始圖片 

void loading(); // 載入圖片 

void initialization()
{
	ori_bg = newimage();
	
	for(int i = 0; i < 16; i++)
	{
		player_ori_img[i] = newimage(); // 創建圖片 
		player_ori_msk[i] = newimage();
		
		player.player_img[i] = newimage(76, 66); // 創建 76 * 66 大小的圖片 
		player.player_msk[i] = newimage(76, 66);
	}
	
	loading(); // 載入圖片
	// 設定初始值 
	player.x = wid / 2; // 暫定 
	player.y = hih / 2; // 暫定
	player.hp = 5;
	player.dir = 'd';
	player.output_idx = 0;
	
	left_walk_cnt = 0;
	right_walk_cnt = 0;
	atk_cnt = 0;
	
	// 縮放後的圖片儲存在其他位置後
	// 將原本的圖片刪除 
	delimage(ori_bg);
	
	for(int i = 0; i < 16; i++)
	{
		delimage(player_ori_img[i]);
		delimage(player_ori_msk[i]);
	}
}

void loading() // 載入圖片 
{
	getimage(ori_bg, "images\\back_ground_01.png");
	
	getimage(player_ori_msk[0], "images\\main_char\\0_d_stand_msk.png");
	getimage(player_ori_img[0], "images\\main_char\\0_d_stand_img.png");
	
	getimage(player_ori_msk[1], "images\\main_char\\1_a_stand_msk.png");
	getimage(player_ori_img[1], "images\\main_char\\1_a_stand_img.png");
	
	getimage(player_ori_msk[2], "images\\main_char\\2_d_walk_1_msk.png");
	getimage(player_ori_img[2], "images\\main_char\\2_d_walk_1_img.png");
	
	getimage(player_ori_msk[3], "images\\main_char\\3_a_walk_1_msk.png");
	getimage(player_ori_img[3], "images\\main_char\\3_a_walk_1_img.png");
	
	getimage(player_ori_msk[4], "images\\main_char\\4_d_walk_2_msk.png");
	getimage(player_ori_img[4], "images\\main_char\\4_d_walk_2_img.png");
	
	getimage(player_ori_msk[5], "images\\main_char\\5_a_walk_2_msk.png");
	getimage(player_ori_img[5], "images\\main_char\\5_a_walk_2_img.png");
	
	getimage(player_ori_msk[6], "images\\main_char\\6_d_atk_1_msk.png");
	getimage(player_ori_img[6], "images\\main_char\\6_d_atk_1_img.png");
	
	getimage(player_ori_msk[7], "images\\main_char\\7_a_atk_1_msk.png");
	getimage(player_ori_img[7], "images\\main_char\\7_a_atk_1_img.png");
	
	getimage(player_ori_msk[8], "images\\main_char\\8_d_atk_2_msk.png");
	getimage(player_ori_img[8], "images\\main_char\\8_d_atk_2_img.png");
	
	getimage(player_ori_msk[9], "images\\main_char\\9_a_atk_2_msk.png");
	getimage(player_ori_img[9], "images\\main_char\\9_a_atk_2_img.png");
	
	getimage(player_ori_msk[10], "images\\main_char\\10_d_atk_3_msk.png");
	getimage(player_ori_img[10], "images\\main_char\\10_d_atk_3_img.png");
	
	getimage(player_ori_msk[11], "images\\main_char\\11_a_atk_3_msk.png");
	getimage(player_ori_img[11], "images\\main_char\\11_a_atk_3_img.png");
	
	getimage(player_ori_msk[12], "images\\main_char\\12_d_atk_4_msk.png");
	getimage(player_ori_img[12], "images\\main_char\\12_d_atk_4_img.png");
	
	getimage(player_ori_msk[13], "images\\main_char\\13_a_atk_4_msk.png");
	getimage(player_ori_img[13], "images\\main_char\\13_a_atk_4_img.png");
	
	getimage(player_ori_msk[14], "images\\main_char\\14_d_atk_5_msk.png");
	getimage(player_ori_img[14], "images\\main_char\\14_d_atk_5_img.png");
	
	getimage(player_ori_msk[15], "images\\main_char\\15_a_atk_5_msk.png");
	getimage(player_ori_img[15], "images\\main_char\\15_a_atk_5_img.png");
	
	// 將載入後的圖片進行縮放 
	putimage(new_bg, 0, 0, wid, hih, ori_bg, 0, 0, 1000, 740);
	
	for(int i = 0; i < 16; i++)
	{	
		putimage(player.player_msk[i], 0, 0, 76, 66, player_ori_msk[i], 0, 0, 38, 33);
		putimage(player.player_img[i], 0, 0, 76, 66, player_ori_img[i], 0, 0, 38, 33);
	}
	
}
