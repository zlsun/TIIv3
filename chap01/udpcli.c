
#include "cliserv.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in serv;
    char* request;
    size_t size;
    char reply[MAX_REPLY];
    int sockfd, n;

    if (argc > 2)
        err_quit("usage: udpcli [<IP of server>]");

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        err_sys("socket error");

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(argc == 2 ? argv[1] : "127.0.0.1");
    serv.sin_port = htons(UDP_SERV_PORT);

    for (;;) {
        printf("> ");
        if ((n = getline(&request, &size, stdin)) == -1)
            break;
        request[n - 1] = '\0';
        if (sendto(sockfd, request, MAX_REQUEST, 0, (SA)&serv, sizeof(serv)) != MAX_REQUEST)
            err_sys("sendto error");
        if ((n = recvfrom(sockfd, reply, MAX_REPLY, 0, (SA)NULL, NULL)) < 0)
            err_sys("recvfrom error");
        printf("%s\n", reply);
    }

    free(request);
    exit(0);
}
