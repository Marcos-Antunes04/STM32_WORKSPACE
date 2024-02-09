#include "main.h"

void PA0_CFG(void);
void SysClockConfig(void);
void delay(uint32_t time);

int flag = 0;
int count = 0;

int main(void){
	SysClockConfig();
	PA0_CFG();

	while(1){
		if(flag){
			delay(100000);
			count++;
			flag=0;
		}
	}

	return 0;
}


void EXTI0_IRQHandler(void){
	/*
		-> CHECK THE PIN, WHICH TRIGGERED THE INTERRUPT
		-> CLEAR THE INTERRUPT PENDING BIT
	*/

	if (EXTI->PR & (1<<0)){ // Checking if the interrupt was triggered by NVIC LINE 0
		EXTI->PR &= (1<<0); //Cleaning the interrupt pending bit
		flag = 1;
	}


}

void PA0_CFG(void){
	RCC->AHB1ENR |= (1<<0); //ENABLES GPIOA

	GPIOA->MODER &= ~(3<<0); //PIN A0 AS INPUT
	GPIOA->PUPDR |= (1<<1);  //ENABLES PULLUPS

	RCC->APB2ENR |= (1<<14); //System configuration clock enabled
	SYSCFG->EXTICR[0] &= ~(0x0F<<0);

	EXTI->FTSR |= (1<<0);  // FALLING EDGE TRIGGER ENABLED
	EXTI->RTSR &= ~(1<<0); // RISING EDGE TRIGGER DISABLED
	EXTI->IMR |= (1<<0);   // DISABLES MASK ON EXTI1

	NVIC_SetPriority(EXTI0_IRQn,1);
	NVIC_EnableIRQ(EXTI0_IRQn);


	//EXTI->PR = (1<<0);

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
	RCC->PLLCFGR = (4 <<0) | (180 << 6) | (0 <<16) | (1<<22);

	//Enable the PLL and wait for it to become ready
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));

	//Select the Clock Source and wait for it to be set
	RCC->CFGR |= 0x02;
	while ((RCC->CFGR & (3<<2)) != 0x08);

}

void delay(uint32_t time){
	while(time--);
}

