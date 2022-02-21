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

#include <errno.h>

#define PORT 1231
#define LINE 1024


int main(int argc, char const *argv[])
{
	char buf[LINE];
	char *hello_to_server = "London is the capital of GB";
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in servaddr;
	servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	int len = sizeof(servaddr);
	
	if (sockfd < 0)
	{
		perror("socket()");
		return 1;
	}
	int a = 1024;
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &a, sizeof(a)) < 0)
	{
		perror("setsockopt()");
		return 1;
	}

	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind()");
		return 1;
	}



	if (sendto(sockfd, hello_to_server, strlen(hello_to_server), MSG_CONFIRM, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
	{
		perror("sendto()");
		return 1;
	}


	int n = 0;
	if (recvfrom(sockfd, buf, sizeof(buf), MSG_PEEK, (struct sockaddr *)&servaddr, &len) < 0)
	{
		printf("Error recvfrom\n");
		return 1;
	}
	printf("buf = %s\n", buf);


	return 0;
}