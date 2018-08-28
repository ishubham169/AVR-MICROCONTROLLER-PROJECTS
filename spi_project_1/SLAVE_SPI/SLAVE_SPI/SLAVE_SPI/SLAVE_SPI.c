#define F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
void lcd_init(void);
void lcd_command(char );
void command_enable();
void lcd_data(char );
void data_enable();

int main(void)
{
	 lcd_init(); // INITIATE LCD
	 
	 DDRB=DDRB&~(1<<PINB4);// SET SS PIN AS INPUT
	 DDRB=DDRB&~(1<<PINB5); // SET MOSI PIN AS INPUT
	 DDRB=DDRB|(1<<PINB6);// SET MISO PIN AS OUTPUT
	 DDRB=DDRB&~(1<<PINB7);//SET SCK PIN AS INPUT
	 
	  int s=0;// DECLARATION OF VARIABLE
	 SPCR=SPCR|(1<<SPR0)|(1<<SPE); //SET SPEED OF SPI AND SPI ENABLE BIT
	 SPSR=SPSR|(1<<SPI2X); //DOUBLE THE SPEED OF SPI
	
	 
    while(1)
    {

		while( (SPSR&(1<<SPIF))==0);//WAIT TILL DATA TRANSMITTED FROM MASTER
		lcd_data(SPDR); //IF DATA COMPLETELY TRANSFERRED FROM MASTER THAN DISPLAY IT TO LCD
		
		s++;
		
		if(s>12) //AS WE KNOW LENGTH OF DATA IS '12' SO WE DATA COMPLETELY DISPLAY ON LCD THEN CLEAR LCD
		{
			s=0;
			_delay_ms(250);
			lcd_command(0x01);// CLEAR LCD IF DATA COMPLETELY DISPLAYED ON LCD
		
		}	
					
		
    }
}

void lcd_init()// WE HAVE STUDIED ALL THE FUNCTIONS BELOW IN PREVIOUS SECTION SO WE WON'T DISCUSS IT HERE
{
	DDRD=0xff;
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0e);

}
void lcd_command(char x)
{
	PORTD=x&0xf0;command_enable();
	PORTD=(x<<4)&0xf0; command_enable();
}
void command_enable()
{
	PORTD=PORTD&~(1<<0);//rs=0
	PORTD=PORTD&~(1<<1);//rw=0
	PORTD=PORTD|(1<<2); //en=1
	_delay_ms(1);
	PORTD=PORTD&~(1<<2);//en=0
	_delay_ms(2);
}

void lcd_data(char x)
{
	PORTD=x&0xf0; data_enable();
	PORTD=(x<<4)&0xf0; data_enable();
}
void data_enable()
{
	PORTD=PORTD|(1<<0);//rs=1
	PORTD=PORTD&~(1<<1);//rw=0
	PORTD=PORTD|(1<<2); //en=1
	_delay_ms(1);
	PORTD=PORTD&~(1<<2);//en=0
	_delay_ms(2);
}
