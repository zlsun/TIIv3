#ifndef CLISERV_H
#define CLISERV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#ifndef MSG_EOF
# ifdef MSG_FIN
#  define MSG_EOF MSG_FIN
# else
#  error Must have either MSG_EOF or MSG_FIN defined
# endif
#endif

#define MAX_REQUEST 400
#define MAX_REPLY 400
#define MAX_LINE 1024

#define UDP_SERV_PORT 7777
#define TCP_SERV_PORT 8888
#define TTCP_SERV_PORT 9999

#define SA struct sockaddr*

int read_stream(int fd, char* buf, int max);

void err_msg(const char*, ...);
void err_dump(const char*, ...) __attribute__((noreturn));
void err_quit(const char*, ...) __attribute__((noreturn));
void err_cont(int, const char*, ...);
void err_exit(int, const char*, ...) __attribute__((noreturn));
void err_ret(const char*, ...);
void err_sys(const char*, ...) __attribute__((noreturn));

#endif /* CLISERV_H */
