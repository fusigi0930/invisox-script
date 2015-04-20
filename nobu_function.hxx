#ifndef __NOBU_ONLINE_FUNCTION__
#define __NOBU_ONLINE_FUNCTION__
#define NORMAL_DELAY_TIME 400
#include ".\inc\v_key.h"

#define DIG_STATUS_NO_MP		100

void Nobu_DropItem();
void Nobu_KeepItem();
void Nobu_onKeypress(unsigned int uKey, int nTimes);
void Nobu_PreDropProc();
int Nobu_PostDropProc();
void Nobu_RejectInvoke();
void Nobu_MakeItem();
void Nobu_MoveCursorUse();
void Nobu_LeaveGame();
int Nobu_DetectEscape(int nCount, int nMax);
int Nobu_ChangeHandEqu();
int Nobu_Digging(void (*fnDropProc)(), int nMaxLoop);

void Nobu_DropItem() {
	MRF_Delay(200);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(500);
	IOC_onKeypress('J');
	MRF_Delay(300);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(800);
	IOC_onKeypress('I');
	MRF_Delay(300);
}

void Nobu_KeepItem() {
	MRF_Delay(200);
	IOC_onKeypress(VK_ESCAPE);
	MRF_Delay(200);
	IOC_onKeypress('I');
	MRF_Delay(300);
}

void Nobu_onKeypress(unsigned int uKey, int nTimes) {
	while (nTimes > 0) {
		IOC_onKeypress(uKey);
		MRF_Delay(75);
		nTimes--;
	}
}

void Nobu_PreDropProc() {
	MRF_Delay(800);
	// 整理道具
	IOC_onKeypress(VK_F11);
	MRF_Delay(500);
	//Nobu_MoveCursorUse();
	IOC_onKeypress('K');
	MRF_Delay(500);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(5000);
	// 開始丟東西
	Nobu_onKeypress('K',3);
	MRF_Delay(500);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(500);
	Nobu_onKeypress('L', 10);
}

int Nobu_PostDropProc() {
	// Detect Yes No
	int x=0, y=0;
	if (MRF_MatchPic("nobu_pic\\YesNo.bmp", &x, &y, 1024, 768)) {
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress('I');
		MRF_Delay(NORMAL_DELAY_TIME);
	}
	else if (MRF_MatchPic("nobu_pic\\MultiYes.bmp", &x, &y, 1024, 768)) {
		IOC_onKeypress(VK_ESCAPE);
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress('I');
		MRF_Delay(NORMAL_DELAY_TIME);	
	}
	else if (MRF_MatchPic("nobu_pic\\ProtectItem.bmp", &x, &y, 1024, 768)) {
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress('I');
		MRF_Delay(NORMAL_DELAY_TIME);		
	}		
	else if (MRF_MatchPic("nobu_pic\\CanNotDrop.bmp", &x, &y, 1024, 768)) {
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+300);
		IOC_onKeypress(VK_ESCAPE);
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress('K');
		MRF_Delay(NORMAL_DELAY_TIME+100);
		IOC_onKeypress(VK_ESCAPE);
		MRF_Delay(NORMAL_DELAY_TIME+700);		
		return 1;
	}		
	return 0;
}

void Nobu_RejectInvoke() {

}

void Nobu_MakeItem() {
	int x=0, y=0;
	while (!MRF_MatchPic("nobu_pic\\CreateEnd.bmp", &x, &y, 1024, 768)) {
		MRF_Delay(30);
		IOC_onKeypress(VK_RETURN);	
	}
	IOC_onKeydown(VK_CONTROL);
	MRF_Delay(30);
	IOC_onKeydown(VK_F10);
	MRF_Delay(30);
	IOC_onKeyup(VK_CONTROL);
}

void Nobu_MoveCursorUse() {
	int x=0, y=0;
	if (MRF_MatchPic("nobu_pic\\ItemNotInUse.bmp", &x, &y, 1024, 768)) {
		IOC_onKeypress('K');
		MRF_Delay(200);
		if (!MRF_MatchPic("nobu_pic\\ItemNotInUse.bmp", &x, &y, 1024, 768)) {
			IOC_onKeypress('I');
			MRF_Delay(200);			
		}
		else {
			IOC_onKeypress('K');
			MRF_Delay(200);				
		}
	}
}

