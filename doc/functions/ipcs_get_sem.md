[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_get_shm(\_)

Retrieve semaphore.

## **Declaration**

```C
int ipcs_get_sem(
                    key_t key
                )
```

## **Parameters**
**key**  
The ipc key associated to the semaphore. Created with [`ipcs_create_key`](ipcs_create_key.md) or retrieved with [`ipcs_get_key`](ipcs_get_key.md).


## **Result**
Return the semaphore id, `IPCS_NO_VAL` if failed.
