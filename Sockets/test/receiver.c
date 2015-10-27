#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 		3333
#define BUFSIZE		1024

int main()
{
	int sockfd;
	struct sockaddr_in addr;
	char buffer[BUFSIZE];
	int bytesRead;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket() failed");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		exit(1);
	}

	while (1)
	{
		bytesRead = recvfrom(sockfd, buffer, BUFSIZE, 0, 0, 0);
		buffer[bytesRead] = '\0';
		printf("%s\n", buffer);
	}

	close(sockfd);

	return 0;
}