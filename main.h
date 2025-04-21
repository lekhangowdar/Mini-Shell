/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Define the structure for maintaining command and process information
typedef struct node
{
    char command[50]; // Store the command executed
    int child_pid;    // Store the process ID of the child process
    struct node *next; // Pointer to the next node
} Sig_action;

// Command type definitions
#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

// ANSI color codes for shell prompt styling
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Function declarations
void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);
void copy_change(char *prompt, char *input_string);
void execute_external_commands(char *input_string);
int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char external_commands[][30]);
int insert_at_first(Sig_action **head, char *input_string, pid_t c_pid);
int delete_at_first(Sig_action **head);
void background(void);
void foreground(void);
void jobs();

#endif