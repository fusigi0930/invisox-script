/*
±ƒ∂¿ª…
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 50
#define MAX_COUNT 8000
#define KEYHOLD_TIME 30
#define CHANGE_HAND_EQU_TIMES 0
#define CHANGE_HAND_LIMIT_TIMES 601

void DropProc() {
	Nobu_PreDropProc();
	int nKeepItem1=0;
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+500);
		int x=0, y=0;
		// •·ª…ƒq•€
        if (MRF_MatchPic("nobu_pic\\DropItem005.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// •·ª…
        else if (MRF_MatchPic("nobu_pic\\DropItem006.bmp", &x, &y, 1024, 768)) {
			if (nKeepItem1 > 2)
				Nobu_DropItem();
			else {
				nKeepItem1++;
				Nobu_KeepItem();
				continue;
			}
		}
		// •·§Ï∏`÷ﬂ§g
        else if (MRF_MatchPic("nobu_pic\\DropItem014.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();	
		// •·∂¬÷ﬂ§g
        else if (MRF_MatchPic("nobu_pic\\DropItem029.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// •·µµ§Ù¥π
        else if (MRF_MatchPic("nobu_pic\\DropItem030.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// •·≠∏•€
        else if (MRF_MatchPic("nobu_pic\\DropItem031.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// •·≈K¨‚
        else if (MRF_MatchPic("nobu_pic\\DropItem007.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// •·≈K
        else if (MRF_MatchPic("nobu_pic\\DropItem008.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();			
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
		else if (nCount >= ACTION_TIMES)°@{
			DropProc();
			nCount=0;
			continue;
		}
		else {
			nFixed=0;
		}	
		if (Nobu_DetectEscape(nTotalCount, MAX_COUNT))
			break;
		// Ctrl+F4
		IOC_onKeydown(VK_CONTROL);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeypress(VK_F4);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeyup(VK_CONTROL);
		
		MRF_Delay(NORMAL_DELAY_TIME+nFixed);
		x=200; y=200;
		if (MRF_MatchPic("nobu_pic\\StartAction.bmp", &x, &y, 900, 600)) {
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