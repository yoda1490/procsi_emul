/**
 * \file main.c
 * \brief Programme de tests.
 * \author Lucas.C
 * \version 1.0
 * \date 18 décembre 2011
 *
 * Programme de test pour la simulation de PROCSI.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "function.h"

#include "parser.h"

//int nb_instr = 8;

// 8 registres
int reg[8];
int PC,SP,SR;
mot* mem;

// Mémoire de tests pour ADD
/* mot mem[TAILLE_MEM] = {
        {.codage = {ADD, REGREG, 1,2 }},
        {.codage = {STORE, DIRREG, 1,0}},
        {.brut = 2000                 },
        {.codage = {LOAD, REGIMM, 0,6}},
        {.brut = 2000                },
        {.codage = {ADD, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {ADD, REGIMM, 0, 3}},
        {.brut = 1                    },
        {.codage = {ADD, REGIND, 6, 4}}
};  */

// Mémoire de tests pour SUB
/* mot mem[TAILLE_MEM] = {
        {.codage = {SUB, REGREG, 1,2 }},
        {.codage = {STORE, DIRREG, 2,0}},
        {.brut = 2000                 },
        {.codage = {LOAD, REGIMM, 0,6}},
        {.brut = 2000                },
        {.codage = {SUB, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {SUB, REGIMM, 0, 3}},
        {.brut = 1                    },
        {.codage = {SUB, REGIND, 6, 4}}
}; */

// Mémoire de tests pour LOAD
/* mot mem[TAILLE_MEM] = {
        {.codage = {LOAD, REGIMM, 0,3}},
        {.brut = 2000                 },
        {.codage = {STORE, DIRREG, 3,0}},
        {.brut = 2000                 },
        {.codage = {LOAD, REGIND, 3,1 }},
        {.codage = {LOAD, REGDIR, 0,6}},
        {.brut = 2000                 }
}; */

// Mémoire de tests pour STORE
/* mot mem[TAILLE_MEM] = {
        {.codage = {LOAD, REGIMM, 0,3}},
        {.brut = 2000                 },
        {.codage = {LOAD, REGIMM, 0,4}},
        {.brut = 2001                 },
        {.codage = {STORE, DIRIMM, 0,0}},
        {.brut = 2002                  },
        {.brut = 2                     },
        {.codage = {STORE, DIRREG, 3,0}},
        {.brut = 2003                 },
        {.codage = {STORE, INDIMM, 0,3}},
        {.brut = 2000                 },
        {.codage = {STORE, INDREG, 3,4}}
}; */

// Mémoire de tests pour JMP
/* mot mem[TAILLE_MEM] = {
        {.codage = {ADD, REGREG, 1,2 }},
        {.codage = {STORE, DIRREG, 1,0}},
        {.brut = 2000                 },
        {.codage = {JMP, REGIMM       }},
        {.brut = 9                    },
        {.codage = {ADD, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {ADD, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {ADD, REGIMM, 0, 3}},
        {.brut = 1                    },
        {.codage = {ADD, REGIND, 6, 4}}
}; */

// Mémoire de tests pour JEQ
/* mot mem[TAILLE_MEM] = {
        {.codage = {ADD, REGREG, 0,0 }}, // exécution du JEQ car SR = 0
        {.codage = {STORE, DIRREG, 1,0}},
        {.brut = 2000                 },
        {.codage = {JEQ, REGIMM       }},
        {.brut = 9                    },
        {.codage = {ADD, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {ADD, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {ADD, REGIMM, 0, 3}},
        {.brut = 1                    },
        {.codage = {ADD, REGIND, 6, 4}}
}; */

// Mémoire de tests pour PUSH et POP
/* mot mem[TAILLE_MEM] = {
        {.codage = {PUSH, DIRIMM     }},
        {.brut = 2000                 },
        {.codage = {PUSH, DIRIMM     }},
        {.brut = 3000                 },
        {.codage = {POP, REGDIR, 0,0 }},
        {.codage = {POP, DIRIMM      }},
        {.brut = 2000                 }
}; */

