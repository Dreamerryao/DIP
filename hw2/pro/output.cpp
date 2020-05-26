#include "bmp.h"
extern int flag;

unsigned char  OSTU(BMPDATA* bmp){

	int width = bmp->width;
	int height = bmp->height;
//	int threshold = 0;
	
	int nHistogram[256] = {0};
	for(int i=0;i<height;i++){
		for(int j = 0;j<width;j++){
			nHistogram[bmp->data[i][j]]++;
		}
	}
	
	unsigned int sumB = 0;
    unsigned int sum1 = 0;
    float wB = 0.0f;
    float wF = 0.0f;
    float mF = 0.0f;
    float max_var = 0.0f;
    float inter_var = 0.0f;
    unsigned char threshold = 0;
    unsigned short index_histo = 0;

    for ( index_histo = 1; index_histo < 256; ++index_histo )
    {
        sum1 += index_histo * nHistogram[ index_histo ];
    }

    for (index_histo = 1; index_histo < 256; ++index_histo)
    {
        wB = wB + nHistogram[ index_histo ];
        wF = width*height - wB;
        if ( wB == 0 || wF == 0 )
        {
            continue;
        }
        sumB = sumB + index_histo * nHistogram[ index_histo ];
        mF = ( sum1 - sumB ) / wF;
        inter_var = wB * wF * ( ( sumB / wB ) - mF ) * ( ( sumB / wB ) - mF );
        if ( inter_var >= max_var )
        {
            threshold = index_histo;
            max_var = inter_var;
        }
    }

    return threshold;
	
}


void output(const char *filepath ,BMPDATA* bmp){
	WORD bfType;
	BITMAPFILEHEADER bf;  
    BITMAPINFOHEADER bi;
    unsigned char pixVal = '\0';
    RGB* quad;
    int offset = 0;
	unsigned char threshold = OSTU(bmp);
    printf("threshold: %d\n",threshold);

    
    
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
		
	for (int i=bmp->height-1; i>-1; i--)  
        {  
            for (int j=0; j<bmp->width; j++)  
            {  
                pixVal = bmp->data[i][j];
//				[i*bmp->width+j];  
				if(flag==0){
					if(pixVal>=threshold)
                pixVal = 255;
                else
                pixVal = 0;

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
			flag++;
		 fclose(fp);  
  
    printf("output finish");  
    }  



