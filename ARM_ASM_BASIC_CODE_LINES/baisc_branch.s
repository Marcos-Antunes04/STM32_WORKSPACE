.global _start
_start:
	mov r0, #2
	mov r1, #1
	
	cmp r1,r0
	bgt greater  //branch greater than -> greater
	bne greater	 //branch not equal -> greater
	mov r3, #1
	bal default  //branch all -> default
greater:
	mov r2, #1
default:
	mov r2, r1