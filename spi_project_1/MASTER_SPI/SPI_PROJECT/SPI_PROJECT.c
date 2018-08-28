#define F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
void transfer(char *);
void keyscan();
#define row0 0
#define row1 1
#define row2 2
#define row3 3
#define col0 4
#define col1 5
#define col2 6
#define col3 7

int main(void)
{
	DDRA=0b11110000; //SET THESE FOR KEYPAD
	PORTA=0b00001111;//SET THESE FOR KEYPAD
	
	DDRB=DDRB|(1<<PINB4); //SET SS BIT AS OUTPUT
	DDRB=DDRB|(1<<PINB5);//SET SS BIT AS OUTPUT
	DDRB=DDRB&~(1<<PINB6);//SET MISO BIT AS INPUT
	DDRB=DDRB|(1<<PINB7);//SET SS BIT AS OUTPUT
	
    SPCR=SPCR|(1<<SPE)|(1<<SPR0)|(1<<MSTR);// SET SPI ENABLE BIT, SET SPEED OF SPI,SET MSTR BIT TO USE MASTER MODE 
	SPSR=SPSR|(1<<SPI2X);// DOUBLE THE SPEED OF SPI
	 
     while(1)
    {
       keyscan();//ALWAYS CHECK WHETHER AN KEY IS PRESSED OR NOT AND IF KEY PRESSED THEN, TRANSFER THE NUMBER WRITTEN ON IT TO SLAVE USING SPI PROTOCOL.
    }
}
void transfer(char *x) //DECLARATION OF TRANSFER FUNCTION
{
	
	while(*x)
	{
		SPDR= *x++; // TRANSMIT ONE CHARACTER AT A TIME.
	
		while( (SPSR&(1<<SPIF))==0);// WAIT TILL DATA TRANSMITTED
	   _delay_ms(25);	
	}
}

void keyscan()// WE HAVE STUDIED KEYSCAN FUNCTION IN "INTERFACING WITH KEYPAD" SECTON
{
	PORTA=PORTA&~(1<<col0);
	PORTA=PORTA|(1<<col1)|(1<<col2)|(1<<col3);
	if( (PINA&(1<<row0))==0)
	{
		transfer("key 7 pressed");

		
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer("key 4 pressed");
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer("key 1 pressed");
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer("key O pressed");		
	}

	PORTA=PORTA&~(1<<col1);
	PORTA=PORTA|(1<<col0)|(1<<col2)|(1<<col3);

	if( (PINA&(1<<row0))==0)
	{
		
		transfer("key 8 pressed");
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer("key 5 pressed");
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer("key 2 pressed");
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer("key 0 pressed");
	}

	PORTA=PORTA&~(1<<col2);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col3);
	if( (PINA&(1<<row0))==0)
	{
		
		transfer("key 9 pressed");
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer("key 6 pressed");
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer("key 3 pressed");
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer("key = pressed");
	}
	PORTA=PORTA&~(1<<col3);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col2);

	if( (PINA&(1<<row0))==0)
	{
	
		transfer("key / pressed");
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer("key x pressed");
	}
	else if( (PINA&(1<<row2))==0)
	{
	
	transfer("key - pressed");
	}
	else if( (PINA&(1<<row3))==0)
	{
			transfer("key + pressed");
	}
	
	
}
