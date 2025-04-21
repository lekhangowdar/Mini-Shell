/*
    Name: Lekhan Gowda R
    Reg_no: 24008_023
    Date: 02/12/2024
    Description: Implementation of Minishell
*/
#include "main.h"

extern Sig_action *head; // Pointer to the head of the job list
extern int status; // Status of the last executed command

// Add a new job to the front of the linked list
int insert_at_first(Sig_action **head, char *input_string, pid_t c_pid)
{
    Sig_action *new = malloc(sizeof(Sig_action)); // Allocate memory for a new job

    if(new == NULL)
    {
        return -1; // Return error if memory allocation fails
    }

    strcpy(new->command, input_string); // Store the command string
    new->child_pid = c_pid; // Store the child process ID

    new->next = *head; // Insert the new job at the beginning of the list
    *head = new; // Update the head pointer

    return 0; // Success
}

// Remove the first job from the linked list
int delete_at_first(Sig_action **head)
{
    if(*head == NULL)
    {
        return -1; // Return error if the list is empty
    }
    Sig_action *job = *head; // Get the first job

    *head = (*head)->next; // Update the head pointer to the next job

    free(job); // Free the memory of the removed job
    return 0; // Success
}

// Resume the first background job and remove it from the list
void background()
{
    Sig_action *job = head; // Get the first job in the list
    if(job)
    {
        printf("%s \n", job->command); // Print the command being resumed
        kill(job->child_pid, SIGCONT); // Resume the job
        delete_at_first(&head); // Remove the job from the list
    }
    else
    {
        printf("No command running\n"); // No background jobs to resume
    }
}

// Resume the first job in the foreground and wait for its completion
void foreground()
{
    Sig_action *job = head; // Get the first job in the list

    if(job)
    {
        kill(job->child_pid, SIGCONT); // Resume the job
        printf("%s\n", job->command); // Print the command being resumed
        waitpid(job->child_pid, &status, WUNTRACED); // Wait for the job to complete or stop
        delete_at_first(&head); // Remove the job from the list
    }
    else
    {
        printf("No command running\n"); // No foreground jobs to resume
    }
}

// Display all stopped jobs in the job list
void jobs()
{
    Sig_action *job = head; // Start from the head of the job list
    if (job == NULL)
    {
        printf("No jobs in progress\n"); // Print if no jobs in the list
    }
    else
    {
        int job_number = 1; // Initialize job numbering
        while (job)
        {
            printf("[%d] Stopped   %s\n", job_number++, job->command); // Print job details
            job = job->next; // Move to the next job
        }
    }
}
