
#include "cliserv.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in serv;
    char* request;
    size_t size;
    char reply[MAX_REPLY];
    int sockfd, n;

    if (argc > 2)
#ifdef USE_TTCP
        err_quit("usage: ttcpcli [<IP of server>]");
#else
        err_quit("usage: tcpcli [<IP of server>]");
#endif

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(argc == 2 ? argv[1] : "127.0.0.1");
#ifdef USE_TTCP
    serv.sin_port = htons(TTCP_SERV_PORT);
#else
    serv.sin_port = htons(TCP_SERV_PORT);
#endif

    if (connect(sockfd, (SA)&serv, sizeof(serv)) < 0)
        err_sys("connect error");

    for (;;) {
        printf("> ");
        if ((n = getline(&request, &size, stdin)) == -1)
            break;
        request[n - 1] = '\0';

#ifdef USE_TTCP
        if (sendto(sockfd, request, MAX_REQUEST, 0, (SA)&serv, sizeof(serv)) != MAX_REQUEST)
            err_sys("sendto error");
#else
        if (write(sockfd, request, MAX_REQUEST) != MAX_REQUEST)
            err_sys("write error");
#endif
        if ((n = read_stream(sockfd, reply, MAX_REPLY)) < 0)
            err_sys("read error");

        printf("%s\n", reply);
    }

    if (shutdown(sockfd, 1) < 0)
        err_sys("shutdown error");

    free(request);
    exit(0);
}
