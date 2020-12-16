[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_sem_setVal(\_,\_,\_)

Set a semaphore value.

## **Declaration**

```C
int ipcs_sem_setVal(
                    int sem_id,
                    int sem_i,
                    int val
                )
```

## **Parameters**
**sem_id**  
The semaphore set id. Created with [`ipcs_create_sem`](ipcs_create_sem.md) or retrieved with [`ipcs_get_sem`](ipcs_get_sem.md).

**sem_i**  
The index of the semaphore to set.

**val**  
The value to give to the semaphore.

## **Result**
On error `IPCS_NO_VAL` is returned, `errno` indicate the error. For more info, you can check the [man page](https://man7.org/linux/man-pages/man2/semctl.2.html).
