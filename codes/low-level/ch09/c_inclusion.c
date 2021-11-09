#include <stdio.h>

// inclusion: every struct's address is the same as the address of its first
// element

struct parent
{
  const char *field_parent;
};

struct child
{
  struct parent base;
  const char *field_child;
};

void
parent_print (struct parent *this)
{
  printf ("%s\n", this->field_parent);
}

int
main (int argc, char const *argv[])
{
  struct child c;
  c.base.field_parent = "parent";
  c.field_child = "child";

  parent_print ((struct parent *)&c); // cast
  return 0;
}
