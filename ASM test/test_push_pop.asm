	
// Instructions de tests : PUSH, POP
	LOAD	R2, #4	
	LOAD	R1, #2001
	STORE	[2001], #156
	PUSH	R2
	PUSH	[R1]
	PUSH	[2002]
	PUSH	#453
	POP	R0
	POP	[R1]
	POP	[2000]
	HALT