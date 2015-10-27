#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT		3333

char message1[] = "Hello user!";
char message2[] = "Bye!";

int main()
{
	int sockfd;
	struct sockaddr_in addr;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket() failed");
		exit(1);
	}

	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(PORT);
	addr.sin_addr.s_addr 	= htonl(INADDR_LOOPBACK);

	sendto(sockfd, message1, sizeof(message1), 0, (struct sockaddr*)&addr, sizeof(addr));

	connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	send(sockfd, message2, sizeof(message2), 0);

	close(sockfd);

	return 0;
}