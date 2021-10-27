#include "apue.h"
#include "apue_thd.h"
#include <errno.h>
#include <signal.h>
#include <string.h>
// #include <syslog.h>

void
reread (void)
{
  printf ("in reread\n");
}

void
sigterm (int signo)
{
  // syslog (LOG_INFO, "got SIGTERM; exiting");
  // exit (0);
  err_quit ("got SIGTERM; exiting");
}

void
sighup (int signo)
{
  // syslog(LOG_INFO, "Re-reading configuration file");
  printf ("Re-reading configuration file\n");

  reread ();
}

int
main (int argc, char *argv[])
{
  char *cmd;
  struct sigaction sa;
  const char *lockfilepath = "reread_m.pid";

  // if ((cmd = strrchr (argv[0], '/')) == NULL)
  // cmd = argv[0];
  // else
  // cmd++;
  cmd = argv[0];

  // daemonize (cmd);

  if (already_running (lockfilepath))
    {
      // syslog ("LOG_ERR", "daemon already running");
      // exit (1);
      err_quit ("daemon already running");
    }

  // handle signal of interest
  sa.sa_handler = sigterm;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGHUP);
  sa.sa_flags = 0;
  if (sigaction (SIGTERM, &sa, NULL) < 0)
    {
      // syslog (LOG_ERR, "can not catch SIGTERM: %s", strerror (errno));
      // exit (1);
      err_quit ("can not catch SIGTERM: %s", strerror (errno));
    }
  sa.sa_handler = sighup;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGTERM);
  sa.sa_flags = 0;
  if (sigaction (SIGHUP, &sa, NULL) < 0)
    {
      // syslog(LOG_ERR, "can not catch SIGHUP: %s", strerror(errno));
      // exit(1);
      err_quit ("can not catch SIGHUP: %s", strerror (errno));
    }

  for (;;)
    {
      printf (".");
      sleep (2);
    }

  exit (0);
}