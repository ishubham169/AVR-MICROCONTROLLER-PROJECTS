#define F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
void transfer(int );
void transfer1(char *);
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
	
	DDRD=DDRD&~(1<<0);
	DDRD=DDRD&~(1<<1);
    DDRB=DDRB|(1<<PINB0)|(1<<PINB1);
	DDRA=0b11110000;
	PORTA=0b00001111;
	DDRB=DDRB|(1<<PINB4)|(1<<PINB5)|(1<<PINB7);
     SPCR=SPCR|(1<<SPE)|(1<<SPR0)|(1<<MSTR)|(1<<DORD)|(1<<CPOL)|(1<<CPHA);
	 SPSR=(1<<SPI2X);
	 PORTB=PORTB&~(1<<PINB4);
	 PORTB=PORTB&~(1<<PINB0);
	 PORTB=PORTB&~(1<<PINB1);
	 DDRB=DDRB&~(1<<PINB6);
	
	 PORTB=PORTB&~(1<<PINB0);
	 PORTB=PORTB|(1<<1);_delay_ms(100);transfer1("GAME BEGINS  ");
	 PORTB=PORTB&~(1<<PINB1); 
	 PORTB=PORTB|(1<<0);transfer1("GAME BEGINS  ");
	 PORTB=PORTB|(1<<PINB0);
	 PORTB=PORTB|(1<<PINB1);
	  
    while(1)
    {
	if((PIND&(1<<0))==0)
		{
		   PORTB=PORTB&~(1<<PINB0);	
			PORTB=PORTB|(1<<1);
			keyscan();
		
	}			
	else if((PIND&(1<<0))==1)
		{
			PORTB=PORTB&~(1<<1);
			PORTB=PORTB|(1<<0);
			keyscan();

		}			
       
	   
    }
}
void transfer(int x)
{
	
	
	
		SPDR= x;
	
		while( (SPSR&(1<<SPIF))==0);
	   _delay_ms(19);	
	
}
void transfer1(char *x)
{
	
	while(*x!='\0')
	{
	SPDR= *x++;
	
	while( (SPSR&(1<<SPIF))==0);
	_delay_ms(19);
}	
	
}
void keyscan()
{
	PORTA=PORTA&~(1<<col0);
	PORTA=PORTA|(1<<col1)|(1<<col2)|(1<<col3);
	if( (PINA&(1<<row0))==0)
	{
		transfer(7);
		
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer(4);
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer(1);
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer(0);
	}

	PORTA=PORTA&~(1<<col1);
	PORTA=PORTA|(1<<col0)|(1<<col2)|(1<<col3);

	if( (PINA&(1<<row0))==0)
	{
		
		transfer(8);
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer(5);
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer(2);
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer(0);
	}

	PORTA=PORTA&~(1<<col2);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col3);
	if( (PINA&(1<<row0))==0)
	{
		
		transfer(9);
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer(6);
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer(3);
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer(7);
	}

	PORTA=PORTA&~(1<<col3);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col2);

	if( (PINA&(1<<row0))==0)
	{
		
		transfer(7);
	}
	else if( (PINA&(1<<row1))==0)
	{
		
		transfer(7);
	}
	else if( (PINA&(1<<row2))==0)
	{
		
		transfer(7);
	}
	else if( (PINA&(1<<row3))==0)
	{
		
		transfer(7);
	}
	
}
