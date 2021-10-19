#include <stdio.h>

int _strlen (char *s);

int
main (int argc, char *argv[])
{
  char array[] = "hello, array"; // array declaration and intialization
  char *ptr;

  printf ("%d\n", _strlen ("hello, world"));
  printf ("_strlen(array)=%d\n", _strlen (array)); // array name

  ptr = "hello, pointer";
  printf ("_strlen(ptr)=%d\n", _strlen (ptr));
  ptr = array; // array name
  printf ("_strlen(ptr)=%d\n", _strlen (ptr));
  ptr = &array[0];
  printf ("_strlen(ptr)=%d\n", _strlen (ptr));
  ptr = &array[1];
  printf ("_strlen(ptr)=%d\n", _strlen (ptr));

  return 0;
}

int
_strlen (char *s)
{
  int n;
  for (n = 0; *s != '\0'; s++)
    n++;
  return n;
}
