#include ".\inc\v_key.h"

void main(){
	//MRF_Delay(2000);
	/*
	IOC_onMouseMove(100, 100, 1);
	IOC_onMouseDown(1);
	MRF_Delay(500);
	IOC_onMouseMove(500, 500, 1);
	IOC_onMouseUp(1);
	*/
	while (1) {
		Sleep(30);
		IOC_onKeypress(VK_RETURN);
	}
}
