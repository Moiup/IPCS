#include "server_info.h"


int main()
{
    key_t key;
    int sem_id;

    /*******************/
    /* Key             */
    /*******************/
    // Getting the key
    key = ipcs_get_key(SERVER_NAME, LETTER_CODE);
    if(key == IPCS_NO_VAL)
    {
        fprintf(stdout, "(client, main) Error getting the key.\n");
        exit(EXIT_FAILURE);
    }

    /*******************/
    /* Semaphore       */
    /*******************/
    // Getting the semaphore
    sem_id = ipcs_get_sem(key);
    if(sem_id == IPCS_NO_VAL)
    {
        fprintf(stdout, "(client, main) Error getting the semaphore.\n");
        exit(EXIT_FAILURE);
    }

    // Taking the semaphore to perform action
    ipcs_sem_P(sem_id, NB_SEM_P);
    fprintf(stdout, "(client, main) Pocess %d got the sem. Waiting %d second.\n", getpid(), TIME_TO_WAIT);
    sleep(TIME_TO_WAIT);
    fprintf(stdout, "(client, main) Process %d releasing the sem.\n\n", getpid());
    // Releasing the semaphore
    ipcs_sem_V(sem_id, NB_SEM_V);


    /*******************/
    /* End             */
    /*******************/

    return EXIT_SUCCESS;
}
