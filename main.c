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
#include <ncurses.h>
#include <menu.h>
#include "function.h"
#include "interface.h"
#include "parser.h"

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
//mot* mem;

int main(int argc, char* argv[]){
   
    /* Initialisation des registres */
    PC = 0;
    SP = 0;
    SR = 0;

    /* Allocation de la mémoire */
    //mem = malloc(sizeof(mot)*TAILLE_MEM);

    // Lancer l'interface
    
    init_gui();
    int nb_instr;
    //parse("example.asm", &nb_instr);
}
