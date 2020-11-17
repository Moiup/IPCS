/**
 * Name: server.c
 *
 * Description: A example of a script creating ipcs and using them.
 *
 * Creation date: 17/11/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */

#include "server_info.h"


int main(int argc, char **argv, char **envp)
{
    // to skip the warnings
    (void)argc;
    (void)argv;

    char *child_arg[] = {CHILD_NAME, NULL};

    int shm_id;
    char *shm;
    int pid;

    /*********************/
    /* Key               */
    /*********************/
    // Creating the key
    key_t key = ipcs_create_key(SERVER_NAME, LETTER_CODE);
    if(key == IPCS_NO_VAL)
    {
        fprintf(stdout, "(server, main) Error creating the key.\n");
        exit(EXIT_FAILURE);
    }

    /*****************************/
    /* Shared memory             */
    /*****************************/
    // Creating a shared memory corresponding to an array of char of size 5
    // (string of length 5)
    shm_id = ipcs_create_shm(key, SHM_SIZE * sizeof(char));
    if(shm_id == IPCS_NO_VAL)
    {
        fprintf(stdout, "(server, main) Error creating the shared memory.\n");
        exit(EXIT_FAILURE);
    }

    // Attaching the shared memory
    shm = ipcs_shmat(shm_id);
    if(shm == (char *)-1)
    {
        // Removing the shared memory if failed attaching it
        ipcs_shmctl(shm_id);
        fprintf(stdout, "(server, main) Error attaching the shared memory.\n");
        exit(EXIT_FAILURE);
    }

    // Setting all value to 'm' in the shared memory
    memset(shm, SHM_INIT_CONTENT, SHM_SIZE * sizeof(char));
    // Printing the shared memory content
    fprintf(stdout, "(server, main) Shared memory content: %s.\n", shm);

    /*******************************/
    /* Fork client                 */
    /*******************************/
    pid = fork();
    if(pid == NO_VAL)
    {
        fprintf(stdout, "(server, main) Error in fork.\n");
        // Detaching the shared memory and removing it
        ipcs_shmdt(shm);
        ipcs_shmctl(shm_id);
    }
    else if(pid == 0)
    {
        // Inside the child
        execve(CHILD_NAME, child_arg, envp);
        exit(EXIT_FAILURE);
    }

    /*******************************/
    /* Ending                      */
    /*******************************/
    // Waiting for the client to end
    waitpid(NO_VAL, NULL, 0);

    // Printing shm content
    fprintf(stdout, "(server, main) Shared memory content: %s.\n", shm);

    
    // Detaching the shm
    ipcs_shmdt(shm);

    // Deleting the shm
    ipcs_shmctl(shm_id);

    fprintf(stdout, "(server, main) Program over.\n");
    

    return EXIT_SUCCESS;
}

