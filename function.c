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


