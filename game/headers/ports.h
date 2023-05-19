// Function to initialize Port B of the MCU
void PortB_Init(void);
// Interrupt handler for Port B
void GPIOPortB_Handler(void);
// Enable interrupts
void EnableInterrupts(void);
// Wait for interrupts
void WaitForInterrupt(void);
