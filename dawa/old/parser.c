#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

#include "function.h"
#include "parser.h"


#define TAILLE_MAX 1000
#define MAX_INSTRUCTION 1999


mot * parse(char * file, int * nb_instruction){
    FILE* fichier = NULL;
    int caractereActuel = 0;
    char chaine[TAILLE_MAX] = "";
    fichier = fopen(file, "r");
    mot* tab_mot = malloc(sizeof(mot)*MAX_INSTRUCTION); //pour une gestion plus simplifier on déclare un tableau de 1999, comme sa pas d'erreur de segmentation si le codeur ASM accès des des zones non déclaré ...
    
    mot mot_temp; //mot temporaire que l'on va placer dans tab_mot
    
    
    int err; //erreur de regex ... les erreurs ne sont pas testé ici car on suppose toutes les regex valide
    int inutil = 0; //est incrémenté à chaque ligne du fichier qui ne sert à rienn (commentaire ou ligne vide) pour pouvoir retourner la ligne de l'erreur
    
    //pour récupéré source et dest
    size_t nmatch = 0;
    regmatch_t pmatch[nmatch];
      
    
    
    
    
    
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
    const char *operateur_ret_regex = "^[ \t]*RET[ \t]*\n$"; //n'a aucune opérande donc régex unique pour lui
    err = regcomp (&preg_ret, operateur_ret_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_push;
    const char *operateur_push_regex = "^[ \t]*PUSH";
    err = regcomp (&preg_push, operateur_push_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_pop;
    const char *operateur_pop_regex = "^[ \t]*POP";
    err = regcomp (&preg_pop, operateur_pop_regex, REG_NOSUB | REG_EXTENDED);
    regex_t preg_halt;
    const char *operateur_halt_regex = "^[ \t]*HALT[ \t]*\n$"; //même commentaire que pour RET
    err = regcomp (&preg_halt, operateur_halt_regex, REG_NOSUB | REG_EXTENDED);
    
     //pour les lignes vide et de commentaire
    regex_t preg_empty;
    const char *operateur_empty_regex = "^[ \t]*(//(.+))*(#(.+))*\n$"; //même commentaire que pour RET
    err = regcomp (&preg_empty, operateur_empty_regex, REG_NOSUB | REG_EXTENDED);
    
    
    
    regex_t preg_regreg;
    const char *operateur_regreg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R([0-7])[ \t]*,[ \t]*R([0-7])([ \t])*\n$";
    err = regcomp (&preg_regreg, operateur_regreg_regex,  REG_EXTENDED);
    regex_t preg_dirreg;
    const char *operateur_dirreg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[([2-3][0-9]{1,3})\\][ \t]*,[ \t]*R([0-7])([ \t])*\n$"; 
    err = regcomp (&preg_dirreg, operateur_dirreg_regex,  REG_EXTENDED);
    regex_t preg_indreg;
    const char *operateur_indreg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[R([0-7])\\][ \t]*,[ \t]*R([0-7])([ \t])*\n$";
    err = regcomp (&preg_indreg, operateur_indreg_regex,  REG_EXTENDED);
    regex_t preg_regimm;
    const char *operateur_regimm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R([0-7])[ \t]*,[ \t]*#([1-9][0-9]{0,5})([ \t])*\n$";
    err = regcomp (&preg_regimm, operateur_regimm_regex,  REG_EXTENDED);
    regex_t preg_dirimm;
    const char *operateur_dirimm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[([2-3][0-9]{1,3})\\][ \t]*,[ \t]*#([1-9][0-9]{0,5})([ \t])*\n$";
    err = regcomp (&preg_dirimm, operateur_dirimm_regex,  REG_EXTENDED);
    regex_t preg_indimm;
    const char *operateur_indimm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[R([0-7])\\][ \t]*,[ \t]*#([1-9][0-9]{0,5})([ \t])*\n$";
    err = regcomp (&preg_indimm, operateur_indimm_regex,  REG_EXTENDED);
    regex_t preg_regdir;
    const char *operateur_regdir_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R([0-7])[ \t]*,[ \t]*\\[([2-3][0-9]{1,3})\\]([ \t])*\n$";
    err = regcomp (&preg_regdir, operateur_regdir_regex,  REG_EXTENDED);
    regex_t preg_regind;
    const char *operateur_regind_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R([0-7])[ \t]*,[ \t]*\\[R([0-7])\\]([ \t])*\n$";
    err = regcomp (&preg_regind, operateur_regind_regex,  REG_EXTENDED);
    
    
    //opérande unique pour JMP JEQ CALL PUSH POP
    //certaines parenthèses son "en trop" cela permet d'utiliser les mêmes fonctions de récupération d'opérande d'au dessus
    regex_t preg_reg;
    const char *operateur_reg_regex = "^[ \t]*([A-Z]{3,5})[ \t]+R([0-7])([ \t])*\n$";
    err = regcomp (&preg_reg, operateur_reg_regex,  REG_EXTENDED);
    regex_t preg_dir;
    const char *operateur_dir_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[([2-3][0-9]{1,3})\\]([ \t])*\n$";
    err = regcomp (&preg_dir, operateur_dir_regex,  REG_EXTENDED);
    regex_t preg_ind;
    const char *operateur_ind_regex = "^[ \t]*([A-Z]{3,5})[ \t]+\\[R([0-7])\\]([ \t])*\n$";
    err = regcomp (&preg_ind, operateur_ind_regex,  REG_EXTENDED);
    regex_t preg_imm;
    const char *operateur_imm_regex = "^[ \t]*([A-Z]{3,5})[ \t]+#([1-9][0-9]{0,5})([ \t])*\n$";
    err = regcomp (&preg_imm, operateur_imm_regex,  REG_EXTENDED);
    
    //pour RET et HALT qui n'ont aucune opérande, la regex total est faite dans la première partie (dans la regex pour RET et HALP
   
    
   //suite pour récupérer les opérandes
   nmatch = preg_regreg.re_nsub;
   
    
    *nb_instruction = 0;
   if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            *nb_instruction += 1; //ne pas oublier d'incrementer le nombre d'instruction 
            //printf("%i", *nb_instruction);
            
           char * source[1];
           char * dest[1] ;
            
            //pour les ADD
            if (regexec (&preg_add, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("ADD");
                        
                        if(regexec (&preg_regreg, chaine, nmatch, pmatch, 0) != REG_NOMATCH){ 
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(ADD, REGREG, atoi(*source), atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            //mot save_brut(int brut, int * nb_instr)
                            
                            printf (" REGREG %i %i", tab_mot[*nb_instruction-1].codage.source, tab_mot[*nb_instruction-1].codage.dest);
                        
                        }else if(regexec (&preg_regimm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(ADD, REGIMM, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" REGIMM %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        
                        }else if(regexec (&preg_regdir, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(ADD, REGDIR, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" REGDIR %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        
                        }else if(regexec (&preg_regind, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(ADD, REGIND, atoi(*source), atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            //mot save_brut(int brut, int * nb_instr)
                            
                            printf (" REGIND %i %i", tab_mot[*nb_instruction-1].codage.source, tab_mot[*nb_instruction-1].codage.dest);
                        
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
            //pour les SUB
            }else if (regexec (&preg_sub, chaine, 0, NULL, 0) != REG_NOMATCH) {
                        printf ("SUB");
                        if(regexec (&preg_regreg, chaine, nmatch, pmatch, 0) != REG_NOMATCH){ 
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(SUB, REGREG, atoi(*source), atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            //mot save_brut(int brut, int * nb_instr)
                            
                            printf (" REGREG %i %i", tab_mot[*nb_instruction-1].codage.source, tab_mot[*nb_instruction-1].codage.dest);
                        
                        }else if(regexec (&preg_regimm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(SUB, REGIMM, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" REGIMM %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        
                        }else if(regexec (&preg_regdir, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(SUB, REGDIR, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" REGDIR %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        
                        }else if(regexec (&preg_regind, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(SUB, REGIND, atoi(*source), atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            //mot save_brut(int brut, int * nb_instr)
                            
                            printf (" REGIND %i %i", tab_mot[*nb_instruction-1].codage.source, tab_mot[*nb_instruction-1].codage.dest);
                        
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
                        
            //pour les LOAD            
            }else if (regexec (&preg_load, chaine, 0, NULL, 0) != REG_NOMATCH)
                 {
                        printf ("LOAD");
                        if(regexec (&preg_regimm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(LOAD, REGIMM, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" REGIMM %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        
                        }else if(regexec (&preg_regdir, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(LOAD, REGDIR, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" REGDIR %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        
                        }else if(regexec (&preg_regind, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(LOAD, REGIND, atoi(*source), atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            //mot save_brut(int brut, int * nb_instr)
                            
                            printf (" REGIND %i %i", tab_mot[*nb_instruction-1].codage.source, tab_mot[*nb_instruction-1].codage.dest);
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
                        
            
            //pour les STORE
        }else if (regexec (&preg_store, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("STORE");
                        if(regexec (&preg_dirreg, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(STORE, DIRREG, atoi(*source), 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            
                            printf (" DIRREG %i %i", tab_mot[*nb_instruction-2].codage.source, tab_mot[*nb_instruction-1].brut);
                        
                        } else if(regexec (&preg_dirimm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(STORE, DIRIMM, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" DIRIMM %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].brut);
                        
                        } else if(regexec (&preg_indreg, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(STORE, INDREG, atoi(*source), atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            //mot save_brut(int brut, int * nb_instr)
                            
                            printf (" INDREG %i %i", tab_mot[*nb_instruction-1].codage.source, tab_mot[*nb_instruction-1].codage.dest);
                        
                        } else if(regexec (&preg_indimm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            tab_mot[*nb_instruction-1] = save_mot(STORE, INDIMM, 0, atoi(*dest)) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*source));
                            
                            printf (" DIRREG %i %i", tab_mot[*nb_instruction-1].brut, tab_mot[*nb_instruction-2].codage.dest);
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
        //pour les JMP    
        }else if (regexec (&preg_jmp, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("JMP");
                        if(regexec (&preg_imm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            //INDIMM car le IMM n'existe pas ni le IMMIMM
                            tab_mot[*nb_instruction-1] = save_mot(JMP, INDIMM, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            
                            printf (" IMM %i", tab_mot[*nb_instruction-1].brut);
                        
                        }  else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
        //pour les JEQ    
        }else if (regexec (&preg_jeq, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("JEQ");
                        if(regexec (&preg_imm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            //INDIMM car le IMM n'existe pas ni le IMMIMM
                            tab_mot[*nb_instruction-1] = save_mot(JEQ, INDIMM, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            
                            printf (" IMM %i", tab_mot[*nb_instruction-1].brut);
                        
                        }  else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
        //pour les CALL    
        }else if (regexec (&preg_call, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("CALL");
                        if(regexec (&preg_imm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            //INDIMM car le IMM n'existe pas ni le IMMIMM
                            tab_mot[*nb_instruction-1] = save_mot(CALL, INDIMM, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            
                            printf (" IMM %i", tab_mot[*nb_instruction-1].brut);
                        
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
        //pour les RET    
        }else if (regexec (&preg_ret, chaine, 0, NULL, 0) != REG_NOMATCH){
                        tab_mot[*nb_instruction-1] = save_mot(RET, INDIMM, 0, 0) ;
                        printf ("RET");
                        
        //pour les PUSH
        }else if (regexec (&preg_push, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("PUSH");
                        if(regexec (&preg_reg, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                             get_operandes(chaine, pmatch, source, dest);
                            //REGREG car le REG n'existe pas
                            tab_mot[*nb_instruction-1] = save_mot(PUSH, REGREG, atoi(*dest), 0) ;
                            printf (" REG %i", tab_mot[*nb_instruction-1].codage.source);
                        
                        } else if(regexec (&preg_imm, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            //INDIMM car le IMM n'existe pas ni le IMMIMM
                            tab_mot[*nb_instruction-1] = save_mot(PUSH, INDIMM, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            
                            printf (" IMM %i", tab_mot[*nb_instruction-1].brut);
                        
                        } else if(regexec (&preg_dir, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            //REGDIR car le DIR n'existe pas ni le DIRDIR
                            tab_mot[*nb_instruction-1] = save_mot(PUSH, REGDIR, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));
                            
                            printf (" DIR %i", tab_mot[*nb_instruction-1].brut);
                        
                        } else if(regexec (&preg_ind, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            //REGIND seul mode dispo pour indiqué que c'est IND
                            tab_mot[*nb_instruction-1] = save_mot(PUSH, REGIND, atoi(*dest), 0) ;
                            printf (" IND %i", tab_mot[*nb_instruction-1].codage.source);
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
        //pour les pop
        
        }else if (regexec (&preg_pop, chaine, nmatch, NULL, 0) != REG_NOMATCH){
                        printf ("POP");
                        
                        
                        if(regexec (&preg_reg, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                             get_operandes(chaine, pmatch, source, dest);
                            //REGREG car le REG n'existe pas
                            tab_mot[*nb_instruction-1] = save_mot(POP, REGREG, atoi(*dest), 0) ;
                            printf (" REG %i", tab_mot[*nb_instruction-1].codage.source);
                        
                        } else if(regexec (&preg_dir, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                            get_operandes(chaine, pmatch, source, dest);
                            
                            tab_mot[*nb_instruction-1] = save_mot(POP, REGDIR, 0, 0) ; //-1 car un tableau commence a 0 et ici nous incrémentons avant cette operation
                            *nb_instruction += 1;
                            tab_mot[*nb_instruction-1] = save_brut(atoi(*dest));

			    printf (" DIR %i", tab_mot[*nb_instruction-1].brut);
                        
                        } else if(regexec (&preg_ind, chaine, nmatch, pmatch, 0) != REG_NOMATCH){
                             get_operandes(chaine, pmatch, source, dest);
                            
                            tab_mot[*nb_instruction-1] = save_mot(POP, REGIND, atoi(*dest), 0) ;
                            printf (" IND %i", tab_mot[*nb_instruction-1].codage.source);
                        
                        } else{
                            *nb_instruction += 2000 + inutil;
                            return NULL;
                        }
         //HALT fin du code asm donc on quitte  
        }else if (regexec (&preg_halt, chaine, 0, NULL, 0) != REG_NOMATCH){
                        printf ("HALT");
                        //fclose(fichier);
                        return tab_mot; //a completer !!!
                        
            
            }else if (regexec (&preg_empty, chaine, 0, NULL, 0) != REG_NOMATCH){
                        //ligne vide ou de commentaire
                inutil += 1; //on l'incrémente pour renvoyer la ligne de l'erreur
                *nb_instruction -= 1; //in le s'agit pas d'une instruction donc on décrémente ce qu'on avait incémenté plus haut
                printf("Vide ou commentaire");

            } else{
                            *nb_instruction += 4000 + inutil;
                            return NULL;
                        }
        
        
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
            
            
           
            
            
        }
        
       
        *nb_instruction = -2;
    }
    else{
        *nb_instruction = -1;
    }
    
     fclose(fichier);
 
    //return 0;
}

void get_operandes(char * chaine, regmatch_t *pmatch, char ** source, char ** dest){ 
    //on récupère l'operande destination on la fou dans dest_temp et on donne l'adresse de dest_temp à dest 
    int start = pmatch[2].rm_so;
    int end = pmatch[2].rm_eo;
    size_t size = end - start;
    char * dest_temp = malloc ((size + 1) * sizeof(char));
    if (dest_temp)
       {
        
      strncpy (dest_temp, &chaine[start], size);
      
      dest_temp[size] = '\0';
       //printf ("non %c non\n", dest[size-1]);
      *dest = dest_temp;
       //printf ("\nAZERTY %s %s QWERTY\n", *dest, dest_temp);
       }
    
    //même chose pour l'operande destination
    start = pmatch[3].rm_so;
    end = pmatch[3].rm_eo;
    size = end - start;
    char * source_temp = malloc ((size + 1) * sizeof(char));
    if (source_temp)
       {
        
      strncpy (source_temp, &chaine[start], size);
      
      source_temp[size] = '\0';
       //printf ("non %c non\n", dest[size-1]);
      *source = source_temp;
       //printf ("\nAZERTY %s %s QWERTY\n", *source, dest_temp);
       }
}

mot save_mot(mnemonique operateur, mode le_mode, int source, int dest){
     mot mot_temp;
     mot_temp.brut = 0;
     mot_temp.codage.codeop = operateur;
     mot_temp.codage.mode = le_mode;
     mot_temp.codage.source = source;
     mot_temp.codage.dest = dest;
     return mot_temp;
}

mot save_brut(int brut){
     mot mot_temp;
     mot_temp.brut = brut;
     return mot_temp;
    
}

int main(int argc, char *argv[])
{
    int nb_instr = 0; 
    parse("example.asm", &nb_instr);
    
    
    if(nb_instr == -1){
        printf("\nErreur lors de l'ouverture du fichier\n");
    }else if(nb_instr == -2){
        printf("\nInstruction HALT en fin de fichier non trouvé\n");
    }else if(nb_instr > 2000 && nb_instr <= 4000){
        printf("\nErreur: mode d'adressage non disponible pour l'opérateur ligne %i\n", nb_instr-2000);
    }else if(nb_instr > 4000 && nb_instr <= 6000){
        printf("\nErreur: opérateur inconnue ligne %i\n", nb_instr-4000);
    }
}