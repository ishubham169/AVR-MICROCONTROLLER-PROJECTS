#define F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
void i2c_start(void );
void i2c_stop(void  );
void i2c_write(unsigned char );
void i2c_read(char  );
void i2c_init(void  );
void usart_init();
void i2c_slave_address();
void txstring(char *);
void i2c_start(void )
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	switch(TWSR)
	{
		case 0x08: txstring("A START condition has been transmitted\r"); break;
		case 0x10: txstring("A repeated START condition has been transmitted\r"); break;
		default: txstring("Error in START\r");

	}
}
void usart_init()
{
	UCSRB=UCSRB|(1<<TXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRL=0x33;
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
	switch(TWSR)
	{
		case 0x28: txstring("Data byte has been transmitted; ACK has been received\r"); break;
		case 0x30: txstring("Data byte has been transmitted; NOT ACK has been received\r"); break;
		case 0x38: txstring(" Arbitration lost in SLA+W or data bytes\r"); break;
		default: txstring("Error in data Transmission\r");

	}
}
void i2c_slave_address()
{
	TWDR=0xD0;
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	switch(TWSR)
	{
		case 0x18: txstring("SLA+W has been transmitted; ACK has been received\r"); break;
		case 0x20: txstring("SLA+W has been transmitted; NOT ACK has been received\r"); break;
		default: txstring("Error in addrss writing\r");

	}
}


int main(void)
{
usart_init();
	DDRC=DDRC|(1<<PC0)|(1<<PC1);
	TWBR=8;
	
	i2c_start();
	i2c_slave_address();
	i2c_write(0x07);
	i2c_write(0x00);
	i2c_stop();
    _delay_ms(1000);
	i2c_start();
	i2c_slave_address();
	i2c_write(0x00);
	i2c_write(0x55);
	i2c_write(0x58);
	i2c_write(0x19);
	
	
	i2c_stop();

	
	
	
    while(1)
    {
         
    }
}
void txstring(char *x)
{
	while(*x)
	{
		UDR=*x;
	while( (UCSRA&(1<<UDRE))==0){}
	x++;
	_delay_ms(10);
}
}