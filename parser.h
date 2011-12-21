#ifndef PARSER_H
#define PARSER_H


#include <regex.h>

mot * parse(char * file, int * nb_instruction);
void get_operandes(char * chaine, regmatch_t *pmatch, char ** source, char ** dest);
mot save_brut(int brut);
mot save_mot(mnemonique operateur, mode le_mode, int source, int dest);


#endif