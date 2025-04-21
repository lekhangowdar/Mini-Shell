/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#include "main.h"
extern char external_commands[200][30]; // Array of external commands loaded from file

char *get_command(char *input_string)
{
    char *word = malloc(sizeof(input_string)); // Allocate memory for the extracted command
    int i = 0;

    // Extract the first word (command) from the input string
    while(input_string[i] != ' ' && input_string[i] != '\0')
    {
        word[i] = input_string[i];
        i++;
    }
    return word; // Return the extracted command
}

int check_command_type(char *command)
{
    // List of built-in commands
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
                        "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
                        "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

    int i;

    // Check if the command matches any external command
    for(i = 0; strcmp(external_commands[i], "\0") != 0; i++)
    {
        if(strcmp(command, external_commands[i]) == 0)
        {
            return EXTERNAL; // Return EXTERNAL if command is found in external commands list
        }
    }

    // Check if the command matches any built-in command
    for(i = 0; builtins[i] != NULL; i++)
    {
        if(strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN; // Return BUILTIN if command is found in built-in commands list
        }
    }    

    return NO_COMMAND; // Return NO_COMMAND if no match is found
}
