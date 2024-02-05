#include "main.h"
#include "stdio.h"

void ADC_Init(void);
void ADC_Enable(void);
void ADC_Start(void);
void ADC_WaitForConv(void);
uint16_t ADC_GetVal(void);
void ADC_Disable(void);
void SysClockConfig(void);

int _write(int file, char* ptr, int len){
	int i = 0;
	for(i=0; i < len; i++)
		ITM_SendChar((*ptr++));
	return len;
}

uint16_t ADC_VAL;
int main(void){
	SysClockConfig();
	ADC_Init();
	ADC_Enable();

	while (1){
		ADC_Start();
		ADC_WaitForConv();
		ADC_VAL = ADC_GetVal();
		printf("VALUE -> %d\n",(int)ADC_VAL);
	}
}



void ADC_Init(void){
	RCC->APB2ENR |= (1<<8); //Start ADC
	RCC->AHB1ENR |= (1<<0); //Start GPIOA

	ADC->CCR |= (2<<16); //Adc PCLK2 divide by 6 prescaler

	ADC1->CR1 = (1<<8); // scan mode enabled
	ADC1->CR1 &= ~(1<<24); //Sets resolution to 12bits(default)

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


	// Setting GPIOA 1 and 4 as Analog mode
	GPIOA->MODER |= (3<<2);  // analog mode for PA 1
	GPIOA->MODER |= (3<<8);  // analog mode for PA 4
}

void ADC_Enable(void){
	// Once the configuration has been completed, now its time to enable the ADC
	ADC1->CR2 |= 1<<0;
	uint32_t delay = 10000;
	while(delay--);
}

void ADC_Start(void){
	//Sequence in which the channels will be converted
	ADC1->SQR3 |= (1<<0);  // SEQ1 for Channel 1
	ADC1->SQR3 |= (4<<5);  // SEQ2 for CHannel 4
	ADC1->SQR3 |= (18<<10);  // SEQ3 for CHannel 18

	//Needed for the conversion to start
	ADC1->SR = 0;        // clear the status register

	ADC1->CR2 |= (1<<30);  // start the conversion
}

void ADC_WaitForConv(void){
	while(!(ADC1->SR & (1<<1))); // WAIT FOR EOC FLAG TO SET
}
uint16_t ADC_GetVal(void){
	return ADC1->DR; // Read the Data Register
}

void ADC_Disable(void){
	ADC1->CR2 &= ~(1<<0); // DISABLE ADC
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
