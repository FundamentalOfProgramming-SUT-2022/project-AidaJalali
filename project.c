#include <stdio.h>
#include <sys\stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define MAXSIZE 1024

//TOOLS
void commander();
    char command[MAXSIZE];

//Tools->Error Functions
void error();               
int doctor_life(char *);    
int doctor_death(char *);   

//Tools->Address Functions

char address[MAXSIZE];

//recognizer address type
void r();

//A) address without quotation
void address_maker_A(); 
//B) address with quotation
void address_maker_B();

char* chopchop();
    void slash_counter();
        int slash_num = 0;
        int current_slash = 1;
    char address_copy[MAXSIZE];

//syntax
void dash_file();
void dash_pos();
void dash_str();

void dash_size(); 
    int size;

int  dash_f_b();
    int f_b;

//Tools->else
int find_pos(char*,int,int,int); //find the byte number
char* find_str(int,int);

//Vim Functions
void create_file(char *);
void create_folder(char *);
void cat_file(char *);
void insert_str(char *, char *, int, int);
void remove_str(char *, int, int, int ,int);
void copy_str(char *);
void paste_str(char*);
void cut_str(char*);


// global Variable
char str[MAXSIZE]; // for remove and find_str


// *commands list*           *format*


// createfile       |  createfile -- file name of file      
// cat              |                           
// insert           |                           
// remove           |                           
//copystr           |                           
//pastestr          |                              
//cutstr            |                          
//replace           |                     
//grep              |                                               
//undo              |
//auto_indent       |
//compare           |
//tree              |


int main(int argc , char * argv[])
{
    printf("Hi!\nwelcome to vim world!\nplease enter your command.\n\n");
    commander();
}


void commander()
{
    scanf("%[^ ]s" , &command);
    getchar();
    if (!(strcmp(command, "createfile")))
    {
        dash_file();
        r();
        create_folder(address);
        return;
    }

    if ( !( strcmp (command, "cat") ) )
    {
        dash_file();
        r();
        cat_file(address);
        return;
    }

    if( ! ( strcmp (command,"insert") ) )
    {
        /*dash_file();
        r();
        dash_str();
        insert_str(address , "this is a test!this is a test!" , 50 , 2);
        return;*/
    }
    
    if( ! ( strcmp (command,"remove") ) )
    {
        /*dashfile();
        r();
        dash_str();
        remove_str(address , 2 , 3 , 10 , 0);
        return;*/
    }
    if(!(strcmp(command,"copy")))
    {
        /*dash_file();
        r();
        dash_str();*/
    }
    if(!(strcmp(command,"paste")))
    {
        /*dash_file();
        r();
        dash_str();*/
    }
    if(!(strcmp(command, "cut")))
    {
        /*dash_file();
        r();
        dash_str();*/
    }
    else error();
}

void r()
{
    char R;
    scanf("%c" , &R);
    if(R == '/')
    {
        address_maker_A();
        return;
    }
    if(R == '"')
    {
        address_maker_B();
        return;
    }
    else error();
}


void address_maker_A()
{
    scanf("%[^ ]s" , &address);
    slash_counter();
    return;
}

void address_maker_B()
{
    //Empty
}

char* chopchop()
{
    int counter = 0 ;
    for( int i = 0 ; counter < current_slash ; i++)
    {   
        if( address[i] == '/')
        {
            counter++ ;
            if(counter == current_slash) break;
        } 
        address_copy[i] = address[i];
    }
current_slash ++;
return(address_copy);
}

void slash_counter()
{
    for(int i = 0 ; address[i] != '\0' ; i++)
    {
        if(address[i] == '/') slash_num++;
    }
}

void dash_file()
{   
    char syntax[MAXSIZE];
    scanf("%[^ ]s" , &syntax);
    getchar();
    if(strcmp(syntax,"--file")) error();
}

void dash_str()
{   
    char syntax[MAXSIZE];
    scanf("%[^ ]s" , &syntax);
    getchar();
    if(strcmp(syntax,"-str")) error();
}

void dash_pos()
{
    char syntax[MAXSIZE];
    scanf("%[^ ]s" , &syntax);
    getchar();
    if(strcmp(syntax,"-pos")) error();
    //continue
}

void dash_size()
{
    char syntax[MAXSIZE];
    scanf("%[^ ]s" , &syntax);
    getchar();
    if(strcmp(syntax,"-size")) error();
    //continue
}

void dash f_b()
{
    char syntax[MAXSIZE];
    scanf("%[^ ]s" , &syntax);
    getchar();
    if(strcmp(syntax,"-f") || strcmp(syntax , "-b")) error();
    //continue
}


void error()
{
    printf("invalid command!");
    exit(0);
}

