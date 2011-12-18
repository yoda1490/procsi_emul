#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <menu.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <regex.h>



#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4



typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;


char *choices[] = {
                        "Ouvrir un fichier Assembleur",
                        "Lancer l'émulation d'un exemple",
                        "Exit",
                  };
 

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);
void draw_menu(char ** menu_liste, void (*ptrfonction)(int, const char *, char *), char * folder, int taille_menu);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void execute_main_menu(int choice,const char * choice_name, char * folder);
char ** list_file(char * folder, int* nb_result);
void tri_iteratif(char *tableau[], int taille);
void clean_window(WINDOW *  my_menu_win);
void clean_menu(MENU * my_menu);
int exists(const char *fname);
void execute_file_menu(int choice,const char * choice_name, char * folder);

int main(int argc, char *argv[])
{	WIN win;
	int ch;

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

	for(i = 0; i < taille_menu; ++i){
	        my_items[i] = new_item(menu_liste[i], ""); //ajoute les éléments dans mon tableau d'item
        }
	my_items[taille_menu] = (ITEM *)NULL; //ajoute un item vide à la fin du tableau
        my_menu = new_menu((ITEM **)my_items); //creer un menu contenan les items
	mvprintw(LINES - 2, 0, "F5 to close the menu"); //affiche un pied de page pour fermer le menu
        
        my_menu_win = newwin(10, 45, (LINES-10)/2, (COLS-45)/2); //créer une nouvelle fenetre
        keypad(my_menu_win, TRUE); //active le clavier pour le menu
       
        
        item_opts_off(my_items[6], O_SELECTABLE);
        
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
       

	while((c = getch()) != KEY_F(5) && c != 27)
	{   switch(c)
	    {	case KEY_DOWN:
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
			//mvprintw(5, 0, "Item selected is : %s", item_name(current_item(my_menu)));
                        //clean_menu(my_menu); // nécéssaire pour la ligne d'en dessous executer_tache !!!
                        clean_window(my_menu_win);
                        (*ptrfonction)(item_index(current_item(my_menu)), item_name(current_item(my_menu)), folder);
			pos_menu_cursor(my_menu);
			break;
                 

		}
                wrefresh(my_menu_win);
	}
        
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
        mvprintw(LINES-2, 0, "Exiting...", choice);
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
    strcat(folder_complet, "/");
    
    if(exists(choice_name) == 1){
         
         mvprintw(LINES-2, 0, "                                                        ");
        
    }
    else if(exists(choice_name) == 2){
        int i;
        char ** files = list_file(folder_complet, &i);
        mvprintw(LINES-1, 0, "%s, %i", folder_complet, i);
        draw_menu(files, execute_file_menu, folder_complet, i);
    }
    else{
        mvprintw(LINES-1, 0, "Une erreur s'est produite lors de l'ouverture du fichier");
        int i;
        char ** files = list_file("", &i);
        draw_menu(files, execute_file_menu,"", i);
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
    FILE *file = fopen(fname, "r");
    //mvprintw(LINES - 4, 0, "%i", file);
    if(file == NULL){
        return 0;
    }else{
        FILE *folder = fopen(fname, "a+");
        if(folder == NULL){
            return 2;
        }
        else{
            return 1;
        }
    }

}
