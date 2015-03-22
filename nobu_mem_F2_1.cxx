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
		// ¥á¤Ñ¯ó
		case NOBU_ITEM_0012:
			if (g_nKeepItem1 > 3)
				Nobu_MemDropItem(ptrItem->dbNumber);
			else {
				g_nKeepItem1++;
				//Nobu_MemKeepItem();
				break;
			}
			break;
		// ¥á¤ô
		case NOBU_ITEM_0000:
		// ¥á®ø¬´
		case NOBU_ITEM_0003:
		// ¥á®üÂA
		case NOBU_ITEM_0004:
		// ¥á²M¤ô
		case NOBU_ITEM_0006:
		// ¥á¥Ö­²
		case NOBU_ITEM_0007:
		// ¥áÃ·¤l
		case NOBU_ITEM_0008:
		// ¥áµw¥Ö­²
		case NOBU_ITEM_0010:
		// ¥áºµÁx
		case NOBU_ITEM_0013:
		// ¥á¤s¬Ã
		case NOBU_ITEM_0017:
		// ¥á¯¡¥Û
		case NOBU_ITEM_0018:
		// ¥á¹p³¾¦Ð¤ò
		case NOBU_ITEM_0019:
		// ¥áªê´³ÂÎ¯»
		case NOBU_ITEM_0022:
		// ¥á³Â
		case NOBU_ITEM_0023:
		// ¥áÅúÃµ´ß
		case NOBU_ITEM_0024:
		// ¥á´Öªá
		case NOBU_ITEM_0026:
		// ¥á¤p®x°|¥Û
		case NOBU_ITEM_0027:
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
		IOC_onKeypress(VK_F2);
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