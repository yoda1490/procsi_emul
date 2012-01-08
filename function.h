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

#define TAILLE_MEM 4501

#define ADR_INSTR_MIN 0
#define ADR_INSTR_MAX 1999
#define ADR_DONNEE_MIN 2000
#define ADR_DONNEE_MAX 3999
#define ADR_PILE_MIN 4500 // Le sommet de la pile croît vers les adresses inférieur (dans le sujet de Lippi)
#define ADR_PILE_MAX 4000


/**
    * \union mot
    * \brief Mot en mémoire.
    *
    * Représentation d'un mot en mémoire.
    *
    */
typedef union
{
    int brut; /*!< Valeur brut (16 bits). Utile pour des instructions sur plusieurs mots.*/
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
   //BRUT,
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
}
mnemonique;

typedef enum
{
   M_MENU,    /*!< Mode menu. */
   M_EXEC,   /*!< Mode exécution d'un programme. */
}
mode_window;


//mémoire du programme
mot mem_prog[TAILLE_MEM];
// registres généraux
int reg[8];
// registres spécialisés
int sp, PC, SR;

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


#endif
