#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/timers.h"
#include "..\\./headers/ports.h"

extern unsigned long SW1, SW2; // input from PF4,PF0
volatile unsigned long delay;

void PortB_Init(void)
{
  SYSCTL_RCGC2_R |= 0x00000002;
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTB_LOCK_R = 0x4C4F434B;
  GPIO_PORTB_CR_R = 0x01;
  GPIO_PORTB_AMSEL_R = 0x00;
  GPIO_PORTB_PCTL_R = 0x00000000;
  GPIO_PORTB_DIR_R = 0xEE;
  GPIO_PORTB_AFSEL_R = 0x00;
  GPIO_PORTB_DEN_R = 0xFF;
  GPIO_PORTB_PUR_R = 0x11;
  GPIO_PORTB_IS_R &= ~0x11;
  GPIO_PORTB_IBE_R &= ~0x11;
  GPIO_PORTB_IEV_R &= ~0x11;
  GPIO_PORTB_ICR_R = 0x11;
  GPIO_PORTB_IM_R |= 0x11;
  NVIC_PRI0_R = (NVIC_PRI0_R & 0xffff8fff) | 0x00000000;
  NVIC_EN0_R = 0x00000002;
  NVIC_EN0_R = 0x40000000;

  EnableInterrupts();
}

void GPIOPortB_Handler(void)
{

  if (GPIO_PORTB_MIS_R & 0x10) /* is it SW1 (PB4)?*/
  {
    if (GPIO_PORTB_DATA_R & 0x10)
    {
      Delay100ms(2);
      SW1 = 1;
      SW2 = 0;
      GPIO_PORTB_ICR_R |= 0x10;
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
      // GPIO_PORTB_DATA_R &= ~0x01; // clear PB4 data
      // Delay100ms(2);
    }
  }
}