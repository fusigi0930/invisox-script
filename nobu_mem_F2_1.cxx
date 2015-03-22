/*
�Ķ���
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
		// ��ѯ�
		case NOBU_ITEM_0012:
			if (g_nKeepItem1 > 3)
				Nobu_MemDropItem(ptrItem->dbNumber);
			else {
				g_nKeepItem1++;
				//Nobu_MemKeepItem();
				break;
			}
			break;
		// ���
		case NOBU_ITEM_0000:
		// �����
		case NOBU_ITEM_0003:
		// ����A
		case NOBU_ITEM_0004:
		// ��M��
		case NOBU_ITEM_0006:
		// ��֭�
		case NOBU_ITEM_0007:
		// ��÷�l
		case NOBU_ITEM_0008:
		// ��w�֭�
		case NOBU_ITEM_0010:
		// �ẵ�x
		case NOBU_ITEM_0013:
		// ��s��
		case NOBU_ITEM_0017:
		// �ᯡ��
		case NOBU_ITEM_0018:
		// ��p���Ф�
		case NOBU_ITEM_0019:
		// ��괳�ί�
		case NOBU_ITEM_0022:
		// ���
		case NOBU_ITEM_0023:
		// ����õ��
		case NOBU_ITEM_0024:
		// ��֪�
		case NOBU_ITEM_0026:
		// ��p�x�|��
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
		if (nCount >= ACTION_TIMES)�@{
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