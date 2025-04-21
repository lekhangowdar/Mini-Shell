/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#include "main.h"
extern char external_commands[200][30]; // External commands array defined elsewhere
int status, child_p; // Status of child process and child process ID

void scan_input(char *prompt, char *input_string)
{
    // Register signal handlers for SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z)
    signal(SIGINT, signal_handler);  // Handle Ctrl+C
    signal(SIGTSTP, signal_handler); // Handle Ctrl+Z

    extract_external_commands(external_commands); // Load external commands into memory
    
    while(1)
    {
        // Display the prompt in green and read user input
        printf(ANSI_COLOR_GREEN" %s "ANSI_COLOR_RESET, prompt);
        scanf("%[^\n]", input_string);
        getchar(); // Clear the newline character from the input buffer

        // Skip if the input string is empty
        if(strlen(input_string) == 0)
        {
            continue;
        }

        // Handle custom prompt change (e.g., PS1="new_prompt")
        if(strncmp(input_string, "PS1=", 4) == 0 && input_string[4] != ' ')
        {
            strcpy(prompt, input_string + 4); // Update the shell prompt
        }
        else 
        {
            char *command = get_command(input_string); // Extract the command from input
            int ret = check_command_type(command); // Determine the command type
            
            if(ret == BUILTIN)
            {
                // Handle built-in commands
                if(strncmp(input_string,"echo ",5) == 0)
                {
                    // Handle special echo cases
                    if(strcmp(input_string + 5,"$$") == 0)
                    {
                        printf("Pid is %d\n",getpid());
                    }
                    else if(strcmp(input_string + 5,"$?") == 0)
                    {
                        printf("Exit code %d\n",status);
                    }
                    else if(strcmp(input_string + 5,"$SHELL") == 0)
                    {
                        printf("PATH: %s\n",getenv("SHELL"));
                    }
                    else
                    {
                        printf("Invalid command\n");
                    }
                }
                else 
                {
                    execute_internal_commands(input_string); // Execute other built-in commands
                }
            }
            else if(ret == EXTERNAL)
            {
                pid_t pid = fork(); // Create a child process
                child_p = pid; // Store child process ID

                if(pid > 0) // Parent process
                {
                    waitpid(pid, &status, WUNTRACED); // Wait for the child process to finish
                }
                else if (pid == 0) // Child process
                {
                    // Reset signal handlers to default behavior in child process
                    signal(SIGINT, SIG_DFL);
                    signal(SIGTSTP, SIG_DFL);
                    execute_external_commands(input_string); // Execute external command
                }           
            }
            else if(!strcmp(input_string, "bg")) // Handle background job control
            {
                background();
            }
            else if(!strcmp(input_string, "fg")) // Handle foreground job control
            {
                foreground();
            }
            else if(!strcmp(input_string, "jobs")) // Display list of all jobs
            {
                jobs();
            }
            else
            {
                printf("Command not found\n"); // Handle invalid commands
            }           
        }
    }
}

void extract_external_commands(char external_commands[][30])
{
    FILE *fptr = fopen("external_commands.txt", "r"); // Open file for reading

    // Handle file opening errors
    if (fptr == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file\n");
        return;
    }

    char buff[20];
    int count = 0;

    // Read external commands from the file into the array
    while (!feof(fptr) && fscanf(fptr, "%s", buff)) 
    {
        strcpy(external_commands[count], buff);
        count++;
    }
    strcpy(external_commands[count], "\0"); // Mark the end of the commands list

    fclose(fptr); // Close the file
}
