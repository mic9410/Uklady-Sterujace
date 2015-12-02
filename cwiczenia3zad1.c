/*
 * GccApplication1.c
 *
 * Created: 2015-11-25 16:17:19
 *  Author: Administrator
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

uint8_t segment = 0;
unsigned int sekundy = 0;
uint8_t modulo[4] = {1,10,100,1000};
/*
modulo[0] = 1;
modulo[1] = 10;
modulo[2] = 100;
modulo[3] = 1000;
*/
const uint8_t numbers[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
   /* numbers[0] = 0x3F;
    numbers[1] = 0x06;
    numbers[2] = 0x5B;
    numbers[3] = 0x4F;
    numbers[4] = 0x66;
    numbers[5] = 0x6D;
    numbers[6] = 0x7D;
    numbers[7] = 0x07;
    numbers[8] = 0x7F;
    numbers[9] = 0x6F;*/
    int i = 0;  
ISR(TIMER0_COMP_vect){

    //CTC - tryb pracy
    PORTB = ~(1 << segment);
    i = (sekundy/(modulo[segment]))%10; //i - wyliczanie liczby którą chcemy wyświetlić
    PORTA = ~numbers[i]; //przekazanie do portu i wyświetlenie
    segment++;		   
    segment &= 0x03;
}	

int main(void)
{
    //PORTA = segment;
    DDRA = 0xFF; // wlaczenie portu A, ustawienie na wyjscie segmentow
    PORTA = 0x00; //zerujemy   
    
    DDRB = 0xFF; //ustawienie na wyjscie 4 wyśweitlaczy
    PORTB = 0xFF; //ustawiamy zeby nam sie swieciło wszystko na jednym segmencie
    TCCR0 |= (1 << CS01 | (1 << CS00));
    TIMSK |= (1 << OCIE0); //konfiguracja timera, podana na wykładzie
TCNT0 = 0;  
    OCR0 = 250; // konfiguracja przerwań, wartość podana na wykładzie

   sei();			
    while(1)
    {
	sekundy++;
	if(sekundy >= 1250){ //1000/8, bo takie było taktowanie procesora na którym pracowaliśmy 
		sekundy = 0;
	}
	_delay_ms(1000);
   }  
}


// Sprawozdanie powstało na podstawie wiedzy przedstawionej na wykładzie oraz artykułu ze strony http://diycenter.acid19.linuxpl.com/readarticle.php?article_id=3 
