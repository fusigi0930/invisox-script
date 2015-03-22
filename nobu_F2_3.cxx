/*
���e��
*/
#include "nobu_function.hxx"
#define ACTION_TIMES 50
#define MAX_COUNT 7000
#define KEYHOLD_TIME 30
#define CHANGE_HAND_EQU_TIMES 0
#define CHANGE_HAND_LIMIT_TIMES 601

void DropProc() {
	Nobu_PreDropProc();
	int nKeepItem1=0, nKeepItem2=0;
	while (1) {
		MRF_Delay(NORMAL_DELAY_TIME);
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(NORMAL_DELAY_TIME+400);
		int x=0; y=0;
		// ���
        if (MRF_MatchPic("nobu_pic\\Water.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ��M��
        else if (MRF_MatchPic("nobu_pic\\DropItem002.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ��֭�
        else if (MRF_MatchPic("nobu_pic\\DropItem003.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ��p�x�|��
        else if (MRF_MatchPic("nobu_pic\\DropItem013.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();			
		// ��w�֭�
        else if (MRF_MatchPic("nobu_pic\\DropItem015.bmp", &x, &y, 1024, 768))
			Nobu_DropItem();
		// ��ѯ�
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
		else if (nCount >= ACTION_TIMES)�@{
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
		IOC_onKeypress(VK_F2);
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