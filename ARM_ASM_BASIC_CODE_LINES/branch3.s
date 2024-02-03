.global _start
_start:
	mov r0, #1
	mov r1, #3
	push {r0,r1} //pushes r0 and r1 on to the stack
	//pushing r0 and r0 on to the stack makes us able to preserve the value stored in the registers before they get modified inside the function
	bl get_value
	pop {r0,r1}
	b end

get_value:
	mov r0,#5
	mov r1,#7
	add r2,r0,r1
	bx lr


	//bl add2 //branch location
	//mov r3,#4
	//cmp r0,r1
	//addlt r2,#1 //add less than
	//movge -> move greater or equal to

/*	 
add2:
	add r2,r0,r1
	bx lr // branches back to the link register
*/