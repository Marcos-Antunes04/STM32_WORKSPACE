.global _start
_start:
	ldr r0, =list   //r0 = list;
	ldr r1, [r0]    //*r1 = *r0;
	ldr r2, [r0,#4] //*r2 = *(r0+4);
	ldr r3, [r0,#8]!//*r3 = *(r0+8); r0 = r0 + 8 
	ldr r4, [r0]!	//*r4 = *r0; r0 = r0
	
	ldr r0, =list
	ldr r1, [r0]
	ldr r2, [r0],#4 //*r2 = *r0; r0 = r0+4;
	
.data
list:
//.word stands for uint32_t type of data
	.word 4,5,-9,1,0,-3