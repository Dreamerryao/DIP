#include "bmp.h"

const char* filepath1 = "./Data/8bitgray.bmp";
const char* filepath2 = "./Data/test.bmp";

int main(){
	
	BMPDATA* gray = readbmp(filepath1); //∂¡»°8bit bmp 
	BilFilter(filepath2,gray);// bilfiter
	return 0;
	
	}
	
