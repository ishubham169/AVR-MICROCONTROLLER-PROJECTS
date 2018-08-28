#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void txstring(char *);
void usart_init();
void i2c_start();
void  i2c_slave_address();
void i2c_data(char x);
void lcd_init();
void lcd_command(char );
void lcd_data(char );
void lcd_string(char *);
int main()
{
	DDRB=DDRB|(7<<0);
	
	
	DDRC=DDRC|(1<<PC0)|(1<<PC1);
	TWBR=8;
	//usart_init();
	i2c_start();
	i2c_slave_address();
	//lcd_init();
	lcd_command(0x28);
	//	_delay_ms(100);
	
	lcd_command(0x0E);
	//_delay_ms(100);
	lcd_command(0x06);
	//_delay_ms(100);
	
	while(1)
	{
	
		lcd_string("SHUBHAM KAUSHIK");
		_delay_ms(1000);
		lcd_command(0x01);
		_delay_ms(100);
	}
	return 0;
}
void usart_init()
{
	UCSRB=UCSRB|(1<<TXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRL=0x33;
}
void i2c_start()
{
	TWCR=TWCR|(1<<TWINT)|(1<<TWSTA)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	switch(TWSR)
	{
		case 0x08: txstring("A START condition has been transmitted\r"); break;
		case 0x10: txstring("A repeated START condition has been transmitted\r"); break;
		default: txstring("Error in START\r");

	}
}

void i2c_slave_address()
{
	TWDR=0x40;
	TWCR=TWCR|(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
	switch(TWSR)
	{
		case 0x18: txstring("SLA+W has been transmitted; ACK has been received\r"); break;
		case 0x20: txstring("SLA+W has been transmitted; NOT ACK has been received\r"); break;
		default: txstring("Error in addrss writing\r");

	}
}

void i2c_data(char x)
{
	TWDR=x;
	TWCR=TWCR|(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while( (TWCR&(1<<TWINT))==0);
/*	switch(TWSR)
	{
		case 0x28: txstring("Data byte has been transmitted; ACK has been received\r"); break;
		case 0x30: txstring("Data byte has been transmitted; NOT ACK has been received\r"); break;
		case 0x38: txstring(" Arbitration lost in SLA+W or data bytes\r"); break;
		default: txstring("Error in data Transmission\r");

	}*/
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
void lcd_init()
{
	
	TWDR=0x38;//lcd_command(0x38);
   TWDR=0x0E;//	lcd_command(0x0E);
	TWDR=0x06;//lcd_command(0x06);
}
void lcd_command(char x)
{
/*  i2c_data(x);//PORTD=x;
  i2c_data(0x00);//PORTB=PORTB&~(1<<0);//rs=0
  i2c_data(0x00);	 //PORTB=PORTB&~(1<<1);//rw=0
  i2c_data(0x04);//	PORTB=PORTB|(1<<2); //en=1
	_delay_ms(1);
 i2c_data(0x00);//	PORTB=PORTB&~(1<<2);//en=0
	_delay_ms(2);*/
	
    i2c_data(x&0xF0); 	//PORTD=x&0xF0;
	i2c_data((x&0xF0)|(0x04));     //PORTD=PORTD&~(1<<0);//rs=0
	                    //PORTD=PORTD&~(1<<1);//rw=0
	                    //PORTD=PORTD|(1<<2);//en=1
	_delay_ms(1);
	i2c_data((x&0xF0)|(0x00));     //PORTD=PORTD&~(1<<2);//en=0
	_delay_ms(2);
	i2c_data((x<<4)&0xF0);//PORTD=(x<<4)&0xF0;
	i2c_data(((x<<4)&0xF0)|(0x04));       //PORTD=PORTD&~(1<<0);//rs=0
//    	PORTD=PORTD&~(1<<1);//rw=0
 //	PORTD=PORTD|(1<<2);//en=1
	_delay_ms(1);
	 i2c_data(((x<<4)&0xF0)|(0x00));            //PORTD=PORTD&~(1<<2);//en=0
	_delay_ms(2);
	
	
	
	
}
void lcd_data(char x)//0x41'A'
{
/*	i2c_data(x);    //PORTD=x;
    i2c_data(0x01);	//PORTB=PORTB|(1<<0);//rs=1
//	i2c_data(0x01); //PORTB=PORTB&~(1<<1);//rw=0
	i2c_data(0x05);     //PORTB=PORTB|(1<<2); //en=1
	_delay_ms(1);
	i2c_data(0x01); //PORTB=PORTB&~(1<<2);//en=0
	_delay_ms(2);
*/
	
i2c_data(x&0xF0);	//PORTD=x&0xF0;
i2c_data((x&0xF0)|(0x05));//	PORTD=PORTD|(1<<0);//rs=1
//	PORTD=PORTD&~(1<<1);//rw=0
	//PORTD=PORTD|(1<<2);//en=1
	_delay_ms(1);
	i2c_data((x&0xF0)|(0x01));//PORTD=PORTD&~(1<<2);//en=0
	_delay_ms(2);
i2c_data((x<<4)&0xF0);//	PORTD=(x<<4)&0xF0;
i2c_data(((x<<4)&0xF0)|(0x05));//	PORTD=PORTD|(1<<0);//rs=1
	//PORTD=PORTD&~(1<<1);//rw=0
//	PORTD=PORTD|(1<<2);//en=1
	_delay_ms(1);
i2c_data(((x<<4)&0xF0)|(0x01));//	PORTD=PORTD&~(1<<2);//en=0
	_delay_ms(2);
	
	
}
void lcd_string(char *p)
{
	
	while(*p !='\0')
	{
		lcd_data(*p);
		p++;
		 	}
}