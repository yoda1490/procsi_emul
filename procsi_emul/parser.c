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
    const char *operateur_add_regex = "^[ \t]*ADD";
    err = regcomp (&preg_add, operateur_add_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_sub;
    const char *operateur_sub_regex = "^[ \t]*SUB";
    err = regcomp (&preg_sub, operateur_sub_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_load;
    const char *operateur_load_regex = "^[ \t]*LOAD";
    err = regcomp (&preg_load, operateur_load_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_store;
    const char *operateur_store_regex = "^[ \t]*STORE";
    err = regcomp (&preg_store, operateur_store_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_jmp;
    const char *operateur_jmp_regex = "^[ \t]*JMP";
    err = regcomp (&preg_jmp, operateur_jmp_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_jeq;
    const char *operateur_jeq_regex = "^[ \t]*JEQ";
    err = regcomp (&preg_jeq, operateur_jeq_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_call;
    const char *operateur_call_regex = "^[ \t]*CALL";
    err = regcomp (&preg_call, operateur_call_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_ret;
    const char *operateur_ret_regex = "^[ \t]*RET[ \t]*$"; //n'a aucune opérande donc régex unique pour lui
    err = regcomp (&preg_ret, operateur_ret_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_push;
    const char *operateur_push_regex = "^[ \t]*PUSH";
    err = regcomp (&preg_push, operateur_push_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_pop;
    const char *operateur_pop_regex = "^[ \t]*POP";
    err = regcomp (&preg_pop, operateur_pop_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_halt;
    const char *operateur_halt_regex = "^[ \t]*HALT[ \t]*$"; //même commentaire que pour RET
    err = regcomp (&preg_halt, operateur_halt_regex, REG_NOSUB | REG_EXTENDED);
    
    regex_t preg_regreg;
    const char *operateur_regreg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R[0-7][ \t]*,[ \t]*R[0-7][ \t]*\n$";
    err = regcomp (&preg_regreg, operateur_regreg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_dirreg;
    const char *operateur_dirreg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[[2-3][0-9]{1,3}\\][ \t]*,[ \t]*R[0-7][ \t]*\n$"; 
    err = regcomp (&preg_dirreg, operateur_dirreg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_indreg;
    const char *operateur_indreg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[R[0-7]\\][ \t]*,[ \t]*R[0-7][ \t]*\n$";
    err = regcomp (&preg_indreg, operateur_indreg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_regimm;
    const char *operateur_regimm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R[0-7][ \t]*,[ \t]*#[1-9][0-9]{0,5}[ \t]*\n$";
    err = regcomp (&preg_regimm, operateur_regimm_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_dirimm;
    const char *operateur_dirimm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[[2-3][0-9]{1,3}\\][ \t]*,[ \t]*#[1-9][0-9]{0,5}[ \t]*\n$";
    err = regcomp (&preg_dirimm, operateur_dirimm_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_indimm;
    const char *operateur_indimm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[R[0-7]\\][ \t]*,[ \t]*#[1-9][0-9]{0,5}[ \t]*\n$";
    err = regcomp (&preg_indimm, operateur_indimm_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_regdir;
    const char *operateur_regdir_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R[0-7][ \t]*,[ \t]*\\[[2-3][0-9]{1,3}\\][ \t]*\n$";
    err = regcomp (&preg_regdir, operateur_regdir_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_regind;
    const char *operateur_regind_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R[0-7][ \t]*,[ \t]*\\[R[0-7]\\][ \t]*\n$";
    err = regcomp (&preg_regind, operateur_regind_regex, REG_NOSUB | REG_EXTENDED);
    
    
    //opérande unique pour JMP JEQ CALL PUSH POP
    regex_t preg_reg;
    const char *operateur_reg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R[0-7][ \t]*\n$";
    err = regcomp (&preg_reg, operateur_reg_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_dir;
    const char *operateur_dir_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[[2-3][0-9]{1,3}\\][ \t]*\n$";
    err = regcomp (&preg_dir, operateur_dir_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_ind;
    const char *operateur_ind_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[R[0-7]\\][ \t]*\n$";
    err = regcomp (&preg_ind, operateur_ind_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_imm;
    const char *operateur_imm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+#[1-9][0-9]{0,5}[ \t]*\n$";
    err = regcomp (&preg_imm, operateur_imm_regex, REG_NOSUB | REG_EXTENDED);
    
    //pour RET et HALT qui n'ont aucune opérande, la regex total est faite dans la première partie (dans la regex pour RET et HALP
    
    
    
    nb_instruction = 0;
   if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            //pour les ADD
            if (regexec (&preg_add, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("ADD");
                        if(regexec (&preg_regreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGREG");
                        
                        }else if(regexec (&preg_regimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIMM");
                        
                        }else if(regexec (&preg_regdir, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGDIR");
                        
                        }else if(regexec (&preg_regind, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIND");
                        
                        }
            //pour les SUB
            }else if (regexec (&preg_sub, chaine, 0, NULL, 0) != REG_NOMATCH) {
                        printf ("SUB");
                        if(regexec (&preg_regreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGREG");
                        
                        }else if(regexec (&preg_regimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIMM");
                        
                        }else if(regexec (&preg_regdir, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGDIR");
                        
                        }else if(regexec (&preg_regind, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIND");
                        
                        }
                        
            //pour les LOAD            
            }else if (regexec (&preg_load, chaine, 0, NULL, 0) != REG_NOMATCH)
                 {
                        printf ("LOAD");
                        if(regexec (&preg_regimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIMM");
                        
                        }else if(regexec (&preg_regdir, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGDIR");
                        
                        }else if(regexec (&preg_regind, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" REGIND");
                        }
                        
            
            //pour les STORE
        }else if (regexec (&preg_store, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("STORE");
                        if(regexec (&preg_dirreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" DIRREG");
                        
                        } else if(regexec (&preg_dirimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" DIRIMM");
                        
                        } else if(regexec (&preg_indreg, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" INDREG");
                        
                        } else if(regexec (&preg_indimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" INDIMM");
                        }
            
        }else if (regexec (&preg_jmp, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("JMP");
                        if(regexec (&preg_regimm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf ("IMM");
                        
                        } 
            
        }else if (regexec (&preg_jeq, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("JEQ");
                        if(regexec (&preg_imm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" IMM");
                        
                        } 
            
        }else if (regexec (&preg_call, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("CALL");
                        if(regexec (&preg_imm, chaine, 0, NULL, 0) != REG_NOMATCH){
                            printf (" IMM");
                        
                        } 
            
        }else if (regexec (&preg_ret, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("RET");
                        
            
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
