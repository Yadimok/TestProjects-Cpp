#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in addr;

	unsigned short port;
	char *ip;
	char *message;
	int strLength;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s <hostname port message>\n", argv[0]);
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket() failed");
		exit(1);
	}

	ip 						= argv[1];
	port 					= atoi(argv[2]);
	message 				= argv[3];

	memset(&addr, 0, sizeof(addr));

	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(port);
	addr.sin_addr.s_addr 	= inet_addr(ip);

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("connect() failed");
		exit(1);
	}

	strLength = strlen(message);

	if (send(sockfd, message, strLength, 0) != strLength) {
		perror("send() failed");
		exit(1);
	}

	close(sockfd);

	return 0;
}