// Mémoire de tests pour CALL et RET
/* mot mem[TAILLE_MEM] = {
        {.codage = {ADD, REGREG, 1,2 }},
        {.codage = {CALL, DIRIMM     }}, // Simulation d'appel de la fonction f1
        {.brut = 6                    },
        {.codage = {ADD, REGREG, 2,1 }},
        {.codage = {ADD, REGREG, 5,4 }},
        {.codage = {HALT             }}, // Fin d'exécution
        {.codage = {ADD, REGREG, 6,5 }}, // Fonction f1
        {.codage = {ADD, REGREG, 7,6 }},
        {.codage = {RET              }}, // On dépile et on retourne à l'adresse du CALL + 2
}; */

/* int main(int argc, char *argv[]){

    // Initialisation de PC à 0 (première adresse du programme)
    PC = 0;
    // Initialisation du sommet de la pile
    SP = ADR_PILE_MIN;
    SR = 0;

    int i;
    for (i = 0;i<8;i++){
	reg[i] = 0;
    }

    init_gui();
} */

int main(){

	PC = 0;
	SP = ADR_PILE_MIN;
	SR = 0;		

	int nb_instr = 0;

	mot* mem2 = malloc(sizeof(mot)*4500);
	mem2 = parse("test1.asm", &nb_instr);

	//exec_instr();
}

