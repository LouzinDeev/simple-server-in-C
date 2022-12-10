#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <error.h>

int main(int argc, char** argv) {
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_family = AF_INET;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connect");
        exit(1);
    }
    if(send(sock, argv[3], sizeof(255), 0) < 0) {
        perror("Send");
        exit(1);
    }
    char buffer[1050];
    recv(sock, buffer, sizeof(buffer), 0);
    printf("server: %s", buffer);
    close(sock);
    return 0;
}