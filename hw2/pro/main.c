#include "bmp.h"
  	const char* filepath1 = "8bitgray.bmp";

	const char* filepath2 = "binary.bmp";
	const char* filepath3 = "dilation.bmp";
	const char* filepath4 = "erosion.bmp";
	const char* filepath5 = "open.bmp";
	const char* filepath6 = "close.bmp";
	int flag = 0;
	int main(){
		//��ȡgrayͼ 
	BMPDATA* gray = process(filepath1); 
		//���ж�ֵ�� 
	output(filepath2,gray);
		//��ȡ��ֵ��֮���ͼƬ 
	BMPDATA* binary = process(filepath2); 
		//dilation���� 
	BMPDATA* mydilation = dilation(binary);
		//��� 
	output(filepath3,mydilation);
		
		//ersion ���� 
	BMPDATA* myerosion = erosion(binary);
		//��� 
	output(filepath4,myerosion);
	
		//open���� ����erosion���data����dilation���� 
	BMPDATA* myopen = dilation(myerosion);
	output(filepath5,myopen);
		//close���� ����dilation���data����erosion���� 
	BMPDATA* myclose = erosion(mydilation);
	output(filepath6,myclose);
	return 0;
	}

