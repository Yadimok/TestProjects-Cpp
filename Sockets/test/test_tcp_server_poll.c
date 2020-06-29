#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

#define SIZE_FDS        200
#define BUFFER_LINE     32
#define LISTENQ         1024

struct A{
	float X;
	float Y;
	float Z;
};


int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
char *sock_ntop(const struct sockaddr *sa, socklen_t salen);
const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

int main(int argc, char *argv[])
{
	if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int i, maxi, listenfd, connfd, sockfd, on = 1;
    int nready;
    ssize_t n;
    char buffer[BUFFER_LINE];
    socklen_t client_len;
    struct pollfd client[SIZE_FDS];
    struct sockaddr_in client_addr, server_addr;

	struct A a;

	memset(buffer, 0, sizeof(buffer));

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0) {
        printf("setsockopt error\n");
        exit(EXIT_FAILURE);
    }

	if (ioctl(listenfd, FIONBIO, (char *)&on) < 0) {
        printf("ioctl error\n");
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("bind error\n");
        exit(EXIT_FAILURE);
    }		

	if (listen(listenfd, LISTENQ) < 0) {
        printf("listen error\n");
        exit(EXIT_FAILURE);
    }

    client[0].fd = listenfd;
    client[0].events = POLLIN;
    for (i=1; i<SIZE_FDS; i++)
        client[i].fd = -1;
    maxi = 0;

    for (; ;) {

		if ( (nready = poll(client, maxi+1, -1)) < 0) {
	        printf("poll error\n");
    	    exit(EXIT_FAILURE);
    	}

        if (client[0].revents & POLLIN) 
        {
			client_len = sizeof(client_addr);
			connfd = Accept(listenfd, (struct sockaddr *) &client_addr, &client_len);
			printf("new client: %s\n", sock_ntop((struct sockaddr *) &client_addr, client_len));

			for (i = 1; i < SIZE_FDS; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					break;
				}
			if (i == SIZE_FDS) {
                printf("too many clients\n");
                exit(EXIT_FAILURE);
            }

			client[i].events = POLLIN;
			if (i > maxi)
				maxi = i;

			if (--nready <= 0)
				continue;
		}

        for (i = 1; i <= maxi; i++) 
        {
			if ( (sockfd = client[i].fd) < 0)
				continue;
			if (client[i].revents & (POLLIN | POLLERR)) 
            {
				if ( (n = read(sockfd, buffer, BUFFER_LINE)) < 0) {
					if (errno == ECONNRESET) {
						printf("client[%d] aborted connection\n", i);
						if (close(sockfd) < 0) {
        					printf("close error\n");
        					exit(EXIT_FAILURE);
    					}
						client[i].fd = -1;
					} else {
                        printf("read error\n");
                    }
				} else if (n == 0) {
					printf("client[%d] closed connection\n", i);
					if (close(sockfd) < 0) {
        				printf("close error\n");
        				exit(EXIT_FAILURE);
    				}
					client[i].fd = -1;
				} else {
					memcpy((char *)&a, buffer, sizeof(buffer));
					printf("X: %-3.6f\t Y: %-3.6f\t Z: %-3.6f\n", a.X, a.Y, a.Z);
                }

				if (--nready <= 0)
					break;
			}
		}
    } //for

    exit(EXIT_SUCCESS);
}


int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int		n;

again:
	if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef	EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else {
            printf("accept error\n");
            exit(EXIT_FAILURE);
        }
	}
	return(n);
}

char *sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
    char		portstr[8];
    static char str[128];

	switch (sa->sa_family) 
    {
	case AF_INET: 
    {
		struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return(NULL);
		if (ntohs(sin->sin_port) != 0) {
			snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
			strcat(str, portstr);
		}
		return(str);
	}

	default:
		snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);
		return(str);
	}
    return (NULL);
}

const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const unsigned char *p = (const unsigned char *) addrptr;

	if (family == AF_INET) {
		char	temp[16];

		snprintf(temp, sizeof(temp), "%d.%d.%d.%d",
				 p[0], p[1], p[2], p[3]);
		if (strlen(temp) >= len) {
			errno = ENOSPC;
			return (NULL);
		}
		strcpy(strptr, temp);
		return (strptr);
	}
	errno = EAFNOSUPPORT;
	return (NULL);
}
