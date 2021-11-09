
// anonymous structs and unions

union vec3d
{
  struct
  {
    double x;
    double y;
    double z;
  } named;
  double raw[3];
};

union vec3d2
{
  struct
  {
    double x;
    double y;
    double z;
  };
  double raw[3];
};

int
main (int argc, char const *argv[])
{
  union vec3d vec;
  vec.named.x = 1;
  union vec3d2 vec2;
  vec2.x = 1;

  return 0;
}
