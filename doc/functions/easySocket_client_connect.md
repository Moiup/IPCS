[Main menu](../../Readme.md)->[doc](../easySocket-doc.md)

# easySocket_client_connect(\_,\_,\_)

Connect the client to a given server

## **Declaration**

```C
int easySocket_client_connect(
                            int sock_id,
                            char *address,
                            int port
                        )
```

## **Parameters**
**sock_id**  
The client socket id (generated with [easySocket_client_creation](easySocket_client_creation.md)).

**address**  
The server address.

**port**  
The server port.

## **Result**
Return `easySocket_SUCCESS` for success, `easySocket_NO_VAL` otherwise.