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

/**
 * \fn void stateRegister(int* reg, int PC, int SP, int SR)
 * \brief Affiche l'état des registre, utilisé pour tester avant l'utilisation de ncurses.
 *
 * \param reg Tableau contenant les registres.
 * \param PC registre PC
 * \param SP registre SP
 * \param SR registre SR
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
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

/**
 * \fn char* toHexa(int n)
 * \brief Convertie un entier en Hexadecimal (sous forme de String)
 *
 * \param n l'entier à convertire.
 * \return Une chaine contenant l'entier donnée convertie en hexa (inutile puisque sprintf permet déjà de le faire --> a supprimer dans une version future)
 */
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

/**
 * \fn char* toBinaire(int n)
 * \brief Convertie un entier en binaire (sous forme de String)
 *
 * \param n l'entier à convertire.
 * \return Une chaine contenant l'entier donnée convertie en binaire (inutile puisque sprintf permet déjà de le faire --> a supprimer dans une version future)
 */
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

/**
 * \fn char* add0(char* bin, int size)
 * \brief Ajoute des 0 en tête d'une chaine
 *
 * \param bin Chaine contenant un nombre binaire
 * \param taille de la chaine finale (après rajout des 0)
 * \return Une chaine contenant un binaire de taille size (inutile puisque sprintf permet déjà de le faire --> a supprimer dans une version future)
 */
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

/**
 * \fn void add(int* source, int* dest, int* SR)
 * \brief Fonction add de l'émulateur ASM (dest = dest + source).
 *
 * \param source Valeur de l'opérande source.
 * \param dest Valeur de l'opérande de destination
 * \param adresse du Status Register
 */
void add( int* source, int* dest, int* SR){
    *dest = *dest + *source;
    // On retourne le résultat pour le stocker dans le registre SR
    *SR = *dest;
}

/**
 * \fn void sub(int* source, int* dest, int* SR)
 * \brief Fonction sub de l'émulateur ASM (dest = dest - source).
 *
 * \param source Valeur de l'opérande source.
 * \param dest Valeur de l'opérande de destination
 * \param adresse du Status Register
 */
void sub( int* source, int* dest, int* SR){
    *dest = *dest - *source;
    // On retourne le résultat pour le stocker dans le registre SR
    *SR = *dest;
}


