#include <stdio.h>
#include <sys\stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <dirent.h>

#define MAXSIZE 1024

// create_folder stop ( chopchop createfile)
// remove -b (Bug)
// copy -b
// paste -cut (Bug)

// TOOLS
void commander();
char command[MAXSIZE];

// Tools->Error Functions
void error();
void error_line();
void empty_line();
void doctor_life(char *);
void doctor_death(char *);

// Tools->Address Functions
char address[MAXSIZE];

// recognizer
void r();

// A) address without quotation
void address_maker_A();
// B) address with quotation
void address_maker_B();

// char* chopchop();
void slash_counter();
int slash_num = 0;
int current_slash = 0;
char address_copy[MAXSIZE];

// syntax
void dash_file();

void dash_pos();
int x = 0;
int y = 0;

void dash_str();
char content[MAXSIZE];

void dash_size();
int size;

int dash_f_b();
int f_b;

// Tools->else
FILE *find_pos(char *, int, int, int, int);
char *find_str_pos(int, FILE *);
int line_counter(char *, int); // line = 1

// Vim Functions
void create_file(char *);
void create_folder(char *);

void cat_file(char *);

void insert_str(char *, char *, int, int);
void remove_str(char *, int, int, int, int);

void copy_str(char *, int, int, int, int);
void paste_str(char *, int, int);
void cut_str(char *, int, int);

void comparator(char *, char *);
void comparator_1(char *, char *, int);
void comparator_2(char *, char *, int, int);

void auto_indent(char *);

void tree(int);

// global Variable
char str[MAXSIZE]; // for remove and find_str
char clipboard[MAXSIZE];

int main(int argc, char *argv[])
{
    printf("Hi!\nwelcome to vim world!\nplease enter your command.\nFor more information use help\n\n");
    commander();
}

