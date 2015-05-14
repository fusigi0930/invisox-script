#include ".\nobu_mem_function.hxx"
#include ".\inc\nobu_items.h"

void DropProc(SHDNobuItem *ptrItem) {
	SHDNobuDrop dropItems[] = {
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