/*
Assembly para ARM -> ANTUNES
*/

.syntax unified
.thumb
.section .text
.cpu cortex-m4

.equ RCC_AHB1ENR, 	0x40023830
.equ GPIOD_EN, 		(1<<3)

.equ GPIOD_MODER,	0x40020C00
.equ OUTPUT,		(1<<28)

.equ GPIOD_ODR,		0x40020C14
.equ LED_ON,		(1<<14)
.equ LED_OFF,		(0xFFFFFFFF & ~(1<<14))
.equ tempo,			2666666

.global main
main:

	//rcc
	ldr r0, =RCC_AHB1ENR
	ldr r1, [r0]
	orr r1, #GPIOD_EN
	str r1,[r0]

	//gpioa
	ldr r0, =GPIOD_MODER
	ldr r1, [r0]
	orr r1, #OUTPUT
	str r1, [r0]

	ldr r3,=tempo

piscaled:

	//led on
	ldr r0, =GPIOD_ODR
	ldr r1, [r0]
	orr r1, #LED_ON
	str r1, [r0]

	bl delay
	ldr r3,=tempo

	//turn led off
	ldr r0, =GPIOD_ODR
	ldr r1, [r0]
	and r1, #LED_OFF
	str r1, [r0]

	bl delay
	ldr r3, =tempo
	bl piscaled

delay:
	subs r3,r3,#1
	bne delay
	bx lr
.end
