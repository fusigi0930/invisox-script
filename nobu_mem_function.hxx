#ifndef __NOBU_ONLINE_MEM_FUNCTION__
#define __NOBU_ONLINE_MEM_FUNCTION__
#include ".\nobu_function.hxx"

#define NOBU_ITEMS_01_ADDR	0xa3d704 //0xa3a65c
#define NOBU_ITEMS_OFFSET	0xd0
#define NOBU_MAX_MP_ADDR 0xa866f4 // 0x200ea694
#define NOBU_CUR_MP_ADDR 0xa86706 // 0x200ea698

#define NOBU_ITEMS_01_ADDR_HD 0x138603B4//0x13861c1c
#define NOBU_ITEMS_OFFSET_HD 0xd0
#define NOBU_ITEMS_00_ADDR_HD (NOBU_ITEMS_01_ADDR_HD - NOBU_ITEMS_OFFSET_HD)
#define NOBU_ITEMS_PROTECT_HD 0xbf
#define NOBU_ITEMS_PROTECT_OFFSET_HD 0xa9

#define NOBU_ITEMS_OFFSET_HD_IDX 0x06
#define NOBU_ITEMS_OFFSET_HD_TYPE 0x07
#define NOBU_ITEMS_OFFSET_HD_CNT 0x08

#define NOBU_ITEMS_TYPE_HD_ITEM 1

#define NOBU_MAX_MP_ADDR_HD 0x138a93a4 // 0x200ea694
#define NOBU_CUR_MP_ADDR_HD 0x138a93b6 // 0x200ea698

#define TYPE_SD 100
#define TYPE_HD 200

#define NOBU_CURSOR_SELECT_NAME_ADDR_HD 0x17790d54 //0x2000b6bc
#define NOBU_CURSOR_SELECT_STAT_ADDR_HD 0x17790C73
#define NOBU_CURSOR_SELECT_STAT_HD 0x01 // selected
#define NOBU_CURSOR_SELECT_STAT_HD 0x41 // not selected

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

void Nobu_MemDropItem(unsigned char nNum);
void Nobu_MemKeepItem();
int Nobu_MemPostDropProc();
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

void Nobu_MemKeepItem() {
	MRF_Delay(250);
	IOC_onKeypress('I');
	MRF_Delay(400);
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

int _Nobu_GetItemMem(SHDNobuItem *ptrItems, int nLeng, int addr) {
	unsigned char ar_chBuf[20480];
	if (IOC_onReadGameMemory(0, addr, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("get item memor failed\n");
		return;
	}
	
	// Get the last item
	SHDNobuItem *ptrCurItem=(SHDNobuItem*) ar_chBuf;
	memcpy (ptrItems, ar_chBuf, nLeng);
	return 0;
}

int Nobu_GetItemMem(SHDNobuItem *ptrItems, int nLeng) {
	return _Nobu_GetItemMem(ptrItems, nLeng, NOBU_ITEMS_01_ADDR);
}

int NobuHD_GetItemMem(SHDNobuItem *ptrItems, int nLeng) {
	return _Nobu_GetItemMem(ptrItems, nLeng, NOBU_ITEMS_01_ADDR_HD);
}

int _detectMemDigStatus(int *lastMP, int addrCur, int addrMax) {
	unsigned char ar_chBuf[256];
	if (IOC_onReadGameMemory(0, addrMax, ar_chBuf, sizeof(ar_chBuf)) != 0) {
		MRF_DebugMsg("detect hd memory dig stats get item memory failed\n");
		return;
	}
	
	unsigned short nMaxMP=*((unsigned short*) (ar_chBuf+(addrMax-addrMax)));
	unsigned short nCurMP=*((unsigned short*) (ar_chBuf+(addrCur-addrMax)));
	
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

int detectMemDigStatus(int *lastMP) {
	return _detectMemDigStatus(lastMP, NOBU_CUR_MP_ADDR, NOBU_MAX_MP_ADDR);
}

int detectHDMemDigStatus(int *lastMP) {
	return _detectMemDigStatus(lastMP, NOBU_CUR_MP_ADDR_HD, NOBU_MAX_MP_ADDR_HD);
}

int _Nobu_MemDigging(void (*fnHDDropProc)(SHDNobuItem *ptrItem), int nMaxLoop, int nType) {
	int nCount=0;
	int nLastMP=0;

	if (fnHDDropProc == NULL)
		return -1;
	
	for (nCount=1; nCount <= nMaxLoop; nCount++) {
		int nStatus=0;
		if (nType == TYPE_SD) {
			nStatus=detectMemDigStatus(&nLastMP);
		}
		else if (nType == TYPE_HD) {
			nStatus=detectHDMemDigStatus(&nLastMP);
		}
		if (nStatus == DIG_STATUS_NORMAL) {
			MRF_Delay(1800);
			NobuDigProc();	
			if ((nCount%3) != 0) {
				continue;
			}
		}
		else if (nStatus == DIG_STATUS_FULL) {
			break;
		}
		MRF_Delay(15000);
		Nobu_onKeypress(VK_RETURN, 5);
		Nobu_onKeypress(VK_ESCAPE, 5);
		SHDNobuItem items[60]={0};
		SHDNobuItem *ptrItem=items;
		Nobu_PreDropProc();
		if (nType == TYPE_SD) {
			Nobu_GetItemMem(items, sizeof(items));
		}
		else if (nType == TYPE_HD) {
			NobuHD_GetItemMem(items, sizeof(items));
		}		
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

int Nobu_HDMemDigging(void (*fnHDDropProc)(SHDNobuItem *ptrItem), int nMaxLoop) {
	return _Nobu_MemDigging(fnHDDropProc, nMaxLoop, TYPE_HD);
}

int Nobu_MemDigging(void (*fnHDDropProc)(SHDNobuItem *ptrItem), int nMaxLoop) {
	return _Nobu_MemDigging(fnHDDropProc, nMaxLoop, TYPE_SD);
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