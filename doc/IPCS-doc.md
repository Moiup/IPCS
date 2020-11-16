[Main menu](../Readme.md)

# easySocket

## **Key creation**

```C
key_t ipcs_create_key(char *, int)
```
Create a key. [More here.](./functions/ipcs_create_key.md)

```C
key_t ipcs_get_key(char *, int)
```
Retreive a key. [More here.](./functions/ipcs_create_key.md)

## **Shared memory**

```C
int ipcs_create_shm(key_t, size_t)
```
Create a shared memory segment. [More here.](./functions/ipcs_create_shm.md)

```C
int ipcs_get_shm(key_t)
```
Retreive a shared memory. [More here.](./functions/ipcs_get_shm.md)

```C
void *ipcs_shmat(int)
```
Attach the shared memory segment. [More here.](./functions/ipcs_shmat.md)

```C
int ipcs_shmdt(void *)
```
Detach the shared memory segment. [More here.](./functions/ipcs_shmdt.md)

```C
int ipcs_shmctl(int)
```
Delete a shared memory. [More here.](./functions/ipcs_shmctl.md)

## **Semaphore**

```C
int ipcs_create_sem(key_t, int)
```
Create a semaphore. [More here.](./functions/ipcs_create_sem.md)

```C
int ipcs_get_sem(key_t)
```
Retreive an existing semaphore. [More here.](./functions/ipcs_get_sem.md)

```C
int ipcs_semctl(int)
```
Delete a semaphore. [More here.](./functions/ipcs_semctl.md)

```C
int ipcs_sem_P(int, int)
```
Action P on semaphore (take). [More here.](./functions/ipcs_sem_P.md)

```C
int ipcs_sem_V(int, int)
```
Action V on semaphore (release). [More here.](./functions/ipcs_sem_V.md)
