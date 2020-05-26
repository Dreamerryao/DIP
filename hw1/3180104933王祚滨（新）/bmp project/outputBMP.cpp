#include "bmp.h"

void outputBMP(const char *filepath ,BMPDATA* bmp){
	
	//初始化 
	WORD bfType;
	BITMAPFILEHEADER bf;  
    BITMAPINFOHEADER bi;
    unsigned char pixVal = '\0';
    int offset = 0;
    
    
	FILE* fp = fopen(filepath,"wb");
	if (fp ==NULL)  
    {  
       printf("output fail");
    }
    
    offset = bmp->width*3%4;
    if(offset!=0){
    	offset = 4-offset;
	}
	  bfType = 0x4D42;
	fwrite(&bfType, sizeof(WORD), 1, fp); 
	
	 //进行bf设置 
		bf.bfSize = 54 +bmp->height*(bmp->width*3 +offset);
        bf.bfReserved1 = 0;  
        bf.bfReserved2 = 0;  
        bf.bfOffBits = 54 ; 
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp); 
	//进行bi设置 
		bi.biSize = 40;  
        bi.biWidth = bmp->width; 
		//debug 
        printf("%d\n",bmp->width);
        bi.biHeight = bmp->height;
		//debug 
		 printf("%d\n",bmp->height);
        bi.biPlanes = 1;  
        bi.biBitCount = 24;  
        bi.biCompression = 0;  
        bi.biSizeImage = bmp->height*(bmp->width*3 +offset);  
        bi.biXPelsPerMeter = 0;  
        bi.biYPelsPerMeter = 0;  
        bi.biClrUsed = 0;  
        bi.biClrImportant = 0;  
		fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);
		int flag = 0;
		//这里将遍历反过来 
	for (int i=bmp->height-1; i>-1; i--)  
        {  
        
            for (int j=0; j<bmp->width; j++)  
            {  
                 pixVal = bmp->data[i*bmp->width*3+j*3];  
                fwrite(&pixVal, sizeof(unsigned char), 1, fp);
				     pixVal = bmp->data[i*bmp->width*3+j*3+1];  
                fwrite(&pixVal, sizeof(unsigned char), 1, fp);
                 pixVal = bmp->data[i*bmp->width*3+j*3+2];  
                fwrite(&pixVal, sizeof(unsigned char), 1, fp);

            }  
            if (offset!=0)  
            {  
                for (int k=0; k<offset; k++)  
                {  
                    pixVal = '\0';  
                    fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
                }  
            }  
        } 

		 fclose(fp);  
  	//成功提示 
    printf("output finish\n");  
    }  

