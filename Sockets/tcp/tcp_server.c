#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define	BUFSIZE		1024

int main(int argc, char *argv[])
{
	int sockfd, listener;
	struct sockaddr_in addr;
	char buffer[BUFSIZE];
	int bytesRead;
	unsigned short serverPort;

	if (argc !=2) {
		fprintf(stderr, "Usage: %s <server port>\n", argv[0]);
		exit(1);
	}

	if ((listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket() failed");
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	memset(buffer, 0, sizeof(buffer));

	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(atoi(argv[1]));
	addr.sin_addr.s_addr 	= htonl(INADDR_ANY);

	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind() failed");
		exit(1);
	}

	if (listen(listener, 1) < 0) {
		perror("listen() failed");
		exit(1);
	}

	if ((sockfd = accept(listener, 0, 0)) < 0) {
		perror("accept() failed");
		exit(1);
	}

	// while(1) {
		if ((bytesRead = recv(sockfd, buffer, BUFSIZE, 0)) < 0) {
			perror("recv() failed");
			exit(1);
		}

		printf("Receive bytes: - %d\t%s\n", bytesRead, buffer);
	// }

	close(listener);

	return 0;
}