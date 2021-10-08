#include "codec/codec.h"
#include "db/scanner.h"
#include "ui/ui.h"
#include <stdio.h>

int
main (int argc, char **argv)
{

  printf ("Calling codec(): %d\n", codec ());
  printf ("Calling ui(): %d\n", ui ());
  return 0;
}