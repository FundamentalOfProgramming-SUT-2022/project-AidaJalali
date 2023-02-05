// Aida Jalali : 401170542
#include <stdio.h>
#include <sys\stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <ctype.h>
#include <curses.h>

#define MAXSIZE 1024

// BASE
void commander();
void error();
void Done();
// Address Functions
void r();               // Recognizer
void address_maker_A(); // A) address without quotation
void address_maker_B(); // B) address with quotation
void slash_counter();
// syntax
void dash_file();
void dash_pos();
void dash_str(char *);
void dash_str_find();
void dash_size();
void dash_f_b();
void dash_files();
void dash_option();
void dash_find_option();
// Tools
void doctor_life(char *);
void doctor_death(char *);
void find(char *, int, int, int);
int line_counter(char *, int);             // line = 1
void place_checker(char *, int, int, int); // check error 5 and error 6
void check_pattern();                      // for find_option
// Vim Functions
void create_file(char *);
void create_folder(char *);
void cat_file(char *);
void insert_str(char *, char *, int, int);
void remove_commander(char *, int, int, int, int);
void remove_str_f(char *, int, int, int);
void remove_str_b(char *, int, int, int);
void copy_str(char *, int, int, int, int);
void paste_str(char *, int, int);
void cut_str(char *, int, int);
void find_commander();
void find_ww();
void find_0();
void find_1();
void find_2();
void find_3();
void replace_commander();
void replace();
void replace_1();
void replace_2();
void grep_commander(char *);
void grep(char *, char *);
void comparator(char *, char *);
void comparator_1(char *, char *, int);
void comparator_2(char *, char *, int, int);
void auto_indent(char *);
void tree(char *address, int depth);
void undo(char *);
void undo_memory(char *);
// VARIABLE
char command[MAXSIZE];
char address[MAXSIZE] = "root/";
char address[MAXSIZE];
char address_copy[MAXSIZE]; // for remove function
char clipboard[MAXSIZE];    // for copy function
char content[MAXSIZE];      // for --str function
char file_list[MAXSIZE];    // for grep
char str[MAXSIZE];          // for remove and grep and find
char str_copy[MAXSIZE];     //
char str1[MAXSIZE];         // for replace command
char str2[MAXSIZE];         // for replace command
int find_option[MAXSIZE];   // for find option (count = 0 - at = 1 - byword = 2 - all = 3)
int size;                   // for --size function
int slash_num = 0;          // for slash counter
int current_slash = 0;      // for slash counter
int x = 0;                  // for pos
int y = 0;                  // for pos
int f_b = 0;                // forward and backward ( f = 1 & b = 0)
int c = 0;                  // for c option in grep
int ch_counter = 0;         // for find_0
int ans = 0;                // for replace
int word = 0;               // for find option
int word_str = 0;           // for find option
int s;                      // for at(find function)
char option;                // for grep command ()
char *token;                // for grep_commander

int main(int argc, char **argv)
{
    initscr();
    raw();

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);

    int height, width, start_y, start_x;
    height = 20;
    width = 40;
    start_y = start_x = 10;

    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();

    // box(win , 103 , 103);
    attron(COLOR_PAIR(1));
    mvwprintw(win, 0, 0, "Hi! welcome to vim world!\nplease enter your command.\nFor more information use help\n\n");
    attroff(COLOR_PAIR(1));

    wrefresh(win);
    refresh();
    commander();
}

