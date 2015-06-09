/*
±Ä®Û¥Ö
*/
#include ".\nobu_mem_function.hxx"
#include ".\inc\nobu_items.h"

void DropProc(SHDNobuItem *ptrItem) {
	SHDNobuDrop dropItems[] = {
		{NOBU_ITEM_0000, 0},
		{NOBU_ITEM_0003, 0},
		{NOBU_ITEM_0004, 0},
		{NOBU_ITEM_0006, 0},
		{NOBU_ITEM_0007, 0},
		{NOBU_ITEM_0008, 0},
		{NOBU_ITEM_0009, 0},
		{NOBU_ITEM_0010, 0},
		{NOBU_ITEM_0012, 0},
		{NOBU_ITEM_0013, 0},
		{NOBU_ITEM_0017, 0},
		{NOBU_ITEM_0018, 0},
		{NOBU_ITEM_0019, 0},
		{NOBU_ITEM_0020, 0},
		{NOBU_ITEM_0022, 0},
		{NOBU_ITEM_0023, 0},
		{NOBU_ITEM_0024, 0},
		{NOBU_ITEM_0026, 0},
		{NOBU_ITEM_0027, 0},
		{NOBU_ITEM_0028, 0},
		{NOBU_ITEM_0014, 0},
		{NOBU_ITEM_0015, 0},
		{NOBU_ITEM_0016, 0},
		{NOBU_ITEM_1000, 0},
		{NOBU_ITEM_1002, 0},
		{NOBU_ITEM_1003, 0},
		{NOBU_ITEM_1004, 0},
		{NOBU_ITEM_1005, 0},
		{NOBU_ITEM_1006, 0},
		{NOBU_ITEM_1007, 0},
		{NOBU_ITEM_1008, 0},
		{NOBU_ITEM_1009, 0},
		{NOBU_ITEM_1010, 0},
		{NOBU_ITEM_1011, 0},
		{NOBU_ITEM_1012, 0},
		{NOBU_ITEM_1014, 0},
		{NOBU_ITEM_1015, 0},
		{NOBU_ITEM_1016, 0},
		{NOBU_ITEM_1017, 0},
		{NOBU_ITEM_1018, 0},
		{NOBU_ITEM_1019, 0},
		{NOBU_ITEM_1020, 0},
		{NOBU_ITEM_1021, 0},
		{NOBU_ITEM_3000, 0},
		{NOBU_ITEM_3001, 0},
		{NOBU_ITEM_3002, 0},
		{NOBU_ITEM_3005, 0},
		{NOBU_ITEM_3006, 0},
		{NOBU_ITEM_3007, 0},
		{NOBU_ITEM_3008, 0},
		{NOBU_ITEM_3009, 0},
		{NOBU_ITEM_3010, 0},
		{NOBU_ITEM_3011, 0},
		{NOBU_ITEM_3012, 0},
		{NOBU_ITEM_3014, 0},
		{NOBU_ITEM_3015, 0},		
		{ 0, 0 },
	};

	Nobu_HDmemDropMainProc(dropItems, ptrItem);

}

void main() {
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	Nobu_MemDigging(DropProc, 800);
} 