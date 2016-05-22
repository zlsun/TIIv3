
#include "cliserv.h"

int read_stream(int fd, char* buf, int max)
{
    int nleft, nread;
    nleft = max;
    while (nleft > 0) {
        if ((nread = read(fd, buf, nleft)) < 0)
            return nread;
        if (nread == 0) break;
        nleft -= nread;
        buf += nread;
    }
    return max - nleft;
}

