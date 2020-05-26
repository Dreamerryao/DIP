#include "bmp.h"

void Laplace(const char *filepath,BMPDATA* bmp){
	
	
	
	WORD bfType;
	BITMAPFILEHEADER bf;  
    BITMAPINFOHEADER bi;
    unsigned char pixVal = '\0';
    RGB* quad;
    int offset = 0;

    
    
	FILE* fp = fopen(filepath,"wb");
	if (fp ==NULL)  
    {  
       printf("output fail");
    }
    
    offset = bmp->width%4;
    if(offset!=0){
    	offset = 4-offset;
	}
	  bfType = 0x4D42;
	fwrite(&bfType, sizeof(WORD), 1, fp); 
	
	 
		bf.bfSize = 54 +256*4 + bmp->height*(bmp->width+offset);  
        bf.bfReserved1 = 0;  
        bf.bfReserved2 = 0;  
        bf.bfOffBits = 54 +256*4;  
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp); 
		
		bi.biSize = 40;  
        bi.biWidth = bmp->width;  
        printf("%d\n",bmp->width);
        bi.biHeight = bmp->height;  
        bi.biPlanes = 1;  
        bi.biBitCount = 8;  
        bi.biCompression = 0;  
        bi.biSizeImage = bmp->height*(bmp->width+offset);  
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
		
	
		int ** LP;
		LP= (int **)malloc(sizeof(int *)*bmp->height);
		for(int i=0;i<bmp->height;i++){
			LP[i] = (int *)malloc(sizeof(int)*bmp->width);
			
		}
		
		for(int i=0;i<bmp->height;i++){
			for(int j=0;j<bmp->width;j++){
				LP[i][j] = 0;
			}
		}
		for(int i=1;i<bmp->height-1;i++){
			for(int j=1;j<bmp->width-1;j++){
				LP[i][j] = bmp->data[i][j-1]+bmp->data[i][j+1]
//						   +bmp->data[i-1][j-1]+bmp->data[i-1][j]+bmp->data[i-1][j+1]
//						   +bmp->data[i+1][j-1]+bmp->data[i+1][j]+bmp->data[i+1][j+1]
						   +bmp->data[i-1][j]+bmp->data[i+1][j]
						   -bmp->data[i][j]*4;
				
				LP[i][j]=-1*LP[i][j];
				
			}
		}


	for(int i=0;i<bmp->height;i++)
        {  
        	for(int j=0;j<bmp->width;j++)

            {  
            //越界判定 
            	if(bmp->data[i][j]+LP[i][j]*0.1>255)
            	pixVal =255;
            	if(bmp->data[i][j]+LP[i][j]*0.1<0)
            	pixVal = 0;
            	//LP输出为enhancement图像 
//				if(LP[i][j]>255)
//				pixVal = 255;
//				if(LP[i][j]<0)
//				pixVal = 0;
			//赋值 
            	else
                pixVal = bmp->data[i][j]+LP[i][j]*0.1;
//				pixVal = LP[i][j];
				 
               
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
