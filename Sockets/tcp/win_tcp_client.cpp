#include <cstdio>
#include <winsock2.h>

int main(int argc, char *argv[])
{
    WSAData wsaData;
    SOCKET sock;
    sockaddr_in addr;

    unsigned short port;
    char *ip;
    char *message;

    int result = WSAStartup(MAKEWORD(2, 4), &wsaData);

    if (result != NOERROR)
    {
        printf("Error WSAStartup()");
        return 1;
    }

    if (argc != 4)
    {
        printf("Usage: %s <hostname port message>", argv[0]);
        return 1;
    }

    ip      = argv[1];
    port    = atoi(argv[2]);
    message = argv[3];

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("socket() failed");
        WSACleanup();
        return 1;
    }

    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(port);
    addr.sin_addr.s_addr    = inet_addr(ip);

    if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        printf("connect() failed");
        WSACleanup();
        return 1;
    }

    int bytesSent;

    bytesSent = send(sock, message, strlen(message), 0);
    printf("Send message - %d", bytesSent);

    closesocket(sock);
    WSACleanup();

    return 0;
}