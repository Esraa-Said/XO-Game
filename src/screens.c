// Including necessary header files
#include "..\./headers/tm4c123gh6pm.h"
#include "..\./headers/Nokia5110.h"
#include "..\./headers/timers.h"
#include "..\./headers/shapes.h"
#include "..\./headers/leds.h"
#include "..\./headers/screens.h"

// Declaring external integer array of size 3x3
extern int arr[3][3];
extern int time, turn;

// Defining macros for square height, vertical line height, and playAgain screen height
#define SQUAREHEIGHT     ((unsigned char)square[22])
#define VH               ((unsigned char)VLine[22])
#define playAgainH       ((unsigned char)playAgain[22])
#define EXITH ((unsigned char)exit[22])
#define TURNXOBOXH ((unsigned char)turnxbox[22])
#define TURNTIMERBOXH ((unsigned char)t1[22])
#define XOH ((unsigned char)xo[22])

/*
  0 empty
  1 x
  2 y
  3 selected
*/

// Function to start the game
void startGame(void)
{
  // Initializing variables
  int i, j, dim = 10, outerY = 2, outerX = 1, b = 8;

  // Clearning Nokia5110 buffer
  Nokia5110_ClearBuffer();

  // Nested loop to iterate over all elements of array arr
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      unsigned char*tmp;

      // Checking value at current index of array arr
      if(arr[i][j] == 0) tmp = square;
      else if(arr[i][j] == 1) tmp = X;
      else if(arr[i][j] == 2) tmp = O;
      else if(arr[i][j] == 3)	tmp = Select;
          
      // Displaying the corresponding shape at the correct position on Nokia5110 screen
      Nokia5110_PrintBMP(j * SQUAREHEIGHT + outerX + b + TURNXOBOXH, (SQUAREHEIGHT - 1) + (dim * i) + outerY, tmp, 0);
      Nokia5110_DisplayBuffer();
        
      // Updating X-coordinate for the next shape to be displayed in the same row
      outerX += 1;
    }
    
    // Resetting X-coordinate and updating Y-coordinate for the next row of shapes to be displayed
    outerX = 1;
    outerY += 5;
  }
}

// Function to display O's turn on Nokia5110 screen
void turnO(void)
{
  startGame();

  // set LED for O
  setLED_O();

  // Displaying vertical line separator between game board and player information
  Nokia5110_PrintBMP(3 * SQUAREHEIGHT + 6, VH, VLine, 0);
  Nokia5110_DisplayBuffer();

  // Displaying "PLAY" and "O" at the correct positions on Nokia5110 screen
 Nokia5110_PrintBMP(0, TURNXOBOXH - 1, turnobox, 0);
	Nokia5110_DisplayBuffer();

  // Printing time elapsed since starting the game
  printTime();
}

// Function to display X's turn on Nokia5110 screen
void turnX(void)
{
  startGame();

  // set LED for X
  setLED_X();
  
  // Displaying vertical line separator between game board and player information
  Nokia5110_PrintBMP(3 * SQUAREHEIGHT + 6, VH, VLine, 0);
  Nokia5110_DisplayBuffer();

  // Displaying "PLAY" and "X" at the correct positions on Nokia5110 screen
	Nokia5110_PrintBMP(0, TURNXOBOXH - 1, turnxbox, 0);
	Nokia5110_DisplayBuffer();


  // Printing time elapsed since starting the game
  printTime();
}

// Function to display splash screen on Nokia5110 screen
void splashScreen(void)
{
	Nokia5110_PrintBMP(0, 47, xo, 0);
	Nokia5110_DisplayBuffer();
}

// Function to display draw on Nokia5110 screen
void draw(void) 
{
  // set LED for D (Draw)
	setLED_D();

  // Displaying the draw image
	Nokia5110_PrintBMP(0, 47, Draw, 0);
  Nokia5110_DisplayBuffer();
}

// Function to display winner X on Nokia5110 screen
void winner_x(void) 
{
  // set LED for X
  setLED_X();

  // Displaying the winner
  Nokia5110_PrintBMP(0, 47, Winner_x, 0);
  Nokia5110_DisplayBuffer();
}

// Function to display winner O on Nokia5110 screen
void winner_o(void) 
{
  // set LED for O
	setLED_O();

  // Displaying the winner
	Nokia5110_PrintBMP(0, 47, Winner_o, 0);
  Nokia5110_DisplayBuffer();
}

// Function to end the game
void end_game(void)
{
  // clear all LEDs
  clearLEDS();

  // Clearing Nokia5110 screen and displaying "XO GAME" at the correct position
  Nokia5110_Clear();
Nokia5110_PrintBMP(0, EXITH - 1,exit , 0);
Nokia5110_DisplayBuffer();
}

// Function to display play again option on Nokia5110 screen
void play_again(void)
{
  // set LED for D (Draw)
  setLED_D();

  // Clearing Nokia5110 screen and displaying  play again option
  Nokia5110_ClearBuffer();
  Nokia5110_PrintBMP(0, playAgainH - 1, playAgain, 0);
  Nokia5110_DisplayBuffer();
}


void printTime(void)
{

  if (time == 1)
    Nokia5110_PrintBMP(84 - TURNTIMERBOXH, TURNTIMERBOXH - 1, t1, 0);

  else if (time == 2)
    Nokia5110_PrintBMP(84 - TURNTIMERBOXH, TURNTIMERBOXH - 1, t2, 0);

  else if (time == 3)
    Nokia5110_PrintBMP(84 - TURNTIMERBOXH, TURNTIMERBOXH - 1, t3, 0);
  else if (time == 4)
    Nokia5110_PrintBMP(84 - TURNTIMERBOXH, TURNTIMERBOXH - 1, t4, 0);
  else if (time == 5)
    Nokia5110_PrintBMP(84 - TURNTIMERBOXH, TURNTIMERBOXH - 1, t5, 0);
}

