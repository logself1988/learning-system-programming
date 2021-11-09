// 1. global type namespace
// 2. tag-namespace: shared between struct, union and enum datatypes

typedef unsigned int type;
struct type
{
  char c;
};

int
main (int argc, char const *argv[])
{
  struct type st;
  type t;

  return 0;
}
