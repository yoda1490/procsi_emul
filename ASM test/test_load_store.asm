	
// Instructions de tests : LOAD, STORE

	LOAD 	R1, #2000
	LOAD	R2, #2004
	STORE	[2000], #2005
	STORE 	[2005], #32
	LOAD	R2, [2000]
	LOAD	R3, [R2]
	STORE 	[2001], R1
	STORE	[R2], R1
	STORE	[R2], #345
	HALT
