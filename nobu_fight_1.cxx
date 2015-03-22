/*
Áë 3000
*/
#include "nobu_fight_function.hxx"

void fightCmd(int nRound) {
	int xCmd,yCmd;
	xCmd=0; yCmd=0;
	//MRF_Delay(150);
	//IOC_onKeypress(VK_ESCAPE);
	//MRF_Delay(150);
	return;
	//MRF_Delay(1550);
	// ÁnªFÀ»¦è
	if (MRF_MatchPic("nobu_pic\\fight_cmd_01.bmp", &xCmd, &yCmd, 450, 768)) {
		IOC_onMouseMove(xCmd+2, yCmd+5);
		MRF_Delay(150);
		IOC_onMouseClick();
		MRF_Delay(150);
	}	
}

void main() {
	runningStatusMachine(fightCmd);	
} 