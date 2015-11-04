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
	int sockfd;
	struct sockaddr_in addr;

	unsigned short port;
	char *ip;

	int bytesRead;
	char buffer[BUFSIZE];

	if (argc != 4) {
		fprintf(stderr, "Usage: %s <hostname port fileName>\n", argv[0]);
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket() failed");
		exit(1);
	}

	ip 		= argv[1];
	port	= atoi(argv[2]);
	const char *fileName = argv[3];

	FILE *fIn = fopen(fileName, "r");
	
	if (!fIn) {
		fprintf(stderr, "Cannot open file name [%s]\n", fileName);
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	memset(buffer, '0', BUFSIZE);

	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(port);
	addr.sin_addr.s_addr 	= inet_addr(ip);

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("connect() failed");
		exit(1);
	}

	printf("Sending file name [%s]....\n", fileName);


	while (1) {
		bytesRead = fread(buffer, 1, BUFSIZE, fIn);
		if (bytesRead <= 0)
			break;
		
		if (send(sockfd, buffer, bytesRead, 0) != bytesRead) {
			perror("send() failed");
			exit(1);
		}

		printf("Read %i bytes from file\n", bytesRead);

	}

	close(sockfd);
	fclose(fIn);

	return 0;
}