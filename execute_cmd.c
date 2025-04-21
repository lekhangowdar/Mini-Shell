/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#include "main.h"

void convertTo2DArray(char *input, char *words[50]); // Helper function to tokenize input
int n_pipe(char **cmd_tok); // Function to handle piped commands

void execute_internal_commands(char *input_string)
{
    // Handle the "exit" command to terminate the shell
    if(strcmp(input_string, "exit") == 0)
    {
        exit(0);
    }
    // Handle the "cd" command to change the current directory
    else if(strncmp(input_string, "cd ", 3) == 0)
    {
        int ret = chdir(input_string + 3);
        if(ret == -1)
        {
            printf("Invalid path\n");
        }
    }
    // Handle the "pwd" command to print the current working directory
    else if(strncmp(input_string, "pwd", 3) == 0)
    {
        char buf[100];
        getcwd(buf, 100);
        printf("%s\n", buf);
    }
}

void execute_external_commands(char *input_string)
{
    char *words[50]; // Array to hold tokenized input
    char *dup_string = malloc(strlen(input_string) + 1);
    strcpy(dup_string, input_string); // Duplicate input string to tokenize
    convertTo2DArray(dup_string, words); // Tokenize the input string

    int j = 0;
    int pipe = 0;

    // Check if the command contains a pipe (|)
    while(words[j] != NULL)
    {
        if(strcmp(words[j], "|") == 0)
        {
            pipe = 1;
            break;
        }
        j++;
    }

    if(pipe)
    {
        n_pipe(words); // Handle piped commands
    }
    else
    {
        execvp(words[0], words); // Execute the command if no pipe is present
    }

    free(dup_string); // Free the duplicated string
}

void convertTo2DArray(char *input, char *words[50]) 
{
    int wordIndex = 0;
    char *token = strtok(input, " "); // Tokenize the input string by spaces
    while(token != NULL) 
    {
        words[wordIndex] = malloc(50); // Allocate memory for each token
        strcpy(words[wordIndex], token); // Copy the token to the array
        token = strtok(NULL, " ");
        wordIndex++;
    }
    words[wordIndex] = NULL; // Null-terminate the array
}

int n_pipe(char **cmd_tok)
{
    int cmd = 0, cmd_count = 1;
    int cmd_arr[25] = {0}; // Array to store the start index of each command

    // Parse the tokens and mark the start of each command
    while(cmd_tok[cmd] != NULL)
    {
        if(strcmp(cmd_tok[cmd], "|") == 0)
        {
            cmd_arr[cmd_count++] = cmd + 1; // Update command start index after pipe
            cmd_tok[cmd] = NULL; // Replace pipe symbol with NULL
        }
        cmd++;
    }

    int fd[2]; // File descriptors for the pipe

    for(int i = 0; i < cmd_count; i++)
    {
        // Create a pipe for inter-process communication, except for the last command
        if(i < cmd_count - 1)
        {
            if(pipe(fd) == -1)
            {
                perror("pipe");
                return -1;
            }
        }

        pid_t pid = fork(); // Fork a new process

        if(pid > 0) // Parent process
        {
            if(i != (cmd_count - 1))
            {
                close(fd[1]); // Close write end of the pipe
                dup2(fd[0], 0); // Redirect input to read end of the pipe
                close(fd[0]);
            }
            int status;
            wait(&status); // Wait for the child process to finish
        }
        else if(pid == 0) // Child process
        {
            if(i != (cmd_count - 1))
            {
                close(fd[0]); // Close read end of the pipe
                dup2(fd[1], 1); // Redirect output to write end of the pipe
            }
            execvp(cmd_tok[cmd_arr[i]], cmd_tok + cmd_arr[i]); // Execute the command
        }
        else // Error during fork
        {
            perror("fork");
        }
    }
    exit(0); // Exit the child process after execution
}
