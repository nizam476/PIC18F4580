#include<p18f4580.h>
#define rs PORTCbits.RC0
#define en PORTCbits.RC1

void lcd_cmd(char cm);
void delay();

void lcd_init(){
//lcd_cmd(0x0f); 	// switch on lcd & cursor blink
lcd_cmd(0x0e); 	// switch on lcd & cursor ON
lcd_cmd(0x01);	// clear screen
lcd_cmd(0x80);	// 1srt line 1st pos
lcd_cmd(0x38);	// 5x7 matrix
}

void lcd_cmd(char cm){
	PORTD=cm;		// 0x0f,01,80,38
	rs=0;	//  command mode		// IOCLR= CM
	//rw=0;	// write data
	en=1;
	delay();	// 450ns
	en=0;
}

void lcd_data(char dt){	// dt='\0'
	PORTD=dt;			// 
	rs=1;	// wirting data mode
	//rw=0;	// write data
	en=1;
	delay();	// 450ns
	en=0;
}

void delay(){
	int i,j;
for(i=0; i<102; i++)
for(j=0; j<102; j++);
}



void lcd_string(const rom char *str)
{// Its store the "string" into ROM memory bcoz ptr 
	// required address of var
	while(*str!='\0'){
		lcd_data(*str);
		str++;
	}
}

void main(){
	TRISC=0x00;
	TRISD=0x00;

	lcd_init();	

 while(1){
	lcd_cmd(0x85);
	lcd_string("Techno");
	lcd_cmd(0xC5);
	lcd_string("Scripts");

 }
}
