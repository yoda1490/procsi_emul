/**
 * \file function.c
 * \brief Fichier source des fonctions utiles à l'application.
 * \author Lucas.C
 * \version 1.0
 * \date 18 décembre 2011
 *
 * Fichier source comportant les méthodes et structure nécessaires à la simulation du PROCSI C.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include <string.h>

//mémoire contenant les insctructions


void stateRegister(int* reg, int PC, int SP, int SR){
        printf("\n\nEtat des registres :");

        int j;
        for(j=0;j<8;j++){
            printf("\nR%d : 0x%s",j,toHexa(reg[j]));
        }

        // Affichage en hexa des registres. On peut changer et passer en binaire.
        printf("\n\nPC : 0x%s",toHexa(PC));
        printf("\nSP : 0x%s",toHexa(SP));
        printf("\nSR : 0x%s",toHexa(SR));
}

void viewMemory(int adresse, int taille, mot* mem){
    printf("\n\n------------- Etat de la memoire ------------");
    printf("\n\n\tadr\tcodeop\tmode\tsource\tdest\t");
    int i;

    // On boucle sur les adresses mémoires
    for (i=0;i<taille;i++){

        if (adresse+i < 2000){
            // Adresse mémoire instruction
            printf("\n\t%d",adresse+i);
            mot m = mem[adresse+i];

            printf("\t%s\t%s\t%s\t%s",add0(toBinaire(m.codage.codeop),6),
                   add0(toBinaire(m.codage.mode),4),
                   add0(toBinaire(m.codage.source),3),
                   add0(toBinaire(m.codage.dest),3));

            // Si le mode de registre fait intervenir des adresses indirect ou immédiate on affiche le 2eme mot
            if (m.codage.mode == DIRREG || m.codage.mode == INDIMM || m.codage.mode == REGIMM || m.codage.mode == REGDIR){
                printf("\n\t%d",adresse+i+1);
                mot m = mem[adresse+i+1];
                printf("\t%s",add0(toBinaire(m.brut),16));
                i++;
            }

            // Si le mode de registre est direct/immédiat l'instruction est sur 3 mots. On affiche donc les deux mots suivants
            if (m.codage.mode == DIRIMM){
                printf("\n\t%d",adresse+i+1);
                mot m = mem[adresse+i+1];
                printf("\t%s",add0(toBinaire(m.brut),16));

                printf("\n\t%d",adresse+i+2);
                m = mem[adresse+i+2];
                printf("\t%s",add0(toBinaire(m.brut),16));
                i++;i++;
            }
        }

        else{
            // Adresse mémoire donnée et pile
            printf("\n\t%d",adresse+i);
            mot m = mem[adresse+i];
            printf("\t%s",add0(toBinaire(m.brut),16));
        }
    }
}

char* toHexa(int n){

    char* retour = malloc(sizeof(char)*40);
    //char retour[20];

    if (n >= 0 && n <= 9) {
        sprintf(retour,"%d",n);
        retour;

    } else if (n == 10)
        return "A";
    else if (n == 11)
        return "B";
    else if (n == 12)
        return "C";
    else if (n == 13)
        return "D";
    else if (n == 14)
        return "E";
    else if (n == 15)
        return "F";
    else if (n > 15) {
        int modulo = n % 16;
        int quotient = n / 16;

        strcpy(retour,toHexa(quotient));
        strcat(retour,toHexa(modulo));
    }

    return retour;
}

char* toBinaire(int n){

    char* retour = malloc(sizeof(char)*40);

    if (n >= 0 && n <= 1) {
        sprintf(retour,"%d",n);

    } else if (n > 1) {
        int modulo = n % 2;
        int quotient = n / 2;

        strcpy(retour,toBinaire(quotient));
        strcat(retour,toBinaire(modulo));
    }

    return retour;
}

char* add0(char* bin, int size){

    // Chaine finale comportant tous les 0 en tête du nombre binaire
    char* ch0 = malloc(sizeof(char)*40);
    // On ajoute le caractère de fin de chaine au nombre binaire
    strcat(bin,"\0");
    // On copie la chaine vide dans la chaine de retour
    strcpy(ch0,"");

    int i=0;
    // On boucle pour obtenir la taille du nombre binaire
    while (bin[i] != '\0'){
        i++;
    }

    int j;
    // On ajoute le nombre de 0 manquant, en tête de la chaine
    for (j=i;j<size;j++)
        strcat(ch0,"0");

    // On ajoute les 0 en tête du nombre binaire
    strcat(ch0,bin);
    return ch0;
}

void add(short int* source, int* dest, int* SR){
    *dest = *dest + *source;
    // On retourne le résultat pour le stocker dans le registre SR
    *SR = *dest;
}

void sub(short int* source, int* dest, int* SR){
    *dest = *dest - *source;
    // On retourne le résultat pour le stocker dans le registre SR
    *SR = *dest;
}


