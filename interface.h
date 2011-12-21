/**
 * \file  interface.h
 * \brief Fichier d'entête.
 * \author Amaury.B
 * \version 1.0
 * \date 21 décembre 2011
 *
 * Fichier d'entête comportant les méthodes de l'interface en ncurses de l'émulateur procsi.
 *
 */
#include <ncurses.h>
#include <menu.h>

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

int init_gui();
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
void display_execution(int num_instruction, mot * tab_mot_instruction, int nb_instruction, int* registres,int nb_reg, int PC, int SP, int SR);
char * codeop_tostring(int codeop);
char * mode_tostring(int a_mode);