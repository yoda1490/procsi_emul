	ADD 	R3, #134
        ADD 	R4, R3

//on initialise R6 a 0
	SUB	R6, R6
#puis on lui donne la valeur 2012
	ADD	R6, #2012

	STORE 	[2000],	R1
	STORE 	[2999],	#600
	STORE 	[R6],	R1
	STORE 	[R6],	#2000

	HALT
