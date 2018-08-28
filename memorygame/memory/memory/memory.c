#define F_CPU 8000000UL
#include<util/delay.h>
#include <avr/io.h>
#include<stdlib.h>
void lcd_init(void);
void lcd_command(char );
void command_enable();
void lcd_data(char );
void data_enable();
void lcdstring(char *);
int main(void)
{
	DDRC=0b00001111;
	PORTC=0x00;
	DDRD=0xFF;
	PORTD=0xFF;
	lcd_init();
	lcdstring("hiii shubham");
	_delay_ms(100);
	lcd_command(0x01);
    while(1)
    {
		int o=rand()%3+1;
		PORTC=PORTC|(1<<o);
		_delay_ms(500);
		PORTC=PORTC&~(1<<o);
		o=rand()%3+1;
		PORTC=PORTC|(1<<o);
		_delay_ms(500);
		PORTC=PORTC&~(1<<o);
		o=rand()%3+1;
		PORTC=PORTC|(1<<o);
		_delay_ms(500);
		PORTC=PORTC&~(1<<o);
		o=rand()%3+1;
		PORTC=PORTC|(1<<o);
		_delay_ms(500);
		PORTC=PORTC&~(1<<o);
		PORTC=PORTC|(0x0f);
		_delay_ms(1000);
		PORTC=0x00;
		
		
		
		
		
				
      
    }
}
void lcdstring(char *p)
{
	while( *p != '\0')
	{
		lcd_data(*p);
		p++;
	}
	
}

void lcd_init()
{
	DDRB=0xFF;

	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0e);

}
void lcd_command(char x)
{
	PORTB=x&0xf0;command_enable();
	PORTB=(x<<4)&0xf0; command_enable();
}
void command_enable()
{
	PORTB=PORTB&~(1<<0);//rs=0
	PORTB=PORTB&~(1<<1);//rw=0
	PORTB=PORTB|(1<<2); //en=1
	_delay_ms(1);
	PORTB=PORTB&~(1<<2);//en=0
	_delay_ms(2);
}

void lcd_data(char x)//'A'//0x41//01000001
{
	PORTB=x&0xf0; data_enable();
	PORTB=(x<<4)&0xf0; data_enable();
}
void data_enable()
{
	PORTB=PORTB|(1<<0);//rs=1
	PORTB=PORTB&~(1<<1);//rw=0
	PORTB=PORTB|(1<<2); //en=1
	_delay_ms(1);
	PORTB=PORTB&~(1<<2);//en=0
	_delay_ms(2);
}




#include <stdio.h>
#include <time.h>
#define MIN 0
#define MAX 100
int getrand(int min, int max);
int main(void) {
	int p=0, i=0;
	srand(time(NULL));
	for(i=0;i<getrand(1,13); i++) p=getrand(MIN,MAX);
	printf("Random value : p\n",p);
	return 0;
}
int getrand(int min,int max){
	return(rand()%(max-min)+min);
}
