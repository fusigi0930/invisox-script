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
		// ��� 
		case NOBU_ITEM_3001:
			if (g_nKeepItem1 > 2)
				Nobu_MemDropItem(ptrItem->dbNumber);
			else {
				g_nKeepItem1++;
				//Nobu_MemKeepItem();
				break;
			}		
			break;
		// ����q�� 
		case NOBU_ITEM_3000:
		// ���`�ߤg
		case NOBU_ITEM_3002:
		// ��ªd�g 
		case NOBU_ITEM_3005:	
		// �ᵵ����
		case NOBU_ITEM_3006:		
		// �᭸��
		case NOBU_ITEM_3007:
		case NOBU_ITEM_3014:
		// ���K
		case NOBU_ITEM_3008:
		// ���K��
		case NOBU_ITEM_3009:
		// ��ƥ�
		case NOBU_ITEM_3010:
		// ������q
		case NOBU_ITEM_3013:
		// ��g�x
		case NOBU_ITEM_3015:
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
		IOC_onKeypress(VK_F4);
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