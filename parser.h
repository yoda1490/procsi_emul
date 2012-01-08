/**
 * \file  parser.h
 * \brief Fichier d'entête.
 * \author Amaury.B
 * \version 1.0
 * \date 21 décembre 2011
 *
 * Fichier d'entête comportant les méthodes de l'interface en ncurses de l'émulateur procsi.
 *
 */
#ifndef PARSER_H
#define PARSER_H


#include <regex.h>

void parse(char * file, int * nb_instruction);
void get_operandes(char * chaine, regmatch_t *pmatch, char ** source, char ** dest);
mot save_brut(int brut);
mot save_mot(mnemonique operateur, mode le_mode, int source, int dest);


#endif
