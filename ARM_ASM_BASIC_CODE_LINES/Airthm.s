.global _start
_start:
	mov r0, #0xFFFFFFFF //-1
	mov r1, #3          //+3
	add r2,r0,r1 //r2 = r0 + r1
	sub r3,r0,r1 //r3 = r0 - r1
	mul r4,r0,r1 //r4 = r0 * r1

.data
list:
	.word