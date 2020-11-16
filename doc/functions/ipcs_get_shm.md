[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_get_shm(\_)

Retrieve a shared memory segment. It a mask of `shmget(key, 0, 0)`

## **Declaration**

```C
int ipcs_get_shm(
                    key_t key,
                )
```

## **Parameters**
**key**  
The ipc key associated to the shared memory. Created with [`ipcs_create_key`](ipcs_create_key.md) or retrieved with [`ipcs_get_key`](ipcs_get_key.md).


## **Result**
Return the shared memory id, `IPCS_NO_VAL` if failed.
