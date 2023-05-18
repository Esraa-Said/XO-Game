
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
void printTime(void);

void reset_timer2(void);
void reset_timer0(void);

int pos, time = 1;

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
	
	PortB_Init();
	PortF_Init();        // Call initialization of port PF4, PF3, PF2, PF1, PF0    
  EnableInterrupts();  // The grader uses interrupts
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Nokia5110_Init();
  
	GPIO_PORTB_DATA_R |= 0x80;
	splashScreen();
	Delay100ms(20);
	
	GPIO_PORTB_DATA_R &= ~(0x80);
	
	//Timer0_Init(5 * 160000000);//1 sec timer
  Timer2_Init(160000000);//1 sec timer
	
	pos=0;
	turn=0;
	arr[0][0]=3;
	turnX();
	SW1=0;
	SW2=0;
	while(1){

		while (ok)
		{
			int i, j;
			
			
			//ok = 0;
			
				
				
			
				if(SW1 && !SW2){                // just SW1 pressed
						pos = 0;
						for ( i = 0; i < 3; i++) {
							for (j = 0; j < 3; j++)
							{
									arr[i][j] = 0;
							}
						}
						arr[0][0] = 3;
						turn = 0;
						SW1=0;
						SW2=0;
						TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
						time = 1;
						ok = 0;
						GPIO_PORTB_DATA_R &= ~(0x80);
						turnX();
				}
				else if(SW2 && !SW1){              // just SW2 pressed
					Nokia5110_Clear();
					GPIO_PORTB_DATA_R &= ~(0x80);			
					Nokia5110_SetCursor(1, 1);
					Nokia5110_OutString("t3ala kol youm");
					return 0;
				}	
			
			}	
		//SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
    		//SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2
	if(SW2 && !SW1){                // just SW2 pressed
			SW1 = 0;
			SW2 = 0;
			move();
			if(turn)turnO();
			else turnX();
			//PortB_Init();
			//Delay100ms(2);
		}
		else if(SW1 && !SW2){              // just SW1 pressed
			SW1 = 0;
			SW2 = 0;
			//Timer0_Init(5 * 160000000);//1 sec timer
			//Timer2_Init(160000000);//1 sec timer
			reset_timer2();
		
			/*GPIO_PORTB_DATA_R |= 0x40; 
			Delay100ms(2);
			GPIO_PORTB_DATA_R &= ~(0x40);*/
			//reset_timer0();
			//Delay100ms(5);
			time = 1;
			if(update()){
				TIMER2_CTL_R &= ~(1 << 0); // Clear bit 0 to disable Timer2A
				Delay100ms(20);
				Nokia5110_Clear();
				GPIO_PORTB_DATA_R &= ~(0x08);
				GPIO_PORTB_DATA_R &= ~(0x04);
				GPIO_PORTB_DATA_R |= 0x80;				
				Nokia5110_SetCursor(1, 1);
				Nokia5110_OutString("SW1 to play again");
				Nokia5110_SetCursor(1, 4);
				Nokia5110_OutString("SW2 To end");
				SW1 = 0;
				SW2 = 0;
				ok = 1;
			}
			else 
			{
				if(turn)turnO();
				else turnX();	
			}
			//PortB_Init();
			//Delay100ms(2);
			
		}
 }
}	

void GPIOPortB_Handler(void){
	
		if (GPIO_PORTB_MIS_R & 0x10) /* is it SW1 (PB4)?*/
    {                             
      if (GPIO_PORTB_DATA_R & 0x10)
      {
				Delay100ms(2);
				SW1 = 1;
				SW2 = 0;
        GPIO_PORTB_ICR_R |= 0x10;
				//GPIO_PORTB_DATA_R &= ~0x10; // clear PB4 data
				      //Delay100ms(2);

			}
    }
    else if (GPIO_PORTB_MIS_R & 0x01) /* then it must be SW2 (PB0) */
    {                                
      if (GPIO_PORTB_DATA_R & 0x01)
      {
				Delay100ms(2);
				SW1 = 0;
				SW2 = 1;
        GPIO_PORTB_ICR_R |= 0x01;
				//GPIO_PORTB_DATA_R &= ~0x01; // clear PB4 data
				      //Delay100ms(2);

			}
    }
		
}


