#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTCLIENT 	3333

char message[] = "Hello user!";
char buffer[sizeof(message)];

int main()
{
	int sockfd;
	struct sockaddr_in addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() failed");
		exit(1);
	}

	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(PORTCLIENT);
	addr.sin_addr.s_addr 	= htonl(INADDR_LOOPBACK);

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		perror("connect() failed");
		exit(1);
	}

	send(sockfd, message, sizeof(message), 0);
	recv(sockfd, buffer, sizeof(message), 0);

	printf("%s\n",buffer);
	close(sockfd);

	return 0;
}