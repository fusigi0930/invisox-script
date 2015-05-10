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
		{ 0, 0 },
	};

	Nobu_HDmemDropMainProc(dropItems, ptrItem);

}

void main() {
	// Init Delay
	MRF_Delay(1000);
	IOC_onKeypress(VK_ALT);
	
	Nobu_HDMemDigging(DropProc, 800);
} 