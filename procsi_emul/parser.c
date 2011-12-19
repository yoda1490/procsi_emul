#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>


#include "fonction.h"


#define TAILLE_MAX 1000
#define MAX_INSTRUCTION 1999

mot * parse(char * file, int * nb_instruction){
    FILE* fichier = NULL;
    int caractereActuel = 0;
    char chaine[TAILLE_MAX] = "";
    fichier = fopen(file, "r");
 
    int err;
    
    int match;
    regex_t preg_add;
    const char *operateur_add_regex = "^ADD";
    err = regcomp (&preg_add, operateur_add_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_sub;
    const char *operateur_sub_regex = "^SUB";
    err = regcomp (&preg_sub, operateur_sub_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_load;
    const char *operateur_load_regex = "^LOAD";
    err = regcomp (&preg_load, operateur_load_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_store;
    const char *operateur_store_regex = "^STORE";
    err = regcomp (&preg_store, operateur_store_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_jmp;
    const char *operateur_jmp_regex = "^JMP";
    err = regcomp (&preg_jmp, operateur_jmp_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_jeq;
    const char *operateur_jeq_regex = "^JEQ";
    err = regcomp (&preg_jeq, operateur_jeq_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_call;
    const char *operateur_call_regex = "^CALL";
    err = regcomp (&preg_call, operateur_call_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_ret;
    const char *operateur_ret_regex = "^RET";
    err = regcomp (&preg_ret, operateur_ret_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_push;
    const char *operateur_push_regex = "^PUSH";
    err = regcomp (&preg_push, operateur_push_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_pop;
    const char *operateur_pop_regex = "^POP";
    err = regcomp (&preg_pop, operateur_pop_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_halt;
    const char *operateur_halt_regex = "^HALT";
    err = regcomp (&preg_halt, operateur_halt_regex, REG_NOSUB | REG_EXTENDED);
    
    regex_t preg_regreg;
    const char *operateur_regreg_regex = "^([A-Z]{3,5})(.+)R[0-7],R[0-7]";
    err = regcomp (&preg_regreg, operateur_regreg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_dirreg;
    const char *operateur_dirreg_regex = "^([A-Z]{3,5})(.+)R[0-7],\[[2-3][0-9]{1,3}"; //impossible d'utiliser \] ... va savoir pourquoi
    err = regcomp (&preg_dirreg, operateur_dirreg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_indreg;
    const char *operateur_indreg_regex = "^([A-Z]{3,5})(.+)R[0-7],\[R[0-7]";
    err = regcomp (&preg_indreg, operateur_indreg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_regimm;
    const char *operateur_regimm_regex = "^([A-Z]{3,5})(.+)[1-9][0-9]{0,5},R[0-7]";
    err = regcomp (&preg_regimm, operateur_regimm_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_dirimm;
    const char *operateur_dirimm_regex = "^([A-Z]{3,5})(.+)[1-9][0-9]{0,5},\[[2-3][0-9]{1,3}";
    err = regcomp (&preg_dirimm, operateur_dirimm_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_indimm;
    const char *operateur_indimm_regex = "^HALT";
    err = regcomp (&preg_halt, operateur_halt_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_regdir;
    const char *operateur_regdir_regex = "^HALT";
    err = regcomp (&preg_halt, operateur_halt_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_regind;
    const char *operateur_regind_regex = "^HALT";
    err = regcomp (&preg_halt, operateur_halt_regex, REG_NOSUB | REG_EXTENDED);
    
    
    
    nb_instruction = 0;
   if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            
            if (regexec (&preg_add, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("ADD");
                        if(regexec (&preg_regreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGREG");
                        
                        }
            }else if (regexec (&preg_sub, chaine, 0, NULL, 0) != REG_NOMATCH) {
                        printf ("SUB");
                        
                        
            }else if (regexec (&preg_store, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("STORE");
                        if(regexec (&preg_dirreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" DIRREG");
                        } else if(regexec (&preg_indreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" INDREG");
                        } else if(regexec (&preg_dirimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" DIRIMM");
                        }
                        
                        
            }else if (regexec (&preg_load, chaine, 0, NULL, 0) != REG_NOMATCH)
                 {
                        printf ("LOAD");
                        if(regexec (&preg_regimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIMM");
                        }
            }
            
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
            nb_instruction ++;
        }
 
        fclose(fichier);
    }
    else{
        *nb_instruction = -1;
    }
 
    //return 0;
}

int main(int argc, char *argv[])
{
    int nb_instr; 
    parse("example.asm", &nb_instr);
    
    if(nb_instr == -1){
        printf("Erreur lors de l'ouverture du fichier");
    }
}
