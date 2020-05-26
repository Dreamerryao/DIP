#include "bmp.h"

BMPDATA* processBMP(const char *filepath){
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

		if(bi.biBitCount==24){
			printf(" process 24 bit map\n");
			bmp->width = width;
			bmp->height = height;
			bmp->data = (unsigned char*)malloc(sizeof(unsigned char)*width*3*height);
			//获取data所需空间，1像素3位，共需要 width*3*height位
			//计算每行的偏移量 
			offset = 3*width%4;
			if(offset !=0){
				offset = 4 - offset;
			}
			
			int a ,j,k;
			//遍历，调整 
			for( a = 0;a<height;a++){
				for ( j = 0;j<width;j++ ){
						fread(&b,sizeof(unsigned char),1,fp);
						fread(&g,sizeof(unsigned char),1,fp);
						fread(&r,sizeof(unsigned char),1,fp);
					
						//进行灰度转化	
						int y = (b*299+g*587+r*114)/1000;
						//进行边界判定；
						//在这里将30以下调为30 
						if(y>255)
						y=255;
						if(y<30)
						y=30;				
						bmp->data[(height-a-1)*width*3 +j*3] = y;
						bmp->data[(height-a-1)*width*3 +j*3+1] =y;
						bmp->data[(height-a-1)*width*3 +j*3+2] =y;

				}
				//偏移读取 ，为了保证读到的数据准确 
				if(offset!=0){
						for( k=0;k<offset;k++){
							fread(&reserved,sizeof(unsigned char),1,fp);
						}
					}
			}
	
	}
	}
	//处理成功提示 
	printf("process success!\n");
	//将bmp反馈，进行输出操作 
	return bmp;
}
