#include "main.h"


void SysClockConfig(void);
void TimerConfig(void);


int main(void){
	SysClockConfig();
	TimerConfig();


	while(1){

	}

	return 0;
}


void TimerConfig(void){
	RCC->APB2ENR |= (1<<0); // Enables timer0
	RCC->CFGR |= (3<<21); // PLL CLOCK SELECTED AS MCO1
	RCC->CFGR |= (0<<24); // MCO1 PRESCALER DIVIDES BY 0
	// MCO1 pin (PA8)
	RCC->AHB1ENR |= (1<<0); // ENABLES GPIOA BUS CLOCK
	GPIOA->OSPEEDR |= (3<<16); //High speed output
	GPIOA->PUPDR |= (1<<16);
	GPIOA->MODER |= (2<<16); // SETS PIN PA8 AS ALTERNATE FUNCTION MODE
	GPIOA->AFR[1] &= ~(0X0F); // PIN PA8 STARTS OPERATING AT AF0 -> SYSTEM ALTERNATE FUNCTION MODE


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
	RCC->CFGR |= 0x00001400U; //APB1 Divided by 4 -> 42MHz
	//APB2 PRESCALER
	RCC->CFGR |= 0x00008000U; //APB2 Divided by 2 -> 84MHz

	//CONFIGURE THE MAIN PLL
	RCC->PLLCFGR = (4 <<0) | (168 << 6) | (0 <<16) | (1<<22);

	//Enable the PLL and wait for it to become ready
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));

	//Select the Clock Source and wait for it to be set
	RCC->CFGR |= 0x02;
	while ((RCC->CFGR & (3<<2)) != 0x08);

}