void commander()
{
    scanf("%[^ ]s", &command);
    getchar();
    if (!strcmp(command, "help"))
    {
        printf("commands list :\n");
        printf("createfile        |  createfile --file name_of_file\n");
        printf("cat               |  cat        --file name_of_file\n");
        printf("insert            |  insert     --file name_of_file --str content --pos y:x\n");
        printf("remove            |  removestr  --file name_of_file --pos y:x --size size f_b\n");
        printf("copy              |  copystr    --file name_of_file --pos y:x --size size f_b\n");
        printf("paste             |  pastestr   --file name_of_file --pos y:x                \n");
        printf("cut               |  cutstr     --file name_of_file --pos y:x --size size f_b\n");
        // replace           |                                                          \n
        // grep              |                                                          \n
        // undo              |                                                          \n
        printf("auto-indent       | auto-indent name_of_file                                 \n");
        printf("compare           | compare     name_of_file_A name_of_file_B                \n");
        // tree              |                                                          \n
        // find              |                                                          \n
        return;
    }
    if (!(strcmp(command, "createfile")))
    {
        dash_file();
        r();
        printf("%s", address);
        create_folder(address);
        return;
    }

    if (!(strcmp(command, "cat")))
    {
        dash_file();
        r();
        doctor_death(address);
        cat_file(address);
        return;
    }

    if (!(strcmp(command, "insert")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_str();
        dash_pos();
        insert_str(address, address, y, x);
        return;
    }

    if (!(strcmp(command, "removestr")))
    {
        dash_file();
        r();
        (doctor_death(address));
        dash_pos();
        dash_size();
        dash_f_b();
        remove_str(address, y, x, size, f_b);
        return;
    }

    // copystr --file /aida/aida.txt --pos 2:3 --size 8 f
    if (!(strcmp(command, "copystr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_pos();
        dash_size();
        dash_f_b();
        copy_str(address, y, x, size, f_b);
        return;
    }
    if (!(strcmp(command, "pastestr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_pos();
        paste_str(address, y, x);
        return;
    }
    if (!(strcmp(command, "cutstr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_pos();
        dash_size();
        dash_f_b();
        // remove_str(address , y , x, size ,f_b);
        return;
    }
    if (!(strcmp(command, "compare")))
    {
        char file_A[MAXSIZE];
        char file_B[MAXSIZE];
        scanf("%s", &file_A);
        getchar();
        scanf("%s", &file_B);

        doctor_death(file_A);
        doctor_death(file_B);
        comparator(file_A, file_B);
        return;
    }
    if (!strcmp(command, "auto_indent"))
    {
        r();
        doctor_death(address);
        auto_indent(address);
        return;
    }
    if (!strcmp(command, "tree"))
    {
        int depth;
        scnaf("%d", &depth);
        tree(depth);
    }
    else
        error();
}

void r()
{
    char R;
    scanf("%c", &R);
    if (R == '/')
    {
        address_maker_A();
        return;
    }
    if (R == '"')
    {
        address_maker_B();
        return;
    }
    else
        error();
}

void address_maker_A()
{
    scanf("%[^ ]s", &address);
    slash_counter();
    return;
}

void address_maker_B()
{
    // Empty
}

char *chopchop()
{
    current_slash++;
    int counter = 0;
    for (int i = 0; counter < current_slash; i++)
    {
        if (address[i] == '/')
        {
            counter++;
            if (counter == current_slash)
                break;
        }
        address_copy[i] = address[i];
    }
    // printf("cuurent  is %d\n" , current_slash);
    printf("***%s\n", address_copy);
    return (address_copy);
}

void slash_counter()
{
    for (int i = 0; address[i] != '\0'; i++)
    {
        if (address[i] == '/')
            slash_num++;
    }
}

void dash_file()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    printf("%s\n", syntax);
    getchar();
    if (strcmp(syntax, "--file") != 0)
        error();
}

void dash_str()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    printf("%s\n", syntax);
    getchar();
    if (strcmp(syntax, "--str") != 0)
        error();
}

void dash_pos()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    printf("%s\n", syntax);
    getchar();
    if (strcmp(syntax, "--pos") != 0)
        error();
    scanf("%d", &y);
    getchar(); // for :
    scanf("%d", &x);
}

void dash_size()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    printf("%s\n", syntax);
    getchar();
    if (strcmp(syntax, "--size") != 0)
        error();
    scanf("%d", &size);
    printf("%d\n", size);
}

int dash_f_b()
{
    getchar(); // for -
    char R = getchar();

    if (R == 'f')
        f_b = 1;
    else if (R = 'b')
        f_b = 0;
    else
        error();
}

void error()
{
    printf("invalid command!\n");
    exit(0);
}

void error_line()
{
    printf("file is too short!\n");
    exit(0);
}

void empty_line()
{
    printf("Empty line!\n");
    exit(0);
}

void invalid_depth()
{
    printf("invalid Depth!");
    exit(0);
}

void opendir()
{
    printf("Could not open directory\n");
}

void doctor_life(char *address)
{
    FILE *file;
    file = fopen(address, "r");
    if (file != NULL)
    {
        printf("alive!\n\n");
        fclose(file);
        exit(0);
    }
    fclose(file);
    return;
}

void doctor_death(char *address)
{
    FILE *file;
    file = fopen(address, "r");
    if (file == NULL)
    {
        printf("No such file exists in Vim world!\n\n");
        fclose(file);
        exit(0);
    }
    fclose(file);
    return;
}

int line_counter(char *address, int y)
{
    char ch;
    FILE *file;
    file = fopen(address, "r");
    ch = fgetc(file);
    while (ch != EOF)
    {
        if (ch == '\n')
            y++;
        ch = fgetc(file);
    }
    fclose(file);
    return y;
}

FILE *find_pos(char *address, int y, int x, int f_b, int size) // (f = 1 & b = 0) //delay!
{
    FILE *file;
    file = fopen(address, "r");
    int y_counter = 1;
    int x_counter = 1;
    while (y_counter < y)
    {
        char c = fgetc(file);
        if (c == '\n')
        {
            y_counter++;
            continue;
        }
    }
    while (x_counter < x)
    {
        char c = fgetc(file);
        x_counter++;
    }
    if (f_b == 1)
    {
        return file;
    }
    if (f_b == 0)
    {
        // something in here
    }
}

char *find_str_pos(int size, FILE *file)
{
    for (int i = 0; i < size; i++)
    {
        char c = fgetc(file);
        str[i] = c;
    }
    fclose(file);
    return str;
}

//                                 *****************Vim Functions***************

void create_folder(char *address)
{
    if (slash_num == current_slash)
    {
        create_file(address);
        return;
    }
    if (slash_num > current_slash)
    {
        chopchop();
        doctor_life(address_copy);
        create_folder(address);
        mkdir(address_copy);
        printf("Nai Nai folder created!\n");
        create_folder(address);
    }
}

void create_file(char *address)
{
    doctor_life(address);

    FILE *file;
    fopen(address, "w");
    printf("Nai Nai file created\n");
    fclose(file);
}

void cat_file(char *address)
{
    doctor_death(address);

    FILE *file;
    file = fopen(address, "r");
    char ch;
    while (!feof(file))
    {
        ch = fgetc(file);
        printf("%c", ch);
    }
    printf("Nai Nai\n");
    fclose(file);
}

void insert_str(char *address, char *text, int line_pos, int char_pos)
{
    FILE *file, *copy;

    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    file = fopen(address, "r");
    copy = fopen(copy_name, "w");

    int current_line = 1;
    int current_char = 0;

    while (1)
    {
        char ch;
        int i = 0;
        ch = fgetc(file);

        if (feof(file))
        {
            if (current_line > line_pos)
                break;

            else if (current_line < line_pos)
            {
                fputc('\n', copy);
                current_line++;
            }
            else
            {
                for (int i = 0; i < char_pos; i++)
                {
                    printf("\n");
                    fputc(' ', copy);
                }
                fputs(text, copy);
                break;
            }
        }

        else
        {

            fputc(ch, copy);
            if (current_line == line_pos)
            {
                if (current_char == char_pos)
                    fputs(text, copy);
                current_char++;
            }
            if (ch == '\n')
                current_line++;
        }
    }

    fclose(file);
    fclose(copy);

    remove(address);
    rename(copy_name, address);

    printf("text inserted!\n");
}

void remove_str(char *address, int line_pos, int char_pos, int size, int direction) //( f = 1 & b = 0) //problem
{
    FILE *file, *copy;

    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    file = fopen(address, "r");
    copy = fopen(copy_name, "w");

    // int x = find_pos(address,line_pos,char_pos,direction);
    int x = 32;

    while (!EOF)
    {
        char ch = fgetc(file);
        if (ftell(file) == x)
        {
            for (int i = 0; i < size; i++)
            {
                fgetc(file);
            }
        }
        else
            fputc(ch, copy);
    }

    fclose(file);
    fclose(copy);
    rename(copy_name, address);
    remove(address);

    printf("text removed!\n");
}

void copy_str(char *address, int y, int x, int size, int f_b)
{
    FILE *file = fopen(address, "r");

    clipboard[0] = '\0';
    char content[MAXSIZE];

    for (int line = 0; line < y; line++)
    {
        fgets(content, MAXSIZE, file);
        if (content == NULL)
        {
            fclose(file);
            error_line();
        }
    }
    for (int ch = 0; ch < x; ch++)
    {
        fgetc(file);
    }
    for (int i = 0; i < size; i++)
    {
        char ch = fgetc(file);
        clipboard[i] = ch;
    }
    // printf("%s" , clipboard);
    printf("Text Copied to Clipboard!\n");
    fclose(file);
}

void paste_str(char *address, int y, int x)
{
    FILE *file = fopen(address, "w");

    if (clipboard == NULL)
    {
        printf("Empty!");
        exit(0);
    }
    for (int line = 0; line < y; line++)
    {
        fgets(content, MAXSIZE, file);
        if (content == NULL)
        {
            fclose(file);
            error_line();
        }
    }
    for (int ch = 0; ch < x; ch++)
    {
        fgetc(file);
    }
    for (int i = 0; i < size; i++)
    {
        char ch = fgetc(file);
        fputc(clipboard[i], file);
    }

    clipboard[0] = '\0';

    printf("Nai Nai!\n");
    fclose(file);
}

void comparator(char *file_A, char *file_B)
{
    int A_num = line_counter(file_A, 1);
    int B_num = line_counter(file_B, 1);
    if (A_num == B_num)
        comparator_1(file_A, file_B, A_num);
    if (A_num > B_num)
        comparator_2(file_A, file_B, A_num, B_num);
    if (A_num < B_num)
        comparator_2(file_B, file_A, B_num, A_num);

    return;
}

void comparator_1(char *file_A, char *file_B, int num)
{
    FILE *A;
    FILE *B;
    A = fopen(file_A, "r");
    B = fopen(file_B, "r");
    char A_l[MAXSIZE];
    char B_l[MAXSIZE];
    for (int i = 1; i < num; i++)
    {
        fgets(A_l, MAXSIZE, A);
        fgets(B_l, MAXSIZE, B);
        if (strcmp(A_l, B_l))
        {
            printf("======== #%d ========\n", i);
            printf("%s\n", A_l);
            printf("%s\n", B_l);
        }
    }
    fclose(A);
    fclose(B);
    return;
}

void comparator_2(char *file_A, char *file_B, int N, int n) // N --> Big
{
    comparator_1(file_A, file_B, n);
    FILE *file;
    file = fopen(file_A, "r");
    char line[MAXSIZE];
    for (int i = 1; i < n; i++)
    {
        fgets(line, MAXSIZE, file);
    }
    for (int i = n; i <= N; i++)
    {
        fgets(line, MAXSIZE, file);
        printf("<<<<<<<<<< #%d - #%d <<<<<<<<<\n", n, N);
        printf("%s\n", line);
    }
    fclose(file);
    return;
}

void auto_indent(char *address)
{
    FILE *file;
    FILE *copy;

    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    file = fopen(address, "r");
    copy = fopen(copy_name, "w");

    char ch = fgetc(file);
    if (ch == NULL)
        line_error();

    fseek(file, 0, SEEK_SET);

    int counter = 0;
    while (1)
    {
        char ch = fgetc(file);
        if (ch != EOF)
        {
            if (ch == '{')
            {
                fputs("\n", copy);
                for (int i = 0; i < counter; i++)
                    fputs("\t", copy);
                fputc(ch, copy);
                counter++;
                fputs("\n", copy);
                for (int i = 0; i < counter; i++)
                    fputs("\t", copy);
            }

            else if (ch == '}')
            {
                counter--;
                fputs("\n", copy);
                for (int i = 0; i < counter; i++)
                    fputs("\t", copy);

                fputc(ch, copy);
            }
            else
                fputc(ch, copy);
        }
        else
        {
            fclose(file);
            fclose(copy);

            remove(address);
            rename(copy_name, address);
            exit(0);
        }
    }
}

void tree(int depth)
{
    /*struct entry * d;
    DIR * dir = opendir(".");

    if(dir == NULL) printf("Could not open directory");

    for( int i = 0 ; i < depth ; i++)
    {
        if( (dir = readdir(dir)) == NULL)
        {
            closedir(d);
            invalid_depth();
        }

    }*/
}
