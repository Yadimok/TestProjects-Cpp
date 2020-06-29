#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "common.h"

static volatile sig_atomic_t gotAlarm = 1;

static void signalAlarmHandler(int sig);
void timerHandler(int signum);

int main()
{
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
    timer.it_interval.tv_usec = 1000; //500 ms

    setitimer(ITIMER_REAL, &timer, NULL);

    signal(SIGINT, signalAlarmHandler);
    while (gotAlarm) {
    }

    return 0;
}

static void signalAlarmHandler(int sig) 
{
    gotAlarm = 0;
    printf("Signal stopped\n");
}

void timerHandler(int signum)
{
    printf("X: %-3.6f\t Y: %-3.6f\t Z: %-3.6f\n",
            valueX[rand() % numberX],
            valueY[rand() % numberY],
            valueZ[rand() % numberZ]);
}