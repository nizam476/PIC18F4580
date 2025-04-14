#include<p18f4580.h>
# define rs PORTCbits.RC0
#define en PORTCbits.RC1

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

void cmd(char a);
void dat(char b);
void delay(int a);
void lcdinit(void );
void msg(const char Adr,rom const char *str);

void delay(int a){
int i,j;
for(i=0;i<a;i++)
for(j=0;j<233;j++);
}
void main(){
ADCON1=0X0F;  // all pins are set to digital
TRISD=0X00;  //make all pin as output pins
TRISB=0X00;	// row =0, col=1
// TRISB=0xF0;
TRISC=0X00;

lcdinit();
msg(0x81, "Hello");  
cmd(0x1);

//1111 all c1=c2=c3=c4=1
//1110 r1=0 and r2=r3=r4=0
//FOR R1

while(1){
//	cmd(0xC0);

	PORTB=0XFE;
if(PORTB==0XEE)
	{
	while(PORTB==0xEE);
	dat('1');
	delay(100);
//cmd(0x01);
	}
if(PORTB==0XDE)
	{
	while(PORTB==0xDE);
	dat('2');
//delay(1000);
//cmd(0x01);
	}
if(PORTB==0XBE)
	{
	dat('3');
	delay(100);
	cmd(0x01);
	}


//FOR R2
PORTB=0XFD;
if(PORTB==0XED)
{
	dat('4');
	delay(100);
	cmd(0x01);
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


//FOR R3
PORTB=0XFB;
if(PORTB==0XEB)
{
	while(PORTB==0xEB);
	dat('7');
	delay(100);
	cmd(0x01);
}
if(PORTB==0XDB)
{
	dat('8');
	delay(100);
	cmd(0x01);
}
if(PORTB==0XBB)
{
	dat('9');
	delay(100);
	cmd(0x01);
}

//FOR R4
PORTB=0XF7;
if(PORTB==0XE7)
{
	dat('*');
	delay(100);
	cmd(0x01);
}
if(PORTB==0XB7)
{
	dat('#');
	delay(100);
	cmd(0x01);
}
if(PORTB==0XD7)
{
	dat('0');
	delay(1000);
	cmd(0x01);
}
}
}

void cmd(char a)
{
	PORTD=a;
	rs=0;
	en=1;
	delay(100);
	en=0;
}

void dat(char b)
{
	PORTD=b;
	rs=1;
	en=1;
	delay(100);
	en=0;
}

void msg(const char Adr,rom const char *str){
	cmd(Adr);	// 80 , C0
	while(*str!='\0'){
		dat(*str);
		str++;
	}
}

void lcdinit(){
cmd(0x38);
	delay(10);
	cmd(0x0E);
	delay(10);
	cmd(0x01);	delay(10);
	cmd(0x80);
	cmd(0x06);
	delay(10);
}