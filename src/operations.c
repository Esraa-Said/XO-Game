// Including necessary header files
#include "..\./headers/screens.h"
#include "..\./headers/operations.h"
#include "..\./headers/timers.h"

// Declaring global variables
extern int arr[3][3], pos, turn;

// Function to get the first position can be selected
void getFirst(void)
{
  // Initializing position
  pos = 0;
  // Checking if the current position is already occupied
  // If yes, moving to next position
  while(arr[pos / 3][pos % 3]) pos = (pos + 1) % 9;
  // Assigning the current position to be selected
  arr[pos / 3][pos % 3] = 3;
  return;
}

// Function to make a move
void move(void)
{
  // Removing the previous move from the board
  arr[pos / 3][pos % 3] = 0;
  // Moving to the next empty position on the board
  pos = (pos + 1) % 9;
  while(arr[pos / 3][pos % 3]) pos = (pos + 1) % 9;
  // Assigning the current position to be selected
  arr[pos / 3][pos % 3] = 3;
}

// Function to update the game after each move
int update(void)
{
  int w;

  // If it's player 1's turn, updating the board with player 1's move
  if(turn == 0)
  {
    arr[pos / 3][pos % 3] = 1;
  }
  // If it's player 2's turn, updating the board with player 2's move
  else
  {
    arr[pos / 3][pos % 3] = 2;
  }

  // Checking if there's a winner
  w = checkWinner();

	// if The match is ended
	if(w != 0) 
	{
		startGame(); // Call the function to see how the match ended
		disable_timer2(); // Disable timer 2
		Delay100ms(10); // Wait for 1 second before announcing the result 
	}

  // Displaying the winner or draw message if there's a winner or if it's a draw
  if(w == 1)
  {
    winner_x();
  }
  else if(w == 2)
  {
    winner_o();
  }
  else if(w == 3)
  {
    draw();
  }

  // Returning 1 if there's a winner, else continuing the game
  if (w != 0) return 1;

  // Getting the first place to be selected and updating the turn
  getFirst();
  turn ^= 1;
  return 0;	
}

// Function to check if there's a winner or if it's a draw
int checkWinner(void)
{
  int i, j, x = 0, o = 0, d = 0, xd = 0, od = 0, rdo = 0, rdx = 0, xc = 0, oc = 0;

  // Checking for horizontal and vertical wins
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      if(arr[i][j] == 1)
      {
        if(i == j) xd++;
        if(2 - i == j) rdx++;
        
        x++;	
        d++;
      }
      else if(arr[i][j] == 2)
      {
        if(i == j) od++;
        if(2 - i == j) rdo++;
        
        o++;
        d++;
      }

      if(arr[j][i] == 1) xc++;
      else if(arr[j][i] == 2) oc++;
  }

    if(x == 3 || xc == 3) return 1;
    else if(o == 3 || oc == 3) return 2;
    
    x = 0, o = 0, xc = 0, oc = 0;
  }

  // Checking for diagonal wins
  if(xd == 3 || rdx == 3) return 1;
  if(od == 3 || rdo == 3) return 2;

  // Checking if it's a draw
  if(d == 9) return 3;

  return 0;
}
