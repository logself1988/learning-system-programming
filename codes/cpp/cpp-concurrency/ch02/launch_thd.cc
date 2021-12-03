#include <iostream>
#include <thread>

// a class with a function call operator
class backgroud_task
{
  public:
  void operator()() const {
    do_something();
  }
  void do_something() const {
    std::cout << "I am background_task." << std::endl;
  }
};

void do_something() {
      std::cout << "I am do_something function." << std::endl;
}

int main(int argc, char const *argv[])
{
  // pass an instance of a class with function call operator
  backgroud_task task;
  std::thread my_thread(task);
  my_thread.join();

// using lambda expressions
  std::thread my_thread2([]
                         { do_something(); });
  my_thread2.join();

  return 0;
}
