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

#include "interface.h"

#include "parser.h"





int exec_instr()
{

    // Etats des registres
    //stateRegister(reg, PC,SP,SR);

    // Traitement des instructions
    while(PC < 50){
        switch (mem_prog[PC].codage.codeop){
            case ADD :
                // Addition
                //printf("\n\nInstruction ADD");
 
                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                        //printf("\nMode REGREG");
                        //printf("\ninstruction (PC:%d) => add R%d,R%d",PC,mem_prog[PC].codage.dest,mem_prog[PC].codage.source);
                        // Addition
                        add(&reg[mem_prog[PC].codage.source],&reg[mem_prog[PC].codage.dest],&SR);
                        //printf("\nSR=%d",SR);
                        PC += 1;
                        break;

                    case REGIMM :
                        //printf("\nMode REGIMM");
                        //printf("\ninstruction (PC:%d) => add R%d,#%d",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);

                        add(&mem_prog[PC+1].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 2;
                        //printf("\nSR=%d",SR);
                        break;

                    case REGDIR :
                        //printf("\nMode REGDIR");
                        //printf("\ninstruction (PC:%d) => add R%d,[%d]",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);

                        add(&mem_prog[mem_prog[PC+1].brut].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        //printf("\nSR=%d",SR);
                        PC += 2;
                        break;

                    case REGIND :
                        //printf("\nMode REGIND");
                        //printf("\ninstruction (PC:%d) => add R%d,[R%d]",PC,mem_prog[PC].codage.dest,mem_prog[PC].codage.source);

                        add(&mem_prog[reg[mem_prog[PC].codage.source]].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        //printf("\nSR=%d",SR);
                        PC += 2;
                        break;
                }

                break;

            case SUB :
                // Soustraction
                //printf("\n\nInstruction SUB");

                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                        //printf("\nMode REGREG");
                        //printf("\ninstruction (PC:%d) => sub R%d,R%d",PC,mem_prog[PC].codage.dest,mem_prog[PC].codage.source);

                        sub(&reg[mem_prog[PC].codage.source],&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 1;
                        break;

                    case REGIMM :
                        //printf("\nMode REGIMM");
                         //printf("\ninstruction (PC:%d) => sub R%d,#%d",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);

                         sub(&mem_prog[PC+1].brut,&reg[mem_prog[PC].codage.dest],&SR);
                         PC += 2;
                        break;

                    case REGDIR :
                        //printf("\nMode REGDIR");
                        //printf("\ninstruction (PC:%d) => sub R%d,[%d]",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);

                        sub(&mem_prog[mem_prog[PC+1].brut].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 2;
                        break;

                    case REGIND :
                        //printf("\nMode REGIND");

                        //printf("\ninstruction (PC:%d) => sub R%d,[R%d]",PC,mem_prog[PC].codage.dest,mem_prog[PC].codage.source);

                        sub(&mem_prog[reg[mem_prog[PC].codage.source]].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 2;
                        break;
                }

                break;

            case LOAD :
                // Chargement d'un registre depuis la mémoire
                //printf("\n\nInstruction LOAD");

                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                        //printf("\nMode REGIMM");
                        //printf("\ninstruction (PC:%d) => load R%d,#%d",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);
                        reg[mem_prog[PC].codage.dest] = mem_prog[PC+1].brut;
                        PC += 2;
                        break;

                    case REGDIR :
                        //printf("\nMode REGDIR");
                        //printf("\ninstruction (PC:%d) => load R%d,[%d]",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);
                        reg[mem_prog[PC].codage.dest] = mem_prog[mem_prog[PC+1].brut].brut;
                        PC += 2;
                        break;

                    case REGIND :
                        //printf("\nMode REGIND");
                        //printf("\ninstruction (PC:%d) => load R%d,[R%d]",PC,mem_prog[PC].codage.dest,mem_prog[PC].codage.source);
                        reg[mem_prog[PC].codage.dest] = mem_prog[reg[mem_prog[PC].codage.source]].brut;
                        PC += 2;
                        break;
                }

                break;

            case STORE :
                // Chargement en mémoire
                //printf("\n\nInstruction STORE");

                switch (mem_prog[PC].codage.mode){
                    case DIRREG :
                        //printf("\nMode DIRREG");
                        //printf("\ninstruction (PC:%d) => store [%d],R%d",PC,mem_prog[PC+1].brut,mem_prog[PC].codage.source);
                        mem_prog[mem_prog[PC+1].brut].brut = reg[mem_prog[PC].codage.source];
                        PC += 2;
                        break;

                    case DIRIMM :
                        //printf("\nMode DIRIMM");
                        //printf("\ninstruction (PC:%d) => store [%d],#%d",PC,mem_prog[PC+1].brut,mem_prog[PC+2].brut);
                        mem_prog[mem_prog[PC+1].brut].brut = mem_prog[PC+2].brut;
                        PC += 3;
                        break;

                    case INDREG :
                        //printf("\nMode INDREG");
                        //printf("\ninstruction (PC:%d) => store [R%d],R%d",PC,mem_prog[PC].codage.dest,mem_prog[PC].codage.source);
                        mem_prog[reg[mem_prog[PC].codage.dest]].brut = reg[mem_prog[PC].codage.source];
                        PC += 2;
                        break;

                    case INDIMM :
                        //printf("\nMode INDIMM");
                        //printf("\ninstruction (PC:%d) => store [R%d],#%d",PC,mem_prog[PC].codage.dest,mem_prog[PC+1].brut);
                        mem_prog[reg[mem_prog[PC].codage.dest]].brut = mem_prog[PC+1].brut;
                        PC += 2;
                        break;
                }

                break;

            case JMP :
                // Saut
                //printf("\n\nInstruction JMP");

                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :
                        //printf("\ninstruction (PC:%d) => jmp #%d",PC,mem_prog[PC+1].brut);
                        // Exécution de l'instruction
                        PC = mem_prog[PC+1].brut;
                        // On enléve 1 au PC par anticipation du +1 de la boucle for
                        //PC--;  maintenan on incrémente dans chaque mode
                }

                break;

            case JEQ :
                // Saut conditionnel
                //printf("\n\nInstruction JEQ");

                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :
                        //printf("\ninstruction (PC:%d) => jeq #%d",PC,mem_prog[PC+1].brut);

                        if (SR == 0){
                            // Exécution de l'instruction
                            PC = mem_prog[PC+1].brut;
                            // On enléve 1 au PC par anticipation du +1 de la boucle for
                            //PC--; //maintenan on incrémente dans chaque mode
                        }

                        break;
                }

                break;

            case CALL :
                //printf("\n\nInstruction CALL");

                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :

                        //printf("\ninstruction (PC:%d) => call #%d",PC,mem_prog[PC+1].brut);

                        // Exécution de l'instruction
                        mem_prog[SP].brut = PC;
                        SP = SP - 1;
                        PC = mem_prog[PC+1].brut;
                        //PC--;
                        break;
                }

                break;

            case RET :
                //printf("\n\nInstruction RET");
                //printf("\ninstruction (PC:%d) => ret",PC);

                // Exécution de l'instruction
                SP = SP + 1;
                PC = mem_prog[SP].brut;
                PC += 1;
                break;

            case PUSH :
                //printf("\n\nInstruction PUSH");

                // On distingue les modes d'adressage pour savoir si la source se trouve dans un second mot ou non
                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                    case DIRREG :
                    case INDREG :

                        //printf("\ninstruction (PC:%d) => push R%d",PC,mem_prog[PC].codage.source);

                        // On empile directement la valeur du registre source
                        mem_prog[SP].brut = reg[mem_prog[PC].codage.source];
                        SP = SP - 1;
                        PC += 1;

                        break;

                    case REGIND :

                        //printf("\ninstruction (PC:%d) => push [R%d]",PC,mem_prog[PC].codage.source);

                        // On empile la valeur se trouvant é l'adresse contenue dans le registre source
                        mem_prog[SP].brut = mem_prog[reg[mem_prog[PC].codage.source]].brut;
                        SP = SP - 1;
                        PC += 1;

                        break;

                    case REGIMM :
                    case INDIMM :
                    case DIRIMM :

                        //printf("\ninstruction (PC:%d) => push #%d",PC,mem_prog[PC+1].brut);

                        // On empile une valeur immdédiate
                        mem_prog[SP].brut = mem_prog[PC+1].brut;
                        SP = SP - 1;
                        PC += 2;

                        break;

                    case REGDIR :

                        //printf("\ninstruction (PC:%d) => push [%d]",PC,mem_prog[PC+1].brut);

                        // On empile la valeur se trouvant é l'adresse spécifiée
                        mem_prog[SP].brut = mem_prog[mem_prog[PC+1].brut].brut;
                        SP = SP - 1;
                        PC += 2;

                        break;
                }

                break;

            case POP :
                //printf("\n\nInstruction POP");

                // On distingue les modes d'adressage pour savoir si la source se trouve dans un second mot ou non
                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                    case REGDIR :
                    case REGIMM :
                    case REGIND :

                        //printf("\ninstruction (PC:%d) => pop R%d",PC,mem_prog[PC].codage.dest);

                        // On empile directement la valeur du registre source
                        SP = SP + 1;
                        reg[mem_prog[PC].codage.dest] = mem_prog[SP].brut;
                        PC += 1;

                        break;

                    case DIRIMM :
                    case DIRREG :

                        //printf("\ninstruction (PC:%d) => pop [%d]",PC,mem_prog[PC+1].brut);

                        // On empile directement la valeur du registre source
                        SP = SP + 1;
                        mem_prog[mem_prog[PC+1].brut].brut = mem_prog[SP].brut;
                        PC += 2;

                        break;

                    case INDIMM :
                    case INDREG :


                        //printf("\ninstruction (PC:%d) => pop [R%d]",PC,mem_prog[PC].codage.dest);

                        // On empile directement la valeur du registre source
                        SP = SP + 1;
                        mem_prog[reg[mem_prog[PC].codage.dest]].brut = mem_prog[SP].brut;
                        PC += 1;
                        break;
                }

                break;

            case HALT :
                //printf("\ninstruction (PC:%d) => halt",PC);
                //printf("\n\nFin de l'exécution.");
                return -10;
                break;
        }
        
        display_execution(SP, mem_prog, 50, reg, 8, PC, SP, SR);
        
    }
    
    
    //stateRegister(reg, PC,SP,SR);
    //viewMemory(3999,5, mem);

    return 0;
}
