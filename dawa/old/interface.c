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



#define FILE_MAX 100


//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test


mot mem[12] = {
        {.codage = {ADD, REGREG, 1,2 }},
        {.codage = {STORE, DIRREG, 1,0}},
        {.brut = 2000                 },
        {.codage = {LOAD, REGIMM, 0,6}},
        {.brut = 2000                },
        {.codage = {ADD, REGDIR, 0,7}},
        {.brut = 2000                 },
        {.codage = {ADD, REGIMM, 0, 3}},
        {.brut = 1                    },
        {.codage = {ADD, REGIND, 6, 4}}
};


int taille_mem = 12;
int taille_reg = 8;
int reg[8] = {0,0,0,0,0,0,0,0};
int PC,SP,SR;

//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test
//to delete after test




 
//dans e main qui sera remplacer par un init_gui(void (*ptrfonction)(char **), void (*ptrfonction)(char *))
//il faudra donner comme paramètre 1: la fonction qui traitera le fichier à parser
//                                 2: la fonction qui parsera le fichier



int init_gui()
{	WIN win;
	int ch;
        int i;
        char ** files;

	initscr();			/* Start curses mode 		*/
	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);

	/* Initialize the window parameters */
	init_win_params(&win);
	print_win_params(&win);

	attron(COLOR_PAIR(1));
        printw("F2: Ouvrir un fichier");
        printw("\t F3: Lancer l'émulation");
	printw("\t F5: Quitter");
        attron(A_BOLD);
        attron(COLOR_PAIR(2));
        char chaine[]="Welcome to ProcSI emulator";
        mvprintw((LINES/2) -3,(COLS-strlen(chaine))/2,chaine);
        attroff(A_BOLD);
	refresh();
	attroff(COLOR_PAIR(1));
	
	create_box(&win, TRUE);
        draw_menu(choices, execute_main_menu, "", 3);
        
	while((ch = getch()) != KEY_F(5))
	{
            switch(ch)
	    {	case KEY_F(5):
                        mvprintw(LINES-2, 0, "Exiting...");
                        endwin();			/* End curses mode		  */
                        exit(0);
            
                case KEY_F(2):
                        files = list_file("", &i);
                        draw_menu(files, execute_file_menu, "", i);
            }
            
	}
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
void create_box(WIN *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

void draw_menu(char ** menu_liste, void (*ptrfonction)(int,const char *, char *), char * folder, int taille_menu){
        ITEM **my_items;
	int c;		
        WINDOW *my_menu_win;
	MENU *my_menu;
	int i;
	ITEM *cur_item;
        my_items = (ITEM **)calloc(taille_menu + 1, sizeof(ITEM *));
        int menu_alrdy_dlt = 0; //pour ne pas supprimer le menu 2 fois --> évite les erreur de segmentation lorsqu'on quitte
        char ** files; //pour le cas ou on utilise F2 (ouvrir un fichier)
        
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
                        files = list_file("", &i);
                        clean_menu(my_menu);
                        clean_window(my_menu_win);
                        draw_menu(files, execute_file_menu, "", i);
                        return;
                    
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
                        move(20, 0);
			clrtoeol();
                        num_choix = item_index(current_item(my_menu));
                        strcpy(choix, item_name(current_item(my_menu)));
			//mvprintw(5, 0, "Item selected is : %s", item_name(current_item(my_menu)));
                        clean_menu(my_menu);
                        menu_alrdy_dlt = 1;
                        clean_window(my_menu_win);
                        (*ptrfonction)(num_choix, choix, folder);
			pos_menu_cursor(my_menu);
			break;
                 

		}
                wrefresh(my_menu_win);
	}
        if(menu_alrdy_dlt == 0)
                clean_menu(my_menu);
        clean_window(my_menu_win);
        
       
        
    
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
    
    if(choice == 2){
        mvprintw(LINES-2, 0, "Exiting...");
        endwin();			/* End curses mode		  */
        exit(0);
    }
    
}

