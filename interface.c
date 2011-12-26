#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <menu.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <regex.h>


#include "function.h"
#include "interface.h"
#include "parser.h"

mode_window mWindow;
WINDOW *register_win;
MENU *register_menu;
WINDOW *instructions_win;
MENU *instruction_menu;
WINDOW *memory_win;
MENU *memory_menu;
int num_adr;
ITEM * current_memory;
int current_int_memory = 2000;
int fin_prog = 0;

char *choices[] = {
                        "Ouvrir un fichier Assembleur",
                        "Lancer l'émulation d'un exemple",
                        "Exit",
                  };

int init_gui()
{	
	mWindow = M_MENU;
	WIN win;
	int ch;
        int i;
        char ** files;
	num_adr = 0;

	initscr();			/* Start curses mode 		*/
	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on */
					/* everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        

	/* Initialize the window parameters */
	init_win_params(&win);
	print_win_params(&win);

	attron(COLOR_PAIR(1));
        printw("F2: Ouvrir un fichier");
        printw("\t F3: Lancer l'émulation d'un exemple");
	printw("\t F5: Quitter");
        attron(A_BOLD);
        attron(COLOR_PAIR(2));
        char chaine[]="Welcome to ProcSI emulator";
        mvprintw((3) ,(COLS-strlen(chaine))/2,chaine);
        attroff(A_BOLD);
	refresh();
	attroff(COLOR_PAIR(1));
	
	
        draw_menu(choices, execute_main_menu, NULL, 3);
        
	
	endwin();			/* End curses mode		  */
	return 0;
}
void init_win_params(WIN *p_win)
{
	p_win->height = 3;
	p_win->width = 10;
	p_win->starty = (LINES - p_win->height)/2;	
	p_win->startx = (COLS - p_win->width)/2;

	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';

}
void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, 
				p_win->width, p_win->height);
	refresh();
#endif
}


void draw_menu(char ** menu_liste, void (*ptrfonction)(int,const char *, char *), char * folder, int taille_menu){
        ITEM **my_items;
	int c;		
        WINDOW *my_menu_win;
	MENU *my_menu;
	int i;
	ITEM *cur_item;
        my_items = (ITEM **)calloc(taille_menu + 1, sizeof(ITEM *));
        int menu_alrdy_dlt = 0; //pour ne pas supprimer le menu 2 fois -> évite les erreur de segmentation lorsqu'on quitte
        char ** files; //pour le cas ou on utilise F2 (ouvrir un fichier)
        int nb_file = 0;
        
        int num_choix;
        char choix[FILE_MAX];

	for(i = 0; i < taille_menu; ++i){
	        my_items[i] = new_item(menu_liste[i], ""); //ajoute les éléments dans mon tableau d'item
        }
	//my_items[taille_menu+1] = (ITEM *)NULL; //ajoute un item vide à la fin du tableau
        my_menu = new_menu((ITEM **)my_items); //creer un menu contenan les items
	mvprintw(LINES - 2, 0, "F9 to close the menu"); //affiche un pied de page pour fermer le menu
        
        my_menu_win = newwin(10, 45, (LINES-10)/2, (COLS-45)/2); //créer une nouvelle fenetre
        keypad(my_menu_win, TRUE); //active le clavier pour le menu
       
        
        /* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win); //set main menu
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1)); // set sub window
        set_menu_format(my_menu, 5, 1);
        
       /* Set menu mark to the string " * " */
        set_menu_mark(my_menu, " * ");
        
        /* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
        print_in_middle(my_menu_win, 1, 0, 45, "Menu Principal", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
	mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
	refresh();
        
	post_menu(my_menu);
	wrefresh(my_menu_win);
       

	while((c = getch()) != KEY_F(9) && c != 27)
	{   switch(c)
	    {	case KEY_F(5):
                        mvprintw(LINES-2, 0, "Exiting...");
                        endwin();			/* End curses mode		  */
                        exit(0);
            
                case KEY_F(2):
                    //si on est déjà entrain d'ouvir un fichier on ne fait rien
                    if(folder == NULL){
                        if(menu_alrdy_dlt == 0){
                            menu_alrdy_dlt = 1;
                            clean_menu(my_menu);
                            clean_window(my_menu_win);
                        }
                        files = list_file("", &nb_file);
                        draw_menu(files, execute_file_menu, "", nb_file);
                        return;
                    }
                        break;
            case KEY_F(3):
                        mvprintw((3) ,(COLS-30)/2, "                              ");
                        clean_menu(my_menu);
                        clean_window(my_menu_win);
                        execute_file_menu(0,"example.asm", "");
                        break;

                    
                case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(my_menu, REQ_UP_ITEM);
			break;
                case KEY_NPAGE:
			menu_driver(my_menu, REQ_SCR_DPAGE);
			break;
                case KEY_PPAGE:
			menu_driver(my_menu, REQ_SCR_UPAGE);
			break;
        
            
                case 10:

			if (mWindow == M_MENU){
		                move(20, 0);
		                mvprintw((3) ,(COLS-30)/2, "                              ");
				clrtoeol();
		                num_choix = item_index(current_item(my_menu));
		                strcpy(choix, item_name(current_item(my_menu)));
				//mvprintw(5, 0, "Item selected is : %s", item_name(current_item(my_menu)));
		                clean_menu(my_menu);
		                menu_alrdy_dlt = 1;
		                clean_window(my_menu_win);
		                (*ptrfonction)(num_choix, choix, folder);
				pos_menu_cursor(my_menu);
			}

			break;

		}
                wrefresh(my_menu_win);
	}
        if(menu_alrdy_dlt == 0){
                menu_alrdy_dlt = 1;
                clean_menu(my_menu);
                clean_window(my_menu_win);
        }
        
       
        
    
}


