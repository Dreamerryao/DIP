#include "bmp.h"

//�����ļ�·�� 
const char* filepath1 = "1.bmp";
const char* filepath2 = "1-����.bmp";
const char* filepath3 = "2.bmp";
const char* filepath4 = "8bitgray.bmp";

int main(){
	BMPDATA* mybmp = processBMP(filepath1); //��ȡBMP�ļ������лҶ�ת�� 
	outputBMP(filepath2 ,mybmp);//���Ҷ��ļ���ʾ 
	
	BMPDATA* mybmp2 = process2BMP(filepath1);//��ȡBMP�ļ������м��� 
	outputBMP(filepath3 ,mybmp2);//���������ļ���ʾ 
	
	BMPDATA* mybmp3 = process3BMP(filepath1);//��ȡBMP�ļ�������8λ�Ҷ�ת��
	output8bitBMP(filepath4,mybmp3);
	 
	return 0;
}

