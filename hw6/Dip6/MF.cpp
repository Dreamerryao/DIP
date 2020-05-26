#include "bmp.h"

void BilFilter(const char *filepath,BMPDATA* bmp){
	
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
		
		
//	for(int i=1;i<bmp->height-1;i++){
//		for(int j=1;j<bmp->width-1;j++){
//			bmp->data[i][j]=(bmp->data[i][j]+bmp->data[i][j-1]+bmp->data[i][j+1]
//						   +bmp->data[i-1][j-1]+bmp->data[i-1][j]+bmp->data[i-1][j+1]
//						   +bmp->data[i+1][j-1]+bmp->data[i+1][j]+bmp->data[i+1][j+1])/9;//�������� 
//			}
//	}	
	
	int r = 4; //���ÿ�����ص�Ҫ����İ뾶 
	
	double sigma_s = 1000, sigma_r = 10; //�ռ����׼�ֵ���׼��
	double s_rad = -0.5/(sigma_s*sigma_s); //�ռ�Ȩ�ر��� 
	double  r_rad = -0.5/(sigma_r*sigma_r);//����Ȩ�ر��� 
	
	double r_weight[256]={0};
	double s_weight[10][10];
	
	for(int i=0;i<256;i++){
		r_weight[i] = exp(i*i*r_rad); //���ݹ�ʽ��������Ȩ�ص����� 
	}
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			s_weight[i][j] = exp(((i-r)*(i-r)+(j-r)*(j-r))*s_rad);//���ݹ�ʽ���пռ�Ȩ�ص����� 
		}
	}

	for(int i=0;i<bmp->height;i++)
        {  
        	for(int j=0;j<bmp->width;j++)
            {  
            	double pixel_data = 0;//��ǰҪ�������ص�����ս�� 
            	double pixel_weight = 0;//��ǰҪ�������ص������Ȩ�� 
            	
            	//�����ص���Χ���б���������Ȩ���Լ�data 
            	for(int hh = i-r;hh<=i+r;hh++){
            		for(int ww = j-r;ww<=j+r;ww++){
            			if((hh-i)*(hh-i)+(ww-j)*(ww-j)>r*r)//Բ�����ж� 
            			continue;
            			if(hh<0||hh>=bmp->height||ww<0||ww>=bmp->width)//Խ���ж� 
            			continue;

            			int mflag = (int)abs(bmp->data[i][j] - bmp->data[hh][ww]);//ͨ������ֵ�Ĳ�������ƶ� 
            			double now_weight = s_weight[hh-i+r][ww-j+r]*r_weight[mflag];
						//�ռ���Ȩ��������Ȩ����� 
            			pixel_weight += now_weight;
            			pixel_data += bmp->data[hh][ww]*now_weight;
					}
				}


            
            double pixVal_1 = pixel_data/pixel_weight;
            pixVal = (unsigned char)pixVal_1;
//                pixVal = bmp->data[i][j];
				 
               
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

