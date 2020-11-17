/**
 * Name: ipcs.c
 *
 * Description: The definition of the ipcs functions
 *
 * Creation date: 28/04/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */
#include "ipcs.h"

/****************************/
/* Key                      */
/****************************/

/**
 * Create and return the key, IPCS_NO_VAL otherwise
*/
key_t ipcs_create_key(char *key_name, int key_code)
{
    key_t key;
    FILE *f_key;

    // Getting the file
    f_key = fopen(key_name, "r");
    if (f_key == NULL)
    {
        if (errno == ENOENT)
        {
            f_key = fopen(key_name, "w");
            if (f_key == NULL)
            {
                return IPCS_NO_VAL;
            }
        }
        else
        {
            return IPCS_NO_VAL;
        }
    }

    // Creating the key
    key = ftok(key_name, key_code);
    if (key == IPCS_NO_VAL)
    {
        return IPCS_NO_VAL;
    }

    return key;
}

/**
 * Return the key which must exist (created by the parent process)
 * Return IPCS_NO_VAL if failed
*/
key_t ipcs_get_key(char *key_name, int key_code)
{
    FILE *f_key;
    key_t key;
    
    // Getting the file
    f_key = fopen(key_name, "r");
    if(f_key == NULL)
    {
        return IPCS_NO_VAL;
    }

    // Creating the key
    key = ftok(key_name, key_code);
    if (key == IPCS_NO_VAL)
    {
        return IPCS_NO_VAL;
    }

    return key;
}

/****************************/
/* SHM                      */
/****************************/

/**
 * key: gotten with ipcs_create_key
 * size : the size of the shm
 * 
 * Create and return the SHM id, NULL otherwise
 * (shmget(key, size, IPC_CREAT | IPC_EXCL | 0660))
*/
int ipcs_create_shm(key_t key, size_t size)
{
    int shm_id;

    shm_id = shmget(key, size, IPC_CREAT | IPC_EXCL | 0660);
    if (shm_id == IPCS_NO_VAL)
    {
        return IPCS_NO_VAL;
    }

    return shm_id;
}

/**
 * Get an existing shm. Return the shm_id
 * (shmget(key, 0, 0))
 * 
 * key: gotten by ipcs_get_key
*/
int ipcs_get_shm(key_t key)
{
    return shmget(key, 0, 0);
}

/**
 * Mask shmat -> Attach shared memory segment.
 * (shmat(shm_id, NULL, 0))
 * 
 * shm_id: gotten by ipcs_create_shm
*/
void *ipcs_shmat(int shm_id)
{
    return shmat(shm_id, NULL, 0);
}


/**
 * Mask shmdt -> Detach shared memory segment.
 * (shmdt(shm))
 * 
 * shm: gotten by ipcs_shmat
*/
int ipcs_shmdt(void *shm)
{
    return shmdt(shm);
}

/**
 * Delete an shm
 * (shmctl(shm_id, IPC_RMID, NULL))
 * 
 * shm_id: gotten by ipcs_create_shm
*/
int ipcs_shmctl(int shm_id)
{
    return shmctl(shm_id, IPC_RMID, NULL);
}

/****************************/
/* SEM                      */
/****************************/

/**
 * key: gotten with ipcs_create_key 
 * sem_size: the size of the set of semaphore
 * 
 * Return the semaphore set id, IPCS_NO_VAL if failed
 * (semget(key, nb_sem, IPC_CREAT | IPC_EXCL))
*/
int ipcs_create_sem(key_t key, int sem_size)
{
    return semget(key, sem_size, IPC_CREAT | IPC_EXCL | 0660);
}

/**
 * Get an existing set of semaphore
 * (semget(key, 0, 0))
 * 
 * key: gotten by ipcs_get_key
*/
int ipcs_get_sem(key_t key)
{
    return semget(key, 0, 0);
}

/**
 * Create semaphore inside a set of semaphore
 * nb_sem: the number of semaphore to create
 * 
 * key: gotten by ipcs_get_key
*/
int ipcs_sem_set(int sem_id, int nb_sem)
{
    return semctl(sem_id, 0, SETVAL, nb_sem);
}

/**
 * Delete a set of semaphore
 * (semctl(teams_sem_id, 0, IPC_RMID, NULL))
 * 
 * sem_id: gotten by ipcs_create_sem
*/
int ipcs_sem_rm(int sem_id)
{
    return semctl(sem_id, 0, IPC_RMID, NULL);
}

/**
 * Action P on semaphore (take)
 * 
 * sem_id: gotten by ipcs_get_sem or ipcs_create_sem
 * nb_sem: the amount of semaphore that must be taken (positive value)
*/
int ipcs_sem_P(int sem_id, int nb_sem)
{
    struct sembuf P = {0, -nb_sem, SEM_UNDO};
    
    return semop(sem_id, &P, IPCS_SEM_NB_OP);
}

/**
 * Action V on semaphore (release)
 * 
 * sem_id: gotten by ipcs_get_sem or ipcs_create_sem
 * nb_sem: the amount of semaphore that must be released (positive value)
*/
int ipcs_sem_V(int sem_id, int nb_sem)
{
    struct sembuf V = {0, nb_sem, SEM_UNDO};
    
    return semop(sem_id, &V, IPCS_SEM_NB_OP);
}
