#include "server.h"

client_t* newClient(int socketfd, int client_id) {
    client_t* n_client = malloc(sizeof(client_t));
    n_client->socketfd = socketfd;
    n_client->id = client_id;
    n_client->shutdown = false;
    return n_client;
}

void closeClient(struct client* client) {
    client->shutdown = true;
}

void* handleClient(void* arg) {
    struct client* client = malloc(sizeof(struct client));
    client =  (struct client*)arg;
    char buffer[500];
    char error[1024];
    if(client->socketfd < 0) {
        snprintf(error, sizeof(error), "socket error on client %d", client->id);
        perror(error);
        return NULL;
    } 
    while(!client->shutdown) {
        int res = recv(client->socketfd, buffer, sizeof(buffer), 0); 
        if(res < 0) {
            snprintf(error, sizeof(error), "recv error on client %d", client->id);
            perror(error);
            return NULL;
        }
        if(res != 0) {
            char response[500];
            snprintf(response, sizeof(response), "Mensagem recebida!!!\n");
            printf("client %d: %s\n", client->id, buffer);
            readInstructions(buffer);
            send(client->socketfd, response, sizeof(response), 0);
            memset(buffer, 0, sizeof(buffer));
        } else {
            continue;
        }
    }
    return NULL;
}

void readInstructions(char* buffer) {
    if(buffer[0] == '0') {
        if(buffer[1] == '0')
            writeFile("admin.txt", "SomeData");
        else if(buffer[1] == '1')
            writeFile("admin.txt", "SomeData2");
        else
            puts("Invalid instruction");
    } else if(buffer[0] == '1') {
        if(buffer[1] == '0')
            writeFile("user.txt", "SomeData");
        else if(buffer[1] == '1')
            writeFile("user.txt", "SomeData2");
        else
            puts("Invalid instruction");
    } else {
        puts("Invalid instruction");
        return;
    }
    
}

void writeFile(const char* filename, const char* data) {
    FILE* file = fopen(filename, "w");
    fputs(data, file);
    fclose(file);
}