#define F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
void i2c_start(void );
void i2c_stop(void  );
void i2c_write(unsigned char );
char i2c_read(char );
void i2c_init(void  );
void i2c_slave_address();
void lcd_init(void);
void lcd_command(char );
void command_enable();
void lcd_data(char );
void data_enable();
void rtc_int();
void set_date(char ,char ,char );
void set_time(char ,char ,char );
void get_date(char *,char *,char *);
void get_date(char *,char *,char *);
void lcdstring(char );
void stringdisplay(char *);
void i2c_start(void )
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	
}

void i2c_stop(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	
}
void i2c_init(void)
{
	TWSR=0x00;
	TWBR=0x47;
	TWCR=0x04;
}
void i2c_write(unsigned char x)
{
	TWDR=x;
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	
}
char i2c_read(char x)
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(x<<TWEA);
	while((TWCR&(1<<TWINT))==0);
	return(TWDR);
}
void rtc_int()
{
	TWBR=8;
	i2c_start();
	i2c_slave_address();
	i2c_write(0x07);
	i2c_write(0x00);
	i2c_stop();
	
}
void set_time(char h,char m,char s)
{
	
	i2c_start();
	i2c_slave_address();
	i2c_write(0x00);
	i2c_write(s);
	i2c_write(m);
	i2c_write(h);
	i2c_stop();
}
void set_date(char d,char m,char y)
{
	
	i2c_start();
	i2c_slave_address();
	i2c_write(0x04);
	i2c_write(d);
	i2c_write(m);
	i2c_write(y);
	i2c_stop();
}
void get_time(char *h,char *m,char *s)
{
	
	i2c_start();
	i2c_slave_address();
	i2c_write(0x00);
	i2c_stop();
	i2c_start();
	i2c_write(0xD1);
	*s=i2c_read(1);
	*m=i2c_read(1);
	*h=i2c_read(0);
	i2c_stop();
}
void get_date(char *d,char *m,char *y)
{
	
	i2c_start();
	i2c_slave_address();
	i2c_write(0x04);
	i2c_stop();
	i2c_start();
	i2c_write(0xD1);
	*d=i2c_read(1);
	*m=i2c_read(1);
	*y=i2c_read(0);
	i2c_stop();
}
void i2c_slave_address()
{
	TWDR=0xD0;
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	
}


int main(void)
{
	DDRA=0xFF;
	DDRB=0xFF;
	lcd_init();
	char hour,min,sec,date,month,year;
	TWBR=8;
	rtc_int();
	set_time(0x20,0x25,0x15);
	set_date(0x11,0x07,0x17);
	lcd_command(0x0C);
	stringdisplay("TIME:");lcd_command(0xC0);
	stringdisplay("DATE:");lcd_command(0x80);
		
	while(1)
	{
        lcd_command(0x86); 
	    get_time(&hour,&min,&sec);
	    get_date(&date,&month,&year);
	    lcdstring(((hour>>4)&0x0F)+48);
	    lcdstring((hour&0x0F)+48);lcdstring(':');
		lcdstring(((min>>4)&0x0F)+48);
		lcdstring((min&0x0F)+48);lcdstring(':');   
	    lcdstring(((sec>>4)&0x0F)+48);
	    lcdstring((sec&0x0F)+48);
		
		lcd_command(0xC6);
		
		lcdstring(((date>>4)&0x0F)+48);
		lcdstring((date&0x0F)+48);lcdstring('/');
		lcdstring(((month>>4)&0x0F)+48);
		lcdstring((month&0x0F)+48);lcdstring('/');
		lcdstring(((year>>4)&0x0F)+48);
		lcdstring((year&0x0F)+48);
			    
		lcd_command(0x80);		
	}
}

void lcdstring(char p)
{

		lcd_data(p);
	
}
void stringdisplay(char *p)
{
while(*p!='\0')
	lcd_data(*p++);
	
}
void lcd_command(char x)
{
	PORTB=x&0xf0;command_enable();
	PORTB=(x<<4)&0xf0; command_enable();
}
void command_enable()
{
	PORTB=PORTB&~(1<<0);
	PORTB=PORTB&~(1<<1);
	PORTB=PORTB|(1<<2); 
	_delay_ms(1);
	PORTB=PORTB&~(1<<2);
		_delay_ms(2);
}

void lcd_data(char x)
{
	PORTB=x&0xf0; data_enable();
	PORTB=(x<<4)&0xf0; data_enable();
}
void data_enable()
{
	PORTB=PORTB|(1<<0);
	PORTB=PORTB&~(1<<1);
	PORTB=PORTB|(1<<2); 
	_delay_ms(1);
	PORTB=PORTB&~(1<<2);
	_delay_ms(2);
}
void lcd_init()
{
	DDRB=0xff;
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0e);

}