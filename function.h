/**
 * \file function.h
 * \brief Fichier d'entête.
 * \author Lucas.C
 * \version 1.0
 * \date 18 décembre 2011
 *
 * Fichier d'entête comportant les méthodes et structure nécessaires à la simulation du PROCSI C.
 *
 */

#ifndef FUNCTION_H
#define FUNCTION_H

/**
    * \union mot
    * \brief Mot en mémoire.
    *
    * Représentation d'un mot en mémoire.
    *
    */
typedef union
{
    short brut; /*!< Valeur brut (16 bits). Utile pour des instructions sur plusieurs mots.*/
    /**
    * \struct codage
    * \brief Codage d'un mot sur 16 bits.
    *
    * Codage d'un mot sur 16 bits.
    *
    */
    struct
    {
        unsigned codeop : 6; /*!< Code opération (6 bits). */
        unsigned mode : 4;   /*!< Mode d'adressage (4 bits). */
        unsigned source : 3; /*!< Opérande source (3 bits). */
        unsigned dest : 3;   /*!< Opérande destination (3 bits). */
    }codage;    /*!< Codage d'un mot en mémoire (16 bits). */
}mot;

/**
 * \enum mode
 * \brief Constantes de mode d'adressage.
 *
 * mode est une série de constantes représentant les différents mode d'adressage.
 */
typedef enum
{
   REGREG,    /*!< Mode registre/registre. */
   DIRREG,    /*!< Mode direct/registre. */
   INDREG,    /*!< Mode indirect/registre. */
   REGIMM,    /*!< Mode registre/immédiat. */
   DIRIMM,    /*!< Mode direct/immédiat. */
   INDIMM,    /*!< Mode indirect/immédiat. */
   REGDIR,    /*!< Mode registre/direct. */
   REGIND,    /*!< Mode registre/indirect. */
   ERROR      /*!< Erreur dans le mode d'adressage. */
}
mode;

/**
 * \enum mnemonique
 * \brief Constantes des mnémoniques.
 *
 * mnemonique est une série de constantes représentant les différentes mnémoniques.
 */
typedef enum
{
   LOAD,    /*!< Instruction LOAD. */
   STORE,   /*!< Instruction STORE. */
   ADD,     /*!< Instruction ADD. */
   SUB,     /*!< Instruction SUB. */
   JMP,     /*!< Instruction JMP. */
   JEQ,     /*!< Instruction JEQ. */
   CALL,    /*!< Instruction CALL. */
   RET,     /*!< Instruction RET. */
   PUSH,    /*!< Instruction PUSH. */
   POP,     /*!< Instruction POP. */
   HALT,     /*!< Instruction HALT. */
   UNKOWN   /*!< Instruction inconnue. */
}
mnemonique;

/**
 * \fn void add(int* source, int* dest)
 * \brief Fonction ajoutant l'opérande source à l'opérande dest.
 * Résultat stocker dans l'opérande dest.
 * Modification du registre SR.
 *
 * \param source Opérande source.
 * \param dest Opérande destination.
 */
void add(int* source, int* dest, int* SR);

/**
 * \fn void sub(int* source, int* dest)
 * \brief Fonction soustrayant l'opérande source à l'opérande dest.
 * Résultat stocker dans l'opérande dest.
 * Modification du registre SR.
 *
 * \param source Opérande source.
 * \param dest Opérande destination.
 */
void sub(int* source, int* dest, int* SR);

/**
 * \fn char* toHexa(int n)
 * \brief Fonction de convertion d'un nombre entier en base 16.
 *
 * \param n Nombre entier à convertir.
 * \return Nombre convertit en base 16 (sans 0 inutile en tête).
 */
char* toHexa(int n);

/**
 * \fn char* toBinaire(int n)
 * \brief Fonction de convertion d'un nombre entier en base 2.
 *
 * \param n Nombre entier à convertir.
 * \return Nombre convertit en base 2 (sans 0 inutile en tête).
 */
char* toBinaire(int n);

/**
 * \fn char* add0(char* bin, int nb0)
 * \brief Fonction ajoutant un nombre prédéfini de 0 devant un nombre binaire (ou hexadécimal).
 *
 * \param bin Bombre binaire (ou hexadécimal).
 * \param size Taille du nombre binaire (ou hexadécimal) à retourner.
 * \return Nombre binaire (ou hexadécimal) ayant la taille size comportant les 0 nécessaires en tête.
 */
char* add0(char* bin, int size);

/**
 * \fn void stateRegister()
 * \brief Fonction affichant l'état des registres R0..R7 ainsi que des registres PC, SP et SR.
 *
 */
void stateRegister();

/**
 * \fn void viewMemory(int adresse, int longueur)
 * \brief Fonction affichant l'état de la mémoire à partir d'une certaine adresse.
 *
 * \param adresse Adresse mémoire de début d'affichage.
 * \param longueur Nombre d'adresse mémoire à afficher.
 */
void viewMemory(int adresse, int taille, mot* mem);


#endif