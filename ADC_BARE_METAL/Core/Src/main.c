#include "main.h"

int main(void){
	RCC->APB2ENR |= (1<<8); //Start ADC
	RCC->AHB1ENR |= (1<<0); //Start GPIOA

	ADC->CCR |= (2<<16); //Adc PCLK2 divide by 6 prescaler

	ADC1->CR1 = (1<<8); // scan mode enabled
	ADC1->CR1 &~ (1<<24); //Sets resolution to 12bits(default)

	/*
	-> Continuous Conversion specifies whether we want to convert the ADC values continuously, or should it stop after one conversion only.
	-> EOC is End Of Conversion specifies whether the EOC Flag should set after each conversion, or at the end of all the conversions.
	-> DMA specifies whether we want to use DMA for ADC.
	-> Data Alignment specifies whether the 12 bit data should be Right Aligned or Left Aligned in a 16 bit Register
	 */

	ADC1->CR2 = (1<<1);
	ADC1->CR2 |= (1<<10);
	ADC1->CR2 &= ~(1<<11);

	ADC1->CR2 |= (1<<8);
	ADC1->CR2 |= (1<<9);


	//Sampling time of 3 cycles for channels 1 and 4
	ADC1->SMPR2 &= ~((7<<3) | (7<<12));

	//6. Set the Regular channel sequence length in ADC_SQR1
	ADC1->SQR1 |= (2<<20);   // SQR1_L =2 for 3 conversions


	//Sequence in which the channels will be converted
	ADC1->SQR3 |= (1<<0);  // SEQ1 for Channel 1
	ADC1->SQR3 |= (4<<5);  // SEQ2 for CHannel 4
	ADC1->SQR3 |= (18<<10);  // SEQ3 for CHannel 18

	// Setting GPIOA 1 and 4 as Analog mode
	GPIOA->MODER |= (3<<2);  // analog mode for PA 1
	GPIOA->MODER |= (3<<8);  // analog mode for PA 4

	// Once the configuration has been completed, now its time to enable the ADC
	ADC1->CR2 |= 1<<0;


	//Needed for the conversion to start
	ADC1->SR = 0;        // clear the status register

	ADC1->CR2 |= (1<<30);  // start the conversion


	while (1){

	}
}
