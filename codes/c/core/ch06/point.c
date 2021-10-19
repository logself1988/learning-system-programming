#include <stdio.h>

struct point
{
  int x;
  int y;
};

struct rect
{
  struct point pt1;
  struct point pt2;
};

void _print_point (struct point);
struct point makepoint (int x, int y);

int
main (int argc, char const *argv[])
{
  struct rect screen;
  struct point middle;

  screen.pt1 = makepoint (0, 0);
  screen.pt2 = makepoint (100, 100);
  middle = makepoint ((screen.pt1.x + screen.pt2.x) / 2,
                      (screen.pt1.y + screen.pt2.y) / 2);
  _print_point (middle);

  return 0;
}

void
_print_point (struct point p)
{
  printf ("struct {x=%d, y=%d}\n", p.x, p.y);
}
struct point
makepoint (int x, int y)
{
  struct point temp;

  temp.x = x;
  temp.y = y;
  return temp;
}
