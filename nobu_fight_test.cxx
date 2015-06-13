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
	unsigned char ar_chBuf[2048];
	if (IOC_onReadGameMemory(0, FIGHT_ENEMY_NAME_ADDR, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("get item memor failed\n");
		return true;
	}
	char *ptr=(char*) ar_chBuf;
	SEnemy *ptrEnemy=(SEnemy *)ptr;	
	for (int i=0; i<7; i++) {
		MRF_DebugMsg("test %d: 0x%04x, size: 0x%x\n", i+1, ptrEnemy->wszFirstName[0], sizeof(SEnemy));
		if (ptrEnemy->nAlive == FIGHT_ENEMY_STATUS_ALIVE) {
			MRF_DebugMsg("e%d: alive\n", i+1);
		}
		else {
			MRF_DebugMsg("e%d: dead\n", i+1);
		}
		if (ptrEnemy->nFightStatus == 0) {
			break;
		}
		ptr+=FIGHT_ENEMY_OFFSET;
		ptrEnemy=(SEnemy *)ptr;
	}
} 