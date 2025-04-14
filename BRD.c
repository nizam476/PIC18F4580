/*#include<p18f4580.h>
#define buzz PORTEbits.RE0

void main(){
	TRISEbits.RE0=0;
	while(1){
	buzz=1;

	}
}
*/
	// LED INTERFACING
/*
#include<p18f4580.h>
#define led1 PORTBbits.RB1
#define led2 PORTBbits.RB2
#define led3 PORTBbits.RB3

void delay();

void main(){
	TRISB=0x00;
	ADCON1=0x0f;
	while(1){
	led1=1;
	led2=1;
	led3=1;
	delay();
	led1=0;	led2=0;	led3=0;
	delay();
	}
}

void delay(){
	int i,j;
for(i=0; i<123; i++)
for(j=0; j<123; j++);

}
*/


		//	 LCD INTERFACING
/*
#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1
void lcd_cmd(char cm);
void delay();
void msg(rom const char *st);

void lcd_init(){
lcd_cmd(0x0f); 	// switch on lcd & cursor blink
lcd_cmd(0x01);	// clear screen
lcd_cmd(0x80);	// 1srt line 1st pos
lcd_cmd(0x38);	// 5x7 matrix
}

void lcd_cmd(char cm){
PORTD=cm;		// 0x0f,01,80,38
rs=0;	// wirting command
en=1;
delay();	// 450ns
en=0;
}
void delay(){
	int i,j;
for(i=0; i<523; i++)
for(j=0; j<523; j++);
}
void lcd_data(char dt){	// dt='A'
PORTD=dt;			// 
rs=1;	// wirting data
en=1;
delay();	// 450ns
en=0;
}

void msg(rom const char *st){
	while(*st!='\0')
		lcd_data(*st++);
}

void main(){
	TRISC=0x00;
	TRISD=0x00;

	lcd_init();
	lcd_data('A');
	while(1){
	lcd_cmd(0xc0);
	msg("Bottle");
	}
}
*/
/*
					//TIMER 0
#include<p18f4580.h>
#define led PORTBbits.RB2

void t0_delay(void){
//	TMR0H=0xB3;
//	TMR0L=0x68;		// 1000ms
	TMR0H=0x66;
	TMR0L=0xD0;		// 2000ms
	T0CONbits.TMR0ON=1;	// start timer
	while(INTCONbits.TMR0IF==0);//waiting for overflow
	INTCONbits.TMR0IF=0;	// clear flag bit
	T0CONbits.TMR0ON=0;	// stop timer
}

void main(){
	ADCON1=0x0f;
	TRISB=0x00;
	T0CON=0x07;	// prescale 1:256, 
	while(1){ 
	led=~led;
	t0_delay();
	}
}
*/

				// DC MOTOR working on hardware
/*
#include<p18f4580.h>
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1


void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<132; j++);
}
void main(){
	TRISC=0x00;
	while(1){
	IN1=1;
	IN2=0;
	delay(100);
	}
}
*/

					// Working on BRD
/*
#include<p18f4580.h>
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define sw PORTCbits.RC2
#define sw1 PORTBbits.RB5


void main(){
	TRISC=0x04;
	TRISB=0xFF;
	ADCON1=0x0f;

	while(1){
if(sw==0){
	IN1=1;
	IN2=0;
	}
else if(sw1==0){
	IN1=0;
	IN2=1;
}
	else{
	IN1=0;
	IN2=0;
	}	
  }
}
*/

						/*Keypad 4x4*/
/*
  char);
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
TRISB=0X00;
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
while(PORTB==0XEE); // still button is pressed
dat('7');
//delay(100);
//cmd(0x01);
}
if(PORTB==0XDE)
{
dat('8');
while(PORTB==0xde); // polling method
//delay(100);
//cmd(0x01);
}
if(PORTB==0XBE)
{
dat('9');
delay(100);
cmd(0x01);

}
if(PORTB==0X7E)
{
dat('/');
delay(100);
cmd(0x01);
}

//FOR R2=0
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
if(PORTB==0X7D)
{
dat('*');
delay(100);
cmd(0x01);
}

//FOR R3=0
PORTB=0XFB;
if(PORTB==0XEB)
{
while(PORTB==0xEB);
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

//FOR R4=0
PORTB=0XF7;
if(PORTB==0XE7)
{
dat('C');
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
delay(10);
cmd(0x01);
}
if(PORTB==0X77)
{
	while(PORTB==0x77);
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
*/
	// LED INTERFACING
