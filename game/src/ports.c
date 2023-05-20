// Including necessary header files for the program
#include "..\./headers/tm4c123gh6pm.h"
#include "..\./headers/timers.h"
#include "..\./headers/ports.h"

// Declaring global variables SW1 and SW2 of type unsigned long
extern unsigned long SW1, SW2;

// Declaring a volatile unsigned long variable named 'delay'
volatile unsigned long delay;

// Function to initialize Port B of the MCU
void PortB_Init(void)
{
	SYSCTL_RCGC2_R |= 0x00000002;   // Enabling clock for Port B
	delay = SYSCTL_RCGCGPIO_R;      // Delaying 3-5 clock cycles

	GPIO_PORTB_LOCK_R = 0x4C4F434B; // Unlocking Port B
	GPIO_PORTB_CR_R = 0xFF;         // Allowing changes to all

	GPIO_PORTB_AMSEL_R = 0x00;      // Disabling analog functionality
	GPIO_PORTB_PCTL_R = 0x00000000; // Configuring PB7-0 as GPIO pins
	GPIO_PORTB_DIR_R = 0xEE;        // make all output except PB0 and PB4

	GPIO_PORTB_AFSEL_R = 0x00;      // Disabling alternate function
	GPIO_PORTB_DEN_R = 0xFF;        // Enabling digital function for all pins of Port B

	GPIO_PORTB_PUR_R = 0x11;        // Activating pull-up resistors for PB0 and PB4
	GPIO_PORTB_IS_R &= ~0x11;       // Setting PB0 and PB4 as edge-sensitive
	GPIO_PORTB_IBE_R &= ~0x11;      // Disabling both rising and falling edge triggering
	GPIO_PORTB_IEV_R &= ~0x11;      // Configuring interrupt to be triggered on falling edge for both PB0 and PB4
	GPIO_PORTB_ICR_R = 0x11;        // Clearing the interrupt flag for PB0 and PB4
	GPIO_PORTB_IM_R |= 0x11;        // Enabling interrupts for PB0 and PB4s

	// Configuring the priority of the interrupt handlers
	NVIC_PRI0_R = (NVIC_PRI0_R & 0xffff8fff) | 0x00000000;	// Preority = 0 best heighest one 

	// Enabling interrupts for Port B in NVIC register			// IRQ = 1
	NVIC_EN0_R = 0x00000002;

	// Enabling global interrupts
	EnableInterrupts();
}

// Interrupt handler for Port B
void GPIOPortB_Handler(void)
{	
	if (GPIO_PORTB_MIS_R & 0x10)   	// Checking if interrupt is caused by PB4
	{

		//if (GPIO_PORTB_DATA_R & 0x10) // Checking if the button is pressed or released	=> always true here
		//{
			GPIO_PORTB_ICR_R |= 0x10; 	// Clearing the interrupt flag for PB4
			Delay100ms(2);         			// Debouncing the switch
			SW1 = 1;                		// Setting SW1 to 1 indicating button press event
			SW2 = 0;                		// Setting SW2 to 0 indicating no button press event
		//}
	}
	else if (GPIO_PORTB_MIS_R & 0x01) // Checking if interrupt is caused by PB0
	{

		//if (GPIO_PORTB_DATA_R & 0x01)   // Checking if the button is pressed or released => always true here
		//{
			GPIO_PORTB_ICR_R |= 0x01;   	// Clearing the interrupt flag for PB0
			Delay100ms(2);            		// Debouncing the switch
			SW1 = 0;                  		// Setting SW1 to 0 indicating no button press event
			SW2 = 1;                  		// Setting SW2 to 1 indicating button press event
		//}
	}	
}
