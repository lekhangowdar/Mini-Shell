/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#include "main.h"

char prompt[100] = "minishell$:"; // Default shell prompt
char input_string[100]; // Buffer to store user input
char external_commands[200][30]; // Array to store external commands
char command[100]; // Buffer to store the extracted command

int main()
{
    system("clear"); // Clear the terminal screen
    scan_input(prompt, input_string); // Scan user input with the shell prompt

    return 0; // Exit the shell program
}
