#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 

char keyboard(){
	unsigned char result = 0;	
	DDRB = 0x0F; // ustawiamy zera dla wszystkich kolumn klawiatury
	PORTB = 0xF0;
	_delay_us(2);
	result = PINB; //odczytujemy wiersze
	
	DDRB = 0xF0; // ustawiamy zera dla wszystkich wierszy klawiatury
	PORTB= 0x0F;
	_delay_us(2);
	result = result | PINB; //uzyskanie kodu skanowania 

	switch(result){
	case 0b01110111 : return 1;
	case 0b01111011 : return 2;
	case 0b01111101 : return 3;
	case 0b01111110 : return 4;
	case 0b10110111 : return 5;
	case 0b10111011 : return 6;
	case 0b10111101 : return 7;
	case 0b10111110 : return 8;
	case 0b11010111 : return 9;
	case 0b11011011 : return 10;
	case 0b11011101 : return 11;
	case 0b11011110 : return 12;
	case 0b11100111 : return 13;
	case 0b11101011 : return 14;
	case 0b11101101 : return 15;
	case 0b11101110 : return 16;	
	}

}

uint8_t segment = 0;
unsigned int sekundy = 0;
uint8_t modulo[4] = {1,10,100,1000};
const uint8_t numbers[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int i = 0;  

ISR(TIMER0_COMP_vect){

    //CTC - tryb pracy
    PORTB = ~(segment);
    i = (sekundy/(modulo[segment]))%10; //i - wyliczanie liczby którą chcemy wyświetlić
    PORTA = ~numbers[i]; //przekazanie do portu i wyświetlenie
    segment++;		   
    segment &= 0x03;
}

int main(void){
//konfiguracja pomocniczego portu do wyświetlania wyniku skanowania
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

    PORTA = keyboard();			  
	sekundy++;
	if(sekundy >= 1250){ //1000/8, bo takie było taktowanie procesora na którym pracowaliśmy 
		sekundy = 0;
	}
	_delay_ms(1000);
   }  
  return 0;
}
}





