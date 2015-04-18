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
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	Nobu_Digging(DropProc, 800);
} 