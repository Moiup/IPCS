[Main menu](../../Readme.md)
# **Shared Memory example**

This is an example to show how the functions works for semaphore. There are three files: `server_info.h`, `server.c` and `client.c`.

The task accomplished here is simple. The server creates multiple child process (client). Each child ask for authorisation (P) to perform its task. Here the task is simple, it is just a call to `sleep(1)`. Then the child release the semaphore he took (V) so other process can get their authorisation.

You can find the complete example and its `Makefile` in the folder `SHM_example`.

The example here might seems silly, but it just here to show how the functions related to semaphores work. Of course, we can think of more complex application by using semaphore in order to access shared memory segment.

### **Result**
The output must be pair of messages with the same pid. Here an example:
```
(client, main) Pocess 22091 got the sem. Waiting 1 second.
(client, main) Process 22091 releasing the sem.

(client, main) Pocess 22090 got the sem. Waiting 1 second.
(client, main) Process 22090 releasing the sem.

(client, main) Pocess 22092 got the sem. Waiting 1 second.
(client, main) Process 22092 releasing the sem.

(client, main) Pocess 22089 got the sem. Waiting 1 second.
(client, main) Process 22089 releasing the sem.

(client, main) Pocess 22093 got the sem. Waiting 1 second.
(client, main) Process 22093 releasing the sem.

(server, main) Program finished!
```


## **server info**

Constant and includes shared between the two programs: client and server.

```C
/**
 * Name: server_info.h
 *
 * Description: Constant and include declaration.
 *
 * Creation date: 17/11/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */

#include "../IPCS/ipcs.h"
#include <unistd.h>

#define CLIENT_NAME "./client"

#define SERVER_NAME "file.serv"
#define LETTER_CODE 'b'

#define NO_VAL -1

#define NB_SEM 1
#define SEM_VAL 1
#define NB_SEM_P 1
#define NB_SEM_V 1

#define NB_CHILD 5

#define TIME_TO_WAIT 1

#define TRUE 1
#define FALSE 0
```

## **server**
The server creates the set of semaphore and put one semaphore in it. The it creates 5 children and waits for them to finish their task. Finaly, in remove the set of semaphore.

```C
//**
 * Name: server.c
 *
 * Description: A example of a script creating a set of semaphore.
 *
 * Creation date: 17/11/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */
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
    sem_id = ipcs_create_sem(key, NB_SEM);
    if(sem_id == IPCS_NO_VAL)
    {
        fprintf(stdout, "(server, main) Error creating the semaphore.\n");
        exit(EXIT_FAILURE);
    }

    // Setting the semaphore
    if(ipcs_sem_setAll(sem_id, 1, 1) == IPCS_NO_VAL)
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
```

## **client**
The client get the set of semaphore. Then, it waits until it can take a semaphore in order to perform its task:
- printint: "(client, main) Pocess %d got the sem. Waiting %d second."
- sleeping for 1 second.
- printing: "(client, main) Process %d releasing the sem.\n\n"
After completing its task, it releases the semaphore it took in order to let the other perform their task. Then, it exit.

```C
/**
 * Name: client.c
 *
 * Description: A example of a script getting a set of semaphore and using it.
 *
 * Creation date: 17/11/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */
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

    // Taking the semaphore
    ipcs_sem_P(sem_id, FIRST_SEM, NB_SEM_P);
    // Doing some action
    fprintf(stdout, "(client, main) Pocess %d got the sem. Waiting %d second.\n", getpid(), TIME_TO_WAIT);
    sleep(TIME_TO_WAIT);
    fprintf(stdout, "(client, main) Process %d releasing the sem.\n\n", getpid());
    // Releasing the semaphore
    ipcs_sem_V(sem_id, FIRST_SEM, NB_SEM_V);


    /*******************/
    /* End             */
    /*******************/

    return EXIT_SUCCESS;
}

```
