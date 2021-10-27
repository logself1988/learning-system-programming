#include "apue.h"
#include "apue_thd.h"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h> // umask
#include <syslog.h>

int
makethread_detached (void *(*fn) (void *), void *arg)
{
  int err;
  pthread_t tid;
  pthread_attr_t attr;

  err = pthread_attr_init (&attr);
  if (err != 0)
    return (err);
  err = pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  if (err == 0)
    err = pthread_create (&tid, &attr, fn, arg);
  pthread_attr_destroy (&attr);
  return (err);
}

int
already_running (const char *lockfilepath)
{
  int fd;
  char buf[16];

  // see susv4-2018: open(): Opening a File for Writing by the Owner
  fd = open (lockfilepath, O_RDWR | O_CREAT,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd < 0)
    {
      // syslog (LOG_ERR, "can not open %s: %s", LOCKFILE, strerror (errno));
      // exit (1);
      err_quit ("can not open %s: %s", lockfilepath, strerror (errno));
    }

  // try to lock file
  if (lockfile (fd) < 0)
    {
      if (errno == EACCES || errno == EAGAIN)
        {
          close (fd);
          return (1);
        }

      // syslog (LOG_ERR, "can not lock %s: %s", LOCKFILE, strerror (errno));
      // exit (1);
      err_quit ("can not open %s: %s", lockfilepath, strerror (errno));
    }

  ftruncate (fd, 0);
  sprintf (buf, "%ld", (long)getpid ());
  write (fd, buf, strlen (buf) + 1);
  return (0);
}

void
daemonize (const char *cmd)
{
  int i, fd0, fd1, fd2;
  pid_t pid;
  struct rlimit rl;
  struct sigaction sa;

  // clean file creation mask
  umask (0);

  // get maximum number of file descriptors
  if (getrlimit (RLIMIT_NOFILE, &rl) < 0)
    err_quit ("%s: can not get file limit", cmd);

  // become a session leader to lose controlling TTY
  if ((pid = fork ()) < 0)
    err_quit ("%s: can not fork", cmd);
  else if (pid != 0) // parent
    exit (0);
  setsid ();

  // ensure future opens will not allocate controlling TTYs
  sa.sa_handler = SIG_IGN;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction (SIGHUP, &sa, NULL) < 0)
    err_quit ("%s: can not ignore SIGHUP", cmd);
  if ((pid = fork ()) < 0)
    err_quit ("%s: can not fork()", cmd);
  else if (pid != 0) // parent
    exit (0);

  if (chdir ("/") < 0)
    err_quit ("%s: can not change directory to /", cmd);

  // close all open fds
  if (rl.rlim_max == RLIM_INFINITY)
    rl.rlim_max = 1024;
  for (i = 0; i < rl.rlim_max; i++)
    close (i);

  // attach fd 0,1,2 to /dev/null
  fd0 = open ("/dev/null", O_RDWR);
  fd1 = dup (0);
  fd2 = dup (0);

  // initialze log file
  openlog (cmd, LOG_CONS, LOG_DAEMON);
  syslog (LOG_INFO, "%s", cmd);

  if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
      syslog (LOG_ERR, "unexpected fd %d %d %d", fd0, fd1, fd2);
      exit (1);
    }
}