[Main menu](../../Readme.md)->[doc](../easySocket-doc.md)

# easySocket_read(\_,\_,\_)

Read a message. (Works exactly like the POSIX read function).

## **Declaration**

```C
size_t easySocket_read(
                    int sock_id,
                    void *meassage_buffer,
                    size_t count
                )
```

## **Parameters**
**sock_id**  
The socket to read.

**message**  
The buffer where will the message be stored.

**count**  
The number of bytes to read.

## **Result**
Return the number of bytes read.