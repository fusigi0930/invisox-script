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
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	Nobu_Digging(DropProc, 800);
} 