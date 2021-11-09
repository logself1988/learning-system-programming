struct type
{
  int a;
  int b;
};

typedef struct type type;

int
main (int argc, char const *argv[])
{
  type d;
  d.a = 0;
  d.b = 1;
  return 0;
}
