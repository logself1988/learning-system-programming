#include <iostream>

double mysqrt(double x) {
  if (x <= 0) {
    return 0;
  }

  double result = x;

#if defined(HAVE_LOG) && defined(HAVE_EXP)
  result = exp(log(x) * 0.5);
#else
  // do ten iterations
  for (int i = 0; i < 10; ++i) {
    if (result <= 0) {
      result = 0.1;
    }
    double delta = x - (result * result);
    result = result + 0.5 * delta / result;
    std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
  }
#endif

  return result;
}