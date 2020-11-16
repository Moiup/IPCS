[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_shmat(\_)

Attach the shared memory segment. It a mask of `shmat(shm_id, NULL, 0)`

## **Declaration**

```C
void *ipcs_shmat(
                    int shm_id
                )
```

## **Parameters**
**shm\_id**  
The shared memory id. Created with [`ipcs_create_shm`](ipcs_create_shm.md) or retrieved with [`ipcs_get_shm`](ipcs_get_shm.md).


## **Result**
Return the shared memory segment. If failure, it will return `(type *) -1`, with type being the type of your shared memory segment.