void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void execute_main_menu(int choice,const char * choice_name, char * folder){
    //mvprintw(9, 0, "Item selected is : %i", choice);
    
    //un case serais plus approprier ... à modifier si j'ai le temps
    if(choice == 0){
        int i;
        char ** files = list_file("", &i);
        draw_menu(files, execute_file_menu, "", i);
    }
    
    else if(choice == 1){
        execute_file_menu(0,"example.asm", "");   
    }
    
    else if(choice == 2){
        mvprintw(LINES-2, 0, "Exiting...");
        endwin();			/* End curses mode		  */
        exit(0);
    }
    
}

void execute_file_menu(int choice,const char * choice_name, char * folder){
    char file[strlen(choice_name)];
    char folder_complet[strlen(folder)+strlen(file)+1];
    

    // Remise à zéro des variables pour nettoyer avant exécution du programme
    reset();

    strcpy(file, choice_name);
    
    strcpy(folder_complet, folder);
    strcat(folder_complet, file);
    
    
    if(exists(folder_complet) == 1){
         
         mvprintw(LINES-2, 0, "                                                        ");
         mvprintw(LINES-1, 0, "%s                                                                ", folder_complet);
         int nb_instr;
         parse(folder_complet, &nb_instr);

         /* int reg[8] = {0,0,0,0, 0,0,0,0};*/
         int taille_reg = 8;
         
        attron(A_BOLD);
        attron(COLOR_PAIR(2));
        mvprintw(LINES-1, 0, "Compilation en cours ...");
        
         
        
        
         if(nb_instr == -1){
            mvprintw(LINES-3, 0, "Erreur lors de l'ouverture du fichier");
        }else if(nb_instr == -2){
            mvprintw(LINES-3, 0, "Instruction HALT en fin de fichier non trouvé");
        }else if(nb_instr > 2000 && nb_instr <= 4000){
            mvprintw(LINES-3, 0, "Erreur: mode d'adressage non disponible pour l'opérateur ligne %i", nb_instr-2000);
        }else if(nb_instr > 4000 && nb_instr <= 6000){
            mvprintw(LINES-3, 0, "Erreur: opérateur inconnue ligne %i", nb_instr-4000);
        }else{
            attroff(A_BOLD);
            attroff(COLOR_PAIR(1));
            
            
            mvprintw(LINES-1, 0, "Execution ... (Appuyez sur espace pour passer à l'instruction suivante)");
            refresh();
            
             attron(COLOR_PAIR(3));
            
             //Emulation de l'assembleur PROCSI
             exec_instr();
             mvprintw(LINES-1, 0, "Fin de l'éxecution                                                      ");
             fin_prog = 1;
             display_execution(PC, mem_prog, ADR_INSTR_MAX, reg, 8);
        }
        
        //on remet la couleur en noir
        attroff(COLOR_PAIR(1));
        
        /* refresh();
        attroff(A_BOLD);
	attroff(COLOR_PAIR(1)); */
        
    }
    else if(exists(folder_complet) == 2){
        strcat(folder_complet, "/");
        int i;
        char ** files = list_file(folder_complet, &i);
        mvprintw(LINES-1, 0, "Dossier:  %s                                                        ", folder_complet);
        draw_menu(files, execute_file_menu, folder_complet, i);
    }
    else{
        mvprintw(LINES-1, 0, "Une erreur s'est produite lors de l'ouverture du fichier. Retour à ./");
        int i;
        char ** files = list_file("", &i);
        draw_menu(files, execute_file_menu, "", i);
    }
}

