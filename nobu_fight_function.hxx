#ifndef __NOBU_ONLINE_FIGHT_FUNCTION__
#define __NOBU_ONLINE_FIGHT_FUNCTION__
#include ".\nobu_function.hxx"


#define FIGHT_ENEMY_NAME_ADDR 0xae16f0
#define FIGHT_ENEMY_OFFSET 0xe4
#define FIGHT_STATUS_ADDR 0xae1714
#define FIGHT_STATUS_STANDBY 0x0000
#define FIGHT_ENEMY_STATUS_ALIVE 0x0c
#define FIGHT_ENEMY_STATUS_DEAD 0x14
#define FIGHT_PROGRESS_ADDR 0xae1784

#define FIGHT_MEMBER_NAME_ADDR 0xae9a8a

struct SEnemy {
	unsigned short wszFirstName[4];
	unsigned char arRes1[10];
	unsigned short wszLastName[4];
	unsigned char arRes2[10];
	unsigned long nFightStatus;
	unsigned short nAlive;
	unsigned char arRes4[0x6a];
	unsigned short nSkill1[3];
	unsigned char arRes5[2];
	unsigned short nSkill2[3];
	unsigned char arRes6[0x3c];
};

enum ENStatus {
	EN_STATUS_IDLE	=	0,
	EN_STATUS_INPUT_CMD,
	EN_STATUS_GET_EXP,
	EN_STATUS_SELECT_ITEMS,
	EN_STATUS_ITEM_LIST,
	EN_STATUS_QUIT,
	EN_STATUS_IGNORE,
	EN_STATUS_INFIGHT,
	EN_STATUS_UNKNOW = -1
};

int detectFightStatus();
int detectFightStatus_mem();
void fightingCmd(void (*fnFight) (int), int nRound);
void runningStatusMachine(void (*fnFight) (int));

bool detectToIdle() {
	int nX=0, nY=0;
	if (MRF_MatchPic("nobu_pic\\fight_to_idle1.bmp", &nX, &nY, 1024, 768) || 
		MRF_MatchPic("nobu_pic\\fight_to_idle2.bmp", &nX, &nY, 1024, 768)) {
		return true;
	}
	return false;
}

bool detectToIdle_mem() {
	unsigned char ar_chBuf[20];
	if (IOC_onReadGameMemory(0, FIGHT_STATUS_ADDR, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("get item memor failed\n");
		return true;
	}
	unsigned short nFightStatus=*((unsigned short*)ar_chBuf);
	if (nFightStatus == FIGHT_STATUS_STANDBY) {
		return true;
	}
	return false;
}

int detectFightStatus_mem(int nStatus) {
	//MRF_DebugMsg("find fight_quit\n");
	if (detectToIdle_mem()) {
		nStatus=EN_STATUS_IDLE;
	}
	switch(nStatus) {
		case EN_STATUS_INFIGHT: 
			if (MRF_MatchPic("nobu_pic\\fight_flag.bmp", &xCmd, &yCmd, 1024, 768)) {
				//MRF_DebugMsg("still infight\n");
				nStatus=EN_STATUS_INFIGHT;
			}
			else {
				//MRF_DebugMsg("goto the get exp status\n");
				nStatus=EN_STATUS_GET_EXP;
			}
			break;
		case EN_STATUS_GET_EXP:
			if (MRF_MatchPic("nobu_pic\\fight_list.bmp", &xCmd, &yCmd, 1024, 768)) {
				nSatatus=EN_STATUS_ITEM_LIST;
			}
			//else if (detectToIdle()) {
			//	nSatatus=EN_STATUS_IDLE;
			//}
		case EN_STATUS_ITEM_LIST:
			IOC_onMouseMove(800, 600);
			break;
		default:
			if (MRF_MatchPic("nobu_pic\\fight_flag.bmp", &xCmd, &yCmd, 1024, 768)) {
				nStatus=EN_STATUS_INFIGHT;
			}			
			break;				
	}
	return nStatus;
}

int detectFightStatus(int nStatus) {
	int xCmd, yCmd;
	//while (1) {
		xCmd=0; yCmd=0;
		//MRF_DebugMsg("find fight_quit\n");
		if (detectToIdle()) {
			nStatus=EN_STATUS_IDLE;
		}
		switch(nStatus) {
			case EN_STATUS_INFIGHT: 
				if (MRF_MatchPic("nobu_pic\\fight_flag.bmp", &xCmd, &yCmd, 1024, 768)) {
					//MRF_DebugMsg("still infight\n");
					nStatus=EN_STATUS_INFIGHT;
				}
				else {
					//MRF_DebugMsg("goto the get exp status\n");
					nStatus=EN_STATUS_GET_EXP;
				}
				break;
			case EN_STATUS_GET_EXP:
				if (MRF_MatchPic("nobu_pic\\fight_list.bmp", &xCmd, &yCmd, 1024, 768)) {
					nSatatus=EN_STATUS_ITEM_LIST;
				}
				//else if (detectToIdle()) {
				//	nSatatus=EN_STATUS_IDLE;
				//}
			case EN_STATUS_ITEM_LIST:
				IOC_onMouseMove(800, 600);
				break;
			default:
				if (MRF_MatchPic("nobu_pic\\fight_flag.bmp", &xCmd, &yCmd, 1024, 768)) {
					nStatus=EN_STATUS_INFIGHT;
				}			
				break;				
		}
		return nStatus;
	//}
	return nStatus;
}

void fightingCmd(void (*fnFight) (int), int nRound) {
	//MRF_DebugMsg("fightingCmd\n");
	MRF_Delay(190);
	IOC_onKeypress('K');
	MRF_Delay(150);
	IOC_onKeypress(VK_RETURN);	
	MRF_Delay(350);
	if (fnFight) fnFight(nRound);
}

void moveFindNpc() {
	MRF_Delay(100);
	IOC_onKeydown('A');
	MRF_Delay(500);
	IOC_onKeyup('A');
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(200);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(700);
}

void runningStatusMachine(void (*fnFight) (int)) {
	int nStatus=EN_STATUS_IDLE;
	int nRound=0;
	while (1) {
		nStatus=detectFightStatus(nStatus);
		//MRF_DebugMsg("the status is: %d, %d\n", nStatus, EN_STATUS_INPUT_CMD);
		switch (nStatus) {
			case EN_STATUS_IDLE:
				//IOC_onMouseMove(100, 600);
				moveFindNpc();
				break;
			case EN_STATUS_INFIGHT:
				//IOC_onMouseMove(200, 600);
				break;
			case EN_STATUS_INPUT_CMD:
				//MRF_DebugMsg("EN_STATUS_INPUT_CMD: 0x%x\n", fnFight);
				//IOC_onMouseMove(300, 600);
				fightingCmd(fnFight, nRound);
				break;
			case EN_STATUS_GET_EXP:
				//IOC_onMouseMove(400, 600);
				MRF_Delay(100);
				IOC_onKeypress(VK_RETURN);
				break;
			case EN_STATUS_ITEM_LIST:	
				MRF_Delay(350);
				//IOC_onMouseMove(500, 600);
				IOC_onKeypress(VK_RETURN);	
				break;
			case EN_STATUS_SELECT_ITEMS:
				MRF_Delay(250);
				IOC_onKeypress('I');	
				MRF_Delay(350);
				IOC_onKeypress(VK_RETURN);	
				break;
			case EN_STATUS_QUIT:
				//IOC_onMouseMove(600, 600);
				nRound=0;
				break;
		}
		MRF_Delay(100);
	}
	//IOC_onMouseMove(500, 700);
}


#endif // __NOBU_ONLINE_FIGHT_FUNCTION__