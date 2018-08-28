#define F_CPU 8000000UL
#define row0 0
#define row1 1
#define row2 2
#define row3 3
#define col0 4
#define col1 5
#define col2 6
#define col3 7
int keyscan();
#include <avr/io.h>
#include<util/delay.h>
void lcd_init(void);
void lcd_command(char );
void command_enable();
void lcd_data(char );
void data_enable();
void lcdstring(char *);
int main(void)
{
	lcd_init();
	DDRD=0xff;
	DDRB=DDRB&~(1<<PINB7);
	DDRB=DDRB|(1<<PINB5);
	DDRB=DDRB&~(1<<PINB4);
	DDRB=DDRB&~(1<<PINB6);
	 DDRA=0b11110000;
	 PORTA=0b00001111;
	SPCR=SPCR|(1<<SPR0)|(1<<SPE)|(1<<DORD)|(1<<CPOL)|(1<<CPHA); 
	SPSR=(1<<SPI2X);

	int score=0;
	for(int s=1;s<=13;s++){
		while( (SPSR&(1<<SPIF))==0);
		lcd_data(SPDR);
		if(s>12)
		{
			_delay_ms(100);
			lcd_command(0x01);
			
		}
	}	
	int flag=0;
	while(1)
	{

		while( (SPSR&(1<<SPIF))==0);
		char result1[1];
		sprintf(result1,"%d",SPDR);
		lcdstring(result1);
		if(score<21){_delay_ms(50);}
		   else if((score>21)&&(score<41)){_delay_ms(40);}
			  else if((score>41)&&(score<61)){_delay_ms(30);}
				else if((score>61)&&(score<81)){_delay_ms(25);}	
				    else if((score>81)&&(score<101)){_delay_ms(20);}
			            
		lcd_command(0x01);
		int p1=99;
		while(p1==99){
	    p1=keyscan();
		}		
		if(p1==SPDR)
		{
			score=score+10;
		}
		flag++;
		if(flag==10)
		{
			break;
		}
	SPSR=SPSR|(1<<SPIF);
		
}
char result[3];
sprintf(result,"%d",score);
lcdstring("SCORE:");lcd_command(0x87);
lcdstring(result);_delay_ms(1000);lcd_command(0x01);

	lcdstring("WELL PLAYED");
}
int keyscan()
{
	PORTA=PORTA&~(1<<col0);
	PORTA=PORTA|(1<<col1)|(1<<col2)|(1<<col3);
	if( (PINA&(1<<row0))==0)
	{
		
		return(7);
	}
	else if( (PINA&(1<<row1))==0)
	{
		return(4);}
	else if( (PINA&(1<<row2))==0)
	{
		return(1);}
	else if( (PINA&(1<<row3))==0)
	{
		return(0);}

	PORTA=PORTA&~(1<<col1);
	PORTA=PORTA|(1<<col0)|(1<<col2)|(1<<col3);

	if( (PINA&(1<<row0))==0)
	{
		return(8);
	}
	else if( (PINA&(1<<row1))==0)
	{
		return(5);}
	else if( (PINA&(1<<row2))==0)
	{
		return(2);}
	else if( (PINA&(1<<row3))==0)
	{
		return(0);}

	PORTA=PORTA&~(1<<col2);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col3);
	if( (PINA&(1<<row0))==0)
	{
		return(9);
	}
	else if( (PINA&(1<<row1))==0)
	{
		return(6);
	}
	else if( (PINA&(1<<row2))==0)
	{
		return(3);
	}
	else if( (PINA&(1<<row3))==0)
	{
		return(7);
	}

	PORTA=PORTA&~(1<<col3);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col2);

	if( (PINA&(1<<row0))==0)
	{
		return(7);
	}
	else if( (PINA&(1<<row1))==0)
	{
		return(7);
	}
	else if( (PINA&(1<<row2))==0)
	{
		return(7);
	}
	else if( (PINA&(1<<row3))==0)
	{
		return(7);
	}
	return(99);
	
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

void lcd_data(char x)//'A'//0x41//01000001
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
