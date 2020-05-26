#include "bmp.h"


BMPDATA* readbmp(const char *filepath){
	BMPDATA* bmp = NULL;
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	unsigned char pixVal='\0';
	int width = 0;
	int height = 0;
	int offset = 0;
	RGB* quad;
	WORD type;
	
		
	bmp = (BMPDATA*)malloc(sizeof(BMPDATA));
	FILE* fp = fopen(filepath,"rb");
	if(fp==NULL){
		printf(" open file error");
		return NULL;
		
	}
	fread(&type,sizeof(WORD),1,fp);
	if(type ==  0x4D42){
			printf("read a bmp file!\n");
		fread(&bf,sizeof(BITMAPFILEHEADER),1,fp);
		
		//debug
			printf("read bf\n");
			printf("bfsize = %d\n",bf.bfSize); 
			printf("bfReserved1 = %d\n",bf.bfReserved1);
			printf("bfReserved2 = %d\n",bf.bfReserved2);
			printf("bfOffBits = %d\n",bf.bfOffBits);
		fread(&bi,sizeof(BITMAPINFOHEADER),1,fp);
		//debug
			printf("read bi\n");
			printf("biSize = %d\n",bi.biSize);
			printf("biwidth = %d\n",bi.biWidth);
			printf("biHeight = %d\n",bi.biHeight);
			printf("biPlanes = %d\n",bi.biPlanes);
			printf("biBitCount = %d\n",bi.biBitCount);
			printf("biSizeImage = %d\n",bi.biSizeImage);
			printf("biXPelsPerMeter = %d\n",bi.biXPelsPerMeter);
			printf("biYPelsPerMeter = %d\n",bi.biYPelsPerMeter);
			printf("biClrUsed = %d\n",bi.biClrUsed);
			printf("biClrImportant = %d\n",bi.biClrImportant);
				
		width = bi.biWidth;
		height = bi.biHeight;
		bmp->width=width;
		bmp->height=height;
		bmp->data = (unsigned char**)malloc(sizeof(unsigned char*)*height);
		for(int i=0;i<height;i++){
			bmp->data[i] = (unsigned char *)malloc(sizeof(unsigned char)*width);
		} 
		offset = width%4;
    if(offset!=0){
    	offset = 4-offset;
	}
		quad = (RGB*)malloc(sizeof(RGB)*256);
		fread(quad,sizeof(RGB),256,fp);
		free(quad);
		printf("!");
		
		
		for (int i=0;i<height;i++)  
        {  
            for (int j=0; j<width; j++)  
            {  
               fread(&pixVal,sizeof(unsigned char),1,fp); 

			   bmp->data[i][j] = pixVal;
            }  
            if (offset!=0)  
            {  
                for (int k=0; k<offset; k++)  
                {  
                   fread(&pixVal,sizeof(unsigned char),1,fp); 
                }  
            }  
        }  
    printf("read finish");  
}
return bmp;
}