int doctor_life(char * address) 
{
    FILE *file ;
    file = fopen(address, "r");
    if(file != NULL)
    {
        printf("file is alive!\n\n");
        fclose(file);
        return 1;
    }
    else return 0 ;
}

int doctor_death( char* address)
{
    FILE * file;
    file = fopen( address , "r");
    if(file == NULL)
    {
        printf("No such file exists in Vim world!\n\n");
        fclose(file);
        return 1;
    }
    else return 0 ;
}

int find_pos(char *address ,int line_pos, int char_pos,int direction) // (f = 1 & b = 0) //delay!
{
    FILE *file;
    file = fopen(address , "wb");
    for( int i = 0 ; i < line_pos - 1; i++)
    {
        while(1)
        {
            char c = fgetc(file);
            if( c == '\n')break;
        }
    }
    int count = ftell(file);
    fclose(file);
    if(direction)
    {
        return(count + char_pos);
    }
    else return(count - char_pos);
}

char* find_str(int x,int size)
{
    FILE* file;
    file = fopen(address,"wb");
    fseek(file , x , SEEK_SET);
    for(int i = 0 ; i <= size ;i++)
    {
        str[i] = fgetc(file);
    }
    fclose(file);
    return str;
}


//                                 *****************Vim Functions*************** 


void create_folder(char *address)
{
    if( slash_num == current_slash)
    {
        create_file(address);
        return;
    }
    while(slash_num >= current_slash)
    {
        //printf("%d %d\n" , slash_num ,current_slash);
        int check = mkdir(chopchop());
        printf("****%s\n" ,address_copy);

        //if(check) error();
        
        if(!check)
            printf("Nai Nai folder created!\n");
            continue;
    }   
}

void create_file(char *address)
{
    if(doctor_life(address)) return;
    chopchop(address);
    
    FILE  *file;
    fopen(address, "w");
    printf("Nai Nai file created\n");
    fclose(file);
}

void cat_file(char *address)
{
    if (doctor_death(address) == 1)
    {
        return;
    }
    else
    {
        FILE * file;
        file = fopen(address , "r");
        char ch;
        while (!feof(file))
        {
            ch = fgetc(file);
            printf("%c", ch);
        }
        fclose(file);
    }
}

void insert_str(char *address, char *text, int line_pos, int char_pos)
{
  if(doctor_death(address) == 1) return;
    
    FILE  *file ,*copy ;

    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name,address);
    strcat(copy_name,"___copy");

    file = fopen(address , "r");
    copy = fopen(copy_name, "w");
    
    int current_line = 1;
    int current_char = 0;
        
    while(1)
     {
        char ch ;
        int i = 0;
        ch = fgetc(file);

        if(feof(file))
        {
            if(current_line > line_pos) break;

            else if(current_line < line_pos)
            {
                fputc('\n' ,copy);
                current_line++;
            }
            else
            {
                for( int i = 0 ; i < char_pos ; i++ )
                {
                    printf("\n");
                    fputc( ' ' , copy);
                }
                fputs( text , copy) ;
                break;
            }
        }

        else{

            fputc(ch ,copy); 
            if(current_line == line_pos)
            {
                if( current_char == char_pos) fputs(text , copy);
                current_char++;
            }
            if(ch == '\n')  current_line++;
            }
    }

    fclose(file);
    fclose(copy);

    rename(copy_name,address);
    remove(address);

    printf("text inserted!\n");
    
}

void remove_str( char* address , int line_pos , int char_pos , int size , int direction)//( f = 1 & b = 0) //problem
{
    if(doctor_death(address) == 1) return;

    FILE  *file ,*copy ;

    char copy_name[MAXSIZE] = {0};
    strcpy(copy_name,address);
    strcat(copy_name,"___copy");

    file = fopen(address , "r");
    copy = fopen(copy_name, "w");

    //int x = find_pos(address,line_pos,char_pos,direction);
    int x = 32 ;

    while(!EOF)
    {
        char ch = fgetc(file);
        if( ftell(file) == x)
        {
           for( int i = 0 ; i < size ; i++)
           {
            fgetc(file);
           }
        }
        else fputc(ch ,copy);
    }

    fclose(file);
    fclose(copy);
    rename(copy_name,address);
    remove(address);

    printf("text removed!\n");
}

void copy_str(char * str)
{
    OpenClipboard(0);
    EmptyClipboard();
    const size_t len = strlen(str) + 1 ;
    HGLOBAL H = GlobalAlloc(GMEM_MOVEABLE , len);
    GlobalUnlock(H);
    SetClipboardData(CF_TEXT, H);
    CloseClipboard();
}

void paste_str(char * address)
{
    HANDLE H;
    char * str;
    OpenClipboard(0);
    H = GetClipboardData(CF_TEXT);
    strcpy(str , (char *)H) ; 
    CloseClipboard();
}

void cut_str(char * address)
{
    copy_str(str);
    remove(str);
}
