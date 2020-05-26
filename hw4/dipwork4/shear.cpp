#include "bmp.h"

void shear(const char *filepath,BMPDATA* bmp,double xaxis){
	
	
	WORD bfType;
	BITMAPFILEHEADER bf;  
    BITMAPINFOHEADER bi;
    unsigned char pixVal = '\0';
    RGB* quad;
    int offset = 0;
	int newWidth = bmp->height*tan(xaxis<=0?-1*xaxis:xaxis) +bmp->width;
    int myflag = 0;
    if(xaxis<=0){
    	myflag = 1;
    	xaxis = -1*xaxis;
	}
    
    
	FILE* fp = fopen(filepath,"wb");
	if (fp ==NULL)  
    {  
       printf("output fail");
    }
    
    offset = newWidth%4;
    if(offset!=0){
    	offset = 4-offset;
	}
	  bfType = 0x4D42;
	fwrite(&bfType, sizeof(WORD), 1, fp); 
	
	 
		bf.bfSize = 54 +256*4 + bmp->height*(newWidth+offset);  
        bf.bfReserved1 = 0;  
        bf.bfReserved2 = 0;  
        bf.bfOffBits = 54 +256*4;  
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp); 
		
		bi.biSize = 40;  
        bi.biWidth = newWidth;  
//        printf("%d\n",bmp->width);
        bi.biHeight = bmp->height;  
        bi.biPlanes = 1;  
        bi.biBitCount = 8;  
        bi.biCompression = 0;  
        bi.biSizeImage = bmp->height*(newWidth+offset);  
        bi.biXPelsPerMeter = 0;  
        bi.biYPelsPerMeter = 0;  
        bi.biClrUsed = 256;  
        bi.biClrImportant = 256;  
		fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);
		
		quad = (RGB*)malloc(sizeof(RGB)*256);  
        for (int i=0; i<256; i++)  
        {  
            quad[i].rgbBlue = i;  
            quad[i].rgbGreen = i;  
            quad[i].rgbRed = i;  
            quad[i].rgbReserved = 0;  
        }  
        fwrite(quad, sizeof(RGB), 256, fp);  
        free(quad); 
		
	for (int i=0;i<bmp->height;i++)  
        {  
            for (int j=0;j<newWidth;j++)  
            {  
            
				if(myflag ==1&&j>=((bmp->height-1-i)*tan(xaxis))&&j<=(bmp->height-1-i)*tan(xaxis)+bmp->width-1){
					pixVal = bmp->data[i][j-(int)((bmp->height-1-i)*tan(xaxis))];
					}
				
				else if(myflag ==0&&j>=(i*tan(xaxis))&&j<=i*tan(xaxis)+bmp->width-1){
					pixVal = bmp->data[i][j-(int)(i*tan(xaxis))];
					}
					
				else{
					pixVal = 255;
				}
                fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
            }  
            if (offset!=0)  
            {  
                for (int k=0; k<offset; k++)  
                {  
                    pixVal = 0;  
                    fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
                }  
            }  
        } 
		 fclose(fp);  
  
    printf("output finish"); 
	
}
