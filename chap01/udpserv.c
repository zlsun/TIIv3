
#include "cliserv.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in serv, cli;
    char request[MAX_REQUEST], reply[MAX_REPLY];
    int sockfd, n, count = 0;
    socklen_t clilen;
    char addr[INET_ADDRSTRLEN];

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        err_sys("socket error");

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(UDP_SERV_PORT);

    if (bind(sockfd, (SA)&serv, sizeof(serv)) < 0)
        err_sys("bind error");

    inet_ntop(serv.sin_family, &serv.sin_addr, addr, INET_ADDRSTRLEN);
    printf("Start Server: %s:%d\n", addr, ntohs(serv.sin_port));

    for (;;) {
        clilen = sizeof(cli);
        if ((n = recvfrom(sockfd, request, MAX_REQUEST, 0, (SA)&cli, &clilen)) < 0)
            err_sys("recvfrom error");
        printf("[%d]\n", ++count);
        inet_ntop(cli.sin_family, &cli.sin_addr, addr, INET_ADDRSTRLEN);
        printf("Client: %s:%d\n", addr, ntohs(cli.sin_port));
        printf("Recv: %s\n", request);
        strcpy(reply, request);
        printf("Send: %s\n", reply);
        if (sendto(sockfd, reply, MAX_REPLY, 0, (SA)&cli, sizeof(cli)) != MAX_REPLY)
            err_sys("sendto error");
    }
    printf("End!\n");

    exit(0);
}
