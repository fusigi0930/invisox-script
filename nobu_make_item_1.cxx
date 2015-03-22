#include "nobu_function.hxx"

void main(){
	// Init Delay
	MRF_Delay(300);
	Nobu_MakeItem();
	MRF_Delay(300);
	Nobu_onKeypress(VK_ESCAPE, 5);
}
