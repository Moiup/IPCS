/**
 * Name: ipcs.c
 *
 * Description: The declaration of the ipcs functions
 *
 * Creation date: 28/04/2020
 *
 * Author: Mohammed-Bashir Mahdi
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define IPCS_NO_VAL -1

#define IPCS_SEM_NB_OP 1

/****************************/
/* Key                      */
/****************************/

/**
 * Create and return the key, IPCS_NO_VAL otherwise
*/
key_t ipcs_create_key(char *key_name, int key_code);

/**
 * Return the key which must exist (created by the parent process)
 * Return IPCS_NO_VAL if failed
*/
key_t ipcs_get_key(char *key_name, int key_code);

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
int ipcs_create_shm(key_t key, size_t size);

/**
 * Get an existing shm
 * (shmget(key, 0, 0))
 * 
 * key: gotten by ipcs_get_key
*/
int ipcs_get_shm(key_t key);

/**
 * Mask shmat -> Attach shared memory segment.
 * (shmat(shm_id, NULL, 0))
 * 
 * shm_id: gotten by ipcs_create_shm
*/
void *ipcs_shmat(int shm_id);

/**
 * Mask shmdt -> Detach shared memory segment.
 * (shmdt(shm))
 * 
 * shm: gotten by ipcs_shmat
*/
int ipcs_shmdt(void *shm);

/**
 * Delete an shm
 * (shmctl(shm_id, IPC_RMID, NULL))
 * 
 * shm_id: gotten by ipcs_create_shm
*/
int ipcs_shmctl(int shm_id);

/****************************/
/* SEM                      */
/****************************/

/**
 * key: gotten with ipcs_create_key 
 * nb_sem: the amount of semaphore wanted
 * 
 * Return the semaphore id, IPCS_NO_VAL if failed
 * (semget(key, nb_sem, IPC_CREAT | IPC_EXCL))
*/
int ipcs_create_sem(key_t key, int nb_sem);

/**
 * Get an existing semaphore
 * (semget(key, 0, 0))
 * 
 * key: gotten by ipcs_get_key
*/
int ipcs_get_sem(key_t key);
/**
 * Delete a semaphore
 * (semctl(teams_sem_id, 0, IPC_RMID, NULL))
 * 
 * sem_id: gotten by ipcs_create_sem
*/
int ipcs_semctl(int sem_id);

/**
 * Action P ont semaphore (take)
 * 
 * sem_id: gotten by ipcs_get_sem or ipcs_create_sem
 * nb_sem: the amount of semaphore that must be taken (positive value)
*/
int ipcs_sem_P(int sem_id, int nb_sem);

/**
 * Action V ont semaphore (release)
 * 
 * sem_id: gotten by ipcs_get_sem or ipcs_create_sem
 * nb_sem: the amount of semaphore that must be released (positive value)
*/
int ipcs_sem_V(int sem_id, int nb_sem);
