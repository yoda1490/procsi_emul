        ADD 	R2,	R1	
        ADD 	R7,	[2000]
        ADD 	R3,	#1
        ADD 	R4,	[R6]
 //ceci est un commentaire       
        SUB     R2,     R1
        SUB     R7,     [2000]
        SUB     R3,     #1
        SUB     R4,     [R6]
#ceci est un autre commentaire
	LOAD 	R6,	#2000
	LOAD 	R6,	[2000]
	LOAD 	R6,	[R6]

	STORE 	[2000],	R1
	STORE 	[2000],	#600
	STORE 	[R6],	R1
	STORE 	[R6],	#2000

	JMP	#2000

	JEQ	#2000

	CALL	#1000

	RET

	PUSH	R3
	PUSH	#2000
	PUSH	[2000]
	PUSH	[R3]

	POP	R3
	POP	[2000]
	POP	[R3]
	
	HALT


	POP	R4
