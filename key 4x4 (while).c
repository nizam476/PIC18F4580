#include<p18f4580.h>
# define rs PORTCbits.RC0
#define en PORTCbits.RC1

void cmd( char);
void dat( char);
void delay(int);
void lcdinit();

void delay(int a){
int i,j;
for(i=0;i<a;i++)
for(j=0;j<233;j++);
}
void main(){
ADCON1=0X0F;  	// all pins are set to digital i/p & o/p
TRISD=0X00;  	//make all pin as output pins
TRISB=0Xf0;
TRISC=0X00;

 
//1111 all c1=c2=c3=c4=1
//1110 r1=0 and r2=r3=r4=0
//FOR R1

	cmd(0x38);
	delay(10);
	cmd(0x0E);
	delay(10);
	cmd(0x01);
	delay(10);
	cmd(0x80);
	cmd(0x06);
	delay(10);
while(1){

PORTB=0XFE;	// r1=0 & r2=r3=r4=1
if(PORTB==0XEE)
{
	while(PORTB==0XEE);	// polling method   
// checking the still sw is pressed
dat('7');

}
if(PORTB==0XDE)
{
dat('8');
while(PORTB==0XDE);
}
if(PORTB==0XBE)
{
while(PORTB==0XBE);
dat('9');

}
if(PORTB==0X7E)
{
while(PORTB==0X7E);
dat('/');

}

//FOR R2=0
PORTB=0XFD;
if(PORTB==0XED)
{
while(PORTB==0XED);
dat('4');
}
if(PORTB==0XDD)
{
while(PORTB==0XDD);
dat('5');
}
if(PORTB==0XBD)
{
while(PORTB==0XBD);
dat('6');

}
if(PORTB==0X7D)
{
while(PORTB==0X7D);
dat('*');

}

//FOR R3=0
PORTB=0XFB;
if(PORTB==0XEB)
{
while(PORTB==0xEB);
dat('1');

}
if(PORTB==0XDB)
{
while(PORTB==0XDB);
dat('2');
}
if(PORTB==0XBB)
{
while(PORTB==0XBB);
dat('3');
}
if(PORTB==0X7B)
{
while(PORTB==0X7B);
dat('-');
}

//FOR R4=0
PORTB=0XF7;
if(PORTB==0XE7)
{
while(PORTB==0XE7);
dat('C');
}
if(PORTB==0XB7)
{
while(PORTB==0XB7);
dat('#');
}
if(PORTB==0XD7)
{
while(PORTB==0XD7);
dat('0');
}
if(PORTB==0X77)
{
	while(PORTB==0x77);
dat('+');
}
}
}

void cmd( char a)
{
	PORTD=a;
	rs=0;
	en=1;
	delay(10);
	en=0;
}

void dat(char b)
{
	PORTD=b;
	rs=1;
	en=1;
	delay(10);
	en=0;
}

/*
#define r1 PORTBbits.RB4
#define r2 PORTBbits.RB5
#define r3 PORTBbits.RB6
#define r4 PORTBbits.RB7

#define c1 PORTBbits.RB0
#define c2 PORTBbits.RB1
#define c3 PORTBbits.RB2
#define c4 PORTBbits.RB3
*/