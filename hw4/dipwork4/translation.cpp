#include "bmp.h"

void translate(const char *filepath,BMPDATA* bmp,int x,int y){
	
	WORD bfType;
	BITMAPFILEHEADER bf;  
    BITMAPINFOHEADER bi;
    unsigned char pixVal = '\0';
    RGB* quad;
    int offset = 0;
	
	int xflag = 0;
	int yflag = 0;
	if(x<=0)
	xflag = 1;
	if(y<=0)
	yflag = 1;
    int moveX = x<0?-1*x:x;
    int moveY = y<0?-1*y:y;
    

	FILE* fp = fopen(filepath,"wb");
	if (fp ==NULL)  
    {  
       printf("output fail");
    }
    
    offset = (bmp->width+moveX)%4;
    if(offset!=0){
    	offset = 4-offset;
	}
	  bfType = 0x4D42;
	fwrite(&bfType, sizeof(WORD), 1, fp); 
	
	 
		bf.bfSize = 54 +256*4 + (bmp->height+moveY)*(bmp->width+moveX+offset);  
        bf.bfReserved1 = 0;  
        bf.bfReserved2 = 0;  
        bf.bfOffBits = 54 +256*4;  
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp); 
		
		bi.biSize = 40;  
        bi.biWidth = bmp->width+moveX;  
//        printf("%d\n",bmp->width);
        bi.biHeight = bmp->height+moveY;  
        bi.biPlanes = 1;  
        bi.biBitCount = 8;  
        bi.biCompression = 0;  
        bi.biSizeImage = (bmp->height+moveY)*(bmp->width+moveX+offset);  
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
		
		
		 
        for(int i=0;i<bmp->height+moveY;i++)
        {  
			  for(int j=0;j<bmp->width+moveX;j++)
            {  
            	if(xflag==0&&i<=moveY){
            		pixVal = 255;
            		fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
            		continue;
				}
				if(xflag ==1&&i>=bmp->height){
            		pixVal = 255;
            		fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
            		continue;
		
				}
				if(yflag ==0&&j<=moveX){
			
						pixVal = 255;
            		fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
            		continue;
				}
            	if(yflag ==1&&j>=bmp->width){
						pixVal = 255;
            		fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
            		continue;
				}
				
				
				if(xflag ==1&&yflag ==1)
                pixVal = bmp->data[i][j];
                if(xflag ==1&&yflag ==0)
                pixVal = bmp->data[i][j-moveX];
                if(xflag ==0&&yflag ==1)
                pixVal = bmp->data[i-moveY][j];
                if(xflag ==0&&yflag ==0)
                pixVal = bmp->data[i-moveY][j-moveX];
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
