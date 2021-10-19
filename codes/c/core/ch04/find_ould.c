#include <stdio.h>

#define MAXLINE 1000

int _getline (char line[], int max);
// return pos of searchfor in source
int _strindex (char source[], char searchfor[]);

char pattern[] = "ould";

int
main (int argc, char *argv[])
{
  char line[MAXLINE];
  int found = 0;

  while (_getline (line, MAXLINE))
    {
      if (_strindex (line, pattern) >= 0)
        {
          printf ("%s", line);
          found++;
        }
    }
  printf ("\nFound %d\n", found);

  return 0;
}

int
_getline (char line[], int max)
{
  int c, i;

  i = 0;
  while (--max > 0 && (c = getchar ()) != EOF && c != '\n')
    line[i++] = c;
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';

  return i;
}

int
_strindex (char source[], char searchfor[])
{
  int i, j, k;

  for (i = 0; source[i] != '\0'; i++)
    {
      for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k];
           j++, k++)
        ;
      if (k > 0 && searchfor[k] == '\0')
        return i;
    }

  return -1;
}
