#include "bmp.h"

//定义文件路径 
const char* filepath1 = "1.bmp";
const char* filepath2 = "1-副本.bmp";
const char* filepath3 = "2.bmp";
const char* filepath4 = "8bitgray.bmp";

int main(){
	BMPDATA* mybmp = processBMP(filepath1); //读取BMP文件并进行灰度转化 
	outputBMP(filepath2 ,mybmp);//将灰度文件显示 
	
	BMPDATA* mybmp2 = process2BMP(filepath1);//读取BMP文件并进行加亮 
	outputBMP(filepath3 ,mybmp2);//将加亮后文件显示 
	
	BMPDATA* mybmp3 = process3BMP(filepath1);//读取BMP文件并进行8位灰度转化
	output8bitBMP(filepath4,mybmp3);
	 
	return 0;
}

