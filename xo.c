#include "./headers/Nokia5110.h"
#include "./headers/TExaS.h"
#include "./headers/timers.h"
#include "./headers/ports.h"
#include "./headers/screens.h"
#include "./headers/operations.h"
#include "./headers/leds.h"
#include "./headers/xo.h"

int arr[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int pos, time = 1, turn = 0, ok = 0;
unsigned long SW1, SW2; 

int main(void)
{	

	PortB_Init();
  EnableInterrupts();
	TExaS_Init(SSI0_Real_Nokia5110_Scope);
  Nokia5110_Init();
  
	setLED_D();
	splashScreen();
	clear_switches();

	while (!SW1 && !SW2) {}
	
  Timer2_Init(160000000);
	
	init();
	turnX();

	while(1)
  {

		while (ok)
		{
			if(SW1 && !SW2)
      { 
				init();
				enable_timer2();
				turnX();
			}
			else if(SW2 && !SW1)
      {      
				end_game();
				return 0;
			}	
			
		}	

  	if(SW2 && !SW1)
    { 
			clear_switches();
			move();
			select_turn();
		}
		else if(SW1 && !SW2)
    { 
			clear_switches();
			reset_timer2();

			time = 1;
			
      if(update())
      {
				disable_timer2();
				Delay100ms(20);
				menu();
				clear_switches();
				ok = 1;
			}
			else 
			{
				select_turn();
			}
		}
  }
}	

void select_turn(void) 
{
	if(turn) turnO();
	else turnX();	
}

void clear_switches(void)
{
	SW1 = 0;
	SW2 = 0;
}

void init(void) 
{
	int i, j;

  for (i = 0; i < 3; i++) 
  {
		for (j = 0; j < 3; j++)
		{
      arr[i][j] = 0;
		}
	}

	pos = 0;
	turn = 0;
	SW1 = 0;
	SW2 = 0;
	ok = 0;
	time = 1;
	arr[0][0] = 3;
}
