#include "bmp.h"

const char* filepath1 = "./Data/histarget.bmp";
const char* filepath2 = "./Data/mirror2.bmp";
const char* filepath3 = "./Data/translate2.bmp";
const char* filepath4 = "./Data/shear2.bmp";
const char* filepath5 = "./Data/scale2.bmp";
const char* filepath6 = "./Data/rotate2.bmp";

int main(){
	
	BMPDATA* gray = readbmp(filepath1); //读取8bit位图 
	mirror(filepath2,gray);
	BMPDATA* tr = readbmp(filepath1); 
	translate(filepath3,tr,100,200);//进行translate操作 
	
	BMPDATA* se = readbmp(filepath1);
	shear(filepath4,se,-pi*45/180); 
	BMPDATA* sc = readbmp(filepath1);
	scale(filepath5,sc,2,2);
	BMPDATA* ro = readbmp(filepath1);
	rotation(filepath6,ro,-pi*60/180);
	return 0;
	}
