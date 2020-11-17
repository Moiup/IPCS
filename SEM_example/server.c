#include "server_info.h"



int main(int argc, char **argv, char **envp)
{
    // To mute warnings
    (void)argc;
    (void)argv;

    key_t key;
    int sem_id;

    int status;

    char *args[] = {CLIENT_NAME, NULL};
    int pid;
    
    int i;

    /*******************/
    /* Key             */
    /*******************/
    // Creating the key
    key = ipcs_create_key(SERVER_NAME, LETTER_CODE);
    if(key == IPCS_NO_VAL)
    {
        fprintf(stdout, "(server, main) Error creating the key.\n");
        exit(EXIT_FAILURE);
    }

    /*******************/
    /* Semaphore       */
    /*******************/
    // Creating and initialising the number of semaphore
    sem_id = ipcs_create_sem(key, 1);
    if(sem_id == IPCS_NO_VAL)
    {
        fprintf(stdout, "(server, main) Error creating the semaphore.\n");
        exit(EXIT_FAILURE);
    }

    // Setting the semaphore
    if(ipcs_sem_set(sem_id, SEM_VAL) == IPCS_NO_VAL)
    {
        fprintf(stdout, "(server, main) Error setting the semaphore.\n");
        exit(EXIT_FAILURE);
    }

    /*******************/
    /* Fork            */
    /*******************/
    for(i = 0; i < NB_CHILD; i++)
    {
        pid = fork();
        if(pid == NO_VAL)
        {
            fprintf(stdout, "(server, main) Failed creating a child process.\n");
        }
        else if(pid == 0)
        {
            execve(CLIENT_NAME, args, envp);
            exit(EXIT_FAILURE);
        }
    }

    while(TRUE)
    {
        pid = waitpid(-1, &status, 0);
        if((pid == NO_VAL) && (errno == ECHILD))
        {
            break;
        }
    }

    /*******************/
    /* End             */
    /*******************/
    // Deleting the semaphore
    ipcs_sem_rm(sem_id);

    fprintf(stdout,"(server, main) Program finished!\n");

    return EXIT_SUCCESS;
}
