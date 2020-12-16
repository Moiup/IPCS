[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_sem_rm(\_,\_)

Set a number of semaphore inside a set of semaphore.

## **Declaration**

```C
int ipcs_sem_setAll(
                    int sem_id, int val, int nb_sem)
```

## **Parameters**
**sem_id**  
The semaphore set id. Created with [`ipcs_create_sem`](ipcs_create_sem.md) or retrieved with [`ipcs_get_sem`](ipcs_get_sem.md).

**val** 
The value to set all the semaphore with.

**nb_sem**  
The number of semaphore inside the set.

## **Result**
On error `IPCS_NO_VAL` is returned, `errno` indicate the error. For more info, you can check the [man page](https://man7.org/linux/man-pages/man2/semctl.2.html).
