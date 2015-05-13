/*
±Ä¶À»É
*/
#include ".\nobu_mem_function.hxx"
#include ".\inc\nobu_items.h"

void main() {
	unsigned char ar_chBuf[20480];
	if (IOC_onReadGameMemory(0, NOBU_ITEMS_01_ADDR, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("get item memor failed\n");
		return;
	}
	
	// Get the last item
	SHDNobuItem *ptrCurItem=(SHDNobuItem*) ar_chBuf;
	int nItemIndex=0;
	MRF_DebugMsg("output the item info\n");
	while (ptrCurItem->item.itemIndex != 0xff) {
		
		MRF_DebugMsg("item_id: 0x%x, item index: %d, item type: %d, item_num:%d\n", 
			ptrCurItem->item.itemId, ptrCurItem->item.itemIndex, ptrCurItem->item.itemType, ptrCurItem->item.itemCount);
		ptrCurItem++;
	}
}