[Main menu](../../Readme.md)->[doc](../easySocket-doc.md)

# easySocket_server_accept(\_)

Wait for a client connection.

## **Declaration**

```C
int easySocket_server_accept(
                        int sock_id
                    )
```

## **Parameters**
**sock_id**  
The server socket's id (generated with [easySocket_server_creation](easySocket_server_creation.md)).

## **Result**
Return the id of the accepted client, or `-1` if failed (for more details, check errno value).