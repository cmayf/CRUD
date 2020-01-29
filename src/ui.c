#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"


/* User Interface */

/* Checks if input is a valid length */
int input_limit(char* buffer, int limit)
{
  for(int i = 0; buffer[i]; ++i)
  {
    if(i > limit) return 0;
    if(buffer[i] == ' ') return 0;
    if(i == 0 && buffer[i] == '\n') return 0;
  }
  return 1;
}

void startup()
{
    printf("Starting...\n");
    get_data();
    printf("Startup complete.\n\n");
}

void username(struct User* u)
{
    printf("Enter your username to login to an existing account or create a new one.\n");
    printf("[Usernames have a 25 character limit, cannot contain spaces, and are case sensitive]\n\n");
    char input[500];
    printf("Username: ");
    fgets(input, sizeof(input), stdin);
    if(input_limit(input, 25) == 0)
    {
      printf("Invalid username. Try again.\n\n");
      username(u);
    }
    else
    {
      strtok(input, "\n");
      strcpy(u->username, input);
    }
    printf("\n");
}


void user_catalog(struct User* u)
{
    printf("\n____________________________________________________________________________________\n");
    printf("====================================================================================\n");
    printf("%s's Movie Catalog: \n", u->username);
    printf("------------------------------------------------------------------------------------\n");
    print_catalog(u->user_catalog);
    printf("____________________________________________________________________________________\n\n");
}


void options(struct User* u)
{
    printf("____________________________________________________________________________________\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("|                                     MAIN MENU                                    |\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("| Options: enter c, r, u, or d to select an option or \"quit\" to exit the program   |\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("| Create Entry (c) | Read Entry (r) | Update Entry (u) | Delete Entry (d) | : ");
    scanf("%5[^\n]", u->option);
    scanf("%*[^\n]");
    (void) getchar();
    printf("------------------------------------------------------------------------------------\n");
    if(strcmp("c", u->option) != 0 && strcmp("r", u->option) != 0 && strcmp("u", u->option) != 0 && strcmp("d", u->option) != 0 && strcmp("quit", u->option) != 0)
    {
        printf("Invalid option. Try again.\n\n\n");
        options(u);
        return;
    }
}

// Gets movie title and executes chosen option */
void title(struct User* u)
{
    char* input = malloc(501);
    printf("---------------------------\n");
    printf("Title: ");
    scanf(" %500[^\n]", input);
    scanf("%*[^\n]");
    (void) getchar();
    printf("---------------------------\n\n\n");
    if(input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = '\0';

    if(strcmp(u->option, "c") == 0)
        create(&u->user_catalog, input);

    if(strcmp(u->option, "r") == 0)
        read(&u->user_catalog, input);

    if(strcmp(u->option, "u") == 0)
        update(&u->user_catalog, input);

    if(strcmp(u->option, "d") == 0)
        delete(&u->user_catalog, input);

    free(input);
}


void user_interface()
{
    struct User u = *create_user();
    startup();
    username(&u);
    open_user(&u);
    while(1)
    {
        user_catalog(&u);
        options(&u);
        if(strcmp(u.option, "quit") == 0)
        {
            add_user_log(&u);
            printf("\n\"%s.log\" updated.\n", u.username);
            return;
        }
        title(&u);
    }
}
