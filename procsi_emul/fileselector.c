#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <menu.h>
#include <stdlib.h>
#include <sys/types.h>


char ** list_file(char * folder, int* nb_result){
    
    struct dirent *lecture;
    DIR *rep;
    char relativFolder[(strlen(folder)+2)];
    int nbFolder = 0;
    int cpt=0;
    char **listeRep=NULL;
    
    //int err;
    //regex_t preg;
    //const char *str_regex = "[:alnum:]/[:alnum:]"; //savoir si c'est un sous dossier ou non
    //int match;
    
    //err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
    
    //match = regexec (&preg, folder, 0, NULL, 0);
    //pour ne rajouter le ./ que la première fois
    //if(match != 0){
    //    mvprintw(LINES-3, 20, "oui");
        strcpy(relativFolder, "./");
    //}
   
    
    strcat(relativFolder,folder);
    
     mvprintw(LINES-3, 0, "%s  %i", relativFolder, strlen(folder));
    rep = opendir(relativFolder);
    if(rep != 0){
        while ((lecture = readdir(rep))) {
            nbFolder++;
        }
    }
    
   listeRep = (char**) malloc (nbFolder* sizeof(char*));
   closedir(rep);
    
    rep = opendir(relativFolder);
    cpt=0;
    char rep_point[]= ".";
        if(rep != 0){
            while ((lecture = readdir(rep))) {
                listeRep[cpt] = malloc(strlen(lecture->d_name) * sizeof(char));
                if(strcmp(lecture->d_name, rep_point) != 0){ 
                        //on vire le fichier " . "
                        strcpy(listeRep[cpt], lecture->d_name);
                        cpt++;
                        //printf("%s\n", lecture->d_name);
                        //printf("%i %s\n",cpt,  listeRep[cpt]);
                }
                
            }
        }
        
    
    closedir(rep);
    *nb_result = cpt; 
    tri_iteratif(listeRep, *nb_result);
    return listeRep;
    
}