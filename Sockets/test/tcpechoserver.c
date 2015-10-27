#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTSERVER	3333
#define BUFSIZE		1024

int main()
{
	int sockfd, listener;
	struct sockaddr_in addr;
	char buffer[BUFSIZE];
	int bytesRead;

	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() failed");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORTSERVER);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		exit(1);
	}

	listen(listener, 1);

	// while (1)
	// {
		if ((sockfd = accept(listener, 0, 0)) < 0)
		{
			perror("accept() failed");
			exit(1);
		}

		while (1)
		{
			
			if ((bytesRead = recv(sockfd, buffer, BUFSIZE, 0)) <= 0)
				break;
			send(sockfd, buffer, bytesRead, 0);
		}

		close(sockfd);
	// }
	return 0;
}