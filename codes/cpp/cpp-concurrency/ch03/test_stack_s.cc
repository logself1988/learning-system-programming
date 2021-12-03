#include "stack_s.h"
#include <iostream>

stack_s<int> stack;

// TODO
// void work_push()
// {

// }

// void work_pop()
// {

// }

int main(int argc, char const *argv[])
{
  stack.push(0);
  stack.push(1);
  std::cout << stack.pop() << std::endl;
  return 0;
}
