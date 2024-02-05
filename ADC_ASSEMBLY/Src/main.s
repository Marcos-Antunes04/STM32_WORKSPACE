/*
*	ADC -> ANTUNES
*/
.syntax unified
.thumb
.section .text
.cpu cortex-m4

// -> SETTING REGISTER ADDRESSES
.equ RCC_AHB1ENR, 	0x40023830
.equ RCC_APB2ENR,	0x40023844
.equ RCC_APB1ENR,	0x40023840
.equ RCC_CR,		0x40023800
.equ RCC_CFGR,		0x40023808
.equ RCC_PLLCFGR,	0x40023804
.equ PWR_CR,		0x40007000
.equ ADC1_CR1,		0x40012004
.equ ADC1_CR2,		0x40012008
.equ ADC1_SMPR2,	0x40012010
.equ ADC_CCR,		0x40012304
.equ ADC1_SQR3,		0x40012034
.equ ADC1_SR,		0x40012000
.equ ADC1_DR,		0x4001204C
.equ GPIOA_MODER,	0x40020000
.equ FLASH_ACR,		0x40023C00

.global main
main:
	bl SysClockConfig




ADC_INIT:
	// ENABLING GPIOA
	ldr r0, =RCC_AHB1ENR
	ldr r1, [r0]
	orr r1, #(1<<0)
	str r1, [r0]



	bx lr

SysClockConfig:
	ldr r0, =RCC_CR
	ldr r1, [r0]
	orr r1, (1<<16)
	str r1, [r0]
	loop0:
		ldr r2, =(1<<17)
		tst r1,r2
		bne loop0
		bx lr

	ldr r0, =FLASH_ACR
	ldr r1, [r0]
	orr r1, (1<<9)
	orr r1, (1<<10)
	orr r1, (1<<8)
	orr r1, (0x05)
	str r1, [r0]

	ldr r0, =RCC_CFGR
	ldr r1, [r0]
	orr r1, 0x1400
	orr r1, 0x8000
	str r1, [r0]

	ldr r0, =RCC_PLLCFGR
	ldr r1, [r0]
	orr r1, 4<<0
	orr r1, 180<<6
	orr r1, 0<<16
	orr r1, 1<<22
	str r1, [r0]

	ldr r0, =RCC_CR
	ldr r1, [r0]
	orr r1, 1<<24
	str r1, [r0]

	loop1:
		ldr r2, =(1<<25)
		tst r1,r2
		bne loop1
		bx lr

	ldr r0, =RCC_CFGR
	ldr r1, [r0]
	orr r1, 0x02
	str r1, [r0]

	loop2:
		ldr r2, =(3<<2)
		and r1, r2
		ldr r3, =0x08
		cmp r1,r3
		bne loop2
		bx lr

	bx lr



.end
