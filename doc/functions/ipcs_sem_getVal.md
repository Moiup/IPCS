[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_sem_getVal(\_,\_)

Retrieve the value of a semaphore.

## **Declaration**

```C
int ipcs_sem_getVal(
                    int sem_id,
                    int sem_i,
                )
```

## **Parameters**
**sem_id**  
The id of the semaphore set. Created with [`ipcs_create_sem`](ipcs_create_sem.md) or retrieved with [`ipcs_get_sem`](ipcs_get_sem.md).

**sem_i**  
The index of the semaphore to retrieve the value.

## **Result**
On error `IPCS_NO_VAL` is returned, `errno` indicate the error. For more info, you can check the [man page](https://man7.org/linux/man-pages/man2/semctl.2.html).
