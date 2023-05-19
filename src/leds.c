// Including necessary header files
#include "..\./headers/tm4c123gh6pm.h"
#include "..\./headers/Nokia5110.h"
#include "..\./headers/TExaS.h"
#include "..\./headers/leds.h"

/*
X = PB2     0x04
O = PB3     0x08
D = PB7     0x80
*/

// Function to set LED for X
void setLED_X(void)
{
GPIO_PORTB_DATA_R |= 0x04;         // Setting bit 2 (X) of GPIO port B high
GPIO_PORTB_DATA_R &= ~(0x08);      // Clearing bit 3 (O) of GPIO port B
GPIO_PORTB_DATA_R &= ~(0x80);      // Clearing bit 7 (D) of GPIO port B
}

// Function to set LED for O
void setLED_O(void)
{
GPIO_PORTB_DATA_R &= ~(0x04);      // Clearing bit 2 (X) of GPIO port B
GPIO_PORTB_DATA_R |= 0x08;         // Setting bit 3 (O) of GPIO port B high
GPIO_PORTB_DATA_R &= ~(0x80);      // Clearing bit 7 (D) of GPIO port B
}

// Function to set LED for D
void setLED_D(void)
{
GPIO_PORTB_DATA_R &= ~(0x04);      // Clearing bit 2 (X) of GPIO port B
GPIO_PORTB_DATA_R &= ~(0x08);      // Clearing bit 3 (O) of GPIO port B
GPIO_PORTB_DATA_R |= 0x80;         // Setting bit 7 (D) of GPIO port B high
}

// Function to clear all LEDs
void clearLEDS(void)
{
GPIO_PORTB_DATA_R &= ~(0x04);      // Clearing bit 2 (X) of GPIO port B
GPIO_PORTB_DATA_R &= ~(0x08);      // Clearing bit 3 (O) of GPIO port B
GPIO_PORTB_DATA_R &= ~(0x80);      // Clearing bit 7 (D) of GPIO port B
}