void commander()
{
    // clear();
    move(50, 0);
    // scanf("%[^ ]s", &command);
    getch();
    endwin();
    // if (!strcmp(command, "help"))
    // {
    //     printw("list :\n");
    //     printw("createfile        |  createfile --file name_of_file                                \n");
    //     printw("cat               |  cat        --file name_of_file                                \n");
    //     printw("insert            |  insert     --file name_of_file --str content --pos y:x        \n");
    //     printw("remove            |  removestr  --file name_of_file --pos y:x --size size f_b      \n");
    //     printw("copy              |  copystr    --file name_of_file --pos y:x --size size f_b      \n");
    //     printw("paste             |  pastestr   --file name_of_file --pos y:x                      \n");
    //     printw("cut               |  cutstr     --file name_of_file --pos y:x --size size f_b      \n");
    //     printw("grep              |  grep       --str (option) content --files name_of_files       \n");
    //     printw("auto-indent       |  auto-indent name_of_file                                      \n");
    //     printw("compare           |  compare     name_of_file_A name_of_file_B                     \n");
    //     printw("tree              |  tree        depth                                             \n");
    //     printw("undo              |  undo        --file name_of_file                               \n");
    //     printw("find              |  find        --str content --file name_of_file  option         \n");
    //     printw("replace           |  replace    --str1 content --str2 content --file name_of_file  \n");
    //     printw("arman             |                                                                \n");
    //     return;
    // }
    // if (!(strcmp(command, "createfile")))
    // {
    //     dash_file();
    //     r();
    //     current_slash = 0;
    //     doctor_life(address);
    //     create_folder(address);
    //     Done();
    // }
    // if (!(strcmp(command, "cat")))
    // {
    //     dash_file();
    //     r();
    //     doctor_death(address);
    //     cat_file(address);
    //     Done();
    // }
    // if (!(strcmp(command, "insertstr")))
    // {
    //     dash_file();
    //     r();
    //     doctor_death(address);
    //     dash_str(str);
    //     dash_pos();
    //     place_checker(address, y, x, size);
    //     undo_memory(address);
    //     insert_str(address, str, y, x);
    //     Done();
    // }
    // if (!(strcmp(command, "removestr")))
    // {
    //     dash_file();
    //     r();
    //     (doctor_death(address));
    //     dash_pos();
    //     dash_size();
    //     dash_f_b();
    //     place_checker(address, y, x, size);
    //     undo_memory(address);
    //     remove_commander(address, y, x, size, f_b);
    //     Done();
    // }
    // if (!(strcmp(command, "copystr")))
    // {
    //     dash_file();
    //     r();
    //     doctor_death(address);
    //     dash_pos();
    //     dash_size();
    //     dash_f_b();
    //     place_checker(address, y, x, size);
    //     copy_str(address, y, x, size, f_b);
    //     Done();
    // }
    // if (!(strcmp(command, "pastestr")))
    // {
    //     dash_file();
    //     r();
    //     doctor_death(address);
    //     dash_pos();
    //     place_checker(address, y, x, size);
    //     undo_memory(address);
    //     paste_str(address, y, x);
    //     Done();
    // }
    // if (!(strcmp(command, "cutstr")))
    // {
    //     dash_file();
    //     r();
    //     doctor_death(address);
    //     dash_pos();
    //     dash_size();
    //     dash_f_b();
    //     place_checker(address, y, x, size);
    //     undo_memory(address);
    //     copy_str(address, y, x, size, f_b);
    //     remove_commander(address, y, x, size, f_b);
    //     Done();
    // }
    // if (!(strcmp(command, "grep")))
    // {
    //     dash_option();
    //     dash_str(str);
    //     dash_files();
    //     grep_commander(file_list);
    //     Done();
    // }
    // if (!(strcmp(command, "compare")))
    // {
    //     char file_A[MAXSIZE];
    //     char file_B[MAXSIZE];
    //     scanf("%s", &file_A);
    //     getchar();
    //     scanf("%s", &file_B);
    //     doctor_death(file_A);
    //     doctor_death(file_B);
    //     comparator(file_A, file_B);
    //     Done();
    // }
    // if (!strcmp(command, "auto_indent"))
    // {
    //     r();
    //     doctor_death(address);
    //     undo_memory(address);
    //     auto_indent(address);
    //     Done();
    // }
    // if (!strcmp(command, "tree"))
    // {
    //     int depth;
    //     scanf("%d", &depth);
    //     for (int i = 0; i < strlen(address) - 1; i++)
    //     {
    //         address_copy[i] = address[i + 1];
    //     }
    //     tree(address_copy, depth);
    // }
    // if (!strcmp(command, "undo"))
    // {
    //     dash_file();
    //     r();
    //     doctor_death(address);
    //     undo_memory(address);
    //     undo(address);
    //     Done();
    // }
    // if (!strcmp(command, "find"))
    // {
    //     dash_str(str);
    //     dash_str_find();
    //     dash_file();
    //     scanf("%s", address); // different type of address (no \ or " ")
    //     doctor_death(address);
    //     dash_find_option();
    //     check_pattern();
    //     find_commander();
    //     Done();
    // }
    // if (!(strcmp(command, "replace")))
    // {
    //     dash_str(str1);
    //     dash_str(str2);
    //     dash_file();
    //     scanf("%s", &address); // different type of address (no \ or " ")
    //     doctor_death(address);
    //     dash_find_option();
    //     check_pattern();
    //     replace_commander();
    //     Done();
    // }
    // else
    //     error(0);
}