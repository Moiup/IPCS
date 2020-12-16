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
 * Create and return the SHM id, IPCS_NO_VAL otherwise
 * (shmget(key, size, IPC_CREAT | IPC_EXCL | 0660))
*/
int ipcs_create_shm(key_t key, size_t size)
{
    return shmget(key, size, IPC_CREAT | IPC_EXCL | 0660);
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
 * Set all the value of a set of semaphore
 *
 * sem_id: the id of the set of semaphore
 * val: the value to set all the semaphores with
 * nb_sem: the number of semaphore inside the set
 *
 */
int ipcs_sem_setAll(int sem_id, int val, int nb_sem)
{
    int i;
    int shmctl_ret;
    unsigned short *tab = (unsigned short *)malloc(nb_sem * sizeof(unsigned short));
    if(tab == NULL)
    {
        return IPCS_NO_VAL;
    }

    for(i = 0; i < nb_sem; ++i)
    {
        tab[i] = val;
    }

    fprintf(stdout, "%d\n", tab[0]);
    shmctl_ret = semctl(sem_id, IPCS_NONE, SETALL, tab);
    free(tab);

    return shmctl_ret;
}

/**
 * Set the value of the i-th semathore of the set
 *
 * sem_id: the id of the set of semaphore
 * sem_i: the index of the semaphore to set its value
 * val: the value that will take the semaphore
 */
int ipcs_sem_setVal(int sem_id, int sem_i, int val)
{
    return semctl(sem_id, sem_i, SETVAL, val);
}

/**
 * Get the value of the i-th semaphore from a given set of semaphore
 *
 * sem_id: the id of the set of semaphore
 * sem_i: the i-th semaphore to get its value
 *
 */
int ipcs_sem_getVal(int sem_id, int sem_i)
{
    return semctl(sem_id, sem_i, GETVAL, NULL);
}

/**
 * Delete a set of semaphore
 * (semctl(teams_sem_id, 0, IPC_RMID, NULL))
 * 
 * sem_id: gotten by ipcs_create_sem
*/
int ipcs_sem_rm(int sem_id)
{
    return semctl(sem_id, IPCS_NONE, IPC_RMID, NULL);
}

/**
 * Action P on semaphore (take)
 * 
 * sem_id: the id of the set of semaphore (gotten by ipcs_get_sem or ipcs_create_sem)
 * sem_i: the index of the sempahore to take
 * n: how much it is going to be decreased (positive value)
*/
int ipcs_sem_P(int sem_id, int sem_i, int n)
{
    struct sembuf P = {sem_i, -n, SEM_UNDO};
    
    return semop(sem_id, &P, IPCS_SEM_NB_OP);
}

/**
 * Action V on semaphore (release)
 * 
 * sem_id: the id of the set of semaphore (gotten by ipcs_get_sem or ipcs_create_sem)
 * sem_i: the index of the sempahore to take
 * n: how much it is going to be increased (positive value)
*/
int ipcs_sem_V(int sem_id, int sem_i, int n)
{
    struct sembuf V = {sem_i, n, SEM_UNDO};
    
    return semop(sem_id, &V, IPCS_SEM_NB_OP);
}
