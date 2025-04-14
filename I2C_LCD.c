#include<p18f4580.h>

#define SLAVE_ADDRESS_LCD 0x4E

//void lcd_send_cmd(unsigned char data)
void lcd_init (void)
{
 lcd_send_cmd (0x02);
 lcd_send_cmd (0x28);
 lcd_send_cmd (0x0c);
 lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
 while (*str) lcd_send_data (*str++);
}

void lcd_send_data (unsigned char data)
{
 unsigned char data_l, data_u;
 data_l = (data<<4)&0xf0;  //select lower nibble by moving it to the upper nibble position
 data_u = data&0xf0;  //select upper nibble

 I2C_start();
 I2C_write (SLAVE_ADDRESS_LCD);
 I2C_write (data_u|0x0D);  //enable=1 and rs =1
 I2C_write (data_u|0x09);  //enable=0 and rs =1

 I2C_write (data_l|0x0D);  //enable =1 and rs =1
 I2C_write (data_l|0x09);  //enable=0 and rs =1

 I2C_stop();
}

void lcd_send_cmd(unsigned char data)
{
 unsigned char data_l, data_u;
 data_l = (data<<4)&0xf0;  //select lower nibble by moving it to the upper nibble position
 data_u = data&0xf0;  //select upper nibble

 I2C_start();
 I2C_write (SLAVE_ADDRESS_LCD);
 I2C_write (data_u|0x0C);  //enable=1 and rs =0
 I2C_write (data_u|0x08);  //enable=0 and rs =0

 I2C_write (data_l|0x0C);  //enable =1 and rs =0
 I2C_write (data_l|0x08);  //enable=0 and rs =0

 I2C_stop();
}

int main ()
{
    
    I2C_init(100000);  // initialise I2C at 100KHz
    lcd_init();
    
    lcd_send_string("hello world");

    
    while (1)
    {
       
    }
}
