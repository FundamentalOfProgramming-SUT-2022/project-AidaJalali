#include <stdio.h>
#include <sys\stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <dirent.h>
#include <ctype.h>

#define MAXSIZE 1024

// create_folder stop ( chopchop createfile)
// remove -b (Bug)
// copy -b
// paste -cut (Bug)

// BASE
void commander();
void error();
void Done();

// Address Functions
void r();               // Recognizer
void address_maker_A(); // A) address without quotation
void address_maker_B(); // B) address with quotation
char *chopchop();       // seprate address
void slash_counter();

// syntax
void dash_file();
void dash_pos();
void dash_str();
void dash_size();
void dash_f_b();

// Tools
void doctor_life(char *);
void doctor_death(char *);
void find(char *, int, int, int);
int line_counter(char *, int); // line = 1
void place_checker(char *, int, int, int);

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

void comparator(char *, char *);
void comparator_1(char *, char *, int);
void comparator_2(char *, char *, int, int);

void auto_indent(char *);

void tree(int);

void undo(char *);
void undo_memory(char *);

// VARIABLE
char command[MAXSIZE];
char address[MAXSIZE];
char address_copy[MAXSIZE]; // for remove function
char str[MAXSIZE];          // for remove and find_str
char clipboard[MAXSIZE];    // for copy function
char content[MAXSIZE];      // for --str function
int size;                   // for --size function
int slash_num = 0;          // for slash counter
int current_slash = 0;      // for slash counter
int x = 0;                  // for pos
int y = 0;                  // for pos
int f_b = 0;                // forward and backward ( f = 1 & b = 0)

int main()
{
    printf("Hi!\nwelcome to vim world!\nplease enter your command.\nFor more information use help\n\n");
    // commander();
    // undo("aida/aida.txt");
    // insert_str("aida/aida.txt", "hello mello*******************", 10, 3);
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
        printf("auto-indent       | auto-indent name_of_file                                 \n");
        printf("compare           | compare     name_of_file_A name_of_file_B                \n");
        printf("tree              | tree depth                                               \n");
        printf("undo              | undo        --file name_of_file                          \n");
        printf("replace           |                                                          \n");
        printf("find              |                                                          \n");
        return;
    }

    if (!(strcmp(command, "createfile")))
    {
        dash_file();
        r();
        create_folder(address);
        Done();
    }

    if (!(strcmp(command, "cat")))
    {
        dash_file();
        r();
        doctor_death(address);
        cat_file(address);
        Done();
    }
    // insertstr --file /aida/aida.txt --str hello my name is polo --pos 2:5
    if (!(strcmp(command, "insertstr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_str();
        dash_pos();
        place_checker(address, y, x, size);
        undo_memory(address);
        // printf("address is %s\n" , address);
        // printf("str is %s\n" ,str);
        // printf("y is %d and x is %d\n" , y , x);
        // insert_str("aida/aida.txt", "ghar ghar ghar*******************", 10, 3);
        insert_str(address, str, y, x);
        Done();
    }
    // removestr --file /aida/aida.txt --pos 3:2 --size 4 f
    if (!(strcmp(command, "removestr")))
    {
        dash_file();
        printf("1\n");
        r();
        printf("2\n");
        (doctor_death(address));
        printf("3\n");
        dash_pos();
        printf("4\n");
        dash_size();
        printf("5\n");
        dash_f_b();
        printf("f_b is %d\n", f_b);
        printf("6\n");
        place_checker(address, y, x, size);
        printf("7\n");
        undo_memory(address);
        printf("8\n");
        remove_commander(address, y, x, size, f_b);
        Done();
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
        place_checker(address, y, x, size);
        copy_str(address, y, x, size, f_b);
        Done();
    }
    if (!(strcmp(command, "pastestr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_pos();
        place_checker(address, y, x, size);
        undo_memory(address);
        paste_str(address, y, x);
        Done();
    }
    if (!(strcmp(command, "cutstr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_pos();
        dash_size();
        dash_f_b();
        place_checker(address, y, x, size);
        undo_memory(address);
        // remove_str(address , y , x, size ,f_b);
        Done();
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
        Done();
    }
    if (!strcmp(command, "auto_indent"))
    {
        r();
        doctor_death(address);
        undo_memory(address);
        auto_indent(address);
        Done();
    }
    if (!strcmp(command, "tree"))
    {
        /*int depth;
        scnaf("%d", &depth);
        tree(depth);*/
    }
    if (!strcmp(command, "undo"))
    {
        dash_file();
        r();
        doctor_death(address);
        undo_memory(address);
        undo(address);
        Done();
    }
    else
        error(0);
}

//                               *****************ERROR LIST*****************

void error(int num)
{
    switch (num)
    {
    case 0:

        printf("Invalid command!\n");
        exit(1);

    case 1:

        printf("No such file exists in Vim world!");
        exit(1);

    case 2:

        printf("File already exists in Vim world!");
        exit(1);

    case 3:

        printf("Invalid Address!");
        exit(1);

    case 4:

        printf("Invalid Name!"); // for folder and file name
        exit(1);

    case 5:

        printf("LINE : out of Range!");
        exit(1);

    case 6:

        printf("POS : out of Range!");
        exit(1);

    case 7:

        printf("Invalid Size!");
        exit(1);

    case 8:

        printf("Empty File!");
        exit(1);

    case 9:

        printf("Invalid Depth");
        exit(1);

    case 10:
        printf("Empty Clipboard!");
        exit(1);

    default:
        exit(0);
    }
}

void Done()
{
    printf("Done successfully!");
    exit(0);
}

//                                    *****************SYNTAX*******************

void dash_file()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);

    getchar();
    if (strcmp(syntax, "--file") != 0)
        error(0);

    printf("%s\n", syntax);
}

void dash_str()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    getchar();
    scanf("%[^-]s", &str);

    if (strcmp(syntax, "--str") != 0)
        error(0);

    printf("syntax is %s\n", syntax);
    printf("str is %s\n", str);
}

void dash_pos()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    getchar();
    scanf("%d", &y);
    getchar(); // for :
    scanf("%d", &x);

    if (strcmp(syntax, "--pos") != 0)
        error(0);

    if ((isdigit(x) != 0) || (isdigit(y) != 0))
        error(0);

    printf("syntax is %s\n", syntax);
    printf("y is %d and x is %d\n", y, x);
}

void dash_size()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    getchar();
    scanf("%d", &size);

    if (strcmp(syntax, "--size") != 0)
        error(0);

    if (isdigit(size) != 0)
        error(7);

    printf("syntax is %s\n", syntax);
    printf("size is %d\n", size);
}

