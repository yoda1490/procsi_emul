/**
* \file main.c
* \brief Lancement de l'application
* \author Lucas.C & Amaury.B
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


/**
 * \fn int main (int argc, char* argv[])
 * \brief Fonction main de l'émulateur.
 *
 * \param argc Nombre d'argument donnée lors de l'execution.
 * \param argv Tableau de chaine contenant les différent paramètres données en argument
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main(int argc, char* argv[]){
   
    /* Initialisation des registres */
    PC = 0;
    sp = ADR_PILE_MIN;
    SR = 0;

    // Lance l'interface
    init_gui();
}
