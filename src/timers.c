// Including necessary header files
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/Nokia5110.h"
#include "..\\./headers/timers.h"
#include "..\\./headers/xo.h"

// Declaring external variables from other files
extern int time, turn;
extern unsigned long SW1, SW2;

// Function to initialize Timer 2 with a given period
void Timer2_Init(unsigned long period)
{ 
  unsigned long volatile delay;

  // Enabling Timer 2 clock
  SYSCTL_RCGCTIMER_R |= 0x04; 

  // Waiting for timer to stabilize
  delay = SYSCTL_RCGCTIMER_R;

  // Disabling Timer 2
  TIMER2_CTL_R = 0x00000000;  

  // Configuring Timer 2 to be a periodic timer in 32-bit mode
  TIMER2_CFG_R = 0x00000000;  
  TIMER2_TAMR_R = 0x00000002; 

  // Setting the load value for Timer 2 to the given period - 1
  TIMER2_TAILR_R = period - 1;  

  // Disabling any prescaler
  TIMER2_TAPR_R = 0;          

  // Clearing any pending interrupt flags and enabling the interrupt
  TIMER2_ICR_R = 0x00000001;  
  TIMER2_IMR_R = 0x00000001;  

  // Setting the interrupt priority to 4 (lower than default)
  NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x80000000; 

  // Enabling the interrupt in the NVIC
  NVIC_EN0_R = 1 << 23;    

  // Enabling Timer 2
  TIMER2_CTL_R = 0x00000001;    
}

// Interrupt handler for Timer 2
void Timer2A_Handler(void)
{ 
  // Acknowledge Timer 2A timeout
  TIMER2_ICR_R = 0x00000001;   

  // Increment time variable
	time++;
	
  // If time has reached 6, set SW1 to 1 and SW2 to 0 indicating a turn change
	if (time == 6)
	{
		SW1 = 1;
		SW2 = 0;
		return;
	}
	
  // Otherwise, switch turns
	select_turn();
}

// Function to reset the value of Timer 2
void reset_timer2(void)
{
	TIMER2_TAV_R = 0;
}

// Function to enable Timer 2
void enable_timer2(void) 
{
	TIMER2_CTL_R = 0x00000001; 
}

// Function to disable Timer 2
void disable_timer2(void) 
{
	TIMER2_CTL_R &= ~(1 << 0);
}

// Function to delay program execution by 100ms * count
void Delay100ms(unsigned long count)
{
  unsigned long volatile time;
  
  while(count > 0)
  {
    time = 727240;            // 0.1sec at 80 MHz
    while(time) time--;
    count--;
  }
}
