#include "apue.h"
#include "apue_thd.h"

int
main (int argc, char *argv[])
{
  char *cmd = "sleep 10 && uptime && echo \"xyz\"";

  daemonize (cmd);

  sleep (15);
  exit (0);
}