void display_execution(int num_instruction, mot * tab_mot_instruction, int nb_instruction, int* registres,int nb_reg){

	// Mode Exécution d'un programme en cours => permet de désactiver la touche entrée (sinon erreur de segmentation)
	mWindow = M_EXEC;

        wrefresh(memory_win);

        ITEM *item_en_cour = NULL;

        // for instructions
        char ** tab_instruction;
        ITEM **instructions_items;
	int c;		
	int i;
	instructions_items = (ITEM **)calloc(nb_instruction + 1, sizeof(ITEM *));
        int menu_instruction_alrdy_dlt = 0; //pour ne pas supprimer le menu 2 fois --> évite les erreur de segmentation lorsqu'on quitte
        
        
        // for register
        char ** files;
        char  ** tab_register;
        ITEM **register_items;
	
	register_items = (ITEM **)calloc(nb_reg + 1 +3, sizeof(ITEM *)); //+3 pour PC sp et SR
        int menu_register_alrdy_dlt = 0; //pour ne pas supprimer le menu 2 fois --> évite les erreur de segmentation lorsqu'on quitte
        
        
        // for memory
        char memory_temp[TAILLE_MEM][50];
        ITEM ** memory_items;
	memory_items = (ITEM **)calloc(TAILLE_MEM, sizeof(ITEM *)); 
        char brut_string[2000][10];
        
        
        char pc_string[6], sp_string[6], sr_string[6];
        
        int is_brut = 0; //si le mot précedent contient un mode direct, alors le mot suivant est un brut //si DIRIMM les 2 suivant sont des brut    

        //allocation de mémoire pour les insctruction sous forme de chaine
        tab_instruction = (char**) malloc (nb_instruction* sizeof(char*));
        
        //allocation de mémoire pour le tabeau de registre sous forme de string
        tab_register = (char**) malloc (nb_reg* sizeof(char *));
        
        
        int num_choix;
	int j=0; // j permet de n'afficher que les instructions et pas les valeurs indirectes et immédiates
	i = 0;
        char * choix = NULL;

	/* AFFICHAGE INSTRUCTIONS */
         
	for(i=0; i < ADR_INSTR_MAX; i++){
            
            tab_instruction[i] = malloc(50 * sizeof(char)); //plus simple pour le moment, une instruction ne peut dépasser 50caractères ... a améliorer si assez de temps

	    if(is_brut == 0){

		strcpy(tab_instruction[j],instr_toString(tab_mot_instruction[i],tab_mot_instruction[i+1].brut,tab_mot_instruction[i+2].brut));
		instructions_items[j] = new_item(tab_instruction[j], "");
                
                //si l'instruction contient une source ou destination en mode immediat ou direct, la prochaine instruction sera un brut
                if(tab_mot_instruction[i].codage.mode == REGIMM 
			      || tab_mot_instruction[i].codage.mode == INDIMM 
			      || tab_mot_instruction[i].codage.mode == REGDIR 
			      || tab_mot_instruction[i].codage.mode ==  DIRREG){
                    is_brut = 1;
                }

                else if(tab_mot_instruction[i].codage.mode == DIRIMM){
                    is_brut = 2;
                }

		if(i == num_instruction){
                   //on sauvegarde l'adresse de l'item que l'on est entrain de traiter (celui donner par num_instruction)
                   item_en_cour = instructions_items[j];
                   //n le desactive, cela permet de lui doonner une autre apparence pur le repérer
                   item_opts_off(instructions_items[j], O_SELECTABLE);
            	}

		// On arrête l'affichage après le halt
		if (tab_mot_instruction[i].codage.codeop == HALT){
			i = ADR_INSTR_MAX; // permet de sortir de la boucle
		}

		j++;

            }

            else{
        
               if(is_brut == 2){
                   is_brut = 1; // cas du DIRIMM
               } else{
                   is_brut = 0;
               }
            }	
	
        }
        
	/* AFFICHAGE REGISTRES */

        for(i = 0; i < nb_reg; ++i){
                //contient le registre sous forme de string par exemple R1 ou PC
                tab_register[i] = malloc(3 * sizeof(char));
                
                sprintf(tab_register[i], "R%i: %d",i, registres[i]);
                
                //mvprintw(i+2, 0, "%s", tab_instruction[i]);
                register_items[i] = new_item(tab_register[i], ""); //ajoute les éléments dans mon tableau d'item
        }

        sprintf(pc_string, "%d", PC);
        sprintf(sp_string, "%d", sp);
        sprintf(sr_string, "%d", SR);
        register_items[nb_reg] = new_item("PC:", pc_string); //register_items[8]
        register_items[nb_reg+1] = new_item("SP:", sp_string); //register_items[9]
        register_items[nb_reg+2] = new_item("SR:", sr_string);  //register_items[10]
        //pour cacher la selection du premier registre
        item_opts_off(register_items[0], O_SELECTABLE);
                

	/* AFFICHAGE MEMOIRE */

	for(i = 0; i < 2000; i++){

		if(is_brut == 0){
               
			snprintf(memory_temp[i], 25, "%i: %s", i, mem_toString(i,false));
		        strncat(memory_temp[i], "\0", 1);
		        
		        //si l'instruction contient une source ou destination en mode immediat ou direct, la prochaine instruction sera un brut
		        if(tab_mot_instruction[i].codage.mode == REGIMM 
				      || tab_mot_instruction[i].codage.mode == INDIMM 
				      || tab_mot_instruction[i].codage.mode == REGDIR 
				      || tab_mot_instruction[i].codage.mode ==  DIRREG){
		            is_brut = 1;
		        }
		        if(tab_mot_instruction[i].codage.mode == DIRIMM){
		            is_brut = 2;
		        }
            }

            else{

		snprintf(memory_temp[i], 25, "%i: %s ", i, mem_toString(i,true));
                snprintf(brut_string[i], 6, "%u\0", tab_mot_instruction[i].brut);
                strncat(memory_temp[i], "\0", 1);
        
               if(is_brut == 2){
                   is_brut = 1; // cas du DIRIMM
               } else{
                   is_brut = 0;
               }
            }
                
                memory_items[i] = new_item(memory_temp[i], brut_string[i]);
                
                 if(current_int_memory == i){
                    current_memory = memory_items[i];
                }

        }
        
        //pour le reste de la mémoire
        for(i = 2000; i < 4000; ++i){
                //contient le registre sous forme de string par exemple R1 ou PC
                 //tab_memory[i] = malloc(8 * sizeof(char));
                
                
                
                snprintf(memory_temp[i], 12, "%i: %u", i, mem_prog[i].brut);
                strncat(memory_temp[i], "\0", 1);
                
                memory_items[i] = new_item(memory_temp[i], "");
                
                if(current_int_memory == i){
                    current_memory = memory_items[i];
                }

        }
        
        
        
        
	instruction_menu = new_menu((ITEM **)instructions_items); //creer un menu contenant les instructions 
        register_menu = new_menu((ITEM **)register_items); //creer un menu contenant les registres
        memory_menu = new_menu((ITEM **)memory_items); //creer un menu contenant les cases mémoire
	
        instructions_win = newwin((LINES-4)/2, 45 , 3, (COLS/2)- (COLS-4)/4); //créer une nouvelle fenetre pour les instructions
        register_win = newwin(16, 20 , 3, (COLS/2) + 10); //créer une nouvelle fenetre pour les registres
        memory_win = newwin((LINES-4)/2, 45 , 3+(LINES-4)/2, (COLS/2)- (COLS-4)/4); //créer une nouvelle fenetre pour la mémoire
        
        keypad(memory_win, TRUE); //active le clavier sur la mémoire
        
        /* Set main window and sub window */
        set_menu_win(instruction_menu, instructions_win); //set main menu
        set_menu_sub(instruction_menu, derwin(instructions_win, ((LINES-4)/2)-4, 43, 3, 1)); // set sub window
        set_menu_format(instruction_menu, ((LINES-4)/2)-4, 1);
        
        set_menu_win(register_menu, register_win); //set main menu
        set_menu_sub(register_menu, derwin(register_win, 13, 18, 3, 1)); // set sub window
        set_menu_format(register_menu, 13, 1);
        
        
        set_menu_win(memory_menu, memory_win); //set main menu
        set_menu_sub(memory_menu, derwin(memory_win, ((LINES-4)/2)-4, 43, 3, 1)); // set sub window
        set_menu_format(memory_menu, ((LINES-4)/2)-4, 1);
        
        
        
       /* Set menu mark to the string " * " */
        set_menu_mark(instruction_menu, " * ");
        set_menu_mark(register_menu, "");
        set_menu_mark(memory_menu, " --> ");
        
        
        /* Print a border around the main window and print a title */
        box(instructions_win, 0, 0);
        print_in_middle(instructions_win, 1, 0, 45, "Liste des instructions", COLOR_PAIR(1));
	mvwaddch(instructions_win, 2, 0, ACS_LTEE);
	mvwhline(instructions_win, 2, 1, ACS_HLINE, 43);
	mvwaddch(instructions_win, 2, 44, ACS_RTEE);
	refresh();
        
        box(register_win, 0, 0);
        print_in_middle(register_win, 1, 0, 20, "Registres", COLOR_PAIR(1));
	mvwaddch(register_win, 2, 0, ACS_LTEE);
	mvwhline(register_win, 2, 1, ACS_HLINE, 22);
	mvwaddch(register_win, 2, 19, ACS_RTEE);
	refresh();
        
        box(memory_win, 0, 0);
        print_in_middle(memory_win, 1, 0, 45, "Mémoire", COLOR_PAIR(1));
	mvwaddch(memory_win, 2, 0, ACS_LTEE);
	mvwhline(memory_win, 2, 1, ACS_HLINE, 43);
	mvwaddch(memory_win, 2, 44, ACS_RTEE);
	refresh();
        

	post_menu(instruction_menu);
        post_menu(register_menu);
        post_menu(memory_menu);
        
        //on se place sur l'instruction en cour
        set_current_item (instruction_menu, item_en_cour);
        
        //on se positionne sur la mémoire précédement regardé
        set_current_item (memory_menu, current_memory);
        
	wrefresh(instructions_win);
        wrefresh(register_win);
        wrefresh(memory_win);

	while((c = getch()) != KEY_F(9) ){

		switch(c)
		{	
                    
			case KEY_F(5):
		        mvprintw(LINES-2, 0, "Exiting...");
		        endwin();			/* End curses mode		  */
		        exit(0);
		    
		        case KEY_F(2):

				/* On efface les fenêtres */
				clean_all_menu();

				free(memory_items);
				free(register_items);
				free(instructions_items);

				init_mem();

				/* On repasse en mode Menu => on réactive la touche entrée */
				mWindow = M_MENU;

		                files = list_file("", &i);
		                draw_menu(files, execute_file_menu, "", i);
		                
		        case KEY_DOWN:
				menu_driver(memory_menu, REQ_DOWN_ITEM);
                                current_int_memory = item_index(current_item(memory_menu));
                                

				wrefresh(instructions_win);
		       		wrefresh(memory_win);

				break;

			case KEY_UP:
				menu_driver(memory_menu, REQ_UP_ITEM);
                                current_int_memory = item_index(current_item(memory_menu));
                                
				wrefresh(instructions_win);
		      		wrefresh(memory_win);

				break;

		        case KEY_NPAGE:
				menu_driver(memory_menu, REQ_SCR_DPAGE);
                                current_int_memory = item_index(current_item(memory_menu));
                                
				wrefresh(instructions_win);
		       		wrefresh(memory_win);

				break;

		        case KEY_PPAGE:
				menu_driver(memory_menu, REQ_SCR_UPAGE);
                                current_int_memory = item_index(current_item(memory_menu));
                                
				wrefresh(instructions_win);
		       		wrefresh(memory_win);

				break;
		    
		        case 32:
                            if(fin_prog == 0)
                                return ;
		               
				break;
		}
	}
}


