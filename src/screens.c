#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/Nokia5110.h"
#include "..\\./headers/timers.h"
#include "..\\./headers/shapes.h"
#include "..\\./headers/leds.h"
#include "..\\./headers/screens.h"

extern int arr[3][3];

#define SQUAREHEIGHT     ((unsigned char)square[22])
#define VH               ((unsigned char)VLine[22])

/* 
  0 empty  
  1 x   
  2 y 
  3 selected
*/
void startGame(void)
{
  int i, j, dim = 10, outerY = 2, outerX = 1;
	
  Nokia5110_ClearBuffer(); 
	 
  for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			unsigned char*tmp;
			
      if(arr[i][j] == 0) tmp = square;
			else if(arr[i][j] == 1) tmp = X;
			else if(arr[i][j] == 2) tmp = O;
			else if(arr[i][j] == 3)	tmp = Select;
				
			Nokia5110_PrintBMP(j * SQUAREHEIGHT + outerX, (SQUAREHEIGHT - 1) + (dim * i) + outerY, tmp, 0);
			Nokia5110_DisplayBuffer();
			
      outerX += 1;
		}
		outerX = 1;
		outerY += 5;
	}
}

void turnO(void)
{
	startGame();
  
	setLED_O();
	
  Nokia5110_PrintBMP(3 * SQUAREHEIGHT  + 9, (VH - 1), VLine, 0);
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(8, 2);	
	Nokia5110_OutString("(O)");
	
  printTime();
}

void turnX(void)
{
	startGame();

	setLED_X();
	
  Nokia5110_PrintBMP(3 * SQUAREHEIGHT  + 9, (VH - 1), VLine, 0);
  Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(8, 2);	
	Nokia5110_OutString("(X)");

	printTime();
}

void splashScreen(void)
{
	Nokia5110_PrintBMP(0, 47, xo, 0);
	Nokia5110_DisplayBuffer();
}

void draw(void) 
{
	setLED_D();
	Nokia5110_PrintBMP(0, 47, Draw, 0);
  Nokia5110_DisplayBuffer();
}

void winner_x(void) 
{
  setLED_X();
  Nokia5110_PrintBMP(0, 47, Winner_x, 0);
  Nokia5110_DisplayBuffer();
}

void winner_o(void) 
{
	setLED_O();
	Nokia5110_PrintBMP(0, 47, Winner_o, 0);
  Nokia5110_DisplayBuffer();
}

void end_game(void) 
{
	clearLEDS();			
	
  Nokia5110_Clear();
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("t3ala kol youm");
}

void menu(void) 
{
	setLED_D();		
	
  Nokia5110_Clear();
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("SW1 to play again");
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString("SW2 To end");
}
