#include "nobu_function.hxx"

void main(){
	// Init Delay
	MRF_Delay(500);
	IOC_onKeypress(VK_ALT);
	
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(1500);
	int x=0, y=0;
	int nCount=0;
	while (!MRF_MatchPic("nobu_pic\\CreateIronSec.bmp", &x, &y, 1024, 768)) {
		MRF_Delay(100);	
		if (nCount++ > 30)
		return;
	}
	IOC_onKeypress('K');
	MRF_Delay(300);
	IOC_onKeypress('K');
	MRF_Delay(300);	
	Nobu_MakeItem();
	MRF_Delay(800);
	Nobu_onKeypress(VK_ESCAPE, 1);
	MRF_Delay(1700);
	IOC_onKeypress('K');
	MRF_Delay(300);
	Nobu_MakeItem();	
	MRF_Delay(800);
	Nobu_onKeypress(VK_ESCAPE, 5);
}
