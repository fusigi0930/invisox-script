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
		// ¥á»É 
		case NOBU_ITEM_3001:
			if (g_nKeepItem1 > 2)
				Nobu_MemDropItem(ptrItem->dbNumber);
			else {
				g_nKeepItem1++;
				//Nobu_MemKeepItem();
				break;
			}		
			break;
		// ¥á»ÉÄq¥Û 
		case NOBU_ITEM_3000:
		// ¥á¤ì¸`Öß¤g
		case NOBU_ITEM_3002:
		// ¥á¶Âªd¤g 
		case NOBU_ITEM_3005:	
		// ¥áµµ¤ô´¹
		case NOBU_ITEM_3006:		
		// ¥á­¸¥Û
		case NOBU_ITEM_3007:
		case NOBU_ITEM_3014:
		// ¥áÅK
		case NOBU_ITEM_3008:
		// ¥áÅK¬â
		case NOBU_ITEM_3009:
		// ¥á·Æ¥Û
		case NOBU_ITEM_3010:
		// ¥á¤ô´¹Äq
		case NOBU_ITEM_3013:
		// ¥á¤g¥x
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