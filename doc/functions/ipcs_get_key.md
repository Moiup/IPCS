[Main menu](../../Readme.md)->[doc](../ipcs-doc.md)

# ipcs_get_key(\_,\_)

Retreive a key.

## **Declaration**

```C
key_t ipcs_get_key(
                    char *key_name,
                    int key_code
                )
```

## **Parameters**
**key_name**  
The name of the key file.

**key_code**  
The code associated to the key.

## **Result**
Return the key if it exists, `IPCS_NO_VAL` otherwise.
