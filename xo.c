#include "./headers/Nokia5110.h"
#include "./headers/TExaS.h"
#include "./headers/timers.h"
#include "./headers/ports.h"
#include "./headers/screens.h"
#include "./headers/operations.h"
#include "./headers/leds.h"
#include "./headers/xo.h"

//extern const unsigned char SelectX[], SelectO[], O[], X[] , square[], selectedSquare[] , Select[];
int arr[3][3]={0,0,0,0,0,0,0, 0, 0};

int pos, time = 1;

// check winner  0  draw   1 x     2  o   3 no action
// *************************** Images ***************************
// enemy ship that starts at the top of the screen (arms/mouth closed)
// width=16 x height=10



// 2. Declarations Section
//   Global Variables
unsigned long SW1,SW2;  // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)



int turn = 0; // x = 0 , o = 1
// *************************** Capture image dimensions out of BMP**********
int ok;



int main(void){
  
	
	PortB_Init();
  EnableInterrupts();  // The grader uses interrupts
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Nokia5110_Init();
  
	setLED_D();
	splashScreen();
	clear_switches();
	while (!SW1 && !SW2){}
	
	//Timer0_Init(5 * 160000000);//1 sec timer
  Timer2_Init(160000000);//1 sec timer
	
	init();
	turnX();
	while(1){

		while (ok)
		{
				if(SW1 && !SW2){                // just SW1 pressed
						init();
						enable_timer2();   // 10) enable timer2A
						turnX();
				}
				else if(SW2 && !SW1){              // just SW2 pressed
					end_game();
					return 0;
				}	
			
			}	
		//SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
    		//SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2
	if(SW2 && !SW1){                // just SW2 pressed
			clear_switches();
			move();
			select_turn();
			//PortB_Init();
			//Delay100ms(2);
		}
		else if(SW1 && !SW2){              // just SW1 pressed
			clear_switches();
			reset_timer2();
		
			time = 1;
			if(update()){
				disable_timer2(); // Clear bit 0 to disable Timer2A
				Delay100ms(20);
				menu();
				clear_switches();
				ok = 1;
			}
			else 
			{
				select_turn();
			}
			//PortB_Init();
			//Delay100ms(2);
			
		}
 }
}	

void select_turn(void) {
	if(turn)turnO();
	else turnX();	
}

void clear_switches(void) {
	SW1 = 0;
	SW2 = 0;
}

void init(void) {
	int i, j;
	pos = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
		{
				arr[i][j] = 0;
		}
	}
	arr[0][0] = 3;
	turn = 0;
	SW1=0;
	SW2=0;
	time = 1;
	ok = 0;
}
