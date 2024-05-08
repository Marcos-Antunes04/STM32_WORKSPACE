#include "main.h"

void SysClockConfig(void);
void SPIConfig(void);
void SPITransmit(uint8_t *data, size);


int main(void){
	SysClockConfig();

	while(1){

	}
	return 0;
}

void SPIConfig(void){
	RCC->AHB2ENR |= (1<<12); 			// ENABLE SPI CLOCK
	SPI1->CR1 |= (3<<0); 	 			// CPOL = 1, CPHA = 1
	SPI1->CR1 |= (1<<2);	 			// MASTER MODE
	SPI1->CR1 |= (3<<3);	 			// fpclk/16, PLCK2 = 80MHz, SPI clock = 5MHZz
	SPI1->CR1 |= (1<<8) | (1<<9);		// SSM=1, SSi=1 -> Software Slave Managemen
	SPI1->CR1 &= ~(1<<10);   			// RXONLY = 0, full-duplex
	SPI1->CR1 &= ~(1<<11);   			// DFF=0, 8 bit data
	SPI1->CR2 = 0;			 			// DFF=0, 8 bit data
}

void SPITransmit(uint8_t *data, size){
	int i = 0;
	while(i<size){
		while(!((SPI1->SR)&(1<<1)));    // wait for TXE bit to set -> This will indicate that the buffer is empty
		SPI1->DR = data[i];				// load the data into the Data Register
		i++;
	}
	while(!((SPI1->SR)&(1<<1)));
	while(((SPI1->SR)&(1<<7)));
	uint8_t temp = SPI1->DR;
	temp = SPI1->SR;
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
	RCC->PLLCFGR = (4 <<0) | (160 << 6) | (0 <<16) | (1<<22);

	//Enable the PLL and wait for it to become ready
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));

	//Select the Clock Source and wait for it to be set
	RCC->CFGR |= 0x02;
	while ((RCC->CFGR & (3<<2)) != 0x08);

}
