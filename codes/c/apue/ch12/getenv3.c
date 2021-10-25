#include "apue.h"
#include <pthread.h>

#define MAXSTRINGSZ 4096
static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void
thread_init (void)
{
  pthread_key_create (&key, free);
}

// thread safe version
char *
getenv_s (const char *name)
{
  int i, len;
  char *envbuf;

  pthread_once (&init_done, thread_init);
  pthread_mutex_lock (&env_mutex);
  envbuf = (char *)pthread_getspecific (key);
  if (envbuf == NULL)
    {
      envbuf = malloc (MAXSTRINGSZ);
      if (envbuf == NULL)
        {
          pthread_mutex_unlock (&env_mutex);
          return (NULL);
        }
      pthread_setspecific (key, envbuf);
    }
  len = strlen (name);
  for (i = 0; environ[i] != NULL; i++)
    {
      if ((strncmp (name, environ[i], len) == 0) && (environ[i][len] == '='))
        {
          strncpy (envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
          pthread_mutex_unlock (&env_mutex);
          return (envbuf);
        }
    }

  pthread_mutex_unlock (&env_mutex);
  return (NULL);
}

int
main (int argc, char *argv[])
{
  char *v;

  v = getenv ("SHELL");
  printf ("v=%s\n", v);

  exit (0);
}