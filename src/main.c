#include "common.h"
#include "server.h"

int main(void) {
    puts("Initializing...\n");
    int opt = true;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(3000);
    socklen_t addr_size = sizeof(addr);
    int serversock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
    if(bind(serversock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }
    puts("succefuly binded...\n");
    puts("listening...\n");
    if(listen(serversock, 10) < 0) {
        perror("listen");
        exit(1);
    }
    int count = 0;
    while(1) {
        int client_fd = accept(serversock, (struct sockaddr *)&addr, &addr_size);
        if(client_fd < 0) {
            perror("socket invalid");
            exit(1);
        }
        client_t* client = newClient(client_fd, count);
        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, (void*)client);
        puts("Client successfully created\n");
        count++;
    }
    return 0;
}