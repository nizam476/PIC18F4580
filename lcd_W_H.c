#include<p18f4580.h>
#include "lcd1.h"

void main(){
	TRISC=0x00;
	TRISD=0x00;

	lcd_init();
	while(1){
	msg(0x80,"Hand is paining");
	}
}