void Nobu_LeaveGame() {
	MRF_Delay(4000);
	Nobu_onKeypress(VK_ESCAPE, 10);
	IOC_onKeypress(VK_TAB);
	MRF_Delay(700);
	IOC_onKeypress(VK_TAB);
	MRF_Delay(500);
	for (int i=0; i<10; i++) {
		IOC_onKeypress('K');
		MRF_Delay(100);
	}
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(700);
	for (int i=0; i<7; i++) {
		IOC_onKeypress('K');
		MRF_Delay(100);
	}	
	IOC_onKeypress(VK_RETURN);
}

int Nobu_DetectEscape(int nCount, int nMax) {
	int nRet=0;
	int x=0, y=0;
	if (nCount >= nMax)
		nRet=1;
	else if (MRF_MatchPic("nobu_pic\\DigLimit.bmp", &x, &y, 1024, 768)) 
		nRet=1;
	return nRet;
}

int Nobu_ChangeHandEqu() {
	MRF_Delay(1000);
	Nobu_onKeypress(VK_ESCAPE, 6);
	MRF_Delay(450);
	IOC_onKeypress(VK_TAB);
	MRF_Delay(1000);	
	for (int i=0; i<6; i++) {
		IOC_onKeypress('K');
		MRF_Delay(150);
	}	
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(700);	
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(350);	
	IOC_onKeypress('K');
	MRF_Delay(350);	
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(950);	
	Nobu_onKeypress(VK_ESCAPE, 2);
	MRF_Delay(2500);
	IOC_onKeypress(VK_TAB);
	MRF_Delay(1000);	
	for (int j=0; j<6; j++) {
		IOC_onKeypress('I');
		MRF_Delay(150);
	}	
	Nobu_onKeypress(VK_ESCAPE, 2);
	MRF_Delay(500);
}

void NobuDigProc() {
	// 選稼業
	IOC_onKeypress(VK_TAB);
	MRF_Delay(800);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(1000);
	// 選採集
	Nobu_onKeypress('I', 3);
	MRF_Delay(500);
	
	// 選採集技能
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(1000);
	Nobu_onKeypress('I', 1);
	MRF_Delay(500);
	

	IOC_onKeypress(VK_RETURN);
	MRF_Delay(2000);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(1500);
	
	// 採10次
	Nobu_onKeypress('J', 4);
	MRF_Delay(500);
	
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(3000);	
	
	// 採集提示
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(1000);
	
	// 採完畫面
	Nobu_onKeypress(VK_RETURN, 4);
	MRF_Delay(1000);		
	
	// 經驗
	Nobu_onKeypress(VK_RETURN, 4);
	MRF_Delay(700);			
}

int detectDigStatus() {
	int x=0, y=0;
	if (MRF_MatchPic("nobu_pic\\LessMP.bmp", &x, &y, 900, 600)) {
		MRF_Delay(NORMAL_DELAY_TIME+5000);
		IOC_onKeypress(VK_ESCAPE);
		return DIG_STATUS_NO_MP;
	}
}

int Nobu_Digging(void (*fnDropProc)(), int nMaxLoop) {
	int nCount=0;

	if (fnDropProc == NULL)
		return -1;
	
	for (nCount=1; nCount <= nMaxLoop; nCount++) {
		if (detectDigStatus() != DIG_STATUS_NO_MP) {
			MRF_Delay(1800);
			NobuDigProc();	
			if ((nCount%4) != 0) {
				continue;
			}
		}
		MRF_Delay(15000);
		Nobu_onKeypress(VK_RETURN, 5);
		Nobu_onKeypress(VK_ESCAPE, 5);
		Nobu_PreDropProc();
		fnDropProc();
		MRF_Delay(10000);
	}
	
	Nobu_LeaveGame();
	return 0;
}
#endif