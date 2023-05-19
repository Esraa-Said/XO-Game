// Including necessary header files
#include "./headers/Nokia5110.h"
#include "./headers/TExaS.h"
#include "./headers/timers.h"
#include "./headers/ports.h"
#include "./headers/screens.h"
#include "./headers/operations.h"
#include "./headers/leds.h"
#include "./headers/xo.h"

// Initializing the game board as a 2D array of integers
int arr[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

// Initializing variables used in the game
int pos, time = 1, turn = 0, ok = 0;
unsigned long SW1, SW2;

int main(void)
{	
  // Initializing necessary hardware and software components for the game to function
	PortB_Init();
  EnableInterrupts();
	TExaS_Init(SSI0_Real_Nokia5110_Scope);
  Nokia5110_Init();
	
	// Setting up LED display and displaying splash screen 
	setLED_D();
	splashScreen();
		
	// Clearing any switch inputs
	clear_switches();

	// Waiting for either SW1 or SW2 to be pressed to start the game
	while (!SW1 && !SW2) {}

	// Initializing Timer2 with a frequency of 160000000 Hz
  Timer2_Init(160000000);

	// Setting up initial game state and starting with X's turn
	init();
	turnX();

	while(1)
  {
		// If the game has ended, wait for a button press to restart the game or quit
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
			// If SW2 is pressed, indicating a move selection, clear the switches and make a move
			clear_switches();
			move();
			select_turn();
		}
		else if(SW1 && !SW2)
    { 
			// If SW1 is pressed, indicating a turn change or timer expiration, perform necessary actions
			clear_switches();
			reset_timer2();

			time = 1;

			// If a player has won or the game has tied, display the play again option and set ok to true to wait for restart or quit
      if(update())
      {
				disable_timer2();
				Delay100ms(20);
				play_again();
				clear_switches();
				ok = 1;
			}

			// If the game is still ongoing, switch turns
			else 
			{
				select_turn();
			}
		}
  }
}	

// Function to switch turns between X and O
void select_turn(void) 
{
	if(turn) turnO();
	else turnX();	
}

// Function to clear any switch inputs
void clear_switches(void)
{
	SW1 = 0;
	SW2 = 0;
}

// Function to initialize game state
void init(void) 
{
	int i, j;

	// Initializing every element in the game board array as 0
  for (i = 0; i < 3; i++) 
  {
		for (j = 0; j < 3; j++)
		{
      arr[i][j] = 0;
		}
	}

	// Setting initial position, turn, and switch values
	pos = 0;
	turn = 0;
	SW1 = 0;
	SW2 = 0;
	ok = 0;
	time = 1;

	// Setting the center element of the board as 3 to indicate it is unavailable for moves
	arr[0][0] = 3;
}
