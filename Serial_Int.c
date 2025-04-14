#include<p18f4580.h>
#define led PORTBbits.RB1
#define led1 PORTBbits.RB2

	int i,temp;
void main(){
	ADCON1=0x0f;
	TRISB=0x00;
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// TXEN=1, Async mode, High speed, 8 bit tx
	RCSTA=0x90;	//serial port enable, 8 bit rx, enable reciver  
//	SPBRG=0x19;	// Generate the B.R 9600
	SPBRG=129; //9600 & 20MHz (working)
//	SPBRG=9;	// 20Mhz & 115200

	INTCONbits.GIE=1;
	INTCONbits.PEIE=1;
	PIE1bits.RCIE=1;	// Recieve interrupt enable
		
	while(1){
			
	}
}	

#pragma code Rx_int=0x08
#pragma interrupt Rx_int 

void Rx_int(){
	while(PIR1bits.RCIF==0);
	PIR1bits.RCIF=0;
	temp=RCREG;	// coping the data into temp var
		switch(temp)
			{
			case '1':
				led=1;
			break;
			case '2':
				led=0;
			break;
			case 'a':
				led1=1;
			break;
			case 'b':
				led1=0;
			break;
		}
}


/*
// 2nd Method of Serial Int
#include<p18f4580.h>
#define led PORTDbits.RD0
#define led1 PORTDbits.RD1

	int i,temp;
void main(){
	
	TRISD=0x00;
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// TXEN=1, Async mode, High speed, 8 bit tx
	RCSTA=0x90;	//serial port enable, 8 bit rx, enable reciver  
	SPBRG=0x19;	// Generate the B.R 9600

	INTCONbits.GIE=1;
	INTCONbits.PEIE=1;
	PIE1bits.RCIE=1;	// Recieve interrupt enable
		
	while(1){
			switch(temp)
			{
				case '1':
					led=1;
				break;
				case '2':
					led=0;
				break;
				case 'a':
					led1=1;
				break;
				case 'b':
					led1=0;
				break;
			}
	}
}	

#pragma code Rx_int=0x08
#pragma interrupt Rx_int 

void Rx_int(){
			while(PIR1bits.RCIF==0);
		PIR1bits.RCIF=0;
			temp=RCREG;	// coping the data into temp var
}
*/