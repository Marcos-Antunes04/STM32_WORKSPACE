#include "main.h"

void SysClockConfig();
void GPIO_OUT_Config();
void GPIO_IN_Config();
void Delay(uint32_t time);

int main(void){
	SysClockConfig();
	GPIO_OUT_Config();

	while (1){
		GPIOA->ODR |= (1 << 5);
		Delay(5000000);
		GPIOA->ODR &= ~(1 << 5);
		Delay(5000000);
	}
}



void SysClockConfig(){
	RCC->CR |= (1 << 16); //enables HSE
	while(!(RCC->CR & (1 << 17))); //waits for HSE to become ready
	RCC->APB1ENR |= (1 << 28); //Power enable clock
	PWR->CR |= (3 << 14); //Voltage regulator Scale 1. (DEFAULT)

	//CONFIGURATION OF FLASH ACCESS CONTROL REGISTER
	FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10) | (5 << 0);

	RCC->CFGR &= ~(1<<7);
	RCC->CFGR |= (5<<10);
	RCC->CFGR |= (4<<13);
}

void GPIO_OUT_Config(){
	RCC->AHB1ENR |= (1 << 0); //ENABLES GPIOA CLOCKE
	GPIOA->MODER |= (1 << 10); //SETS PIN PA5 AS GENERAL PORPUSE OUTPUT
	GPIOA->OTYPER &= ~(1 << 5); //SETS PIN PA5 AS A PUSH-PULL GPIO PIN
	GPIOA->OSPEEDR |= (2 << 10); //FAST SPEED FOR PIN PA5
	GPIOA->PUPDR &= ~((1<<10) | (1<<11));
}

void GPIO_IN_Config(){
	RCC->AHB1ENR |= (1 << 0); //ENABLES GPIOA CLOCKE
	GPIOA->MODER &= ~((1 << 10) | (1 << 11)); //SETS PIN PA5 AS INPUT
	GPIOA->OTYPER &= ~(1 << 5); //SETS PIN PA5 AS A PUSH-PULL GPIO PIN
	GPIOA->OSPEEDR |= (2 << 10); //FAST SPEED FOR PIN PA5
	GPIOA->PUPDR |= (1<<10); //ENABLES PULL UP
}

void Delay(uint32_t time){
	//Random delay routine
	while(time--);
}

