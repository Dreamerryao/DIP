#include "bmp.h"

const char* filepath1 = "./Data/cartoon.bmp";
const char* filepath2 = "./Data/Carimf2.bmp";
const char* filepath4 = "./Data/Carenh.bmp";
const char* filepath3 = "./Data/CarLap.bmp";

int main(){
	
	BMPDATA* gray = readbmp(filepath1); 
	MeanFilter(filepath2,gray);
	BMPDATA* gray2 = readbmp(filepath1); 
	Laplace(filepath4,gray2); 
	return 0;
	
	}
