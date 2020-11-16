[Main menu](../../Readme.md)->[doc](../easySocket-doc.md)

# easySocket_server_creation(\_,\_,\_)

Create a server that handles sockets.

## **Declaration**

```C
int easySocket_server_creation(
                        char *address, 
                        int port,
                        int max_connection
                    )
```

## **Parameters**
**address**  
The address of the server.

**port**  
The port to create the server.

**max_connection**  
The maximum number of connection possible.

## **Result**
The server socket id if successful, easySocket_NO_VAL otherwise.
