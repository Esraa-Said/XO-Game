// Including necessary header files
#include "..\./headers/tm4c123gh6pm.h"
#include "..\./headers/Nokia5110.h"
#include "..\./headers/timers.h"
#include "..\./headers/shapes.h"
#include "..\./headers/leds.h"
#include "..\./headers/screens.h"

// Declaring external integer array of size 3x3
extern int arr[3][3];

// Defining macros for square height and vertical line height
#define SQUAREHEIGHT     ((unsigned char)square[22])
#define VH               ((unsigned char)VLine[22])
#define playAgainH ((unsigned char)playAgain[22])
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
  int i, j, dim = 10, outerY = 2, outerX = 1;

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
      Nokia5110_PrintBMP(j * SQUAREHEIGHT + outerX, (SQUAREHEIGHT - 1) + (dim * i) + outerY, tmp, 0);
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
  Nokia5110_SetCursor(8, 1);	
  Nokia5110_OutString("PLAY");
  Nokia5110_SetCursor(9, 3);	
  Nokia5110_OutString("O");

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
  Nokia5110_SetCursor(8, 1);	
  Nokia5110_OutString("PLAY");
  Nokia5110_SetCursor(9, 3);	
  Nokia5110_OutString("X");

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
  Nokia5110_SetCursor(2, 2);
  Nokia5110_OutString("XO GAME");
}

// Function to display menu options on Nokia5110 screen
void menu(void)
{
  // set LED for D (Draw)
  setLED_D();

  // Clearing Nokia5110 screen and displaying menu options at the correct positions
Nokia5110_ClearBuffer();
Nokia5110_PrintBMP(0, playAgainH - 1,playAgain , 0);
Nokia5110_DisplayBuffer();


}
