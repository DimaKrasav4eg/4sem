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

#define PORT 6660
#define LINE 1024


int main(int argc, char const *argv[])
{
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	char *hi = "Hi from server\n";
	struct sockaddr_in any_sockaddr;
	any_sockaddr.sin_addr.s_addr = INADDR_ANY;
	any_sockaddr.sin_port = htons(PORT);
	any_sockaddr.sin_family = AF_INET;
	int a = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(a));


	if (bind(sockfd, (const struct sockaddr *)&any_sockaddr, sizeof(any_sockaddr)) < 0)
	{
		perror("bind()");
		return 1;
	}

	char buf[LINE];

	struct sockaddr_in my_sockaddr;
	int len = sizeof(my_sockaddr), n = 0;

	//while (1)
	{
		if (n = recvfrom(sockfd, (void *)buf, sizeof(buf), MSG_PEEK, (struct sockaddr *)&my_sockaddr, &len) < 0)
		{
			printf("Error recvfrom\n");
			return 1;
		}
		//buf[n] = '\0';
		printf("Client send: %s\n", buf);


		if (sendto(sockfd, (void *)hi, sizeof(hi), MSG_CONFIRM, (struct sockaddr *)&my_sockaddr, sizeof(struct sockaddr_in)) < 0)
		{
			printf("Error sendto\n");
			return 1;
		}
	}

	return 0;
}