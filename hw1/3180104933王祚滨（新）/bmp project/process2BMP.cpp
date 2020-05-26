#include "bmp.h"

BMPDATA* process2BMP(const char *filepath){
	//初始化 
	BMPDATA* bmp = NULL;
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	int width = 0;
	int height = 0;
	int offset = 0;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char reserved;
	unsigned char y;
	unsigned char u;
	unsigned char v;
	RGB* PRGB;
	WORD type;
	
	bmp = (BMPDATA*)malloc(sizeof(BMPDATA));
	FILE* fp = fopen(filepath,"rb");
	if(fp==NULL){
		printf(" open file error");
		return NULL;
		
	}
	fread(&type,sizeof(WORD),1,fp);
	if(type ==  0x4D42){
			printf("read a bmp file!\n");//判断到这一步
		fread(&bf,sizeof(BITMAPFILEHEADER),1,fp);
			printf("read bf\n");
			printf("bfsize = %d\n",bf.bfSize); 
			printf("%d\n",bf.bfReserved1);
			printf("%d\n",bf.bfReserved2);
			printf("bfOffBits = %d\n",bf.bfOffBits);
		fread(&bi,sizeof(BITMAPINFOHEADER),1,fp);
			printf("read bi\n");
			printf("width = %d\n",bi.biWidth);
			printf("height = %d\n",bi.biHeight);
			printf("biBitCount = %d\n",bi.biBitCount);
			printf("%d\n",bi.biPlanes);
			printf("%d\n",bi.biClrUsed);
			printf("%d\n",bi.biClrImportant);
			printf("%d\n",bi.biXPelsPerMeter);
			printf("%d\n",bi.biYPelsPerMeter);
			printf("%d\n",bi.biSizeImage);
			printf("%d\n",bi.biSize);
			
		width = bi.biWidth;
		height = bi.biHeight;

		
		//处理24bitmap 
		if(bi.biBitCount==24){
			printf("24 bit map\n");
			bmp->width = width;
			bmp->height = height;
			bmp->data = (unsigned char*)malloc(sizeof(unsigned char)*width*3*height);
			offset = 3*width%4;
			if(offset !=0){
				offset = 4 - offset;
			}
			printf("%d\n",sizeof(unsigned char)*width*3*height);
			
			int a ,j,k;
			
			for( a = 0;a<height;a++){
				for ( j = 0;j<width;j++ ){
						fread(&b,sizeof(unsigned char),1,fp);
						fread(&g,sizeof(unsigned char),1,fp);
						fread(&r,sizeof(unsigned char),1,fp);
						//进行加亮处理	
						int y = (b*299+g*587+r*114)/1000;
						int u =-0.147*r - 0.289*g +0.463*b;
						int v = 0.615*r - 0.515*g - 0.100*b;
						y = y+20;//提高亮度 
						int bnew = y + 2.032*u;
						//进行边界判定 
						if(bnew>255)
						bnew = 255;
						if(bnew<0)
						bnew = 0; 
						int gnew = y - 0.395*u-0.581*v;
						if(gnew>255)
						gnew = 255;
						if(gnew<0)
						gnew = 0; 
						int rnew = y + 1.140*v;
						if(rnew>255)
						rnew = 255;
						if(rnew<0)
						rnew = 0; 
						//调亮后rgb保存 
						bmp->data[(height-a-1)*width*3 +j*3] = bnew;
						bmp->data[(height-a-1)*width*3 +j*3+1] =gnew;
						bmp->data[(height-a-1)*width*3 +j*3+2] =rnew;

				}
				//偏移处理 
				if(offset!=0){
						for( k=0;k<offset;k++){
							fread(&reserved,sizeof(unsigned char),1,fp);
						}
					}
			}			
		}

	}

	printf("process success!\n");
	return bmp;
}
