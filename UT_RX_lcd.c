#include<p18f4580.h>
//#include "Serial.h"
#include "LCD_4bit.h"


#define led PORTAbits.RA5
#define rs PORTCbits.RC0
#define en PORTCbits.RC1

//void print(const rom unsigned char *msg);
//void tx(unsigned char value);

void main(){
	char read[10],i;
	TRISAbits.RA5=0;	// o/p
	TRISD=0x00;
//	uart_init();

	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
//	SPBRG=0x19;		// 9600 B.R
	SPBRG=129;

	lcd_init();
	lcd_data('t');
	delay(10);
	lcd_cmd(0x01);

	while(1){
	for(i=0; i<=10; i++){
		read[i]=RCREG;
		while(PIR1bits.RCIF==0);// waiting for recieving data
		PIR1bits.RCIF=0;
	}	

	read[i]='\0';
// Sending data to LCD
	for(i=0; i<=10; i++)
		lcd_data(read[i]);
		
	lcd_cmd(0xc0);
  }
}
