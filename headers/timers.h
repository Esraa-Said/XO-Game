// Function to initialize Timer 2 with a given period
void Timer2_Init(unsigned long period);
// Function to reset the value of Timer 2
void reset_timer2(void);
// Interrupt handler for Timer 2
void Timer2A_Handler(void);
// Function to enable Timer 2
void enable_timer2(void); 
// Function to disable Timer 2
void disable_timer2(void); 

// Function to delay program execution by 100ms * count
void Delay100ms(unsigned long count); 
