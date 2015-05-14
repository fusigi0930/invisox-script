/*
±Ä¶À»É
*/
#include ".\nobu_mem_function.hxx"
#include ".\inc\nobu_items.h"

void DropProc(SHDNobuItem *ptrItem) {
	SHDNobuDrop dropItems[] = {
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