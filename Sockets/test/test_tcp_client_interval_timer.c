#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "common.h"


#define BUFFER_LINE 12

static volatile sig_atomic_t gotAlarm = 1;
static void signalHandler(int sig);
void timerHandler(int signum);

int socket_fd;
float x = 0.0f, y = 0.0f, z = 0.0f;
char toServer[BUFFER_LINE];

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s <ip address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in remote;

    time_t t = time(NULL);    
    printf("%s\n", ctime(&t));

    srand(0);

    struct sigaction sa;
    struct itimerval timer;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = timerHandler;
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        printf("sigaction failed\n");
        exit(EXIT_FAILURE);
    }

    //start after 1s
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    //every 1 msec
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 1000;

    setitimer(ITIMER_REAL, &timer, NULL);

    memset(toServer, 0, sizeof(toServer));

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("socket failed\n");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    bzero(&remote, sizeof(remote));
    remote.sin_addr.s_addr = inet_addr(argv[1]);
    remote.sin_family = AF_INET;
    remote.sin_port = htons(atoi(argv[2]));
    if (connect(socket_fd, (struct sockaddr *)&remote, sizeof(struct sockaddr_in)) < 0) {
        printf("connect failed\n");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    (void)signal(SIGINT, signalHandler);
    while (gotAlarm) {

    }

    close(socket_fd);

    return EXIT_SUCCESS;
}

static void signalHandler(int sig)
{
    gotAlarm = 0;
    printf("\nSignal stopped.\n");
}

void timerHandler(int signum)
{
    x = valueX[rand() % numberX];
    y = valueY[rand() % numberY];
    z = valueZ[rand() % numberZ];

    toServer[0] = *((char *)(&x));
    toServer[1] = *((char *)(&x)+1);
    toServer[2] = *((char *)(&x)+2);
    toServer[3] = *((char *)(&x)+3);

    toServer[4] = *((char *)(&y));
    toServer[5] = *((char *)(&y)+1);
    toServer[6] = *((char *)(&y)+2);
    toServer[7] = *((char *)(&y)+3);
    
    toServer[8] = *((char *)(&y));
    toServer[9] = *((char *)(&y)+1);
    toServer[10] = *((char *)(&y)+2);
    toServer[11] = *((char *)(&y)+3);

    if (send(socket_fd, toServer, strlen(toServer), 0) < 0) {
        printf("send failed\n");
        close(socket_fd);
    }

    x = y = z = 0.0f;
}