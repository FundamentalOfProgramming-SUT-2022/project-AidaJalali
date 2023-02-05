// Aida Jalali : 401170542
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
int line_counter(char *, int); // line = 1
int character_counter(char *, int);
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
int main()
{
    printf("Hi!\nwelcome to vim world!\nplease enter your command.\nFor more information use help\n\n");
    commander();
    // Test List
    //    createfile --file /tea/aida.txt            (address with /)
    //    createfile --file "/apple/lolo/maryam.txt" (address with ")
    //    cat --file  /test1.txt  (address with /)
    //    cat --file "/test1.txt" (address with ")
    //    insertstr --file /test1.txt --str boz manam to to --pos 3:5  (It doesn't support \\n item)
    //    removestr --file /test1.txt --pos 2:2 --size 3 -f
    //    copystr --file /test1.txt --pos 1:2 --size 2 f
    //    pastestr --file /test2.txt --pos 3:2
    //    cutstr --file /test1.txt --pos 2:4
    //    find --str toto --file /test1.txt
    //    find --str toto --file /test1.txt --count
    //    find --str toto --file /test1.txt --at 2
    //    find --str toto --file /test1.txt --byword
    //    find --str toto --file /test1.txt --all
    //    find --str toto --file /test1.txt --count --at 3
    //    find --str "toto is moyo" --file /test1.txt
    //    find --str "toto is \*motot tototo " --file /test1.txt
    //    replace --str1 toto --str2 aida --file /test1.txt
    //    replace --str1 toto --str2 aida --file /test1.txt --all
    //    replace --str1 toto --str2 aidakhare --file /test1.txt --at 1
    //    grep --str toto --files root/test1.txt root/test2.txt root/test3.txt
    //    grep -c --str toto --files root/test1.txt root/test2.txt root/test3.txt
    //    auto_indent /test3.txt
    //    compare root/test1.txt root/test2.txt (it doesn't support normal address)
    //    tree 3  //It doesn't support depth
    //    undo --file /test1.txt
}
void commander()
{
    scanf("%[^ ]s", &command);
    getchar();
    if (!strcmp(command, "help"))
    {
        printf("list :\n");
        printf("createfile        |  createfile --file name_of_file                                \n");
        printf("cat               |  cat        --file name_of_file                                \n");
        printf("insert            |  insert     --file name_of_file --str content --pos y:x        \n");
        printf("remove            |  removestr  --file name_of_file --pos y:x --size size f_b      \n");
        printf("copy              |  copystr    --file name_of_file --pos y:x --size size f_b      \n");
        printf("paste             |  pastestr   --file name_of_file --pos y:x                      \n");
        printf("cut               |  cutstr     --file name_of_file --pos y:x --size size f_b      \n");
        printf("grep              |  grep       --str (option) content --files name_of_files       \n");
        printf("auto-indent       |  auto-indent name_of_file                                      \n");
        printf("compare           |  compare     name_of_file_A name_of_file_B                     \n");
        printf("tree              |  tree        depth                                             \n");
        printf("undo              |  undo        --file name_of_file                               \n");
        printf("find              |  find        --str content --file name_of_file  option         \n");
        printf("replace           |  replace    --str1 content --str2 content --file name_of_file  \n");
        printf("arman             |                                                                \n");
        return;
    }
    if (!(strcmp(command, "createfile")))
    {
        dash_file();
        r();
        current_slash = 0;
        doctor_life(address);
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
    if (!(strcmp(command, "insertstr")))
    {
        dash_file();
        r();
        doctor_death(address);
        dash_str(str);
        dash_pos();
        undo_memory(address);
        insert_str(address, str, y, x);
        Done();
    }
    if (!(strcmp(command, "removestr")))
    {
        dash_file();
        r();
        (doctor_death(address));
        dash_pos();
        dash_size();
        dash_f_b();
        place_checker(address, y, x, size);
        undo_memory(address);
        remove_commander(address, y, x, size, f_b);
        Done();
    }
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
        copy_str(address, y, x, size, f_b);
        remove_commander(address, y, x, size, f_b);
        Done();
    }
    if (!(strcmp(command, "grep")))
    {
        dash_option();
        dash_str(str);
        dash_files();
        grep_commander(file_list);
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
        address[0] = '\0';
        address[0] = 'r';
        address[1] = 'o';
        address[2] = 'o';
        address[3] = 't';
        int depth;
        scanf("%d", &depth);
        tree(address, depth);
    }
    if (!strcmp(command, "undo"))
    {
        dash_file();
        r();
        doctor_death(address);
        undo(address);
        Done();
    }
    if (!strcmp(command, "find"))
    {
        dash_str(str);
        dash_str_find();
        dash_file();
        r();
        doctor_death(address);
        dash_find_option();
        check_pattern();
        find_commander();
        Done();
    }
    if (!(strcmp(command, "replace")))
    {
        dash_str(str1);
        dash_str(str2);
        dash_file();
        r();
        doctor_death(address);
        dash_find_option();
        check_pattern();
        replace_commander();
        Done();
    }
    else
        error(0);
}
// ERROR LIST
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
    case 11:
        printf("Unable to create folder!");
        exit(1);
    case 12:
        printf("No such Directory exists in Vim world!");
        exit(1);
    case 13:
        printf("Invalid Pattern!");
        exit(1);
    case 14:
        printf("%s Not Found!", str);
        exit(0);
    case 15:
        printf("0"); // Not Found! (count --> 0)
        exit(1);
    case 16:
        printf("-1"); //(at --> -1)
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
// SYNTAX
void dash_file()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    getchar();
    if (strcmp(syntax, "--file") != 0)
        error(0);
}
void dash_str(char *str)
{
    char syntax[MAXSIZE];
    char temp[MAXSIZE];
    scanf("%s", &syntax);
    getchar();
    scanf("%[^-]s", &temp);
    if ((strcmp(syntax, "--str") != 0) && (strcmp(syntax, "-str") != 0) && strcmp(syntax, "str") != 0 && (strcmp(syntax, "--str1") != 0) && (strcmp(syntax, "--str2") != 0))
        error(0);
    if (temp[0] == '"')
    {
        for (int i = 0; i < strlen(temp) - 3; i++)
        {
            str[i] = temp[i + 1];
        }
    }
    else
    {
        for (int i = 0; i < strlen(temp); i++)
        {
            str[i] = temp[i];
        }
    }
    return;
}
void dash_str_find()
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '*')
        {
            if ((int)str[i - 1] == 92)
            {
                for (int j = 0; j < strlen(str) - 1; j++)
                {
                    if (i != j)
                    {
                        str_copy[j] = str[i];
                    }
                }
                str[0] = '\0';
                for (int k = 0; k < strlen(str_copy); k++)
                {
                    str[k] = str_copy[k];
                }
                return;
            }
            else
            {
                printf("toooo rohe wildcard\n");
                exit(1);
            }
        }
    }
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
}
void dash_files()
{
    char syntax[MAXSIZE];
    scanf("%s", &syntax);
    if (strcmp(syntax, "--files") != 0)
        error(0);
    getchar();
    gets(file_list);
}
void dash_option()
{
    getchar(); // for -
    option = getchar();
    if ((option != '-') && (option != 'l') && (option != 'c'))
        error(0);
    return;
}
void dash_f_b()
{
    getchar();
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
void dash_find_option()
{
    for (int i = 0; i < 4; i++)
    {
        find_option[i] = 0;
    }
    char option[MAXSIZE];
    for (int i = 0; i < 4; i++)
    {
        char R = getchar();
        if (R == '\n')
            break;
        scanf("%s", option);
        if (!strcmp(option, "--count") || !strcmp(option, "-count"))
        {
            find_option[0] = 1;
        }
        if (!strcmp(option, "--at") || !strcmp(option, "-at"))
        {
            scanf("%d", &s);
            find_option[1] = 1;
        }
        if (!strcmp(option, "--byword") || !strcmp(option, "-byword"))
        {
            find_option[2] = 1;
        }
        if (!strcmp(option, "--all") || !strcmp(option, "-all"))
        {
            find_option[3] = 1;
        }
    }
    return;
}
// ADDRESS
void r()
{
    char R;
    scanf("%c", &R);
    if (R == '/')
    {
        address_maker_A();
        return;
    }
    else if (R == '"')
    {
        address_maker_B();
        return;
    }
    else
        error(3);
}
void address_maker_A()
{
    char temp[MAXSIZE];
    scanf("%s", &temp);
    strcat(address, temp);
    slash_counter();
    return;
}
void address_maker_B()
{
    char temp1[MAXSIZE];
    char temp2[MAXSIZE];
    getchar(); // for /
    scanf("%s", &temp1);
    for (int i = 0; i < strlen(temp1) - 1; i++)
    {
        temp2[i] = temp1[i];
    }
    strcat(address, temp2);
    slash_counter();
    return;
}
// TOOLS
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
int character_counter(char *address, int x)
{
    char ch;
    FILE *file;
    file = fopen(address, "rb+");
    ch = fgetc(file);
    while (ch != EOF)
    {
        ch = fgetc(file);
        x++;
    }
    fclose(file);
    return x;
}
void slash_counter()
{
    for (int i = 0; i < strlen(address); i++)
    {
        if (address[i] == '/')
        {
            slash_num++;
        }
    }
}
void check_pattern()
{
    if (find_option[0] == 1 && find_option[1] == 1)
        error(13);
    if (find_option[1] == 1 && find_option[3] == 1)
        error(13);
    else
        return;
}
// FUNCTIONS
void create_folder(char *address)
{
    strcpy(address_copy, address);
    char *token = strtok(address_copy, "/"); // first token is root/ and we don't need it
    current_slash++;
    char temp[MAXSIZE];
    strcpy(temp, token);
    strcat(temp, "/");
    while (slash_num > current_slash)
    {
        token = strtok(NULL, "/");
        strcat(temp, token);
        strcat(temp, "/");
        int check = mkdir(temp);
        if (check)
            error(11);
        current_slash++;
    }

    create_file(address);
}
void create_file(char *address)
{
    FILE *file = fopen(address, "w");
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
    FILE *file, *copy;
    strcpy(address_copy, address);
    strcat(address_copy, "___copy");
    file = fopen(address, "rb+");
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
                for (int j = 0; j < strlen(text); j++)
                {
                    if (text[j] == '\\')
                        fputc('\\', copy);
                    else
                        fputc(text[j], copy);
                }
                break;
            }
        }
        else
        {
            fputc(ch, copy);
            if (current_line == line_pos)
            {
                if (current_char == char_pos)
                {
                    for (int j = 0; j < strlen(text); j++)
                    {
                        if (text[j] == '\\')
                        {
                            fputc('\\', copy);
                        }
                        else
                        {
                            fputc(text[j], copy);
                        }
                    }
                }
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
        return;
    case 0:
        remove_str_b(address, y, x, size);
        return;
    default:
        error(0);
    }
}
void remove_str_f(char *address, int y, int x, int size) //( f = 1 & b = 0)
{
    // y starts from 1 and x starts from 0
    int n = character_counter(address, 0);
    int n_2 = 0;
    strcpy(address_copy, address);
    strcat(address_copy, "___copy");
    FILE *file = fopen(address, "rb+");
    FILE *copy = fopen(address_copy, "wb+");
    for (int i = 1; i < y; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        fputs(line, copy);
        n_2 += strlen(line);
    }
    for (int j = 0; j < size; j++)
    {
        fgetc(file);
        n_2++;
    }
    char ch;
    for (int k = n_2; k < n; k++)
    {
        ch = fgetc(file);
        fputc(ch, copy);
    }
    fclose(file);
    fclose(copy);
    remove(address);
    rename(address_copy, address);
    return;
}
void remove_str_b(char *address, int y, int x, int size)
{
    strcpy(address_copy, address);
    strcat(address_copy, "___copy");
    FILE *file = fopen(address, "rb+");
    FILE *copy = fopen(address_copy, "wb+");
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
        fgetc(file);
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
    int n = character_counter(address, 0);
    int n_2 = 0;
    address_copy[0] = 'r';
    address_copy[1] = 'o';
    address_copy[2] = 'o';
    address_copy[3] = 't';
    address_copy[4] = '/';
    strcat(address_copy, "_clipboard");
    FILE *file = fopen(address, "rb+");
    FILE *copy = fopen(address_copy, "wb+");
    for (int i = 1; i < y; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        n_2 += strlen(line);
    }
    char ch;
    for (int j = 0; j < size; j++)
    {
        ch = fgetc(file);
        fputc(ch, copy);
        n_2++;
    }
    for (int k = n_2; k < n; k++)
    {
        ch = fgetc(file);
    }
    fclose(file);
    fclose(copy);
    return;
}
void paste_str(char *address, int y, int x)
{
    int n = character_counter(address, 0);
    int n_2 = 0;
    address_copy[0] = 'r';
    address_copy[1] = 'o';
    address_copy[2] = 'o';
    address_copy[3] = 't';
    address_copy[4] = '/';
    strcat(address_copy, "_clipboard");
    FILE *file = fopen(address, "rb+");
    FILE *copy = fopen(address_copy, "wb+");
    char r;
    r = fgetc(copy);
    if (r == EOF)
        error(10);
    for (int i = 1; i < y; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        n_2 += strlen(line);
    }
    char ch;
    for (int j = 0; j < size; j++)
    {
        ch = fgetc(file);
        fputc(ch, copy);
        n_2++;
    }
    for (int k = n_2; k < n; k++)
    {
        fgetc(file);
    }
    fclose(file);
    fclose(copy);
    remove(address_copy);
    return;
}
void find_commander()
{
    if (find_option[0] == 1)
    {
        find_0(); // count option
        find_option[0] == -1;
    }
    if (find_option[1] == 1)
    {
        find_1(); // at option
        find_option[1] == -1;
    }
    if (find_option[2] == 1)
    {
        find_2(); // byword option
        find_option[2] == -1;
    }
    if (find_option[3] == 1)
    {
        find_3(); // all option
        find_option[3] == -1;
    }
    if (find_option[0] == 0 && find_option[1] == 0 && find_option[2] == 0 && find_option[3] == 0)
    {
        find_ww();
    }
    return;
}
void find_ww()
{
    FILE *file = fopen(address, "rb+");
    int n = line_counter(address, 1);
    ch_counter = 0;
    for (int i = 0; i < n; i++, ch_counter++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        for (int j = 0; j < strlen(line); j++, ch_counter++)
        {
            while (line[j] == str[k])
            {
                k++;
                j++;
                ch_counter++;
            }
            if (strlen(str) == k)
            {
                printf("It starts from character %d\n", ch_counter - k);
                fclose(file);
                return;
            }
            k = 0;
        }
    }
    fclose(file);
    error(14);
}
void find_0() // count
{
    FILE *file = fopen(address, "rb+");
    int n = line_counter(address, 1);
    int k;
    ans = 0;
    for (int i = 0; i < n; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        k = 0;
        for (int j = 0; j < strlen(line); j++)
        {
            while (line[j] == str[k])
            {
                k++;
                j++;
            }
            if (strlen(str) == k)
            {
                ans++;
                k = 0;
            }
            k = 0;
        }
    }
    if (ans == 0)
    {
        fclose(file);
        error(15);
    }
    printf("pattern repetition : %d\n", ans);
    fclose(file);
    return;
}
void find_1() // at
{
    FILE *file = fopen(address, "rb+");
    int n = line_counter(address, 1);
    int character_num = 0;
    ans = 0;
    for (int i = 0; i < n; i++, character_num++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        for (int j = 0; j < strlen(line); j++, character_num++)
        {
            while (line[j] == str[k])
            {
                character_num++;
                k++;
                j++;
            }
            if (strlen(str) == k)
            {
                ans++; // we need this for copy file
                k = 0;
                if (ans == s)
                {
                    printf("character position :%d\n", character_num - k);
                    fclose(file);
                    return;
                }
            }
        }
    }
    if (ans == 0)
    {
        fclose(file);
        error(15);
    }
    fclose(file);
    return;
}
void find_2() // byword
{
    FILE *file = fopen(address, "rb+");
    int n = line_counter(address, 1);
    word = 0;
    word_str = 0;
    ans = 0;
    for (int i = 0; i < n; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        for (int j = 0; j < strlen(line); j++)
        {
            if (line[j] == ' ')
                word++;
            while (line[j] == str[k])
            {
                if (line[j] == ' ')
                    word++;
                k++;
                j++;
                ans++;
            }
            if (strlen(str) == k)
            {
                for (int k = 0; k < strlen(str); k++)
                {
                    if (str[k] == ' ')
                        word_str++;
                }
                printf("word : %d\n", word - word_str);
                fclose(file);
                return;
            }
        }
    }
    if (ans == 0)
    {
        fclose(file);
        error(15);
    }
    fclose(file);
    return;
}
void find_3() // all
{
    FILE *file = fopen(address, "rb+");
    int n = line_counter(address, 1);
    int ch_counter = 0;
    ans = 0;
    for (int i = 0; i < n; i++, ch_counter++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        for (int j = 0; j < strlen(line); j++, ch_counter++)
        {
            while (line[j] == str[k])
            {
                k++;
                j++;
                ans++;
            }
            if (strlen(str) == k)
            {
                printf("%d\n", ch_counter - k);
                k = 0;
            }
        }
    }
    if (ans == 0)
    {
        fclose(file);
        error(15);
    }
    fclose(file);
    return;
}
void replace_commander()
{
    if (find_option[1] == 1) // at option
    {
        replace_1();
        find_option[1] = -1;
    }
    if (find_option[3] == 1) // all option
    {
        replace_2();
        find_option[3] = -1;
    }
    if (find_option[1] == 0 && find_option[3] == 0)
    {
        replace();
    }
    return;
}
void replace()
{
    FILE *file, *copy;
    strcpy(address_copy, address);
    strcat(address_copy, "___copy");
    file = fopen(address, "rb+");
    copy = fopen(address_copy, "wb+");
    int n = line_counter(address, 1);
    int flag = 0;
    ch_counter = 0;
    for (int i = 0; i < n; i++, ch_counter++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        if (flag == 1)
            break;
        for (int j = 0; j < strlen(line); j++, ch_counter++)
        {
            while (line[j] == str1[k])
            {
                k++;
                j++;
                ch_counter++;
            }
            if (strlen(str1) == k)
            {
                ans = ch_counter - k; // we need this for copy file
                flag = 1;
                break;
            }
            k = 0;
        }
    }
    if (ans < 0)
    {
        fclose(file);
        fclose(copy);
        remove(address);
        rename(address_copy, address);
        error(14);
    }
    else
    {
        fseek(file, 0, SEEK_SET);
        for (int i = 0; i < ans; i++)
        {
            char ch = fgetc(file);
            fputc(ch, copy);
        }
        for (int x = 0; x < strlen(str1) - 1; x++)
        {
            fgetc(file);
        }
        for (int j = 0; j < strlen(str2); j++)
        {
            fputc(str2[j], copy);
        }
        char ch = fgetc(file);
        while (ch != EOF)
        {
            fputc(ch, copy);
            ch = fgetc(file);
        }
    }
    fclose(file);
    fclose(copy);
    remove(address);
    rename(address_copy, address);
    return;
}
void replace_1() // at function
{
    FILE *file, *copy;
    strcpy(address_copy, address);
    strcat(address_copy, "___copy");
    file = fopen(address, "rb+");
    copy = fopen(address_copy, "wb+");
    int n = line_counter(address, 1);
    int flag = 0;
    ch_counter = 0;
    ans = 0;
    for (int i = 0; i < n; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        if (flag == 1)
            break;
        for (int j = 0; j < strlen(line); j++, ch_counter++)
        {
            if (flag == 1)
                break;
            while (line[j] == str1[k])
            {
                ch_counter++;
                k++;
                j++;
            }
            if (strlen(str1) - 1 == k)
            {
                ans = ch_counter - k;
                word++;
                k = 0;
                if (word == s - 1)
                {
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (s - 1 != word)
    {
        fclose(file);
        fclose(copy);
        remove(address);
        rename(address_copy, address);
        error(15);
    }
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < ans; i++)
    {
        char ch = fgetc(file);
        fputc(ch, copy);
    }
    for (int x = 0; x < strlen(str1) - 1; x++)
    {
        fgetc(file);
    }
    for (int j = 0; j < strlen(str2) - 1; j++)
    {
        fputc(str2[j], copy);
    }
    char ch = fgetc(file);
    while (ch != EOF)
    {
        fputc(ch, copy);
        ch = fgetc(file);
    }
    fclose(file);
    fclose(copy);
    remove(address);
    rename(address_copy, address);
    return;
}
void replace_2() // all function
{
    FILE *file = fopen(address, "rb+");
    int n = line_counter(address, 1);
    int k;
    ans = 0;
    for (int i = 0; i < n; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        k = 0;
        for (int j = 0; j < strlen(line); j++)
        {
            while (line[j] == str1[k])
            {
                k++;
                j++;
            }
            if (strlen(str1) - 1 == k)
            {
                ans++; // we need this for copy file
                k = 0;
            }
        }
    }
    if (ans == 0)
    {
        fclose(file);
        // error(15);
    }
    fclose(file);
    for (int i = 0; i < ans; i++)
    {
        replace();
    }
}
void grep_commander(char *file_list)
{
    token = strtok(file_list, " ");
    doctor_death(token);
    grep(token, str);
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            doctor_death(token);
            grep(token, str);
        }
    }
    if (option == 'c')
    {
        printf("%d\n", c);
        return;
    }
}
void grep(char *add, char *str)
{
    FILE *file = fopen(add, "r");
    int n = line_counter(add, 1);
    for (int i = 0; i < n; i++)
    {
        char line[MAXSIZE];
        fgets(line, MAXSIZE, file);
        int k = 0;
        for (int j = 0; j < strlen(line); j++)
        {
            while (line[j] == str[k])
            {
                k++;
                j++;
            }
            if (strlen(str) == k)
            {
                if (option == '-')
                {
                    printf("%s\t%s\n", add, line);
                    k = 0;
                    break;
                }
                else if (option == 'l')
                {
                    printf("%s\n", add);
                    k = 0;
                    break;
                }
                else if (option == 'c')
                {
                    c++;
                    k = 0;
                    break;
                }
            }
            k = 0;
        }
    }
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
    FILE *file, *copy;
    strcpy(address_copy, address);
    strcat(address_copy, "___copy");
    file = fopen(address, "rb+");
    copy = fopen(address_copy, "wb+");
    char ch;
    ch = fgetc(file);
    if (ch == EOF)
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
            rename(address_copy, address);
            return;
        }
    }
}
void undo_memory(char *address)
{
    char copy_name[MAXSIZE];
    strcpy(copy_name, address);
    strcat(copy_name, "_copy");
    FILE *file = fopen(address, "rb+");
    FILE *copy = fopen(copy_name, "wb+");
    fseek(file, 0, SEEK_SET);
    char ch = fgetc(file);
    while (ch != EOF)
    {
        fputc(ch, copy);
        ch = fgetc(file);
    }
    fclose(copy);
    fclose(file);
    return;
}
void undo(char *address)
{
    char copy_name[MAXSIZE];
    strcpy(copy_name, address);
    strcat(copy_name, "_copy");
    FILE *file = fopen(address, "r");
    FILE *copy = fopen(copy_name, "r");
    fclose(file);
    fclose(copy);
    remove(address);
    rename(copy_name, address);
    return;
}
void tree(char *address, int depth)
{
    if (depth == -1)
        error(9);
    DIR *directory = opendir(address);
    if (directory == NULL)
        error(12);
    printf("\t\t|%s\n\t\t|\n", address);
    struct dirent *item;
    item = readdir(directory);
    while (item != NULL && depth > 0)
    {
        printf("\t\t|---");
        printf("%s%s\n\t\t|\n", address, item->d_name);
        if (item->d_type == DT_DIR && strcmp(item->d_name, ".") != 0 && strcmp(item->d_name, "..") != 0)
        {
            char path[100] = {0};
            strcat(path, address);
            strcat(path, "/");
            strcat(path, item->d_name);
            tree(path, depth - 1);
        }
        item = readdir(directory);
    }
    closedir(directory);
}