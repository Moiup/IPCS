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
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define IPCS_NO_VAL -1

#define IPCS_SEM_NB_OP 1

#define IPCS_NONE 0

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
 * sem_size: the size of the set of semaphore
 * 
 * Return the semaphore set id, IPCS_NO_VAL if failed
 * (semget(key, nb_sem, IPC_CREAT | IPC_EXCL))
*/
int ipcs_create_sem(key_t key, int sem_size);

/**
 * Get an existing set of semaphore
 * (semget(key, 0, 0))
 * 
 * key: gotten by ipcs_get_key
*/
int ipcs_get_sem(key_t key);

/**
 * Set all the value of a set of semaphore
 *
 * sem_id: the id of the set of semaphore
 * val: the value to set all the semaphores with
 * nb_sem: the number of semaphore inside the set
 *
 */
int ipcs_sem_setAll(int sem_id, int val, int nb_sem);

/**
 * Set the value of the i-th semathore of the set
 *
 * sem_id: the id of the set of semaphore
 * sem_i: the index of the semaphore to set its value
 * val: the value that will take the semaphore
 */
int ipcs_sem_setVal(int sem_id, int sem_i, int val);

/**
 * Get the value of the i-th semaphore from a given set of semaphore
 *
 * sem_id: the id of the set of semaphore
 * sem_i: the i-th semaphore to get its value
 *
 */
int ipcs_sem_getVal(int sem_id, int sem_i);

/**
 * Delete a set of semaphore
 * (semctl(teams_sem_id, 0, IPC_RMID, NULL))
 * 
 * sem_id: gotten by ipcs_create_sem
*/
int ipcs_sem_rm(int sem_id);

/**
 * Action P on semaphore (take)
 * 
 * sem_id: the id of the set of semaphore (gotten by ipcs_get_sem or ipcs_create_sem)
 * sem_i: the index of the sempahore to take
 * n: how much it is going to be decreased (positive value)
*/
int ipcs_sem_P(int sem_id, int sem_i, int n);

/**
 * Action V on semaphore (release)
 * 
 * sem_id: the id of the set of semaphore (gotten by ipcs_get_sem or ipcs_create_sem)
 * sem_i: the index of the sempahore to take
 * n: how much it is going to be increased (positive value)
*/
int ipcs_sem_V(int sem_id, int sem_i, int n);
