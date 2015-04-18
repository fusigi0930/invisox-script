/*
±ÄÅe­»
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 50
#define MAX_COUNT 7000
#define KEYHOLD_TIME 30
#define CHANGE_HAND_EQU_TIMES 0
#define CHANGE_HAND_LIMIT_TIMES 601

void DropProc() {
	int nKeepItem1=0, nKeepItem2=0;
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+400);
		int x=0; y=0;
		// ¥á¤ô
        if (MRF_MatchPic("nobu_pic\\Water.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á²M¤ô
        else if (MRF_MatchPic("nobu_pic\\DropItem002.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¥Ö­²
        else if (MRF_MatchPic("nobu_pic\\DropItem003.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¤p®x°|¥Û
        else if (MRF_MatchPic("nobu_pic\\DropItem013.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();			
		// ¥áµw¥Ö­²
        else if (MRF_MatchPic("nobu_pic\\DropItem015.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¤Ñ¯ó
        else if (MRF_MatchPic("nobu_pic\\DropItem025.bmp", &x, &y, 1024, 768)) {
			if (nKeepItem1 > 2)
				Nobu_DropItem();
			else {
				nKeepItem1++;
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