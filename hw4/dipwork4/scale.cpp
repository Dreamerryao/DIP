 #include "bmp.h"
 void scale(const char *filepath,BMPDATA* bmp,double x,double y){
 	
 	
 	int newWidth = bmp->width*x;
 	int newHeight = bmp->height*y;
 	WORD bfType;
	BITMAPFILEHEADER bf;  
    BITMAPINFOHEADER bi;
    unsigned char pixVal = '\0';
    RGB* quad;
    int offset = 0;
	int newSize = newWidth*newHeight; 
    
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
	
	 
		bf.bfSize = 54 +256*4 + newHeight*(newWidth+offset);  
        bf.bfReserved1 = 0;  
        bf.bfReserved2 = 0;  
        bf.bfOffBits = 54 +256*4;  
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp); 
		
		bi.biSize = 40;  
        bi.biWidth = newWidth;  
        printf("%d",newWidth);
        bi.biHeight = newHeight;  
        bi.biPlanes = 1;  
        bi.biBitCount = 8;  
        bi.biCompression = 0;  
        bi.biSizeImage = newHeight*(newWidth+offset);  
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
        unsigned char** newdata;
        	newdata = (unsigned char**)malloc(sizeof(unsigned char*)*newHeight);
		for(int i=0;i<newHeight;i++){
			newdata[i] = (unsigned char *)malloc(sizeof(unsigned char)*newWidth);
		}  
		
		unsigned char** flag;
        	flag = (unsigned char**)malloc(sizeof(unsigned char*)*newHeight);
		for(int i=0;i<newHeight;i++){
			flag[i] = (unsigned char *)malloc(sizeof(unsigned char)*newWidth);
		}  
		
		for(int i=0;i<newHeight;i++){
		for(int j=0;j<newWidth;j++){
			flag[i][j] = 0;
			newdata[i][j]=255;
		}
	}

//	unsigned char newdata[newHeight][newWidth]={0};
	printf("init finish\n");
	
//	for(int i=0;i<newHeight;i++){
//		for(int j=0;j<newWidth;j++){
//			float newX,newY; 
//			newX = (j*1.0/x);
//			newY = (i*1.0/y);
//			if(newX >= bmp->width || newY >= bmp->height)
//			newdata[i][j]=255;
//			else
//			newdata[i][j]=bmp->data[int(newY)][int(newX)];
//		}
//	}
	
	for(int i=0;i<newHeight;i++){
		for(int j=0;j<newWidth;j++){
			float newX,newY; 
			newX = (j*1.0/x);
			newY = (i*1.0/y);
			if((int)newY >=  bmp->height || (int)newX >= bmp->width ||(int)newY <0||(int)newX<0)
			continue;
			else{
				newdata[i][j]=bmp->data[int(newY)][int(newX)];
				flag[i][j] = 1;
			}
			
		}
	}
	
	int last[newHeight];
	for(int i=0;i<newHeight;i++){
		int Tlast = -1;
		for(int j=0;j<newWidth;j++){
			if(flag[i][j]==1)
			Tlast = j;
		}
		last[i] = Tlast;
	}
	printf("last[0]=%d\n",last[0]);
	printf("last[height]=%d\n",last[newHeight-1]);
	
	
//	for (int i=0;i<newHeight;i++)  
//        {  
//            for (int j=0;j<newWidth;j++)  
//				 {  	
//                pixVal = newdata[i][j];
//                fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
//            }  
//            if (offset!=0)  
//            {  
//                for (int k=0; k<offset; k++)  
//                {  
//                    pixVal = 0;  
//                    fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
//                }  
//            }  
//        }
	 for (int i=0;i<newHeight;i++)  
        {  
            for (int j=0;j<newWidth;)  
				 {  
				 
				 if(flag[i][j]==1&&j!=last[i]){
				 		int now = j;
				 		pixVal = newdata[i][j];
				 		fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
				 	int h =j+1;
					while(flag[i][h]!=1){
						h++;
					}
					 for(;j+1<h;j++){
					 	pixVal = (int) (newdata[i][h]-newdata[i][now])*(j-now)/(h-now)+newdata[i][now];
					 	fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
					 	
					 }
					 j=h;
				 }
				 else{
				 	pixVal = newdata[i][j];
                fwrite(&pixVal, sizeof(unsigned char), 1, fp);  
                j++;
				 }	
                
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
