/*
 * miniproject2.c
 *
 *  Created on: 14 Sept 2022
 *      Author: marwan
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


/************Print Function**********/
void printnumb(unsigned char number)
{
	PORTC = (PORTC & 0xF0) | (number & 0x0F);
}



/************Variables***********/
unsigned char sec1 = 0;
unsigned char sec2 = 0;
unsigned char min1 = 0;
unsigned char min2 = 0;
unsigned char hour1 = 0;
unsigned char hour2 = 0;



/***************Initialization**************/

void Timer1_Init()
{
	SREG &=~(1<<7);
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
	TIMSK |= (1<<OCIE1A) ;
	TCNT1 = 0;
	OCR1A = 1000;
	SREG |=(1<<7);

}


void INT0_Init()
{
	SREG &=~(1<<7);
	DDRD &=~(1<<2);
	PORTD |=(1<<2);

	MCUCR |= (1<<ISC01);
	MCUCR &=~(1<<ISC00);
	GICR |= (1<<INT0);
	SREG |=(1<<7);
}


void INT1_Init()
{
	SREG &=~(1<<7);
	DDRD &=~(1<<3);

	MCUCR |= (1<<ISC11);
	MCUCR |= (1<<ISC10);
	GICR |=(1<<INT1);
	SREG |=(1<<7);

}

void INT2_Init()
{
	SREG &=~(1<<7);
	DDRB &=~(1<<2);
	PORTB |=(1<<2);
	MCUCSR &=~(1<<ISC2);
	GICR |=(1<<INT2);
	SREG |=(1<<7);
}
/***********************************ISR*************************************/

ISR(TIMER1_COMPA_vect)
{
	sec1++;
	if (sec1==10)
	{
		sec1= 0;
		sec2++;
		if (sec2 == 6)
		{
			sec2 =0;
			sec1 = 0;
			min1++;
		}
	}

	if (min1 == 10)
	{
		sec1=0;
		sec2=0;
		min1 =0;
		min2 ++;
		 if (min2 == 6 )
			{
				sec1=0;
				sec2=0;
				min1 =0;
				min2 = 0;
				hour1++;
			}
	}

	 if (hour1==10)
	{
		sec1=0;
		sec2=0;
		min1 =0;
		min2 = 0;
		hour1 = 0;
		hour2++;


}
	 if ( hour2 == 2 && hour1 ==4 )
						{
			            	sec1=0;
				 			sec2=0;
							min1 =0;
							min2 = 0;
							hour1 = 0;
							hour2= 0 ;

						}
	}


ISR (INT0_vect)
{
	sec1=0;
	sec2=0;
	min1 =0;
	min2 = 0;
	hour1 = 0;
	hour2= 0 ;
}
ISR (INT1_vect)
{
	TCCR1B &= 0xF8;
}
ISR (INT2_vect)
{
	TCCR1B |= (1<<CS10) | (1<<CS12);
}


/*******************Main Code***************/
int main()
{




	DDRC |= 0x0F;
	DDRA |= 0x3F;
	PORTA &=0xC0;
	PORTC &= 0xF0;
	Timer1_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();
	while(1)
	{




		PORTA = (PORTA & 0xC0) | 0x01;
		printnumb(sec1);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x02;
		printnumb(sec2);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x04;
		printnumb(min1);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x08;
		printnumb(min2);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x10;
		printnumb(hour1);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x20;
		printnumb(hour2);
		_delay_ms(3);
	}



}

