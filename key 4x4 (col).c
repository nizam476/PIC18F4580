#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1

void cmd(char);
void dat(char);
void delay(int);
void lcd_init();

void delay(int a){
int i,j;
for(i=0;i<a;i++)
for(j=0;j<233;j++);
}

void main(){
ADCON1=0X0F;  	// Configure all pins are set to digital i/p & o/p

TRISD=0X00;  	//make all pin as output pins
TRISB=0Xf0;		// col i/p & row as o/p
//TRISB=0x00; // if ur not connecting resistor
TRISC=0X00;

//1111 all c1=c2=c3=c4=1
//1110 r1=0 and r2=r3=r4=0
//FOR R1

	lcd_init();

while(1){
// Scan R1 
PORTB=0XFE;		// r1=0 & r2=r3=r4=1

if(PORTB==0XEE)	
{
 while(PORTB==0XEE); // checking the status of pin continuesly
	dat('7');
//	delay(100);
//	cmd(0x01);
}
if(PORTB==0XDE)
{
	while(PORTB==0xde); 
	dat('8');
//	delay(100);
//	cmd(0x01);
}
if(PORTB==0XBE)
{
   while(PORTB==0XBE);// continu check the pin status
	dat('9');
//	delay(100);
//	cmd(0x01);
}
if(PORTB==0X7E)
{
	dat('/');
	delay(100);
	cmd(0x01);
}

//FOR R2=0 & r1=r3=r4=1
PORTB=0XFD;
if(PORTB==0XED)
{
dat('4');
//delay(100);
//cmd(0x01);
}
if(PORTB==0XDD)
{
dat('5');
delay(100);
cmd(0x01);
}
if(PORTB==0XBD)
{
dat('6');
delay(100);
cmd(0x01);
}
if(PORTB==0X7D)
{
dat('*');
delay(100);
cmd(0x01);
}

//FOR R3=0 & R1=R2=R4=1
PORTB=0XFB;
if(PORTB==0XEB)
{
//while(PORTB==0xEB);
dat('1');
delay(100);
cmd(0x01);
}
if(PORTB==0XDB)
{
	dat('2');
	delay(100);
	cmd(0x01);
}
if(PORTB==0XBB)
{
dat('3');
delay(100);
cmd(0x01);
}
if(PORTB==0X7B)
{
dat('-');
delay(100);
cmd(0x01);
}

//FOR R4=0 & R1=R2=R3=1
PORTB=0XF7;
if(PORTB==0XE7)
{
dat('C');
delay(100);
cmd(0x01);
}
if(PORTB==0XB7)
{
dat('=');
delay(100);
cmd(0x01);
}
if(PORTB==0XD7)
{
dat('0');
delay(10);
cmd(0x01);
}
if(PORTB==0X77)
{
//	while(PORTB==0x77);
dat('+');
delay(10);
cmd(0x01);
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

void lcd_init(){
	cmd(0x38);
	delay(10);
	cmd(0x0E);
	delay(10);
	cmd(0x01);
	delay(10);
	cmd(0x80);
	cmd(0x06);
	delay(10);
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