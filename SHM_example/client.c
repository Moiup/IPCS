/**
 * Name: client.c
 *
 * Description: A example of a script getting shm and using it.
 *
 * Creation date: 17/11/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */
#include "server_info.h"


int main()
{
    key_t key;
    int shm_id;
    char *shm;

    /*********************/
    /* Key               */
    /*********************/
    // Getting the key created by server
    key = ipcs_get_key(SERVER_NAME, LETTER_CODE);
    if(key == IPCS_NO_VAL)
    {
        fprintf(stdout, "(client, main) Error getting the key.\n");
        exit(EXIT_FAILURE);
    }

    /*********************/
    /* Shared memory     */
    /*********************/
    // Retreiving the shared memory id
    shm_id = ipcs_get_shm(key);
    if(shm_id == IPCS_NO_VAL)
    {
        fprintf(stdout, "(client, main) Error getting the shared memory.\n");
        exit(EXIT_FAILURE);
    }

    // Retrieving the shared memory
    shm = ipcs_shmat(shm_id);
    if(shm == (char *)-1)
    {
        fprintf(stdout, "(client, main) Error attaching the shared memory.\n");
        exit(EXIT_FAILURE);
    }

    // Printing the shared memory before modificaiton
    fprintf(stdout, "(client, main) Shared memory content: %s.\n", shm);

    // Modifying the first value
    shm[0] = SHM_CLIENT_MODIFY;

    // Printing the shared memory after modification
    fprintf(stdout, "(client, main) Shared memory content: %s.\n", shm);


    return EXIT_SUCCESS;
}
