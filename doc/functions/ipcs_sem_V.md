[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_shmdt(\_)

Action V on semaphore (release).

## **Declaration**

```C
int ipcs_sem_V(
                int sem_id,
                int nb_sem
            )
```

## **Parameters**
**sem\_id**  
The semaphore id. Created with [`ipcs_create_sem`](ipcs_create_sem.md) or retrieved with [`ipcs_get_sem`](ipcs_get_sem.md).

**nb\_sem**  
The amount of semaphore that must be released (positive value).

## **Result**
Return `IPCS_NO_VAL` if error.