void execute_file_menu(int choice,const char * choice_name, char * folder){
    char file[strlen(choice_name)];
    char folder_complet[strlen(folder)+strlen(file)+1];
    
    strcpy(file, choice_name);
    
    strcpy(folder_complet, folder);
    strcat(folder_complet, file);
    
    
    if(exists(folder_complet) == 1){
         
         mvprintw(LINES-2, 0, "                                                        ");
         mvprintw(LINES-1, 0, "%s                                                                ", folder_complet);
         display_execution(6, mem, taille_mem, reg, taille_reg, 1, 2, 3);
        
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

void display_execution(int num_instruction, mot * tab_mot_instruction, int nb_instruction, int* registres,int nb_reg, int PC, int SP, int SR){
        ITEM *item_en_cour = NULL; 
    
        char ** tab_instruction;
        // for instructions
        ITEM **instructions_items;
	int c;		
        WINDOW *instructions_win;
	MENU *instruction_menu;
	int i;
	instructions_items = (ITEM **)calloc(nb_instruction + 1, sizeof(ITEM *));
        int menu_instruction_alrdy_dlt = 0; //pour ne pas supprimer le menu 2 fois --> évite les erreur de segmentation lorsqu'on quitte
        
        
        char ** files;  //in case of F2
        
        // for register
        char  ** tab_register;
        ITEM **register_items;
	WINDOW *register_win;
	MENU *register_menu;
	register_items = (ITEM **)calloc(nb_reg + 1 +3, sizeof(ITEM *)); //+3 pour PC SP et SR
        int menu_register_alrdy_dlt = 0; //pour ne pas supprimer le menu 2 fois --> évite les erreur de segmentation lorsqu'on quitte
        
        
        char dest_string[5];
        char source_string[5];
        char brut_string[10];
        char pc_string[6], sp_string[6], sr_string[6];
        
        
        
        int is_brut = 0; //si le mot précedent contient un mode direct, alors le mot suivant est un brut //si DIRIMM les 2 suivant sont des brut
        
        
        //allocation de mémoire pour les insctruction sous forme de chaine
        tab_instruction = (char**) malloc (nb_instruction* sizeof(char*));
        
        
        
        //allocation de mémoire pour le tabeau de registre sous forme de string
        tab_register = (char**) malloc (nb_reg* sizeof(char *));
        
        int num_choix;
        char * choix = NULL;

         
	for(i = 0; i < nb_instruction; ++i){
            
            tab_instruction[i] = malloc(50 * sizeof(char)); //plus simple pour le moment, une instruction ne peut dépasser 50caractères ... a améliorer si assez de temps
                
            
            if(is_brut == 0){
               
                
                
                sprintf(dest_string, "%d", tab_mot_instruction[i].codage.dest);
                sprintf(source_string, "%d", tab_mot_instruction[i].codage.source);
                
                //si l'instruction contient une source ou destination en mode immediat ou direct, la prochaine instruction sera un brut
                if(is_brut==2 || tab_mot_instruction[i].codage.mode == REGIMM || tab_mot_instruction[i].codage.mode == INDIMM || tab_mot_instruction[i].codage.mode == REGDIR || tab_mot_instruction[i].codage.mode ==  DIRREG){
                    is_brut = 1;
                }
                if(tab_mot_instruction[i].codage.mode == DIRIMM){
                    is_brut = 2;
                }
                
                strcpy(tab_instruction[i], codeop_tostring(tab_mot_instruction[i].codage.codeop) ); //on met tout les élément sous forme de string concaténé et espacé
                strcat(tab_instruction[i], "    "); 
                strcat(tab_instruction[i], mode_tostring(tab_mot_instruction[i].codage.mode));
                strcat(tab_instruction[i], "    "); 
                strcat(tab_instruction[i], dest_string);
                strcat(tab_instruction[i], "    "); 
                strcat(tab_instruction[i], source_string);
            }
            else{
               sprintf(brut_string, "%d", tab_mot_instruction[i].brut); 
               strcpy(tab_instruction[i], brut_string ); 
               if(is_brut == 2){
                   is_brut = 1; // cas du DIRIMM
               } else{
                   is_brut = 0;
               }
            }
                

                //mvprintw(i+2, 0, "%s", tab_instruction[i]);
                instructions_items[i] = new_item(tab_instruction[i], ""); //ajoute les éléments dans mon tableau d'item
                
                if(i == num_instruction){
                        //on sauvegarde l'adresse de l'item que l'on est entrain de traiter (celui donner par num_instruction)
                        item_en_cour = instructions_items[i];
                        //n le desactive, cela permet de lui doonner une autre apparence pur le repérer
                        item_opts_off(instructions_items[i], O_SELECTABLE);
                }
        }
                
        
        
        
        
        for(i = 0; i < nb_reg; ++i){
                //contient le registre sous forme de string par exemple R1 ou PC
                tab_register[i] = malloc(3 * sizeof(char));
                
                sprintf(tab_register[i], "R%i: %d",i, registres[i]);
                
                //mvprintw(i+2, 0, "%s", tab_instruction[i]);
                register_items[i] = new_item(tab_register[i], ""); //ajoute les éléments dans mon tableau d'item
        }
                sprintf(pc_string, "%d", PC);
                sprintf(sp_string, "%d", SP);
                sprintf(sr_string, "%d", SR);
                register_items[nb_reg] = new_item("PC:", pc_string); //register_items[8]
                register_items[nb_reg+1] = new_item("SP:", sp_string); //register_items[9]
                register_items[nb_reg+2] = new_item("SR:", sr_string);  //register_items[10]
                //pour cacher la selection du premier registre
                item_opts_off(register_items[0], O_SELECTABLE);
        
        
	instruction_menu = new_menu((ITEM **)instructions_items); //creer un menu contenant les instructions
        
        register_menu = new_menu((ITEM **)register_items); //creer un menu contenant les registres
	mvprintw(LINES - 2, 0, "F9 to close the menu"); 
        
        
        
        instructions_win = newwin((LINES-4)/2, 40 , 3, (COLS/2)- (COLS-4)/4); //créer une nouvelle fenetre pour les instructions
        register_win = newwin(16, 20 , 3, (COLS/2) + 10); //créer une nouvelle fenetre pour les registres
        
        keypad(instructions_win, TRUE); //active le clavier sur les instructions
       
        
        
        /* Set main window and sub window */
        set_menu_win(instruction_menu, instructions_win); //set main menu
        set_menu_sub(instruction_menu, derwin(instructions_win, ((LINES-4)/2)-4, 38, 3, 1)); // set sub window
        set_menu_format(instruction_menu, ((LINES-4)/2)-4, 1);
        
        set_menu_win(register_menu, register_win); //set main menu
        set_menu_sub(register_menu, derwin(register_win, 13, 18, 3, 1)); // set sub window
        set_menu_format(register_menu, 13, 1);
        
        
        
        
       /* Set menu mark to the string " * " */
        set_menu_mark(instruction_menu, " * ");
        set_menu_mark(register_menu, "");
        
        
        /* Print a border around the main window and print a title */
        box(instructions_win, 0, 0);
        print_in_middle(instructions_win, 1, 0, 40, "liste des instructions", COLOR_PAIR(1));
	mvwaddch(instructions_win, 2, 0, ACS_LTEE);
	mvwhline(instructions_win, 2, 1, ACS_HLINE, 43);
	mvwaddch(instructions_win, 2, 39, ACS_RTEE);
        
        box(register_win, 0, 0);
        print_in_middle(register_win, 1, 0, 20, "Registres", COLOR_PAIR(1));
	mvwaddch(register_win, 2, 0, ACS_LTEE);
	mvwhline(register_win, 2, 1, ACS_HLINE, 22);
	mvwaddch(register_win, 2, 19, ACS_RTEE);
	refresh();
        
	post_menu(instruction_menu);
        post_menu(register_menu);
        
        //on se place sur l'instruction en cour
        set_current_item (instruction_menu, item_en_cour);
        
	wrefresh(instructions_win);
        wrefresh(register_win);
       

	while((c = getch()) != KEY_F(9) && c != 32)
	{   switch(c)
	    {	case KEY_F(5):
                mvprintw(LINES-2, 0, "Exiting...");
                endwin();			/* End curses mode		  */
                exit(0);
            
                case KEY_F(2):
                        files = list_file("", &i);
                        draw_menu(files, execute_file_menu, "", i);
                        
                case KEY_DOWN:
		        menu_driver(instruction_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(instruction_menu, REQ_UP_ITEM);
			break;
                
            
                //case KEY_NPAGE:
		//	menu_driver(my_menu, REQ_SCR_DPAGE);
		//	break;
                //case KEY_PPAGE:
		//	menu_driver(my_menu, REQ_SCR_UPAGE);
		//	break;
        
            
                case 10:
                        move(20, 0);
			clrtoeol();
                       
			break;
                 

		}
                wrefresh(instructions_win);
	}
        if(menu_instruction_alrdy_dlt == 0){
                clean_menu(instruction_menu);
                clean_window(instructions_win);
        }
                if(menu_register_alrdy_dlt == 0){
                clean_menu(register_menu);
                clean_window(register_win);
        }
    
    
}


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