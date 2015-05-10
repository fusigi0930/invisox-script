#ifndef __NOBU_ONLINE_MEM_FUNCTION__
#define __NOBU_ONLINE_MEM_FUNCTION__
#include ".\nobu_function.hxx"

#define NOBU_ITEMS_01_ADDR	0x978b40
#define NOBU_ITEMS_OFFSET	0xcc
#define NOBU_ITEMS_01_ADDR_HD 0x138603B4//0x13861c1c
#define NOBU_ITEMS_OFFSET_HD 0xd0
#define NOBU_ITEMS_00_ADDR_HD (NOBU_ITEMS_01_ADDR_HD - NOBU_ITEMS_OFFSET_HD)
#define NOBU_ITEMS_PROTECT_HD 0xbf
#define NOBU_ITEMS_PROTECT_OFFSET_HD 0xa9

#define NOBU_ITEMS_OFFSET_HD_IDX 0x06
#define NOBU_ITEMS_OFFSET_HD_TYPE 0x07
#define NOBU_ITEMS_OFFSET_HD_CNT 0x08

#define NOBU_ITEMS_TYPE_HD_ITEM 1

#define NOBU_MAX_MP_ADDR_HD 0x138a93a0 // 0x200ea694
#define NOBU_CUR_MP_ADDR_HD 0x138a93b2 // 0x200ea698

struct SHDNobuItem {
	union {
		unsigned char buffer[NOBU_ITEMS_OFFSET_HD];
		struct SItem {
			unsigned short itemId;
			unsigned char reserve1[NOBU_ITEMS_OFFSET_HD_IDX-2];
			unsigned char itemIndex;
			unsigned char itemType;
			unsigned char itemCount;
			unsigned char reserve2[NOBU_ITEMS_PROTECT_OFFSET_HD];
			unsigned char protectMode;
		} item;
	};
};

struct SHDNobuDrop {
	unsigned short itemId;
	int nKeep;
};

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
int Nobu_GetItemMem(SNobuItem *ptrItems, int nLeng);
int Nobu_HDMemDigging(void (*fnHDDropProc)(SHDNobuItem *), int nMaxLoop);

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

int NobuHD_GetItemMem(SHDNobuItem *ptrItems, int nLeng) {
	unsigned char ar_chBuf[20480];
	if (IOC_onReadGameMemory(0, NOBU_ITEMS_01_ADDR_HD, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("get item memor failed\n");
		return;
	}
	
	// Get the last item
	SHDNobuItem *ptrCurItem=(SHDNobuItem*) ar_chBuf;
	memcpy (ptrItems, ar_chBuf, nLeng);
	return 0;
}


int Nobu_MemPostDropProc() {
	MRF_Delay(NORMAL_DELAY_TIME);
	IOC_onKeypress(VK_ESCAPE);
	MRF_Delay(NORMAL_DELAY_TIME);
	IOC_onKeypress('K');
	MRF_Delay(NORMAL_DELAY_TIME+100);
	IOC_onKeypress(VK_ESCAPE);
	MRF_Delay(NORMAL_DELAY_TIME+700);		
	return 0;
}

int detectHDMemDigStatus(int *lastMP) {
	unsigned char ar_chBuf[256];
	if (IOC_onReadGameMemory(0, NOBU_MAX_MP_ADDR_HD, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("detect hd memory dig stats get item memory failed\n");
		return;
	}
	
	unsigned short nMaxMP=*((unsigned short*) (ar_chBuf+(NOBU_MAX_MP_ADDR_HD-NOBU_MAX_MP_ADDR_HD)));
	unsigned short nCurMP=*((unsigned short*) (ar_chBuf+(NOBU_CUR_MP_ADDR_HD-NOBU_MAX_MP_ADDR_HD)));
	
	//MRF_DebugMsg("maxMP: %d, curMP: %d\n", nMaxMP, nCurMP);
	if (nCurMP == *lastMP) {
		return DIG_STATUS_FULL;
	}
	*lastMP=nCurMP;
	if (nCurMP < 800) {
		MRF_Delay(NORMAL_DELAY_TIME+5000);
		IOC_onKeypress(VK_ESCAPE);
		return DIG_STATUS_NO_MP;	
	}
	return DIG_STATUS_NORMAL;
}

int Nobu_HDMemDigging(void (*fnHDDropProc)(SHDNobuItem *ptrItem), int nMaxLoop) {
	int nCount=0;
	int nLastMP=0;

	if (fnHDDropProc == NULL)
		return -1;
	
	for (nCount=1; nCount <= nMaxLoop; nCount++) {
		int nStatus=detectHDMemDigStatus(&nLastMP);
		if (nStatus == DIG_STATUS_NORMAL) {
			MRF_Delay(1800);
			NobuDigProc();	
			if ((nCount%3) != 0) {
				continue;
			}
		}
		else if (nStatus == DIG_STATUS_FULL) {
			return 0;
		}
		MRF_Delay(15000);
		Nobu_onKeypress(VK_RETURN, 5);
		Nobu_onKeypress(VK_ESCAPE, 5);
		SHDNobuItem items[60]={0};
		SHDNobuItem *ptrItem=items;
		Nobu_PreDropProc();
		NobuHD_GetItemMem(items, sizeof(items));
		while (ptrItem->item.itemIndex != 0xff) {
			ptrItem++;
		}
		// pass the last item
		fnHDDropProc(ptrItem-1);
		MRF_Delay(10000);
	}
	
	Nobu_LeaveGame();
	return 0;
}

int Nobu_HDmemDropMainProc(SHDNobuDrop *drops, SHDNobuItem *ptrItem) {
	int nIndex=0;
	while(1) {
		bool isDroped=false;
		
		for (int i=0; drops[i].itemId != 0; i++) {
			if (ptrItem->item.itemId == drops[i].itemId && 
				ptrItem->item.itemType == NOBU_ITEMS_TYPE_HD_ITEM && 
				ptrItem->item.itemCount > 1 &&
				ptrItem->item.protectMode != NOBU_ITEMS_PROTECT_HD) {
				IOC_onKeypress(VK_RETURN);
				MRF_Delay(400);
				Nobu_DropItem();
				MRF_Delay(400);
				isDroped=true;
				break;
			}
		}
		if (ptrItem->item.itemIndex < 15) {
			Nobu_MemPostDropProc();
			break;
		}
		if (!isDroped) {
			Nobu_MemKeepItem();
		}
		else if (isDroped && nIndex==0) {
			ptrItem--;
		}
		isDroped=false;
		ptrItem--;
		nIndex++;
		MRF_Delay(400);
	}
}

#endif // __NOBU_ONLINE_MEM_FUNCTION__