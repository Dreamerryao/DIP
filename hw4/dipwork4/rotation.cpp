 #include "bmp.h"

double afterx(int x,int y ,int cx,int cy,double angle){
	return cx+(x-cx)*cos(angle)-(y-cy)*sin(angle);
} 
double aftery(int x,int y,int cx,int cy,double angle){
	return cy+(x-cx)*sin(angle)+(y-cy)*cos(angle);
}
int computeWidth(int width,int height,int cx,int cy,double angle){
	double Xarray[4];
	double minX=10001,maxX=-1;
	Xarray[0]=afterx(0,0,cx,cy,angle);
	Xarray[1]=afterx(0,height,cx,cy,angle);
	Xarray[2]=afterx(width,0,cx,cy,angle);
	Xarray[3]=afterx(width,height,cx,cy,angle);
	
	for(int i=0;i<4;i++){
		if(Xarray[i]<minX)
		minX = Xarray[i];
		if(Xarray[i]>maxX)
		maxX = Xarray[i];
	}
	return (int)(maxX-minX);
}
int computeHeight(int width,int height,int cx,int cy,double angle){
	double Yarray[4];
	double minY=10001,maxY=-1;
	Yarray[0]=aftery(0,0,cx,cy,angle);
	Yarray[1]=aftery(0,height,cx,cy,angle);
	Yarray[2]=aftery(width,0,cx,cy,angle);
	Yarray[3]=aftery(width,height,cx,cy,angle);
	
	for(int i=0;i<4;i++){
		if(Yarray[i]<minY)
		minY = Yarray[i];
		if(Yarray[i]>maxY)
		maxY = Yarray[i];
	}
	return (int)(maxY-minY);
}

 void rotation(const char *filepath,BMPDATA* bmp,double angle){
 	
 	int cx = bmp->width/2;
 	int cy = bmp->height/2;
 	printf("cx = %d\n",cx);
 	printf("cy = %d\n",cy);
	printf("newWidth = %d\n",computeWidth(bmp->width,bmp->height,cx,cy,angle));
		printf("newHeight = %d\n",computeHeight(bmp->width,bmp->height,cx,cy,angle));
 	int newWidth = computeWidth(bmp->width,bmp->height,cx,cy,angle);
 	int newHeight = computeHeight(bmp->width,bmp->height,cx,cy,angle);
 	int newCx = newWidth/2;
 	int newCy = newHeight/2;
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
	printf("init finish\n");
	
	for(int i=0;i<bmp->height;i++){
		for(int j=0;j<bmp->width;j++){
			float newX,newY; 
			newX = afterx(j,i,cx,cy,angle)+newCx-cx;
			newY = aftery(j,i,cx,cy,angle)+newCy-cy;
			if((int)newY >= newHeight || (int)newX >= newWidth||(int)newY <0||(int)newX<0)
			continue;
			else{
				newdata[(int)newY][(int)newX]=bmp->data[i][j];
				flag[(int)newY][(int)newX] = 1;
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
