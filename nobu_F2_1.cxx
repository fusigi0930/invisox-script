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
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	Nobu_Digging(DropProc, 800);
} 