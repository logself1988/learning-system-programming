struct S
{
  const char *name;
  int value;
};

struct pair
{
  int a;
  int b;
};

int
main (int argc, char const *argv[])
{
  struct S new_s = { "myname", 4 };

  struct pair p = { 0 }; // assign 0 to all fields

  struct pair st = { .a = 1, .b = 2 }; // c99

  return 0;
}
