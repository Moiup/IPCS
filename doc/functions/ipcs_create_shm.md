[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_create_shm(\_,\_)

Create a shared memory segment.

## **Declaration**

```C
int ipcs_create_shm(
                    key_t key,
                    size_t size
                )
```

## **Parameters**
**key**  
The ipc key. Created with [`ipcs_create_key`](ipcs_create_key.md) or retrieved with [`ipcs_get_key`](ipcs_get_key.md).

**size**  
The size of the shared memory to create.

## **Result**
Create and return the shared memory id, `IPCS_NO_VAL` if failed.
