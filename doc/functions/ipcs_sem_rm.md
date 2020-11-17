[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_sem_rm(\_)

Remove a set of semaphore.

## **Declaration**

```C
int ipcs_sem_rm(
                int sem_id
            )
```

## **Parameters**
**sem\_id**  
The semaphore set id. Created with [`ipcs_create_sem`](ipcs_create_sem.md) or retrieved with [`ipcs_get_sem`](ipcs_get_sem.md).


## **Result**
On error `IPCS_NO_VAL` is returned, `errno` indicate the error.
