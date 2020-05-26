#include "bmp.h"

BMPDATA* erosion(BMPDATA* bmp){
	BMPDATA * mybmp = NULL;
	
	mybmp = (BMPDATA*)malloc(sizeof(BMPDATA));
	unsigned char **newdata;
	mybmp->height = bmp->height;
	mybmp->width = bmp->width;
	//init
			newdata = (unsigned char**)malloc(sizeof(unsigned char*)*bmp->height);
		for(int i=0;i<bmp->height;i++){
			newdata[i] = (unsigned char *)malloc(sizeof(unsigned char)*bmp->width);
		} 
		
		for(int i = 0;i<bmp->height;i++){
		for(int j=0;j<bmp->width;j++){
			newdata[i][j]=255;
		}
	}

	int margin = 1;
	for(int i=margin;i<bmp->height-margin;i++){
		for(int j=margin;j<bmp->width-margin;j++){
			if(bmp->data[i][j]==0&&bmp->data[i][j+1]==0
		&&bmp->data[i+1][j]==0
		&&bmp->data[i-1][j]==0&&bmp->data[i][j-1]==0
		){
				newdata[i][j] = 0;
			}
		}
	}
mybmp->data = newdata;
return mybmp;
}
