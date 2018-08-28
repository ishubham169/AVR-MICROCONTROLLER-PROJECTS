#define F_CPU 8000000UL
#include<util/delay.h>

#include <avr/io.h>

int main(void)
{
	
	DDRB=(1<<4)|(1<<5)|(1<<7);
	PORTB=8;
	SPCR=SPCR|(1<<SPE)|(1<<MSTR);
	SPSR=SPSR|(1<<WCOL);
	while(1)
	{
		SPDR='B';
		while((SPSR&(1<<SPIF))==0){}
			//_delay_ms(100);
			SPDR='L';
			while((SPCR&(1<<SPIF))==0){}
		
	}
}