/*
¥á¤s´Ô²É, ¬ã¯ó
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 10
#define MAX_COUNT 1000
#define KEYHOLD_TIME 30
#define CHANGE_HAND_EQU_TIMES 0
#define CHANGE_HAND_LIMIT_TIMES 601

void DropProc() {
	Nobu_PreDropProc();
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+500);
		int x=0, y=0;
		// ¥áºÖ¹Ø¯ó
        if (MRF_MatchPic("nobu_pic\\DropItem009.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¬ã¯ó
        else if (MRF_MatchPic("nobu_pic\\DropItem010.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¤s´Ô²É
        else if (MRF_MatchPic("nobu_pic\\DropItem011.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();	
		// ¥á¹aÄõ
        else if (MRF_MatchPic("nobu_pic\\DropItem012.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥áº¼¤úµæ
        else if (MRF_MatchPic("nobu_pic\\DropItem019.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á·¨±ö¥Ö
        else if (MRF_MatchPic("nobu_pic\\DropItem032.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ¥á¤Hçx	
        if (MRF_MatchPic("nobu_pic\\DropItem018.bmp", &x, &y, 1024, 768))
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