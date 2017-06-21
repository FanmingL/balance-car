#include "main.h"

int main(){
	All_Init();
	while(1){
		if (appTosave){
			appTosave=0;
			AppParamSave();
		}
		Delay_ms(50);
	}
}


