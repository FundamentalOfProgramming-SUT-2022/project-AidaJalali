#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1024

// bug bug bug

//                        ***********public function list************
void reception(char *);
int doctor_file(char *);
// char *chop_chop(char *);



//                        **************private function list************
void create_file(char *);
void create_folder(char *);
void cat_file(char *);
void insert_file(char *, char *, int, int);




// global Variable
char command[100];
char address[1000] = "root/file.txt";
int counter_of_slash = 1;
int flag = 0;

//                                  ********commands list*********
//                                        n out of standard

// createfile
// cat
// insert




int main()
{
    printf("Hi!\n\nwelcome to Vim Hospital!\n\nMy name is help doctor.\n\nIf you don't know where to go , please write 'help'\n\n");


    
    // input
    // scanf("%[^/]", command);
    // getchar();
    // scanf("%[^\n]", address);  // file...
    reception("createfile");
    //reception("cat");
    reception("insert");
}

//                    *****************PUBLIC FUNCTION***************


void reception(char *command)
{

    if (strcmp(command, "createfile") == 0)
    {
        /*while (flag == 0)
        {
            create_folder(address);
        }
        if (flag == 1)
        {
            // printf("%s" , address);
            create_file(address);
            return;
        }*/
        create_file(address);
    }

    if (strcmp(command, "cat") == 0)
    {
        cat_file(address);
        return;
    }

    if( strcmp(command,"insert") == 0)
    {

        insert_file(address , "hello" , 1 , 2);
    }

    else
        printf("You are very sick!\nyou need help!\n\n");
}

int doctor_file(char * address) 
{
    FILE *file ;
    file = fopen(address, "r");
    if(file != NULL)
    {
        printf("file is alive!\nfile is alive!\n\n");
        fclose(file);
        return 1;
    }
    else if (file == NULL)
    {
        printf("No such file exists in Vim world!\n\n");
        fclose(file);
        return 0;
    }
}


// Bugs for chop_chop :(

/*char *chop_chop(char *address)
{
    char *current;
    current = (char *)calloc(1000, sizeof(char));
    int count = 0;
    for (int i = 0; count < counter_of_slash + 1; i++)
    {
        if (address[i] == '\n')
        {
            flag = 1;
            return address;
        }
        if (address[i] == '/')
        {
            count++;
            if (count == counter_of_slash + 1)
            {
                break;
            }
        }
        *(current + i) = *(address + i);
    }
    counter_of_slash++;
    return current;
}*/





//                                        *********PRIVATE FUNCTION************



void create_file(char *address)
{
    if(doctor_file(address) == 1)
    {
        return;
    }
    else
    {
        FILE  *file;
        fopen(address, "w");
        printf("Nai Nai file created\n");
        fclose(file);
    }
}


void create_folder(char *address)
{
    int check;

    check = mkdir(address);
    if(check)
    {
        printf("Folder is alive!!!\n");
    }
    if (!check)
        printf("Nai Nai folder created\n");
    
}


void cat_file(char *address)
{
    if (doctor_file(address) == 0)
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



void insert_file(char *address, char *text, int write_line, int ch)
{
    
    if(doctor_file(address) == 1)
    {
        return;
    }

    FILE  *file ,*copy ;

    char copy_name[MAXSIZE];
    strcpy(copy_name,address);
    strcat(copy_name,"___copy");


    file = fopen(address , "r");
    copy = fopen(copy_name, "w");

    int check = 1; //variable for keep reading
    int current_line = 1;
    char line[MAXSIZE];
    
    do {
        fgets( line  , MAXSIZE , file);
        if(feof(file))
        {
            check = 0 ;
        }
        else if (current_line == write_line)
        {
            fputs( text , copy);
            //check for character
        }
        else 
        {
            current_line++;
        }

        fclose(file);
        fclose(copy);

        remove(address);
        rename(copy_name,address);
    } while (check == 1) ;

}


