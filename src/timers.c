#include "..\\./headers/tm4c123gh6pm.h" 
#include "..\\./headers/Nokia5110.h" 
#include "..\\./headers/timers.h"
#include "..\\./headers/xo.h"

extern int time, turn;
extern unsigned long SW1,SW2;

// You can use this timer only if you learn how it works
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}


void Timer2A_Handler(void){ 
   TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
	time++;
	if (time == 6)
	{
		SW1 = 1;
		SW2 = 0;
		return;
	}
	select_turn();
}

void reset_timer2(void)
{
	TIMER2_TAV_R = 0;           // reset Timer 2A
}

void enable_timer2(void) {
	TIMER2_CTL_R = 0x00000001; 
}

void disable_timer2(void) {
	TIMER2_CTL_R &= ~(1 << 0);
}

void Delay100ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
	
}

void printTime()
{
	Nokia5110_SetCursor(8, 4);	
	if (time == 1)Nokia5110_OutString("01");
	else if (time == 2)Nokia5110_OutString("02");
	else if (time == 3)Nokia5110_OutString("03");
	else if (time == 4)Nokia5110_OutString("04");
	else if (time == 5)Nokia5110_OutString("05");
	else if (time == 6)Nokia5110_OutString("06");
	else if (time == 7)Nokia5110_OutString("07");
	else if (time == 8)Nokia5110_OutString("08");
	else if (time == 9)Nokia5110_OutString("09");
	else if (time == 10)Nokia5110_OutString("10");

}
