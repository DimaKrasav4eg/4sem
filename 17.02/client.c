#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(27312);

    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int a = 1;
    //setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &a, sizeof(a));


    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        printf("%s", recvBuff);
    }

    if(n < 0)
    {
        printf("\n Read error \n");
    }

    return 0;
}