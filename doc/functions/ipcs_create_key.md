[Main menu](../../Readme.md)->[doc](../IPCS-doc.md)

# ipcs_create_key(\_,\_)

Create a key.

## **Declaration**

```C
key_t ipcs_create_key(
                    char *key_name,
                    int key_code
                )
```

## **Parameters**
**key_name**  
The name of the key file. The key file is created if does not already exist.

**key_code**  
The code to associate to the key.

## **Result**
Create and return the key, `IPCS_NO_VAL` otherwise.
