#ifndef __NOBU_ONLINE_MEM_FUNCTION__
#define __NOBU_ONLINE_MEM_FUNCTION__
#include ".\nobu_function.hxx"

#define NOBU_ITEMS_01_ADDR	0x978b40
#define NOBU_ITEMS_OFFSET	0xcc

struct SNobuItem {
	unsigned long ddItemId;
	unsigned short dwReserver1;
	unsigned short dwItemIndex;
	unsigned char dbNumber;
};

typedef void (*fnDropProc)(SNobuItem *ptrItem);

void Nobu_MemDropProc(fnDropProc dropProc);
void Nobu_MemDropItem(unsigned char nNum);
void Nobu_MemKeepItem();
int Nobu_MemPostDropProc();
int Nobu_GetItemMem(SNobuItem *ptrItems);

void Nobu_MemDropItem(unsigned char nNum) {
	//MRF_DebugMsg("memDropItem drop item\n");
	if (nNum > 1) {
		IOC_onKeypress(VK_RETURN);
		MRF_Delay(800);
	}
	else {
		return;
	}
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(600);
	IOC_onKeypress('J');
	MRF_Delay(400);
	IOC_onKeypress(VK_RETURN);
	MRF_Delay(800);
}

void Nobu_MemDropProc(fnDropProc dropProc) {
	Nobu_PreDropProc();
	int nKeepItem1=0;
	if (dropProc == 0) return;
	
	// Get item memory
	SNobuItem items[50]={0};
	int nItemIndex=Nobu_GetItemMem(items);
	MRF_DebugMsg("itemcount: %d\n", nItemIndex);
	int nUniItemCount=0;
	while ((items[nItemIndex].dwItemIndex & 0xff) > 0x01) {
		MRF_DebugMsg("ind: %x, index: 0x%04x, id: 0x%x, num: %d\n", nItemIndex, items[nItemIndex].dwItemIndex, items[nItemIndex].ddItemId, items[nItemIndex].dbNumber);
		if ((items[nItemIndex].dwItemIndex & 0xff00) == 0x0000) {
			nUniItemCount++;
			if (nUniItemCount > 2)
				break;
			Nobu_MemKeepItem();
			nItemIndex--;		
			continue;
		}
		else {
			nUniItemCount=0;
		}
		// drop item
		dropProc(&items[nItemIndex]);
		Nobu_MemKeepItem();
		nItemIndex--;
	}
	Nobu_MemPostDropProc();
}

void Nobu_MemKeepItem() {
	MRF_Delay(250);
	IOC_onKeypress('I');
	MRF_Delay(400);
}

int Nobu_GetItemMem(SNobuItem *ptrItems) {
	unsigned char ar_chBuf[20480];
	if (IOC_onReadGameMemory(0, NOBU_ITEMS_01_ADDR, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("get item memor failed\n");
		return;
	}
	
	// Get the last item
	SNobuItem *ptrCurItem=(SNobuItem*) ar_chBuf;
	int nItemIndex=0;
	MRF_DebugMsg("output the item info\n");
	while (!((ptrCurItem->dwItemIndex & 0xff) == 0 || (ptrCurItem->dwItemIndex & 0xff) == 0xff)) {
		/*
		MRF_DebugMsg("item_id: 0x%x, item_ind: %04x, item_num:%d\n", 
			ptrItem->ddItemId, ptrItem->dwItemIndex, ptrItem->dbNumber);
		*/
		memcpy(ptrItems+nItemIndex, ptrCurItem, sizeof(SNobuItem)); 
		nItemIndex++;
		ptrCurItem=(SNobuItem*) (ar_chBuf+(nItemIndex * NOBU_ITEMS_OFFSET));
	}
	return nItemIndex-1;
}

int Nobu_MemPostDropProc() {
	IOC_onKeypress(VK_ESCAPE);
	MRF_Delay(NORMAL_DELAY_TIME);
	IOC_onKeypress('K');
	MRF_Delay(NORMAL_DELAY_TIME+100);
	IOC_onKeypress(VK_ESCAPE);
	MRF_Delay(NORMAL_DELAY_TIME+700);		
	return 0;
}

#endif // __NOBU_ONLINE_MEM_FUNCTION__