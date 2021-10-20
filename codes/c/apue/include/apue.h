#ifndef INCLUDE_APUE
#define INCLUDE_APUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAXLINE	4096			/* max line length */

void	err_msg(const char *, ...);
void	err_dump(const char *, ...) __attribute__((noreturn));
void	err_quit(const char *, ...) __attribute__((noreturn));
void	err_cont(int, const char *, ...);
void	err_exit(int, const char *, ...) __attribute__((noreturn));
void	err_ret(const char *, ...);
void	err_sys(const char *, ...) __attribute__((noreturn));

#endif /* INCLUDE_APUE */
