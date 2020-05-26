#include "bmp.h"
  	const char* filepath1 = "8bitgray.bmp";

	const char* filepath2 = "binary.bmp";
	const char* filepath3 = "dilation.bmp";
	const char* filepath4 = "erosion.bmp";
	const char* filepath5 = "open.bmp";
	const char* filepath6 = "close.bmp";
	int flag = 0;
	int main(){
		//读取gray图 
	BMPDATA* gray = process(filepath1); 
		//进行二值化 
	output(filepath2,gray);
		//读取二值化之后的图片 
	BMPDATA* binary = process(filepath2); 
		//dilation操作 
	BMPDATA* mydilation = dilation(binary);
		//输出 
	output(filepath3,mydilation);
		
		//ersion 操作 
	BMPDATA* myerosion = erosion(binary);
		//输出 
	output(filepath4,myerosion);
	
		//open操作 ，对erosion后的data进行dilation操作 
	BMPDATA* myopen = dilation(myerosion);
	output(filepath5,myopen);
		//close操作 ，对dilation后的data进行erosion操作 
	BMPDATA* myclose = erosion(mydilation);
	output(filepath6,myclose);
	return 0;
	}

