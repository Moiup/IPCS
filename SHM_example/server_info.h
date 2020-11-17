#include "../IPCS/ipcs.h"
#include <string.h>
#include <unistd.h>

#define SERVER_NAME "server.file"
#define LETTER_CODE 'a'

#define CHILD_NAME "./client"

#define NO_VAL -1

#define SHM_SIZE 5
#define SHM_INIT_CONTENT 'm'
#define SHM_CLIENT_MODIFY 'H'
