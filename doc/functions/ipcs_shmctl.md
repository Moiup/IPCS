[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_shmctl(\_)

Detach the shared memory segment. It a mask of `shmctl(shm_id, IPC_RMID, NULL)`

## **Declaration**

```C
int *ipcs_shmctl(
                    int shm_id
                )
```

## **Parameters**
**shm\_id**  
The shared memory id. Created with [`ipcs_create_shm`](ipcs_create_shm.md) or retrieved with [`ipcs_get_shm`](ipcs_get_shm.md).


## **Result**
On error `IPCS_NO_VAL` is returned, `errno` indicats the error.
