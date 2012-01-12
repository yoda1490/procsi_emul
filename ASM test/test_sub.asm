	
// Instructions de tests : SUB

	ADD 	R0, #2000
	ADD	R3, #2000
	ADD 	R1, #2
	SUB	R0, #200
        SUB 	R0, R1
	STORE	[2000], #45
	SUB	R0, [2000]
	SUB	R0, [R3]
	HALT
