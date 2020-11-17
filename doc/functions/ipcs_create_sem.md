[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_create_sem(\_,\_)

Create a set of semaphore.

## **Declaration**

```C
int ipcs_create_sem(
                    key_t key,
                    int sem_size
                )
```

## **Parameters**
**key**  
The ipc key. Created with [`ipcs_create_key`](ipcs_create_key.md) or retrieved with [`ipcs_get_key`](ipcs_get_key.md).

**sem_size**  
The size of the set of semaphore.

## **Result**
Return the semaphore id, `IPCS_NO_VAL` if failed.
