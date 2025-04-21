/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#include "main.h"

extern char input_string[100]; // Buffer to store user input
extern char prompt[100]; // Shell prompt string
extern pid_t child_p; // PID of the child process
Sig_action *head = NULL; // Linked list head for storing background jobs

// Custom signal handler to manage shell signals
void signal_handler(int signum)
{
    // Handle Ctrl+C or Ctrl+Z when no input is provided
    if(!strlen(input_string) && (signum == SIGTSTP || signum == SIGINT))
    {
        printf("\n");
        printf(ANSI_COLOR_GREEN" %s: "ANSI_COLOR_RESET, prompt); // Redisplay the prompt
        fflush(stdout);
    }
    // Handle Ctrl+Z to suspend the current process
    else if(signum == SIGTSTP)
    {
        insert_at_first(&head, input_string, child_p); // Save process info to linked list
        kill(child_p, SIGTSTP); // Suspend the child process
    }
}
