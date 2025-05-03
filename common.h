#ifndef _COMMON_H_
#define _COMMON_H_

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stddef.h>

#define SERVER_PORT 3000
#define MAX_LINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);
void *bin2hex(const unsigned char *input, size_t len);

#endif // _COMMON_H_
