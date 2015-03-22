#include ".\inc\v_key.h"

void main(){
	int x=0, y=0;
	if (MRF_MatchPic("test.bmp", &x, &y, 1024, 768)) {
		IOC_onMouseMove(x,y);
	}
}