int exec_instr()
{

    // Etats des registres
    //stateRegister(reg, PC,SP,SR);

    // Traitement des instructions

        switch (mem[PC].codage.codeop){
            case ADD :
                // Addition
                printf("\n\nInstruction ADD");
 
                switch (mem[PC].codage.mode){
                    case REGREG :
                        printf("\nMode REGREG");
                        printf("\ninstruction (PC:%d) => add R%d,R%d",PC,mem[PC].codage.dest,mem[PC].codage.source);
                        // Addition
                        add(reg[mem[PC].codage.source],&reg[mem[PC].codage.dest],&SR);
                        printf("\nSR=%d",SR);
                        break;

                    case REGIMM :
                        printf("\nMode REGIMM");
                        printf("\ninstruction (PC:%d) => add R%d,#%d",PC,mem[PC].codage.dest,mem[PC+1].brut);

                        add(&mem[PC+1].brut,&reg[mem[PC].codage.dest],&SR);
                        printf("\nSR=%d",SR);
                        break;

                    case REGDIR :
                        printf("\nMode REGDIR");
                        printf("\ninstruction (PC:%d) => add R%d,[%d]",PC,mem[PC].codage.dest,mem[PC+1].brut);

                        add(&mem[mem[PC+1].brut].brut,&reg[mem[PC].codage.dest],&SR);
                        printf("\nSR=%d",SR);
                        break;

                    case REGIND :
                        printf("\nMode REGIND");
                        printf("\ninstruction (PC:%d) => add R%d,[R%d]",PC,mem[PC].codage.dest,mem[PC].codage.source);

                        add(&mem[reg[mem[PC].codage.source]].brut,&reg[mem[PC].codage.dest],&SR);
                        printf("\nSR=%d",SR);
                        break;
                }

                break;

            case SUB :
                // Soustraction
                printf("\n\nInstruction SUB");

                switch (mem[PC].codage.mode){
                    case REGREG :
                        printf("\nMode REGREG");
                        printf("\ninstruction (PC:%d) => sub R%d,R%d",PC,mem[PC].codage.dest,mem[PC].codage.source);

                        sub(&reg[mem[PC].codage.source],&reg[mem[PC].codage.dest],&SR);
                        break;

                    case REGIMM :
                        printf("\nMode REGIMM");
                         printf("\ninstruction (PC:%d) => sub R%d,#%d",PC,mem[PC].codage.dest,mem[PC+1].brut);

                         sub(&mem[PC+1].brut,&reg[mem[PC].codage.dest],&SR);
                        break;

                    case REGDIR :
                        printf("\nMode REGDIR");
                        printf("\ninstruction (PC:%d) => sub R%d,[%d]",PC,mem[PC].codage.dest,mem[PC+1].brut);

                        sub(&mem[mem[PC+1].brut].brut,&reg[mem[PC].codage.dest],&SR);
                        break;

                    case REGIND :
                        printf("\nMode REGIND");

                        printf("\ninstruction (PC:%d) => sub R%d,[R%d]",PC,mem[PC].codage.dest,mem[PC].codage.source);

                        sub(&mem[reg[mem[PC].codage.source]].brut,&reg[mem[PC].codage.dest],&SR);
                        break;
                }

                break;

            case LOAD :
                // Chargement d'un registre depuis la mémoire
                printf("\n\nInstruction LOAD");

                switch (mem[PC].codage.mode){
                    case REGIMM :
                        printf("\nMode REGIMM");
                        printf("\ninstruction (PC:%d) => load R%d,#%d",PC,mem[PC].codage.dest,mem[PC+1].brut);
                        reg[mem[PC].codage.dest] = mem[PC+1].brut;
                        break;

                    case REGDIR :
                        printf("\nMode REGDIR");
                        printf("\ninstruction (PC:%d) => load R%d,[%d]",PC,mem[PC].codage.dest,mem[PC+1].brut);
                        reg[mem[PC].codage.dest] = mem[mem[PC+1].brut].brut;
                        break;

                    case REGIND :
                        printf("\nMode REGIND");
                        printf("\ninstruction (PC:%d) => load R%d,[R%d]",PC,mem[PC].codage.dest,mem[PC].codage.source);
                        reg[mem[PC].codage.dest] = mem[reg[mem[PC].codage.source]].brut;
                        break;
                }

                break;

            case STORE :
                // Chargement en mémoire
                printf("\n\nInstruction STORE");

                switch (mem[PC].codage.mode){
                    case DIRREG :
                        printf("\nMode DIRREG");
                        printf("\ninstruction (PC:%d) => store [%d],R%d",PC,mem[PC+1].brut,mem[PC].codage.source);
                        mem[mem[PC+1].brut].brut = reg[mem[PC].codage.source];
                        break;

                    case DIRIMM :
                        printf("\nMode DIRIMM");
                        printf("\ninstruction (PC:%d) => store [%d],#%d",PC,mem[PC+1].brut,mem[PC+2].brut);
                        mem[mem[PC+1].brut].brut = mem[PC+2].brut;
                        break;

                    case INDREG :
                        printf("\nMode INDREG");
                        printf("\ninstruction (PC:%d) => store [R%d],R%d",PC,mem[PC].codage.dest,mem[PC].codage.source);
                        mem[reg[mem[PC].codage.dest]].brut = reg[mem[PC].codage.source];
                        break;

                    case INDIMM :
                        printf("\nMode INDIMM");
                        printf("\ninstruction (PC:%d) => store [R%d],#%d",PC,mem[PC].codage.dest,mem[PC+1].brut);
                        mem[reg[mem[PC].codage.dest]].brut = mem[PC+1].brut;
                        break;
                }

                break;

            case JMP :
                // Saut
                printf("\n\nInstruction JMP");

                switch (mem[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :
                        printf("\ninstruction (PC:%d) => jmp #%d",PC,mem[PC+1].brut);
                        // Exécution de l'instruction
                        PC = mem[PC+1].brut;
                        // On enlève 1 au PC par anticipation du +1 de la boucle for
                        PC--;
                }

                break;

            case JEQ :
                // Saut conditionnel
                printf("\n\nInstruction JEQ");

                switch (mem[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :
                        printf("\ninstruction (PC:%d) => jeq #%d",PC,mem[PC+1].brut);

                        if (SR == 0){
                            // Exécution de l'instruction
                            PC = mem[PC+1].brut;
                            // On enlève 1 au PC par anticipation du +1 de la boucle for
                            PC--;
                        }

                        break;
                }

                break;

            case CALL :
                printf("\n\nInstruction CALL");

                switch (mem[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :

                        printf("\ninstruction (PC:%d) => call #%d",PC,mem[PC+1].brut);

                        // Exécution de l'instruction
                        mem[SP].brut = PC;
                        SP = SP - 1;
                        PC = mem[PC+1].brut;
                        PC--;
                        break;
                }

                break;

            case RET :
                printf("\n\nInstruction RET");
                printf("\ninstruction (PC:%d) => ret",PC);

                // Exécution de l'instruction
                SP = SP + 1;
                PC = mem[SP].brut;
                PC++;
                break;

            case PUSH :
                printf("\n\nInstruction PUSH");

                // On distingue les modes d'adressage pour savoir si la source se trouve dans un second mot ou non
                switch (mem[PC].codage.mode){
                    case REGREG :
                    case DIRREG :
                    case INDREG :

                        printf("\ninstruction (PC:%d) => push R%d",PC,mem[PC].codage.source);

                        // On empile directement la valeur du registre source
                        mem[SP].brut = reg[mem[PC].codage.source];
                        SP = SP - 1;

                        break;

                    case REGIND :

                        printf("\ninstruction (PC:%d) => push [R%d]",PC,mem[PC].codage.source);

                        // On empile la valeur se trouvant à l'adresse contenue dans le registre source
                        mem[SP].brut = mem[reg[mem[PC].codage.source]].brut;
                        SP = SP - 1;

                        break;

                    case REGIMM :
                    case INDIMM :
                    case DIRIMM :

                        printf("\ninstruction (PC:%d) => push #%d",PC,mem[PC+1].brut);

                        // On empile une valeur immdédiate
                        mem[SP].brut = mem[PC+1].brut;
                        SP = SP - 1;

                        break;

                    case REGDIR :

                        printf("\ninstruction (PC:%d) => push [%d]",PC,mem[PC+1].brut);

                        // On empile la valeur se trouvant à l'adresse spécifiée
                        mem[SP].brut = mem[mem[PC+1].brut].brut;
                        SP = SP - 1;

                        break;
                }

                break;

            case POP :
                printf("\n\nInstruction POP");

                // On distingue les modes d'adressage pour savoir si la source se trouve dans un second mot ou non
                switch (mem[PC].codage.mode){
                    case REGREG :
                    case REGDIR :
                    case REGIMM :
                    case REGIND :

                        printf("\ninstruction (PC:%d) => pop R%d",PC,mem[PC].codage.dest);

                        // On empile directement la valeur du registre source
                        SP = SP + 1;
                        reg[mem[PC].codage.dest] = mem[SP].brut;

                        break;

                    case DIRIMM :
                    case DIRREG :

                        printf("\ninstruction (PC:%d) => pop [%d]",PC,mem[PC+1].brut);

                        // On empile directement la valeur du registre source
                        SP = SP + 1;
                        mem[mem[PC+1].brut].brut = mem[SP].brut;

                        break;

                    case INDIMM :
                    case INDREG :


                        printf("\ninstruction (PC:%d) => pop [R%d]",PC,mem[PC].codage.dest);

                        // On empile directement la valeur du registre source
                        SP = SP + 1;
                        mem[reg[mem[PC].codage.dest]].brut = mem[SP].brut;

                        break;
                }

                break;

            case HALT :
                printf("\ninstruction (PC:%d) => halt",PC);
                printf("\n\nFin de l'exécution.");
                return -10;
                break;
        }

    //stateRegister(reg, PC,SP,SR);
    //viewMemory(3999,5, mem);

    return 0;
}