/*
#include<p18f4580.h>

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<231; j++);
}
void main(){
	ADCON1=0x0F;
	TRISB=0x00;
	while(1){
	PORTBbits.RB1=1;
	PORTBbits.RB2=1;
	PORTBbits.RB3=1;
	delay(100);
	PORTBbits.RB1=0;
	PORTBbits.RB2=0;
	PORTBbits.RB3=0;
	delay(100);
	}
}
*/
				// Switch Interface with led
/*
#include<p18f4580.h>
#define sw1 PORTCbits.RC3
#define sw2 PORTCbits.RC2
#define sw3 PORTBbits.RB5
#define led1 PORTBbits.RB1
#define led2 PORTBbits.RB2
#define led3 PORTBbits.RB3
void main(){
	ADCON1=0x0F;
	TRISC=0xff;
	TRISB=0x20;
	while(1){
	if(sw1==0)
		led1=1;
	else
	  led1=0;
	if(sw2==0)
		led2=1;
	else 
		led2=0;	
	 if(sw3==0)
		led3=1;
	else 
		led3=0;
	}
}
*/
					// Switch with buzzer
/*
#include<p18f4580.h>
#define sw1 PORTCbits.RC2
#define buzz PORTEbits.RE0

void main(){

	TRISC=0xff;
	TRISE=0x00;
	buzz=0;
	while(1){
	if(sw1==0){
		buzz=1;
	}
	else{
	  buzz=0;
	}
	}
}
*/
					// LCD Interfacing 
/*
#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1
void lcd_cmd(char cm);
void delay();
void msg(char Adr, rom const char *str);
void lcd_init();

void lcd_init(){
lcd_cmd(0x0f); 	// switch on lcd & cursor blink
lcd_cmd(0x01);	// clear screen
lcd_cmd(0x38);	// 5x7 matrix
}

void lcd_cmd(char cm){
PORTD=cm;		// 0x0f,01,80,38
rs=0;	// wirting command
en=1;
delay();	// 450ns
en=0;

}
void delay(){
	int i,j;
for(i=0; i<123; i++)
for(j=0; j<123; j++);
}
void lcd_data(char dt){	// dt='A'
PORTD=dt;			// 
rs=1;	// wirting data
en=1;
delay();	// 450ns
en=0;
}
void main(){
	TRISC=0x00;
	TRISD=0x00;

	lcd_init();
	while(1){
	msg(0x80,"Welcome");
	}
}
void msg(char Adr, rom const char *str){
	lcd_cmd(Adr);
	while(*str!='\0')
		lcd_data(*str++);
}
*/
					//ADC interfacing
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
int Adc_Val,i;
int arr[4];

