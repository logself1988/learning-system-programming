#ifndef INCLUDE_APUE_SOCK
#define INCLUDE_APUE_SOCK

#include <netdb.h>
#include <sys/socket.h>

// sock.c

/*
 * Retryable connect();
 */
int connect_retry(int domain, int type, int protocol,
                  const struct sockaddr *addr, socklen_t alen);

/*
 * Allocate and initialize socket for server.
 */
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen);

#endif /* INCLUDE_APUE_SOCK */
