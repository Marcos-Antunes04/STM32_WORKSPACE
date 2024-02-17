.syntax unified
.thumb
.section .text
.cpu cortex-m4

.global _start
_start:
	ldr r0, =var1 // Stores the memory address of var1 into r0
	ldr r1, [r0] // Stores the value contained into the address into r1
	mov r2, #3
	str r2, [r0] // Stores value containde into r2 into the memory address stored r0

	/*
		and
		orr
		mvn
		eor (XOR)

	*/

.data
var1: .word 5
var2: .word 6
