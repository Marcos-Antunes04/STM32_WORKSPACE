#include "main.h"

void SysClockConfig(void);
void GPIOA_Init(void);
void USART2_Init(void);
void USART2_SendChar(uint8_t c);
uint8_t UART2_GetChar(void);
void delay(uint32_t time);
void USART2_SendString(char *string);

uint8_t buffer[30];
int indx = 0;
int main(void){
	SysClockConfig();
	GPIOA_Init();
	USART2_Init();
	while(1){
		delay(4000000);
		USART2_SendString("Hello world");
		delay(4000000);
	}
	return 0;
}


void USART2_Init(void){
	RCC->APB1ENR |= (1<<17);
	USART2->CR1 |= 0x00;	// Clear all
	USART2->CR1 |= (1<<13); // USART enabled
	USART2->CR1 |= (0<<12); // Word length: 1 start bit, 8 data bits, n stop bit (default)
	USART2->BRR = ((13<<0) | (22<<4)); // APB1 Clock frequency of 42MHz
	USART2->CR1 |= (1<<2);  // Receiver enabled
	USART2->CR1 |= (1<<3);  // Transmitter enabled

}

void USART2_SendChar(uint8_t c){
	USART2->DR = c;
	while(!(USART2->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}

uint8_t UART2_GetChar(void){
	uint8_t Temp;
	while (!(USART2->SR & (1<<5)));  // Wait for RXNE to SET.. This indicates that the data has been Received
	Temp = USART2->DR;  // Read the data.
	return Temp;
}

void GPIOA_Init(void){
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (2<<4);   // Alternate function for pin PA2
	GPIOA->MODER |= (2<<6);   // Alternate function for pin PA3
	GPIOA->AFR[0] |= (7<<8);  // AF7 -> PA2
	GPIOA->AFR[0] |= (7<<12); // AF7 -> PA3
}

void USART2_SendString(char *string){
	while (*string) USART2_SendChar (*string++);
}

void SysClockConfig(void){
	RCC->CR |= (1 << 16); //HSE on
	while(!(RCC->CR & (1<<17)));//Wait for HSE clock ready flag

	RCC->APB1ENR |= (1<<28);
	PWR->CR |= (1<<14);

	FLASH->ACR = (1<<9) | (1<<10) | (1<<8) | 0X05;

	//AHB PRESCALER
	RCC->CFGR |= 0X00;
	//APB1 PRESCALER
	RCC->CFGR |= 0x00001400U;
	//APB2 PRESCALER
	RCC->CFGR |= 0x00008000U;

	//CONFIGURE THE MAIN PLL
	RCC->PLLCFGR = (4 <<0) | (168 << 6) | (0 <<16) | (1<<22);

	//Enable the PLL and wait for it to become ready
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));

	//Select the Clock Source and wait for it to be set
	RCC->CFGR |= 0x02;
	while ((RCC->CFGR & (3<<2)) != 0x08);

}

void delay(uint32_t time){
	while (time--);
}
