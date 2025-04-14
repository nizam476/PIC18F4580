#include<p18f4580.h>
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define EN1 PORTCbits.RC2
#define EN2 PORTCbits.RC3
#define IN3 PORTCbits.RC4
#define IN4 PORTCbits.RC5

#define sw1 PORTBbits.RB0
#define sw2 PORTBbits.RB1
#define sw3 PORTBbits.RB2
#define sw4 PORTBbits.RB3

void main(){
	ADCON1=0x0f;//Analog pin convert/ confiure to dig i/p &o/p
	TRISB=0xff;
	TRISC=0x00;

	while(1){
	if(sw1==0){
	EN1=1;	
	EN2=1;
	IN1=1;
	IN2=0;		// clk wise direction
	IN3=1;
	IN4=0;
	}
	else if(sw2==0){
	EN1=1;	
	EN2=1;
	IN1=0;
	IN2=1;		// Anti-clk wise direction
	IN3=0;
	IN4=1;
	}
	else if(sw3==0){
	EN1=1;
	EN2=0;
	IN1=0;
	IN2=1;
	}
	else if(sw4==0){
	EN1=0;
	EN2=1;
	IN3=1;
	IN4=0;
	}
	else {
//	EN1=0;
//	EN2=0;
	IN1=0;IN2=0;
	IN3=0;IN4=0;
	}
  }
}

