#ifndef _SERVER_H_
#define _SERVER_H_
#include "common.h"

typedef struct client {
    int socketfd;
    uint32_t id;
    bool shutdown;
}client_t;


client_t* newClient(int socketfd, int client_id);
void closeClient(struct client* client);
void* handleClient(void* arg);
void readInstructions(char* buffer);
void writeFile(const char* filename, const char* data);

#endif