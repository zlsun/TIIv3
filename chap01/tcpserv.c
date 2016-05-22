
#include "cliserv.h"

int id = 0;

void handle(int sockfd, struct sockaddr_in cli);

int main(int argc, char *argv[])
{
    struct sockaddr_in serv, cli;
    char addr[INET_ADDRSTRLEN];
    int listenfd, sockfd, pid;
    socklen_t clilen;

    if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
#ifdef USE_TTCP
    serv.sin_port = htons(TTCP_SERV_PORT);
#else
    serv.sin_port = htons(TCP_SERV_PORT);
#endif

    if (bind(listenfd, (SA)&serv, sizeof(serv)) < 0)
        err_sys("bind error");

    inet_ntop(serv.sin_family, &serv.sin_addr, addr, INET_ADDRSTRLEN);
    printf("Start Server: %s:%d\n", addr, ntohs(serv.sin_port));

    if (listen(listenfd, SOMAXCONN) < 0)
        err_sys("listen error");

    for (;;) {
        clilen = sizeof(cli);
        if ((sockfd = accept(listenfd, (SA)&cli, &clilen)) < 0)
            err_sys("accept error");
        if ((pid = fork()) == -1) {
            close(sockfd);
            continue;
        } else if (pid > 0) {
            ++id;
            close(sockfd);
            continue;
        } else {
            ++id;
            handle(sockfd, cli);
            break;
        }
    }

    printf("[%d] End\n", id);
    exit(0);
}

void handle(int sockfd, struct sockaddr_in cli)
{
    char request[MAX_REQUEST], reply[MAX_REPLY];
    char addr[INET_ADDRSTRLEN];
    int n;
    inet_ntop(cli.sin_family, &cli.sin_addr, addr, INET_ADDRSTRLEN);
    printf("[%d] Client: %s:%d\n", id, addr, ntohs(cli.sin_port));
    while ((n = read_stream(sockfd, request, MAX_REQUEST)) != 0) {
        if (n == -1) err_sys("read error");
        printf("[%d] Recv: %s\n", id, request);
        strcpy(reply, request);
        printf("[%d] Send: %s\n", id, reply);
#ifdef USE_TTCP
        if (send(sockfd, reply, MAX_REPLY, MSG_EOF) != MAX_REPLY)
            err_sys("write error");
#else
        if (write(sockfd, reply, MAX_REPLY) != MAX_REPLY)
            err_sys("write error");
#endif
    }
    close(sockfd);
}
