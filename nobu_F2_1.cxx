/*
±Ä¬´, ¤û¶À
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 40
#define MAX_COUNT 1000
#define KEYHOLD_TIME 30

void DropProc() {
	Nobu_PreDropProc();
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+500);
		int x=0; y=0;
		// ¥á¤ô
        if (MRF_MatchPic("nobu_pic\\Water.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á®ø¬´
        else if (MRF_MatchPic("nobu_pic\\DropItem001.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		else if (Nobu_PostDropProc() == 1)
			break;
	}
}

void main() {
	int nCount=0, nTotalCount=0;
	int x=0, y=0;
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	while (nTotalCount < MAX_COUNT) {
		if (nCount >= ACTION_TIMES)¡@{
			DropProc();
			nCount=0;
			continue;
		}
		if (Nobu_DetectEscape(nTotalCount, MAX_COUNT))
			break;
		// Ctrl+F3
		IOC_onKeydown(VK_CONTROL);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeypress(VK_F2);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeyup(VK_CONTROL);
		
		MRF_Delay(NORMAL_DELAY_TIME);
		x=200; y=200;
		if (MRF_MatchPic("nobu_pic\\StartAction.bmp", &x, &y, 900, 600)) {
			nCount++;
			nTotalCount++;
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