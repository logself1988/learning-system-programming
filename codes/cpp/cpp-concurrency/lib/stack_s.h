#ifndef LIB_STACK_S
#define LIB_STACK_S

#include <exception>
#include <memory> // for std::shared_ptr<>
#include <mutex>
#include <stack>

struct empty_statck : std::exception
{
  const char *what () const noexcept
  {
    return "Stack is empty.";
  }
};

//!< a thread-safe stack
template <typename T>
class stack_s
{
public:
  stack_s () 
  {
  }
  
  stack_s (const stack_s &other)
  {
    std::lock_guard<std::mutex> lock (other._mutex);
    _data = other._data;
  }

  stack_s &operator= (const stack_s &) = delete;

  void
  push (T new_value)
  {
    std::lock_guard<std::mutex> lock (_mutex);
    _data.push (std::move (new_value));
  }

  std::shared_ptr<T>
  pop ()
  {
    std::lock_guard<std::mutex> lock (_mutex);
    if (_data.empty ())
      throw empty_statck ();
    std::shared_ptr<T> const res (std::make_shared<T> (_data.top ()));
    _data.pop ();
    return res;
  }
  void
  pop (T &value)
  {
    std::lock_guard<std::mutex> lock (_mutex);
    if (_data.empty ())
      throw empty_statck ();
    value = _data.top ();
    _data.pop ();
  }

  bool
  empty () const
  {
    std::lock_guard<std::mutex> lock (_mutex);
    return _data.empty ();
  }

private:
  std::stack<T> _data;
  mutable std::mutex _mutex;
};

#endif /* LIB_STACK_S */
