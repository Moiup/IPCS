[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_create_sem(\_,\_)



## **Declaration**

```C
int ipcs_create_sem(
                    key_t key,
                    int nb_sem
                )
```

## **Parameters**
**key**  
The ipc key. Created with [`ipcs_create_key`](ipcs_create_key.md) or retrieved with [`ipcs_get_key`](ipcs_get_key.md).

**nb_sem**  
The number of semaphore to create.

## **Result**
Return the semaphore id, `IPCS_NO_VAL` if failed.
