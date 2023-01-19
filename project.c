#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void commander(char *command);
int create_file(char *);
void create_folder(char *);
char *chop_chop(char *);


char command[100];
char address[1000];
int counter_of_slash = 1;
int flag = 0;

// createfile__file/root/dir1/dir2/dir3/file.txt

int main()
{
    // input
    scanf("%[^/]", command);
    getchar();
    scanf("%[^\n]", address);
    commander(command);
}

void commander(char *command)
{
    if (strcmp(command, "createfile__file") == 0)
    {
        while (flag == 0)
        {

            create_folder(chop_chop(address));
        }
        if (flag == 1)
        {
            create_file(chop_chop(address));
            return;
        }
    }

    else
        printf("You idiot can't write the command correctly!\n");
}

char *chop_chop(char *address)
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
}

int create_file(char *address)
{
    FILE *file;
    file = fopen(chop_chop(address), "r");
    if (file != NULL)
    {
        printf("You idiot already made it!\n");
        fclose(file);
        return 1;
    }
    else
    {
        fopen(address, "w");
        printf("Nai Nai folder created\n");
        fclose(file);
    }
    return 0;
}

void create_folder(char *address)
{
    int check;

    check = mkdir(address);

    if (!check)
        printf("Nai Nai folder created\n");
    else
    {
        printf("You idiot already made it!\n");
    }
}
