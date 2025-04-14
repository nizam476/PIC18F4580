#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1

void lcd_cmd(char cm);

void delay(int a){
	int i,j;
	for(i=0; i<=a; i++)
	for(j=0; j<=i; j++);
}

void lcd_init(){
	lcd_cmd(0x01);	// clear screen
	lcd_cmd(0x0E);	//display on cursor on
	lcd_cmd(0x38);	// 2 lines 5x7 
	lcd_cmd(0x80);	//1st line 1st pos
}

void lcd_cmd(char cm){
PORTD=cm;
rs=0;
en=1;
delay(100);
en=0;
}

void lcd_data(char dt){
PORTD=dt;
rs=1;
en=1;
delay(100);
en=0;
}

void Lcd_String(rom const char *st){
	while(*st!='\0'){
	lcd_data(*st++);
	}
}

void main(){

int Adc_Val,i;
int arr[4];

TRISA=0xFF;		// make as i/p 
TRISC=0x00;
TRISD=0x00;

ADCON0=0x03;	// ADON=1, GO=1, channel select AN0
ADCON1=0x0E;	// Make analog i/p pins for AN0
//ADCON2=0x80;	// right justified, clk 2MHZ, 0 TAD
ADCON2=0x88;	// right justified, clk 2MHZ, 2 TAD


//ADCON0=0x07;	// ADON=1, GO=1, channel AN0
//ADCON1=0x0d;	// Make analog i/p pins
//ADCON2=0x8c;

	lcd_init();

	Lcd_String("Adc VAlue:");
	while(1){

	lcd_cmd(0xc0);
	ADCON0bits.GO=1;
	while(ADCON0bits.GO==1);	// conversionn in progress	GO=0
	
	Adc_Val=ADRESH;	// copying 8 bit data
	Adc_Val=Adc_Val<<8;
	Adc_Val=Adc_Val+ADRESL;
	
	for(i=0; i<4; i++){
		arr[i]=Adc_Val%10+'0';	// 1%10= 0.1=1
		Adc_Val=Adc_Val/10;	// 10/10= 1.0
	}
	for(i=3; i>=0; i--){
		lcd_data(arr[i]);
	}
	//lcd_cmd(0x01);
	}
}







/*
#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1

void lcd_cmd(char cm);

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);
}
void lcd_init(){
lcd_cmd(0x01);
lcd_cmd(0x0E);
lcd_cmd(0x38);
lcd_cmd(0x80);
}
void lcd_cmd(char cm){
PORTD=cm;
rs=0;
en=1;
delay(100);
en=0;
}
void lcd_data(char dt){
PORTD=dt;
rs=1;
en=1;
delay(100);
en=0;
}
void msg(char *st){
	while(*st!='\0'){
	lcd_data(*st++);
	}
}

void main(){
int Adc_Val,i,temp;
int arr[4];

ADCON0=0x03;	// ADON=1, GO=1, channel AN0
ADCON1=0x0E;	// Make analog i/p pins
ADCON2=0x80;	// left justified, clk 2MHZ
TRISA=0xFF;		// make as i/p 
TRISC=0x00;
TRISD=0x00;

	lcd_init();
	while(1){
ADCON0bits.GO=1;
	while(ADCON0bits.GO==1);	// conversionn in progress
//-------------
	Adc_Val=ADRESH;	// copying 8 bit data
	Adc_Val=Adc_Val<<8;
	
	temp=ADRESL;	// temp=11000000
	temp=temp>>6;	// temp=00000011
	Adc_Val=Adc_Val+temp;
----------------------	


//	Its working but some issues
	Adc_Val=ADRESL;		// temp=11000000
	Adc_Val=Adc_Val>>6;		// temp=00000011
	Adc_Val=Adc_Val<<8;
	Adc_Val=Adc_Val+ADRESH;	// temp=00000011 + 1111111
	---------
	Adc_Val=ADRESH;		// Adc_Val=1111111
	Adc_Val=Adc_Val<<8;	//Adc_Val=1111111 ---------

	temp=ADRESL;		// temp=11000000
	temp=(temp>>6)&0x0F;		//temp=00000011
	//temp=temp & 0x0F;
	Adc_Val=Adc_Val+temp;	// Adc_Val=1111111 00000011
	
//--------------
Adc_Val=ADRESL;		// Adc_Val=11000000
Adc_Val=(Adc_Val>>6);	//&0x0F;	//Adc_Val=00000011
//Adc_Val=Adc_Val& 0x0F;
Adc_Val=Adc_Val<<8;
Adc_Val=Adc_Val+ADRESH;	//temp=00000011 11111111

	Adc_Val=ADRESL | ADRESH;
	for(i=0; i<4; i++){
		arr[i]=Adc_Val%10+48;	// 1%10= 0.1=1
		Adc_Val=Adc_Val/10;	// 10/10= 1.0
	}
	for(i=3; i>=0; i--){
		lcd_data(arr[i]);
	}
	lcd_cmd(0x01);
	
	}
}
*/