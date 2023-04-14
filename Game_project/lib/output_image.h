#ifndef OUTPUT_IMG_H
#define OUTPUT_IMG_H

#include <graphics.h> 

void output_image();

void loadBG(char filename[]);

void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h);

#endif
