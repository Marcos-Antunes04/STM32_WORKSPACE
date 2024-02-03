.global _start
_start:
	mov r2, #0b111
	mov r1, #0b101
	and r0,r1,r2 //r0 = r1 & r2
	orr r3,r1,r2 //r3 = r1 | r2
	mvn r1,r1	 //r1 = -r1
	mvn r1,r1
	lsr r1,#1 	 //Logical shift to the right by 1 bit
	mov r0, #10
	mov r1, r0, lsl #1
	