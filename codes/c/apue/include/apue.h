#ifndef INCLUDE_APUE
#define INCLUDE_APUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /* max line length */

// error.c
void err_msg(const char *, ...);
void err_dump(const char *, ...) __attribute__((noreturn));
void err_quit(const char *, ...) __attribute__((noreturn));
void err_cont(int, const char *, ...);
void err_exit(int, const char *, ...) __attribute__((noreturn));
void err_ret(const char *, ...);
void err_sys(const char *, ...) __attribute__((noreturn));

// print.c
void pr_exit(int status);
void pr_mask(const char *);

// sync.c
void TELL_WAIT(void);
void TELL_PARENT(pid_t);
void TELL_CHILD(pid_t);
void WAIT_PARENT(void);
void WAIT_CHILD(void);
#if defined(MACOS)
#include <errno.h>
#include <pthread.h>

typedef int pthread_barrierattr_t;
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  int count;
  int tripCount;
} pthread_barrier_t;

int pthread_barrier_init(pthread_barrier_t *barrier,
                         const pthread_barrierattr_t *attr, unsigned int count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);
int pthread_barrier_wait(pthread_barrier_t *barrier);
#endif

#endif /* INCLUDE_APUE */

// thread.c
int makethread_detached(void *(*)(void *), void *);