/**
 * \file main.c
 * \brief Programme de tests.
 * \author Lucas.C
 * \version 1.0
 * \date 18 décembre 2011
 *
 * Emulateur PROCSI
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "interface.h"
#include "parser.h"

void exec_instr()
{

    // Traitement des instructions
    while(PC < ADR_INSTR_MAX){

	// Mise à jour de l'interface
        display_execution(PC, mem_prog, ADR_INSTR_MAX, reg, 8);

        switch (mem_prog[PC].codage.codeop){
            case ADD :

		// Addition
 
                switch (mem_prog[PC].codage.mode){
                    case REGREG :

                        add(&reg[mem_prog[PC].codage.source],&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 1;

                        break;

                    case REGIMM :

                        add(&mem_prog[PC+1].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 2;

                        break;

                    case REGDIR :

                        add(&mem_prog[mem_prog[PC+1].brut].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 2;

                        break;

                    case REGIND :
                      
                        add(&mem_prog[reg[mem_prog[PC].codage.source]].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 1;

                        break;
                }

                break;

            case SUB :

		// Soustraction
                
                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                      
                        sub(&reg[mem_prog[PC].codage.source],&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 1;

                        break;

                    case REGIMM :
                      
                         sub(&mem_prog[PC+1].brut,&reg[mem_prog[PC].codage.dest],&SR);
                         PC += 2;

                        break;

                    case REGDIR :
                        
                        sub(&mem_prog[mem_prog[PC+1].brut].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 2;

                        break;

                    case REGIND :
                      
                        sub(&mem_prog[reg[mem_prog[PC].codage.source]].brut,&reg[mem_prog[PC].codage.dest],&SR);
                        PC += 1;

                        break;
                }

                break;

            case LOAD :

		// Chargement dans un registre
                
                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    
                        reg[mem_prog[PC].codage.dest] = mem_prog[PC+1].brut;
                        PC += 2;

                        break;

                    case REGDIR :
                     
                        reg[mem_prog[PC].codage.dest] = mem_prog[mem_prog[PC+1].brut].brut;
                        PC += 2;

                        break;

                    case REGIND :

                        reg[mem_prog[PC].codage.dest] = mem_prog[reg[mem_prog[PC].codage.source]].brut;
                        PC += 1;

                        break;
                }

                break;

            case STORE :

		// Chargement en mémoire
             
                switch (mem_prog[PC].codage.mode){
                    case DIRREG :
                      
                        mem_prog[mem_prog[PC+1].brut].brut = reg[mem_prog[PC].codage.source];
                        PC += 2;

                        break;

                    case DIRIMM :
                     
                        mem_prog[mem_prog[PC+1].brut].brut = mem_prog[PC+2].brut;
                        PC += 3;

                        break;

                    case INDREG :
                       
                        mem_prog[reg[mem_prog[PC].codage.dest]].brut = reg[mem_prog[PC].codage.source];
                        PC += 1;

                        break;

                    case INDIMM :

                        mem_prog[reg[mem_prog[PC].codage.dest]].brut = mem_prog[PC+1].brut;
                        PC += 2;

                        break;
                }

                break;

            case JMP :
		// Saut
             
                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :
                       
                        PC = mem_prog[PC+1].brut;
                        // On enléve 1 au PC par anticipation du +1 de la boucle for
                        //PC--;  maintenan on incrémente dans chaque mode
                }

                break;

            case JEQ :
                // Saut conditionnel

                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :

                        if (SR == 0){
                            // Exécution de l'instruction
                            PC = mem_prog[PC+1].brut;
                            // On enléve 1 au PC par anticipation du +1 de la boucle for
                            //PC--; //maintenan on incrémente dans chaque mode
			    PC += 1;
                        }
			else {
			    PC += 2;
			}

                        break;
                }

                break;

            case CALL :

		// Appel de fonction                

                switch (mem_prog[PC].codage.mode){
                    case REGIMM :
                    case DIRIMM :
                    case INDIMM :

                        // Exécution de l'instruction
                        mem_prog[sp].brut = PC;
                        sp = sp - 1;
                        PC = mem_prog[PC+1].brut;
                        //PC--;

                        break;
                }

                break;

            case RET :

		// Retour de fonction    

                sp = sp + 1;
                PC = mem_prog[sp].brut;
                PC += 2;

                break;

            case PUSH :

		// Empiler une valeur dans la pile
               
                // On distingue les modes d'adressage pour savoir si la source se trouve dans un second mot ou non
                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                    case REGIND :
                    case REGDIR :

                        // On empile directement la valeur du registre source
                        mem_prog[sp].brut = reg[mem_prog[PC].codage.source];
                        sp = sp - 1;
                        PC += 1;

                        break;

                    case INDREG :
		    case INDIMM :

                        // On empile la valeur se trouvant é l'adresse contenue dans le registre source
                        mem_prog[sp].brut = mem_prog[reg[mem_prog[PC].codage.source]].brut;
                        sp = sp - 1;
                        PC += 1;

                        break;

                    case DIRREG :
                    case DIRIMM :

                        // On empile la valeur se trouvant à l'adresse spécifiée
                        mem_prog[sp].brut = mem_prog[mem_prog[PC+1].brut].brut;
                        sp = sp - 1;
                        PC += 2;

                        break;

		    case REGIMM :

			// On empile une valeur immdédiate
                        mem_prog[sp].brut = mem_prog[PC+1].brut;
                        sp = sp - 1;
                        PC += 2;
                }

                break;

            case POP :

		// Dépiler la pile

                // On distingue les modes d'adressage pour savoir si la source se trouve dans un second mot ou non
                switch (mem_prog[PC].codage.mode){
                    case REGREG :
                    case DIRREG :
                    case INDREG :

                        // On empile directement la valeur du registre source
                        sp = sp + 1;
                        reg[mem_prog[PC].codage.dest] = mem_prog[sp].brut;
                        PC += 1;

                        break;

                    case REGDIR :

                        // On empile directement la valeur du registre source
                        sp = sp + 1;
                        mem_prog[mem_prog[PC+1].brut].brut = mem_prog[sp].brut;
                        PC += 2;

                        break;

                    case REGIND :

                        // On empile directement la valeur du registre source
                        sp = sp + 1;
                        mem_prog[reg[mem_prog[PC].codage.dest]].brut = mem_prog[sp].brut;
                        PC += 1;

                        break;
                }

                break;

            case HALT :

		// Fin du programme
		return;
        }
        
    }
}
