        ADD 	R2,	R1	
        ADD 	R7,	[2000]
        ADD 	R3,	#1
        ADD 	R4,	[R6]
        
        SUB     R2,     R1
        SUB     R7,     [2000]
        SUB     R3,     #1
        SUB     R4,     [R6]

	LOAD 	R6,	#2000
	LOAD 	R6,	[2000]
	LOAD 	R6,	[R6]

	STORE 	[2000],	R1
	STORE 	[2000],	#600
	STORE 	[R6],	R1
	STORE 	[R6],	#2000

	HALT
