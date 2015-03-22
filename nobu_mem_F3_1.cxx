/*
±Ä¶À»É
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
		// ¥áÀsÁx
		case NOBU_ITEM_1007:
		// ¥áº¼¤úµæ
		case NOBU_ITEM_1008:
			if (g_nKeepItem1 > 2)
				Nobu_MemDropItem(ptrItem->dbNumber);
			else {
				g_nKeepItem1++;
				//Nobu_MemKeepItem();
				break;
			}		
			break;
		// ¥á¨¤«¬­¸¥Û 
		case NOBU_ITEM_1000:
		// ¥á¹aÄõ
		case NOBU_ITEM_1003:
		// ¥á¬ã¯ó
		case NOBU_ITEM_1004:	
		// ¥á¤s´Ô²É
		case NOBU_ITEM_1005:		
		// ¥á¤Hçx
		case NOBU_ITEM_1009:
		// ¥áºÖ¹Ø¯ó
		case NOBU_ITEM_1012:
		// ¥áªQ¯×
		case NOBU_ITEM_1016:
		// ¥á¥ÕÀY¯Î
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
		if (nCount >= ACTION_TIMES)¡@{
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