/*
±ƒ≈K µv•€
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 50
#define MAX_COUNT 8000
#define KEYHOLD_TIME 30

void DropProc() {
	Nobu_PreDropProc();
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+500);
		int x=0; y=0;
		// •·≈K¨‚
        if (MRF_MatchPic("nobu_pic\\DropItem007.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// •·≈K
        else if (MRF_MatchPic("nobu_pic\\DropItem008.bmp", &x, &y, 1024, 768))
			//Nobu_DropItem();
			continue;
		// •·§Ï∏`÷ﬂ§g
        else if (MRF_MatchPic("nobu_pic\\DropItem014.bmp", &x, &y, 1024, 768))
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