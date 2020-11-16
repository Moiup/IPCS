[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_semctl(\_)

Detach the shared memory segment. It a mask of `semctl(sem_id, _, IPC_RMID, NULL)`

## **Declaration**

```C
int ipcs_semctl(
                int sem_id
            )
```

## **Parameters**
**sem\_id**  
The semaphore id. Created with [`ipcs_create_sem`](ipcs_create_sem.md) or retrieved with [`ipcs_get_sem`](ipcs_get_sem.md).


## **Result**
On error `IPCS_NO_VAL` is returned, `errno` indicate the error.
