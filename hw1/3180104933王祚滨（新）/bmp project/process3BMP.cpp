#include "bmp.h"

BMPDATA* process3BMP(const char *filepath){
	
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
	WORD type;
	
	bmp = (BMPDATA*)malloc(sizeof(BMPDATA));
	FILE* fp = fopen(filepath,"rb");
	if(fp==NULL){
		printf(" open file error");
		return NULL;
		
	}
	fread(&type,sizeof(WORD),1,fp);
	if(type ==  0x4D42){
			printf("read a bmp file!\n");//?§Ø???????
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
		offset = bf.bfOffBits;
		if(bi.biBitCount==24){
			printf("24 bit map\n");
			bmp->width = width;
			bmp->height = height;
			bmp->data = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
			
			offset = 3*width%4;
			if(offset !=0){
				offset = 4 - offset;
			}
			printf("%d\n",sizeof(unsigned char)*width*height);

			int a ,j,k;
			for( a = 0;a<height;a++){
		
				for ( j = 0;j<width;j++ ){
						fread(&b,sizeof(unsigned char),1,fp);
						fread(&g,sizeof(unsigned char),1,fp);
						fread(&r,sizeof(unsigned char),1,fp);	
						bmp->data[(height-a-1)*width +j] = (b*299+g*587+r*114+500)/1000;

//					}
					
				}
				
				if(offset!=0){
						for( k=0;k<offset;k++){
							fread(&reserved,sizeof(unsigned char),1,fp);
						}
					}
			}

			
		}
		
	}
	
	return bmp;
}