void GPIOF_Handler(void)
{
  while (GPIO_PORTF_MIS_R != 0)
  {
    if (GPIO_PORTF_MIS_R & 0x10) /* is it SW1 (PF4)?*/
    {                            /* GPIOF4 pin interrupt */
      /* turn ON green LED (PD3) */
      Delay100ms(2);
      SW1=1;
				SW2=0;
			if (!(GPIO_PORTF_DATA_R & 0x10))
      {
        SW1=1;
				SW2=0;
        GPIO_PORTF_ICR_R |= 0x10;
      }
    }
    else if (GPIO_PORTF_MIS_R & 0x01) /* then it must be SW2 (PF0) */
    {                                 /* GPIOF0 pin interrupt */
      /* turn ON blue LED (PD3) */
      Delay100ms(2);
      if (!(GPIO_PORTF_DATA_R & 0x01))
      {
        //Sw2Flag = 1;
        GPIO_PORTF_ICR_R |= 0x01;
      }
    }
    else
    { /* We should never get here */
      /* But if we do, clear all pending interrupts */
      GPIO_PORTF_ICR_R = GPIO_PORTF_MIS_R;
    }
  }
}


void Timer2A_Handler(void){ 
   TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
 	GPIO_PORTF_DATA_R^=0x04;
	time++;
	if (time == 6)
	{
		SW1 = 1;
		SW2 = 0;
		return;
	}
	if (turn)turnO();
	else turnX();
}

void reset_timer2(void)
{
	//TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
 	//GPIO_PORTF_DATA_R^=0x04;
	TIMER2_TAV_R = 0;           // reset Timer 2A
}

void reset_timer0(void)
{
	//TIMER0_ICR_R = 0x00000001;   // acknowledge timer2A timeout
 	//GPIO_PORTF_DATA_R^=0x02;
	TIMER0_TAV_R = 0;           // reset Timer 2A
}


void Timer0A_Handler(void){
	TIMER0_ICR_R = 0x00000001;   // acknowledge timer2A timeout
	GPIO_PORTF_DATA_R^=0x02;
	turn = 1 - turn;
	time = 0; 
	//if (turn)turnO();
	//else turnX();
	//SW1=0;
}

void turnO(void)
{
		startGame();
	GPIO_PORTB_DATA_R &= ~(0x04);
	GPIO_PORTB_DATA_R |= 0x08;  
	Nokia5110_PrintBMP(3 * SQUAREHEIGHT  + 9, (VH - 1), VLine, 0);
	Nokia5110_DisplayBuffer();
	 Nokia5110_SetCursor(8, 2);	
	 Nokia5110_OutString("(O)");
	 //Nokia5110_SetCursor(8, 4);	
	 //Nokia5110_OutString("Turn");'
	printTime();
}

void turnX(void)
{
	
	startGame();
	GPIO_PORTB_DATA_R &= ~(0x08);
	GPIO_PORTB_DATA_R |= 0x04;  
	 Nokia5110_PrintBMP(3 * SQUAREHEIGHT  + 9, (VH - 1), VLine, 0);
	 Nokia5110_DisplayBuffer();
	
	 Nokia5110_SetCursor(8, 2);	
	 Nokia5110_OutString("(X)");
	 //Nokia5110_SetCursor(8, 4);	
	 //Nokia5110_OutString("Turn");
	printTime();
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

		if (w != 0)
		{
			startGame();
			//Delay100ms(2);
		}
		
		if(w==1)
		{
			//GPIO_PORTF_DATA_R=0x04; 
			winner_x();
		}
		else if(w==2)
		{
			//GPIO_PORTF_DATA_R = 0x08; 
			winner_o();
		}
		else if(w==3)
		{
				//GPIO_PORTF_DATA_R=0x0F; 
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
	GPIO_PORTB_DATA_R |= 0x80;
	GPIO_PORTB_DATA_R &= ~(0x04);
	GPIO_PORTB_DATA_R &= ~(0x08); 
  Nokia5110_SetCursor(2, 2);
  Nokia5110_OutString("DRAW");
}

void winner_x() {
	Nokia5110_Clear();
	GPIO_PORTB_DATA_R &= ~(0x08);
	GPIO_PORTB_DATA_R |= 0x04;  
	GPIO_PORTB_DATA_R &= ~(0x80); 
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("THE WINNER");
  Nokia5110_SetCursor(4, 3);
  Nokia5110_OutString("( X )");
}

void winner_o() {
	Nokia5110_Clear();
	GPIO_PORTB_DATA_R &= ~(0x04);
	GPIO_PORTB_DATA_R |= 0x08; 
	GPIO_PORTB_DATA_R &= ~(0x80); 
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("THE WINNER");
  Nokia5110_SetCursor(4, 3);
  Nokia5110_OutString("( O )");
}