char ** list_file(char * folder, int* nb_result){
    
    struct dirent *lecture;
    DIR *rep;
    char relativFolder[(strlen(folder)+5)];
    int nbFolder = 0;
    int cpt=0;
    char **listeRep=NULL;
    
    strcpy(relativFolder, "./");
   
    strcat(relativFolder,folder);
     //mvprintw(LINES-3, 40, "                                                         ");
     //mvprintw(LINES-3, 40, "%s  %i", relativFolder, strlen(folder));
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
                       //on vire le fichier " . " et le .. si on est à la racine du dossier
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



void tri_iteratif(char *tableau[], int taille)
{
    char *temp;
    int i, j;
    for (i = 0; i < taille; i++)
        for (j = 0; j < taille; j++)
            if (strcmp(tableau[i], tableau[j]) < 0)
            {
                temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
}

void clean_menu(MENU * my_menu){
        unpost_menu(my_menu);
        if(my_menu != NULL)
                free_menu(my_menu);
        mvprintw(LINES - 2, 0, "                      "); //efface pied de page pour fermer le menu
        refresh();
}

/* On enlève tous les menus "exécution" */
void clean_all_menu(){

	clean_menu(instruction_menu);
        clean_window(instructions_win);
        clean_menu(register_menu);
        clean_window(register_win);
	clean_menu(memory_menu);
   	clean_window(memory_win);
}

void clean_window(WINDOW *  my_menu_win){
        wclear (my_menu_win);
        
        wrefresh(my_menu_win);
}

int exists(const char *fname)
{
    FILE *file = fopen(fname, "a+");
    //mvprintw(LINES - 4, 0, "%i", file);
    if(file != NULL){
        //mvprintw(LINES - 5, 0, "this is a file         ");
        return 1;
    }else{
        FILE *folder = fopen(fname, "r");
        if(folder == NULL){
            //mvprintw(LINES - 5, 0, "this is nothing     ");
            return 0;
           
        }
        else{
            char is_folder[strlen(fname)+1];
            strcpy(is_folder, fname);
            strcat(is_folder, "/");
            FILE *text_file = fopen(is_folder, "r");
            if(text_file != NULL ){
                //mvprintw(LINES - 5, 0, "this is a folder       ");
                return 2; 
            }
            else{
                mvprintw(LINES - 5, 0, "this is not a text file     ");
                return 0;
            }
        }
    }

}


char * codeop_tostring(int codeop){
    

        switch (codeop){

             case LOAD :
                 return "LOAD  ";
                 break;
             case STORE :
                 return "STORE ";
                 break;
             case ADD :
                 return "ADD   ";
                 break;
             case SUB :
                 return "SUB   ";
                 break;
             case JMP :
                 return "JMP   ";
                 break;
             case JEQ :
                 return "JEQ   ";
                 break;
             case CALL :
                 return "CALL  ";
                 break;
             case RET :
                 return "RET   ";
                 break;
             case PUSH :
                 return "PUSH  ";
                 break;
             case POP :
                 return "POP   ";
                 break;
             case HALT :
                 return "HALT  ";
                 break;
             default :
                 return "UNKNOW";
                 break;


    }
}


char * mode_tostring(int a_mode){
    
    //variable mode dea prise ...
    switch (a_mode){
        case REGREG:  
             return "REGREG";
        case DIRREG: 
             return "DIRREG";
        case INDREG:
             return "INDREG";
        case REGIMM: 
             return "REGIMM";
        case DIRIMM:  
             return "DIRIMM";
        case INDIMM: 
             return "INDIMM";
        case REGDIR:  
             return "REGDIR";
        case REGIND:  
             return "REGIND";
            
        default:
           return "ERROR";
    
        }
}

char * instr_toString(mot instr, int brut1, int brut2){

	char* instrToS = malloc(sizeof(char)*50);
	char dest_string[5];
        char source_string[5];
        char brut_string[10];

		if (instr.codage.codeop == ADD || instr.codage.codeop == SUB || instr.codage.codeop == LOAD || instr.codage.codeop == STORE){
		// Instruction à deux opérandes

		strcpy(instrToS,codeop_tostring(instr.codage.codeop));
		strcat(instrToS, "  ");

			if (instr.codage.mode == REGREG){
				strcat(instrToS, "R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, ", ");
				strcat(instrToS, "R");
				sprintf(source_string,"%d",instr.codage.source);
				strcat(instrToS,source_string);
			}

			else if (instr.codage.mode == REGDIR){
				strcat(instrToS, "R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, ", [");
				sprintf(brut_string,"%d",brut1);
				strcat(instrToS,brut_string);
				strcat(instrToS, "]");
			}

			else if (instr.codage.mode == REGIMM){
				strcat(instrToS, "R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, ", #");
				sprintf(brut_string,"%d",brut1);
				strcat(instrToS,brut_string);
			}

			else if (instr.codage.mode == REGIND){
				strcat(instrToS, "R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, ", [R");
				sprintf(dest_string,"%d",instr.codage.source);
				strcat(instrToS,dest_string);
				strcat(instrToS, "]");
			}

			else if (instr.codage.mode == DIRREG){
				strcat(instrToS, "[");
				sprintf(brut_string,"%d",brut1);
				strcat(instrToS,brut_string);
				strcat(instrToS, "], ");
				strcat(instrToS, "R");
				sprintf(source_string,"%d",instr.codage.source);
				strcat(instrToS,source_string);
			}

			else if (instr.codage.mode == DIRIMM){
				strcat(instrToS, "[");
				sprintf(brut_string,"%d",brut1);
				strcat(instrToS,brut_string);
				strcat(instrToS, "], #");
				sprintf(brut_string,"%d",brut2);
				strcat(instrToS,brut_string);
			}

			else if (instr.codage.mode == INDREG){
				strcat(instrToS, "[R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, "], ");
				strcat(instrToS, "R");
				sprintf(source_string,"%d",instr.codage.source);
				strcat(instrToS,source_string);
			}

			else if (instr.codage.mode == INDIMM){
				strcat(instrToS, "[R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, "], #");
				sprintf(brut_string,"%d",brut1);
				strcat(instrToS,brut_string);
			}
		}

		else if (instr.codage.codeop == PUSH || instr.codage.codeop == POP || instr.codage.codeop == CALL || instr.codage.codeop == JMP || instr.codage.codeop == JEQ){
		// Instruction à une opérande

		strcpy(instrToS,codeop_tostring(instr.codage.codeop));
		strcat(instrToS, "  ");

			if (instr.codage.mode == REGREG || instr.codage.mode == REGDIR || instr.codage.mode == REGIND || instr.codage.mode == REGIMM){
				strcat(instrToS, "R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
			}

			else if (instr.codage.mode == DIRREG || instr.codage.mode == DIRIMM){
				strcat(instrToS, ", [");
				sprintf(brut_string,"%d",brut1);
				strcat(instrToS,brut_string);
				strcat(instrToS, "]");
			}

			else if (instr.codage.mode == INDREG || instr.codage.mode == INDIMM){
				strcat(instrToS, "[R");
				sprintf(dest_string,"%d",instr.codage.dest);
				strcat(instrToS,dest_string);
				strcat(instrToS, "]");
			}
		}

		else if (instr.codage.codeop == HALT){
			strcpy(instrToS,codeop_tostring(instr.codage.codeop));
		}

	
	return instrToS;	
}

/**
 * \fn char* mem_toString(int adresse)
 * \brief Fonction affichant l'état de la mémoire à partir à une certaine adresse.
 *
 * \param adresse Adresse mémoire à afficher.
 */
char* mem_toString(int adresse, bool isBrut){

	char* mem_s = malloc(sizeof(char)*16);

        if (adresse > 1999 || isBrut){
    	
            // Adresse mémoire donnée, pile, direct et immdédiat
            sprintf(mem_s,"%s",add0(toBinaire(mem_prog[adresse].brut),16));
	}

	else {

	    // Adresse mémoire instruction
            sprintf(mem_s,"%s %s %s %s",add0(toBinaire(mem_prog[adresse].codage.codeop),6),
                   add0(toBinaire(mem_prog[adresse].codage.mode),4),
                   add0(toBinaire(mem_prog[adresse].codage.source),3),
                   add0(toBinaire(mem_prog[adresse].codage.dest),3));
        }

	return mem_s;
}

void reset(){
	PC = 0;
	sp = ADR_PILE_MIN;
	SR = 0;
	
	int i;
	for (i=0;i<8;i++){
	   reg[i]=0;
	}
}

void init_mem(){

     int i;
     for (i=0; i < TAILLE_MEM; i++){

	mem_prog[i].codage.codeop = 0;
	mem_prog[i].codage.mode = 0;
	mem_prog[i].codage.dest = 0;
	mem_prog[i].codage.source = 0;

	mem_prog[i].brut = 0;
     }
}


