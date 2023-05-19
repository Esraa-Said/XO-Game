#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/timers.h"
#include "..\\./headers/ports.h"

extern unsigned long SW1,SW2;  // input from PF4,PF0
volatile unsigned long delay;


void PortB_Init(void)
{
//17-> 1 in regester so it is in enable0 bit 1 and in priority0 in INTB
  SYSCTL_RCGC2_R |= 0x00000002;   // 1) B clock
  delay = SYSCTL_RCGCGPIO_R;      // delay
  GPIO_PORTB_LOCK_R = 0x4C4F434B; // 2)unlock GPIO of PORTB
  GPIO_PORTB_CR_R = 0x01;         // Enable commit
  GPIO_PORTB_AMSEL_R = 0x00;      // 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTB_DIR_R = 0xEE;        // 5) PORT output for all pins except pins 0 & 4 
  GPIO_PORTB_AFSEL_R = 0x00;      // 6) no alternate function
  GPIO_PORTB_DEN_R = 0xFF;        // 7) enable digital pins PF4-PF0
	// GPIO_PORTB_PUR_R = 0x11;        // enable pullup resistors on PF4,PF0  
	// GPIO_PORTB_IS_R &= ~0x11;       // (d) PF4, PF0 are edge-sensitive
  // GPIO_PORTB_IBE_R &= ~0x11;      // PF4, PF0 are not both edges
  // GPIO_PORTB_IEV_R &= ~0x11;      // PF4, Pf0 are falling edge event
  // GPIO_PORTB_ICR_R = 0x11;        // (e) Clear flag4, flag0
  // GPIO_PORTB_IM_R |= 0x11;        // (f) Arm interrupt on PF4, PF0
	// NVIC_PRI0_R = (NVIC_PRI0_R & 0xffff8fff) | 0x00000000;

  // NVIC_EN0_R = 0x00000002;
	 //NVIC_EN0_R = 0x40000000;

	EnableInterrupts();
}


void GPIOPortB_Handler(void){
	
		if (GPIO_PORTB_MIS_R & 0x10) /* is it SW1 (PB4)?*/
    {                             
      if (GPIO_PORTB_DATA_R & 0x10)
      {
				Delay100ms(2);
				SW1 = 1;
				SW2 = 0;
        GPIO_PORTB_ICR_R |= 0x10;
				//GPIO_PORTB_DATA_R &= ~0x10; // clear PB4 data
				      //Delay100ms(2);

			}
    }
    else if (GPIO_PORTB_MIS_R & 0x01) /* then it must be SW2 (PB0) */
    {                                
      if (GPIO_PORTB_DATA_R & 0x01)
      {
				Delay100ms(2);
				SW1 = 0;
				SW2 = 1;
        GPIO_PORTB_ICR_R |= 0x01;
				//GPIO_PORTB_DATA_R &= ~0x01; // clear PB4 data
				      //Delay100ms(2);

			}
    }
		
}