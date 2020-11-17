# **Shared Memory example**

This is an example to show how the function works for shared memory segment. There are three files: `server_info.h`, `server.c` and `client.c`.

It works like so: a server create a shared memory (a string of size 5) and fullfills it with 'm'. Then, it forks a child (client), which change the first 'm' into an 'H'.

You can find the complete example and its `Makefile` in the folder `SHM_example`.

### **Result**
The program should display this:

```
(server, main) Shared memory content: mmmmm.
(client, main) Shared memory content: mmmmm.
(client, main) Shared memory content: Hmmmm.
(server, main) Shared memory content: Hmmmm.
(server, main) Program over.
```

## **server info**

Constant and includes shared between the two programs: client and server.

```C
#include "../IPCS/ipcs.h"
#include <string.h>
#include <unistd.h>

#define SERVER_NAME "server.file"
#define LETTER_CODE 'a'

#define CHILD_NAME "./client"

#define NO_VAL -1

#define SHM_SIZE 5
#define SHM_INIT_CONTENT 'm'
#define SHM_CLIENT_MODIFY 'H'

```

## **server**
Creates the shared memory, initialises it, displayt its value, forks the client process, wait for him to finish, display the final shm value.

```C
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
```

## **client**
Retrieve le shm created by the server, display its value, change the first 'm' into 'H', display the shm again then quit.

```C
/**
 * Name: client.c
 *
 * Description: A example of a script getting ipcs and using them.
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

```
