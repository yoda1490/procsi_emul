/**
* \file main.c
* \brief Lancement de l'application
* \author Lucas.C
* \version 1.0
* \date 20 décembre 2011
*
* Lancement du simulateur PROCSI
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "interface.h"

#define TAILLE_MEM 4500

#define ADR_INSTR_MIN 0
#define ADR_INSTR_MAX 1999
#define ADR_DONNEE_MIN 2000
#define ADR_DONNEE_MAX 3999
#define ADR_PILE_MIN 4500 // Le sommet de la pile croît vers les adresses inférieur (dans le sujet de Lippi)
#define ADR_PILE_MAX 4000

/* Variables globales du simulateur */
int reg[8];
int PC, SP, SR;
mot* mem;

int main(int argc, char* argv[]){
   
    /* Initialisation des registres */
    PC = 0;
    SP = ADR_PILE_MIN;
    SR = 0;

    /* Allocation de la mémoire */
    mem = malloc(sizeof(mot)*TAILLE_MEM);

    // Lancer l'interface
   init_gui();
}
