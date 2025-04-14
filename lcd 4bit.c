#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1

void delay(int a);
void lcd_data(unsigned char dt);
void lcd_init();
void lcd_cmd(unsigned char cm);
void lcd_string(rom const char *ptr);
//void msg(const char Adr,rom const char *str);

void main(){
//	char str[]="4 bit LCd",i;

	TRISD=0x00;
	TRISC=0x00;

	lcd_init();

	lcd_cmd(0x82);
	lcd_string("Welcome....");
	lcd_cmd(0xc0);
	lcd_string("LCD 4 bit mode");

		while(1){
	}
}

void lcd_string(rom const char *ptr){

	while(*ptr!='\0'){
	lcd_data(*ptr);
	ptr++;
	}
}

void lcd_init(){
	lcd_cmd(0x02);		// 4 bit lcd
	lcd_cmd(0x28);		// 4bit lcd 5x7 matrix
	delay(100);
	lcd_cmd(0x0e);
	delay(100);
	lcd_cmd(0x01);
	lcd_cmd(0x06); // increment cursor
}

void lcd_cmd(unsigned char cm){
	unsigned char temp;
	temp=cm;	// copy data into temp
	
	rs=0;		// command mode
	en=1;
	cm=(cm&0xf0);	// 1st nibble
	PORTD=cm;
	en=0;
	delay(10); 
	
	en=1;
	temp=(temp &0x0f);		// 2nd nibble
	temp=temp<<4;
	PORTD=temp;
	delay(20);
	en=0;

}

void lcd_data(unsigned char dt){
	unsigned char temp;
	temp=dt;
	
	rs=1;			// data mode
	en=1;
	dt=(dt&0xf0);	// 1st nibble
	PORTD=dt;		// 0101 0110
	delay(10);
	en=0;	
	
	en=1;
	temp=(temp &0x0f);	// 2nd nibble 
	temp=temp<<4;
	PORTD=temp;
	delay(10);
	en=0;
}		

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<a; j++);
}

/*
void msg(const char Adr,rom const char *str){
	lcd_cmd(Adr);	// 85 , C0
	while(*str!='\0'){	// W != '\0'
		lcd_data(*str);
		str++;
	}
}
*/