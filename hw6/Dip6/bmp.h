#ifndef BMP_H  
#define BMP_H  
 
#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>
#define pi 3.14159265

typedef unsigned short WORD;
typedef unsigned long DWORD; 

//define WORD&&DWORD
typedef struct{
	int width;
	int height;
	unsigned char **data;
}BMPDATA; 

typedef struct  
{  
//	WORD    bfType;  //Describe the file type. It must be 0x4D42
	DWORD    bfSize;  
	WORD    bfReserved1; //reserved,must be zero. 
	WORD    bfReserved2; //reserved,must be zero.
	DWORD    bfOffBits; 
	//Describe the offset from the beginning of the fileheader 
	//to the real image data with bytes. 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

 
typedef struct  
{  
	DWORD  biSize;   
	long   biWidth;   
	long  biHeight;   
	WORD   biPlanes; //Number of planes. Always be 1..  
	WORD   biBitCount;  
	DWORD  biCompression;   
	DWORD  biSizeImage;  //Image size with bytes. When biCompression=BI_RGB, biSizeImage=0. 
	long   biXPelsPerMeter;   
	long   biYPelsPerMeter;   
	DWORD   biClrUsed; //Number of color indices used in the bitmap (0->all the palette items are used).  
	DWORD   biClrImportant;  //Number of important color indices for image display.
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
 
typedef struct   
{  
	unsigned char rgbBlue; //1 byte for blue 
	unsigned char rgbGreen; //1 byte for green
	unsigned char rgbRed; //1 byte for red 
	unsigned char rgbReserved; //ALWAYS ZERO
} RGB,*PRGB;  

  BMPDATA* readbmp(const char *filepath);
  void BilFilter(const char *filepath,BMPDATA* bmp);

#endif



