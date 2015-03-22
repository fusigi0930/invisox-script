#include ".\inc\v_key.h"

void main() {
	int x=0, y=0;
	MRF_DebugMsg("start");
	if (MRF_MatchPic("ys_fight.bmp", &x, &y, 1024, 768)) {
		IOC_onMouseMove(x,y);
		MRF_DebugMsg("x: %d, y%d\r\n", x, y);
	}
	else
		MRF_DebugMsg("not found");
}