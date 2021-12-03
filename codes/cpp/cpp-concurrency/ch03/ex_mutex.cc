#include <list>
#include <mutex>
#include <algorithm>
#include <thread>
#include <iostream>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

static bool done = false;
void work_add_value()
{
  int i = 0;
  while (!done)  
  {
    add_to_list(i++);
  }
  std::cout << "Done: i="<< i << std::endl;
}

void work_find_value()
{
  int value_to_find = 10000;
  while (!list_contains(value_to_find)) ;
  done = true;
  std::cout << "Found " << value_to_find << std::endl;
}

int main(int argc, char const *argv[])
{
  std::thread t1(work_add_value);
  std::thread t2(work_find_value);

  t1.join();
  t2.join();

  return 0;
}
