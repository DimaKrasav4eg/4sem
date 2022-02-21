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

#define PORT 273
#define LINE 1024


int main(int argc, char const *argv[])
{
	char buf[LINE];
	char *hello_to_server = "London is the capital of GB";
	struct sockaddr_in servaddr;
	int len = sizeof(servaddr);
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	
	if (sockfd < 0)
	{
		perror("socket()");
		return 1;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind()");
		return 1;
	}
	int a = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &a, sizeof(a)) < 0)
	{
		printf("Error setsockopt\n");
		return 1;
	}



	if (sendto(sockfd, (void *)hello_to_server, sizeof(hello_to_server), MSG_CONFIRM, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("sendto()");
		return 1;
	}



	if (recvfrom(sockfd, buf, sizeof(buf), MSG_PEEK, (struct sockaddr *)&servaddr, &len) < 0)
	{
		printf("Error recvfrom\n");
		return 1;
	}
	printf("%s\n", buf);


	return 0;
}