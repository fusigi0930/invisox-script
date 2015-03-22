#include ".\inc\v_key.h"

void main(){
	int x=0;
	int y=0;
	if (MRF_MatchPic("Water.bmp", &x, &y, 1024, 768)) {
		IOC_onKeydown(VK_ALT);
		MRF_Delay(30);
		IOC_onKeypress(VK_F3);
		MRF_Delay(30);
		IOC_onKeyup(VK_ALT);
	}
	else  {
		IOC_onKeydown(VK_ALT);
		MRF_Delay(30);
		IOC_onKeypress(VK_F4);
		MRF_Delay(30);
		IOC_onKeyup(VK_ALT);

	}
}