void dash_f_b()
{
    getchar(); // for -
    char R = getchar();

    if (R == 'f')
    {
        f_b = 1;
        return;
    }
    else if (R = 'b')
    {
        f_b = 0;
        return;
    }
    else
        error(0);
}

//                                    ******************ADDRESS*******************

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
        error(3);
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
    /*current_slash++;
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
    return (address_copy);*/
}

//                                       ***************TOOLS*****************

void doctor_life(char *address) // 1 --> error
{
    FILE *file;
    file = fopen(address, "r");
    if (file != NULL)
    {
        fclose(file);
        error(2);
    }
    fclose(file);
    return;
}

void doctor_death(char *address) // 1 --> error
{
    FILE *file;
    file = fopen(address, "r");
    if (file == NULL)
    {
        fclose(file);
        error(1);
    }
    fclose(file);
    return;
}

void place_checker(char *address, int y, int x, int size) // (f = 1 & b = 0) //delay!
{
    FILE *file = fopen(address, "r");
    int y_counter = 1;
    int x_counter = 1;

    char ch = fgetc(file);

    while (y_counter < y && ch != EOF)
    {
        if (ch == '\n')
        {
            y_counter++;
        }

        ch = fgetc(file);
    }
    if (ch == EOF && (y - y_counter > 1))
        error(5);

    while (x_counter < x && ch != EOF)
    {
        ch = fgetc(file);
        x_counter++;
    }

    if (ch == EOF)
    {
        fclose(file);
        error(6);
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

void slash_counter()
{
    for (int i = 0; address[i] != '\0'; i++)
    {
        if (address[i] == '/')
            slash_num++;
    }
}

//                                 *****************VIM FUNCTIONS*****************

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
        create_folder(address);
    }
}

void create_file(char *address)
{
    doctor_life(address);

    FILE *file;
    fopen(address, "w");
    fclose(file);
    return;
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
    fclose(file);
    return;
}

