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
