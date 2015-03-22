/*
±Ä®Û¥Ö
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 40
#define MAX_COUNT 7000
#define KEYHOLD_TIME 30
#define CHANGE_HAND_EQU_TIMES 0
#define CHANGE_HAND_LIMIT_TIMES 501

void DropProc() {
	Nobu_PreDropProc();
	int nKeepItem1=0, nKeepItem2=0, nKeepItem3=0;
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+500);
		int x=0; y=0;
		// ¥á¤Hçx
        if (MRF_MatchPic("nobu_pic\\DropItem018.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¬ã¯ó
        else if (MRF_MatchPic("nobu_pic\\DropItem010.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¤s´Ô²É
        else if (MRF_MatchPic("nobu_pic\\DropItem011.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();	
		// ¥á¹aÄõ
        else if (MRF_MatchPic("nobu_pic\\DropItem012.bmp", &x, &y, 1024, 768)) {
/*
			if (nKeepItem1 > 2)
				Nobu_DropItem();
			else {
				nKeepItem1++;
				Nobu_KeepItem();
				continue;
			}
*/
			Nobu_DropItem();
		}
		// ¥áÀsÁx
        else if (MRF_MatchPic("nobu_pic\\DropItem026.bmp", &x, &y, 1024, 768)) {
			if (nKeepItem2 > 1)
				Nobu_DropItem();
			else {
				nKeepItem2++;
				Nobu_KeepItem();
				continue;
			}		
		}
		// ¥á·¨±ö¥Ö
        else if (MRF_MatchPic("nobu_pic\\DropItem032.bmp", &x, &y, 1024, 768)) {
			if (nKeepItem3 > 1)
				Nobu_DropItem();
			else {
				nKeepItem3++;
				Nobu_KeepItem();
				continue;
			}		
		}
		else if (Nobu_PostDropProc() == 1)
			break;
	}
}

void main() {
	int nCount=0, nTotalCount=0, nChangeHandEqu=0, nFixed=0;
	int nEquCount=0;
	int x=0, y=0;
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	while (nTotalCount < MAX_COUNT) {
		if ((nEquCount >= CHANGE_HAND_LIMIT_TIMES) && (nChangeHandEqu<CHANGE_HAND_EQU_TIMES)) {
			Nobu_ChangeHandEqu();
			//MRF_DebugMsg("nTotalCount: %d, nChangeHandEqu:%d\n", nTotalCount, nChangeHandEqu);
			nChangeHandEqu++;
			MRF_Delay(300);
			Nobu_onKeypress(VK_RETURN, 5);
			MRF_Delay(400);
			IOC_onKeypress(VK_F11);
			MRF_Delay(300);
			Nobu_onKeypress(VK_ESCAPE, 5);
			MRF_Delay(600);
			nFixed=500;
			nEquCount=0;
		}
		else if (nCount >= ACTION_TIMES)¡@{
			DropProc();
			nCount=0;
			continue;
		}
		else {
			nFixed=0;
		}	
		if (Nobu_DetectEscape(nTotalCount, MAX_COUNT))
			break;
		// Ctrl+F3
		IOC_onKeydown(VK_CONTROL);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeypress(VK_F3);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeyup(VK_CONTROL);
		
		MRF_Delay(NORMAL_DELAY_TIME+nFixed);
		x=0; y=0;
		if (MRF_MatchPic("nobu_pic\\StartAction.bmp", &x, &y, 900, 600)) {
			//MRF_DebugMsg("count: %d\n", nCount);
			nCount++;
			nTotalCount++;
			nEquCount++;
			x=200; y=200;
			while (MRF_MatchPic("nobu_pic\\StartAction.bmp", &x, &y, 900, 600)) {
				IOC_onKeypress(VK_RETURN);
				MRF_Delay(NORMAL_DELAY_TIME+300);
				x=200; y=200;
			}
		}
		else if (MRF_MatchPic("nobu_pic\\LessMP.bmp", &x, &y, 900, 600)) {
			MRF_Delay(NORMAL_DELAY_TIME+5000);
			IOC_onKeypress(VK_ESCAPE);
			DropProc();
			nCount=0;
		}
	}
	Nobu_LeaveGame();
} 