# Game_Project
1.audio bgm wav 轉 mp3

更動檔案
audio/bgm

更動
var.h 增加#pragma comment(lib, "Winmm.lib")

event.cpp game_start.cpp lunch.cpp output_img.cpp player_move3D.cpp中
PlaySound() 改為 mciSendString()
