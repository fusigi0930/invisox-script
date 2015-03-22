/*
�Ķ���
*/
#include ".\nobu_mem_function.hxx"
#include ".\inc\nobu_items.h"
#define ACTION_TIMES 50
#define MAX_COUNT 8000
#define KEYHOLD_TIME 30

int g_nKeepItem1=0;

void resetKeepCount() {
	g_nKeepItem1=0;
}

void DropProc(SNobuItem *ptrItem) {
	switch (ptrItem->ddItemId) {
		// ���s�x
		case NOBU_ITEM_1007:
		// �Ẽ����
		case NOBU_ITEM_1008:
			if (g_nKeepItem1 > 2)
				Nobu_MemDropItem(ptrItem->dbNumber);
			else {
				g_nKeepItem1++;
				//Nobu_MemKeepItem();
				break;
			}		
			break;
		// �ᨤ������ 
		case NOBU_ITEM_1000:
		// ��a��
		case NOBU_ITEM_1003:
		// ����
		case NOBU_ITEM_1004:	
		// ��s�Բ�
		case NOBU_ITEM_1005:		
		// ��H�x
		case NOBU_ITEM_1009:
		// ��ֹد�
		case NOBU_ITEM_1012:
		// ��Q��
		case NOBU_ITEM_1016:
		// ����Y��
		case NOBU_ITEM_1017:
			Nobu_MemDropItem(ptrItem->dbNumber);
			break;
		default: 
			break;
	}	
}

void main() {
	resetKeepCount();
	int nCount=0, nTotalCount=0;
	int x=0, y=0;
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	while (nTotalCount < MAX_COUNT) {
		if (nCount >= ACTION_TIMES)�@{
			Nobu_MemDropProc(DropProc);
			resetKeepCount();
			nCount=0;
			continue;
		}
		if (nTotalCount >= MAX_COUNT)
			break;
		// Ctrl+F4
		IOC_onKeydown(VK_CONTROL);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeypress(VK_F3);
		MRF_Delay(KEYHOLD_TIME);
		IOC_onKeyup(VK_CONTROL);
		
		MRF_Delay(NORMAL_DELAY_TIME);
		// clean the popup message dialog about 5.5 second
		for (int i=0; i<15; i++) {
			IOC_onKeypress(VK_RETURN);
			MRF_Delay(NORMAL_DELAY_TIME-160);		
		}
		nCount++;
		nTotalCount++;

	}
	Nobu_LeaveGame();
} 