void insert_str(char *address, char *text, int line_pos, int char_pos) // problem during automatic execution
{
    // printf("I am HERE\n");
    // printf("address is %s\n" , address);
    // printf("text is %s\n" ,text);
    // printf("y is %d and x is %d\n" , line_pos , char_pos);
    FILE *file, *copy;

    strcpy(address_copy, address);
    strcat(address_copy, "___copy");

    file = fopen(address, "r");
    copy = fopen(address_copy, "wb+");

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
    rename(address_copy, address);

    return;
}

void remove_commander(char *address, int y, int x, int size, int f_b)
{
    switch (f_b)
    {
    case 1:
        remove_str_f(address, y, x, size);

    case 0:
        remove_str_b(address, y, x, size);

    default:
        error(0);
    }
}

void remove_str_f(char *address, int y, int x, int size) //( f = 1 & b = 0) //incomplete
{
    // y starts from 1 and x starts from 0
    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    FILE *file = fopen(address, "r");
    FILE *copy = fopen(copy_name, "wb+");

    char ch;
    for (int i = 1; i < y; i++)
    {
        while (ch != '\n')
        {
            ch = fgetc(file);
            if (ch == EOF)
                error(5);

            fputc(ch, copy);
        }
    }

    for (int i = 0; i < x; i++)
    {
        ch = fgetc(file);
        fputc(ch, copy);
    }

    for (int i = 0; i < size; i++)
    {
        fgetc(file);
    }

    while (ch != EOF)
    {
        fputc(ch, copy);
        fgetc(file);
    }

    fclose(file);
    fclose(copy);

    remove(address);
    rename(address_copy, address);

    return;
}

void remove_str_b(char *address, int y, int x, int size)
{
    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    FILE *file = fopen(address, "r");
    FILE *copy = fopen(copy_name, "wb+");

    char ch;
    for (int i = 1; i < y; i++)
    {
        while (ch != '\n')
        {
            ch = fgetc(file);
            if (ch == EOF)
                error(5);

            fputc(ch, copy);
        }
    }

    for (int i = 0; i < x; i++)
    {
        ch = fgetc(file);
        fputc(ch, copy);
    }

    fseek(copy, -size, SEEK_CUR);

    for (int i = 0; i < size; i++)
    {
        fgetc(file);
    }

    while (ch != EOF)
    {
        fputc(ch, copy);
        fgetc(file);
    }

    fclose(file);
    fclose(copy);

    remove(address);
    rename(address_copy, address);

    return;
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
            error(5);
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
    fclose(file);
    return;
}

void paste_str(char *address, int y, int x)
{
    FILE *file = fopen(address, "w");

    if (clipboard == NULL)
        error(10);

    for (int line = 0; line < y; line++)
    {
        fgets(content, MAXSIZE, file);
        if (content == NULL)
        {
            fclose(file);
            error(5);
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
    fclose(file);
    return;
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
    FILE *A = fopen(file_A, "r");
    FILE *B = fopen(file_B, "r");
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
    FILE *file = fopen(file_A, "r");

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
    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    FILE *file = fopen(address, "r");
    FILE *copy = fopen(copy_name, "w");

    char *ch;
    fgets(ch, MAXSIZE, file);
    if (ch == NULL)
        error(8);

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
            return;
        }
    }
}

void undo_memory(char *address)
{
    char copy_name[MAXSIZE];
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    FILE *file = fopen(address, "r");
    FILE *copy = fopen(copy_name, "w");

    fseek(file, 0, SEEK_SET);
    char ch = fgetc(file);
    while (ch != EOF)
    {
        fputc(ch, copy);
        ch = fgetc(file);
    }

    fclose(file);
    fclose(copy);
    return;
}

void undo(char *address)
{
    char copy_name[MAXSIZE];
    strcpy(copy_name, address);
    strcat(copy_name, "___copy");

    printf("%s\n", copy_name);

    FILE *file = fopen(address, "r");
    FILE *copy = fopen(copy_name, "r");

    fclose(file);
    fclose(copy);

    // printf("%s\n", address);
    // printf("%s\n", copy_name);

    remove(address);
    rename(copy_name, address);
    return;
}

void tree(int depth) // incomplete
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
