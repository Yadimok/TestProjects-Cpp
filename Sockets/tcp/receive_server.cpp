#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE		1024

int main(int argc, char *argv[])
{
	int sockfd, listener;
	struct sockaddr_in addr;
	char buffer[BUFSIZE];
	int bytesRead;
	unsigned short port;

	const char *fileName = "test";

	if (argc != 2) {
		fprintf(stderr, "Usage: <server port>%s\n", argv[0]);
		exit(1);
	}

	if ((listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket() failed");
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	memset(buffer, '0', BUFSIZE);

	port = atoi(argv[1]);

	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(port);
	addr.sin_addr.s_addr 	= htonl(INADDR_ANY);

	if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
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

	FILE *fOut = fopen(fileName, "w");
	if (!fOut) {
		fprintf(stderr, "Cannot open file name [%s]\n", fileName);
		exit(1);	
	}

	while (1) {

		if ((bytesRead = recv(sockfd, buffer, BUFSIZE, 0)) < 0) {
			perror("recv() failed");
			exit(1);
		}

		if (bytesRead == 0) {
			break;
		}

		if (fwrite(buffer, 1, bytesRead, fOut) != bytesRead) {
			perror("fwrite() failed");
			exit(1);
		}

	}

	fclose(fOut);
	close(sockfd);
	close(listener);

	return 0;
}