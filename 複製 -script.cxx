//#pragma include "..\bin\wmobile.dll"
#include "nobu_function.hxx"

void main(){
#if 0
	if (!WMC_Init())
		return;
	WMC_onMouseMove(40, 40);
	WMC_onMouseDown();
	WMC_onMouseMove(100, 100);
	WMC_onMouseUp();
	WMC_Uninit();
#endif
	for (int i=0; i<10; i++) {
		Nobu_ChangeHandEqu();
		MRF_Delay(100);
	}
	//IOC_onMouseMove(40, 40);

}

