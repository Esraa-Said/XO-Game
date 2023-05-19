#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/Nokia5110.h"
#include "..\\./headers/TExaS.h"
#include "..\\./headers/leds.h"

/*
    X = PB2     0x04
    O = PB3     0x08
    D = PB7     0x80
*/


void setLED_X(void) {
	GPIO_PORTB_DATA_R |= 0x04;         // X
    GPIO_PORTB_DATA_R &= ~(0x08);      // O
	GPIO_PORTB_DATA_R &= ~(0x80);      // D
}
void setLED_O(void) {
	GPIO_PORTB_DATA_R &= ~(0x04);      // X
    GPIO_PORTB_DATA_R |= 0x08;         // O
	GPIO_PORTB_DATA_R &= ~(0x80);      // D
}
void setLED_D(void){
    GPIO_PORTB_DATA_R &= ~(0x04);      // X
    GPIO_PORTB_DATA_R &= ~(0x08);      // O
	GPIO_PORTB_DATA_R |= 0x80;         // D
}

void clearLEDS(void) {
    GPIO_PORTB_DATA_R &= ~(0x04);      // X
    GPIO_PORTB_DATA_R &= ~(0x08);      // O
	GPIO_PORTB_DATA_R &= ~(0x80);      // D
}

