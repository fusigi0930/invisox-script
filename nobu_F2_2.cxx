/*
�ĺ�, �Ϩ�
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 30
#define MAX_COUNT 3500
//#define MAX_COUNT 3196
#define KEYHOLD_TIME 30

void DropProc() {
	Nobu_PreDropProc();
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+500);
		int x=0; y=0;
		// ���
        if (MRF_MatchPic("nobu_pic\\Water.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// �����
        else if (MRF_MatchPic("nobu_pic\\DropItem001.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// �ᯡ��
        else if (MRF_MatchPic("nobu_pic\\DropItem004.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// �ả
        else if (MRF_MatchPic("nobu_pic\\DropItem022.bmp", &x, &y, 1024, 768))
			//Nobu_DropItem();			
			continue;
		// ��p���Ф�
        else if (MRF_MatchPic("nobu_pic\\DropItem023.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ��s��
        else if (MRF_MatchPic("nobu_pic\\DropItem024.bmp", &x, &y, 1024, 768))
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