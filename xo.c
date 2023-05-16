
#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "timers.h"
#include "ports.h"
#include "TExaS.h"
#include "shapes.h"
//extern const unsigned char SelectX[], SelectO[], O[], X[] , square[], selectedSquare[] , Select[];
int arr[3][3]={0,0,0,0,0,0,0, 0, 0};
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long count); // time delay in 0.1 seconds
int pos;


// check winner  0  draw   1 x     2  o   3 no action
// *************************** Images ***************************
// enemy ship that starts at the top of the screen (arms/mouth closed)
// width=16 x height=10



void splashScreen(void);
void game_over(void);
void winner_x(void);
void winner_o(void);

// 2. Declarations Section
//   Global Variables
unsigned long SW1,SW2;  // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)

//   Function Prototypes
void PortF_Init(void);
void EnableInterrupts(void);


void startGame(void);
void turnO(void);
void turnX(void);
void move(void);
int update(void);
void getFirst(void);
int checkWinner(void);
int turn = 0; // x = 0 , o = 1
// *************************** Capture image dimensions out of BMP**********


#define SQUAREHEIGHT     ((unsigned char)square[22])
#define VH               ((unsigned char)VLine[22])


int main(void){
  
	int ok = 0;
	
	PortF_Init();        // Call initialization of port PF4, PF3, PF2, PF1, PF0    
  EnableInterrupts();  // The grader uses interrupts
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Nokia5110_Init();
  //Timer0_Init(160000000);//1 sec timer
  //Timer2_Init(160000000);//1 sec timer
	
	splashScreen();
	Delay100ms(5);
	
	pos=0;
	turn=0;
	//arr[0][0]=3;
	turnX();
	
	
	while(1){

		if (ok)break;
		
		 SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
    SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2
	
    if((!SW2) && SW1){                // just SW2 pressed
				move();
			if(turn)turnX();
			else turnO();
		}
		else if((!SW1) && SW2){              // just SW1 pressed
				if(update())break;
			 if(turn)turnO();
			else turnX();
		
		}

	 
	 
 }



	


}

// void Timer2A_Handler(void){ 
//   TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
// 	GPIO_PORTF_DATA_R^=0x04;
	
// 	Nokia5110_ClearBuffer();
// 	Nokia5110_DisplayBuffer();      // draw buffer
// 	//Nokia5110_PrintBMP(f, 19, Bunker0, 0);
// 	//Nokia5110_PrintBMP(f, 23, mm, 0); // player ship middle bottom
// 	Nokia5110_PrintBMP(f, 23, mmm, 0);
// 	Nokia5110_DisplayBuffer();     // draw buffer
// 	if(f<64)f++;
	
// }

// void Timer0A_Handler(void){
//   TIMER0_ICR_R = 0x00000001;   // acknowledge timer2A timeout
// 	GPIO_PORTF_DATA_R^=0x02;
// }

void turnO(void)
{
		startGame();
	Nokia5110_PrintBMP(3 * SQUAREHEIGHT  + 9, (VH - 1), VLine, 0);
	Nokia5110_DisplayBuffer();
	 Nokia5110_SetCursor(8, 2);	
	 Nokia5110_OutString("(O)");
	 Nokia5110_SetCursor(8, 4);	
	 Nokia5110_OutString("Turn");
}

void turnX(void)
{
	
	startGame();

	 Nokia5110_PrintBMP(3 * SQUAREHEIGHT  + 9, (VH - 1), VLine, 0);
	 Nokia5110_DisplayBuffer();
	
	 Nokia5110_SetCursor(8, 2);	
	 Nokia5110_OutString("(X)");
	 Nokia5110_SetCursor(8, 4);	
	 Nokia5110_OutString("Turn");
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

void startGame(void)
{
	//0 empty
	//1 x
	//2 y 
	//3 selected
	int i,j,dim = 10,outerY=2,outerX=1;
	Nokia5110_ClearBuffer(); 
	for(i=0;i<3;i++)
	{
			for(j=0;j<3;j++)
		{
			unsigned char*tmp;
			if(arr[i][j]==0)
				tmp = square;
			else if(arr[i][j]==1)
					tmp = X;
			else if(arr[i][j]==2)
				tmp = O;
			else if(arr[i][j]==3)
				tmp = Select;
				
			
			Nokia5110_PrintBMP(j*SQUAREHEIGHT + outerX, (SQUAREHEIGHT - 1) + (dim*i) + outerY, tmp, 0);
			Nokia5110_DisplayBuffer();
			outerX += 1;
		}
		outerX = 1;
		outerY += 5;
	}
	
	
}

void getFirst()
{
	//if()
	pos = 0;
	while(arr[pos/3][pos%3]) pos = (pos+1)%9;
	arr[pos/3][pos%3] = 3;
	return;
}

void move(){
		arr[pos/3][pos%3] = 0;
		pos = (pos + 1) % 9;
		while(arr[pos/3][pos%3]) pos = (pos+1)%9;
		arr[pos/3][pos%3] = 3;
}

int update(){
			int w;
		if(turn==0){
			arr[pos/3][pos%3] = 1;
		}else arr[pos/3][pos%3] = 2;
		
		w = checkWinner();

		if(w==1)
		{
			GPIO_PORTF_DATA_R=0x04; 
			winner_x();
		}
		else if(w==2)
		{
			GPIO_PORTF_DATA_R=0x08; 
			winner_o();
		}
		else if(w==3)
		{
				GPIO_PORTF_DATA_R=0x0F; 
				game_over();
		}
		
		if (w != 0)return 1;
		
		getFirst();
		turn^=1;
		return 0;
		
}

int checkWinner ()
{
	int i,j, x=0,o=0,d=0,xd=0,od=0,rdo = 0,rdx=0,xc=0, oc=0;
		
	for (i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			
			if(arr[i][j]==1)
			{
				if(i==j )
					xd++;
				if(2-i==j)
					rdx++;
				 
					x++;
					
				d++;
			
			}
			else if(arr[i][j]==2)
			{
				if(i==j )
					od++;
				
				 if(2-i==j)
					rdo++;
					o++;
				 d++;
			}

		if(arr[j][i] == 1) {
			xc++;
		}
		else if(arr[j][i] == 2) {
			oc++;
		}
				
		}
		if(x==3 || xc == 3)
			return 1;
		else if(o==3 || oc == 3)
			return 2;
		x=0,o=0,xc=0,oc=0;
		
	}
	
	if(xd==3||rdx==3)
		return 1;
if(od==3||rdo==3)
	return 2;
	
if(d==9)return 3;
	return 0;
}
void splashScreen()
{
  Nokia5110_Clear();
  Nokia5110_SetCursor(2, 2);
  Nokia5110_OutString("XO GAME");
}

void game_over() {
	Nokia5110_Clear();
  Nokia5110_SetCursor(2, 2);
  Nokia5110_OutString("DRAW");
}

void winner_x() {
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("THE WINNER");
  Nokia5110_SetCursor(4, 3);
  Nokia5110_OutString("( X )");
}

void winner_o() {
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("THE WINNER");
  Nokia5110_SetCursor(4, 3);
  Nokia5110_OutString("( O )");
}