ADCON0=0x03;	// ADON=1, GO=1, channel AN0
ADCON1=0x0E;	// Make analog i/p pins
ADCON2=0x80;	// right justified, clk 2MHZ
TRISA=0xFF;		// make as i/p 
TRISC=0x00;
TRISD=0x00;

	lcd_init();
	while(1){
ADCON0bits.GO=1;
	while(ADCON0bits.GO==1);	// conversionn in progress
	
	Adc_Val=ADRESH;	// copying 8 bit data
	Adc_Val=Adc_Val<<8;
	Adc_Val=Adc_Val+ADRESL;
	
	
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
/*
#include<p18f4580.h>
#define led PORTDbits.RD3

void main(){
ADCON1=0x0F;
TRISDbits.RD3=0;		// make o/p pins
RCONbits.IPEN=0;	// disable the priority
INTCON=0x90;	// global Int enable, INT0 int enable,PEIE=0

//INTCONbits.GIE=1;	// global Int enable
//INTCONbits.INT0IE=1;	//INT0 int enable

INTCON2bits.INTEDG0=0;	// falling edge

led=0;				// led off
	while(1);
}

//#pragma code func_name=priority 
//#pragma interrupt func_name

#pragma code Ext0_ISR=0x08	// Highest priority 
#pragma interrupt Ext0_ISR	// assign the interrupt 	
void Ext0_ISR()
{
	if(INTCONbits.INT0IF==1){	// overlow occurred
	led=~led;
	}
INTCONbits.INT0IF=0;	// clear flag bits
}
*/
/*
				// External sw & led
#include<p18f4580.h>
#define sw1 PORTCbits.RC2
#define buzz PORTDbits.RD0

void main(){

	TRISC=0xff;
	TRISD=0x00;
	buzz=0;
	while(1){
	if(sw1==0){
		buzz=1;
	}
	else{
	  buzz=0;
	}
	}
}
*/

/* 
				// Internal Timer Interuppt 1 sec delay
#include<p18f4580.h>
int Count=0;
void main()
{
	int x=0;
	ADCON1=0x0F;//ADC pins converted to digital
	TRISB=0x00;
	PORTB=0x00;
	
	INTCONbits.GIE=1;// Global interrupt enable
	INTCONbits.PEIE=1;//peripheral interrupt enable
	PIE1bits.TMR1IE=1;// timer1 interrupt enable
	T1CON=0xB1;//configured timer1 to 16bits, prescaler to 1:8
	TMR1L=0x96;
	TMR1H=0xE7;
	while(1)
		{
		if(Count==100)
			{
				Count=0;
				PORTB=~PORTB;
			}
		}
}

#pragma code Interrupt_intr=0x08//here 'code' is keyword , 0x08 is higest priority in 0x08 to 0x18
#pragma interrupt Interrupt_intr//here 'interrupt' is keyword

void Interrupt_intr()
{
	if(PIR1bits.TMR1IF==1)
	{
		PIR1bits.TMR1IF=0;
		Count++;
		TMR1L=0x96;
		TMR1H=0xE7;
	}
}
*/
/*
						//	Interrupt EXT2
#include<p18F4580.h>
void delay(int ms);
void main()
{
	ADCON1=0x0F;				// Make all o/p
	TRISBbits.RB0=2;		//i/p pin RB1
	TRISC=0x00;					// o/p port
	
	INTCONbits.GIE=1;
	INTCONbits.PEIE=0;//disabled peripheral interrupt
	INTCON3bits.INT2IE=1;	// Enables the INT2 external interrupt
	RCONbits.IPEN=1;			// Enable priority level on interrupt
	INTCON2bits.INTEDG2=0;	// falling edge / 1-rising.

		PORTC=0x00;
	while(1);
}

#pragma code interrupt_intr=0x08
#pragma interrupt interrupt_intr
void interrupt_intr()
{
	if(INTCON3bits.INT2IF==1){
		PORTC=~PORTC;
//		delay(100);
}
INTCON3bits.INT2IF=0;
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<ms;j++);
}
*/
/*

						// Timer 0 1sec & 2 sec
#include<p18f4580.h>
#define led PORTBbits.RB0

void t0_delay(void){
	TMR0H=0xB3;
	TMR0L=0x68;		// 1000ms
//	TMR0H=0x66;
//	TMR0L=0xD0;		// 2000ms
	T0CONbits.TMR0ON=1;	// start timer
	while(INTCONbits.TMR0IF==0);//waiting for overflow
	INTCONbits.TMR0IF=0;	// clear flag bit
	T0CONbits.TMR0ON=0;	// stop timer
}

void main(){
	ADCON1=0x0f;
	TRISB=0x00;
	T0CON=0x17;	// prescale 1:256, 
	while(1){ 
	led=~led;
	t0_delay();
	}
}
*/


				/*External Interrupt 0 working on brd*/
/*
#include<p18F4580.h>
void delay(int ms);
void main()
{
	ADCON1=0x0F;
	TRISBbits.RB7=0;	//o/p(led)
	TRISBbits.RB0=1;	//i/p(sw)
	
	INTCONbits.GIE=1;
	INTCONbits.PEIE=0;		//disabled peripheral interrupt
	INTCONbits.INT0IE=1;	
	INTCON2bits.INTEDG0=1;		// falling edge
	PORTBbits.RB7=0;
	
	while(1);
}

#pragma code interrupt_intr=0x08
#pragma interrupt interrupt_intr

void interrupt_intr()
{
	while(INTCONbits.INT0IF==0);
	INTCONbits.INT0IF=0;
	PORTBbits.RB7=1;
	delay(1000);
	PORTBbits.RB7=0;
	delay(1000);	
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<ms;j++);
}
*/

// External Interrupt 1 not work
/*
#include<p18F4580.h>
void delay(int ms);
void main()
{
	ADCON1=0x0F;
	TRISBbits.RB7=0;	//o/p(led)
	TRISBbits.RB1=1;	//i/p(sw)
	
	INTCONbits.GIE=1;
	INTCONbits.PEIE=0;		//disabled peripheral interrupt
	INTCON3bits.INT1IE=1;	// ext int 1 enable
	INTCON2bits.INTEDG1=0;		// falling edge
	PORTBbits.RB7=0;				// led off
	
	while(1);
}

#pragma code interrupt_intr=0x08
#pragma interrupt interrupt_intr

void interrupt_intr()
{
	while(INTCON3bits.INT1IF==0);	//  interrupt is occured
	INTCON3bits.INT1IF=0;		// clear flag bit
	PORTBbits.RB7=1;
	delay(100);
	PORTBbits.RB7=0;
	delay(100);	
	
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<ms;j++);
}
*/

		// External Interrupt 2
/*
#include<p18F4580.h>
void delay(int ms);
void main()
{
	ADCON1=0x0F;				// Make all o/p
	TRISBbits.RB2=1;		//i/p pin RB2
	TRISC=0x00;					// o/p port
	
	INTCONbits.GIE=1;
	INTCONbits.PEIE=0;//disabled peripheral interrupt
	
	INTCON3bits.INT2IE=1;	// Enables the INT2 external interrupt
//	RCONbits.IPEN=1;		// Enable priority level on interrupt
	INTCON2bits.INTEDG2=0;	// falling edge / 1-rising.

		PORTC=0x00;
		
	while(1);

}

#pragma code interrupt_intr=0x08
#pragma interrupt interrupt_intr
void interrupt_intr()
{
	if(INTCON3bits.INT2IF==1){
		PORTC=~PORTC;
		delay(100);
}
INTCON3bits.INT2IF=0;
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<ms;j++);
}
*/



/*
// working on hardware
#include<p18f4580.h>
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1


void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<132; j++);
}
void main(){
	TRISC=0x00;
	while(1){
	IN1=1;
	IN2=0;
	delay(100);
	}
}
*/

// Working on BRD
/*
#include<p18f4580.h>
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define sw PORTCbits.RC2
#define sw1 PORTBbits.RB5


void main(){
	TRISC=0x04;
	TRISB=0xFF;
	ADCON1=0x0f;

	while(1){
if(sw==0){
	IN1=1;
	IN2=0;
	}
else if(sw1==0){
	IN1=0;
	IN2=1;
}
	else{
	IN1=0;
	IN2=0;
	}	
  }
}
*/

// UART TX
/*
#include<p18f4580.h>
#define led PORTAbits.RA5

void delay(int a);

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);
}
void main(){
	char i;
	TRISAbits.RA5=0;	// o/p
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
//	SPBRG=0x19;		// 9600 B.R & 4Mhz
	SPBRG=129;		// 9600 & 20Mhz
//  SPBRG=9;		// 115200 &20Mhz

	
	while(1){
	TXREG='B';
	while(PIR1bits.TXIF==0);
	PIR1bits.TXIF=0;	
	delay(1000);
	}
}
*/
// UART RX

#include<p18f4580.h>
#define led PORTBbits.RB1

void main(){
	char temp;
	TRISBbits.RB1=0;	// o/p
	ADCON1=0x0f;
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
	SPBRG=129;		// 9600 B.R

	while(1){
	while(PIR1bits.RCIF==0);// waiting for recieving data
		temp=RCREG;
	PIR1bits.RCIF=0;
		
		switch(temp){
		case '1':
		led=1;
		break;
		case '2':
		led=0;
		break;
		
		}
	}
}

// 	VARY PWM
/*
#include <p18f4580.h>

void MSdelay(unsigned int);

void main()
{
    unsigned int duty_cycle;  
   
    TRISCbits.TRISC2=0;  // Set CCP1 pin as output for PWM out 
    PR2=199;             // load period value in PR2 register 
    CCPR1L=1;            // load duty cycle 
    T2CON=0;             // no pre-scalar,timer2 is off 
    CCP1CON=0x0C;        // set PWM mode and no decimal value for PWM 
    TMR2=0;
    T2CONbits.TMR2ON=1;  // Turn ON Timer2 
    while(1)
    {
     for(duty_cycle=1;duty_cycle<1023;duty_cycle++){
          CCPR1L = duty_cycle;   // load duty cycle 
            MSdelay(50);
     }
     MSdelay(1500);
        
      for(duty_cycle=1023;duty_cycle>1;duty_cycle--){
        CCPR1L = duty_cycle;   // load duty cycle 
        MSdelay(50);
      }  
       MSdelay(1500);
   	} 
}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
       for(j=0;j<165;j++);      //This count Provide delay of 1 ms for 8MHz Frequency 
}
*/
/*		UART String
#include<p18f4580.h>
#define led PORTAbits.RA5
void print(const rom unsigned char *msg);
void tx(unsigned char value);

void delay(int a){
	int i,j;
for(i=0; i<a ;i++)
for(j=0; j<123; j++);
}
void main(){
	char str[]="Techno",i;
	TRISAbits.RA5=0;	// o/p
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
//	SPBRG=0x19;		// 9600 B.R
	SPBRG=129;
		
	while(1){
	for(i=0;i!='\0'; i++){
		TXREG=str[i];
		while(PIR1bits.TXIF==0);// waiting for recieving data
		PIR1bits.TXIF=0;
		delay(2000);
	}	
  }
}
*/