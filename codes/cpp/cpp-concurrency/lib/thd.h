#ifndef LIB_THD
#define LIB_THD

#include <thread>

//! guard to thread join
class thread_guard
{
public:
  explicit thread_guard (std::thread &t) : _t (t) {}
  ~thread_guard ()
  {
    if (_t.joinable ())
      {
        _t.join ();
      }
  }
  thread_guard (thread_guard const &)
      = delete; //!< not provide copy constructor
  thread_guard &operator= (thread_guard const &)
      = delete; //!< not provide copy-assignment operator

private:
  std::thread &_t;
};

//! take ownership of the thread
class scoped_thread
{
public:
  explicit scoped_thread (std::thread t) : _t (std::move (t))
  {
    if (!_t.joinable ())
      {
        throw std::logic_error ("No thread");
      }
  }
  ~scoped_thread () { _t.join (); }

private:
  std::thread _t;
};

//! similar to std::thread, automatically join in the destructor
class joining_thread
{
public:
  joining_thread () noexcept = default;
  template <typename Callable, typename... Args>
  explicit joining_thread (Callable &&func, Args &&... args)
      : _t (std::forward<Callable> (func), std::forward<Args> (args)...)
  {
  }
  explicit joining_thread (std::thread t) noexcept : _t (std::move (t)) {}
  joining_thread (joining_thread &&other) noexcept : _t (std::move (other._t))
  {
  }
  joining_thread &
  operator= (joining_thread &&other) noexcept
  {
    if (joinable ())
      join ();
    _t = std::move (other._t);
    return *this;
  }
  joining_thread &
  operator= (std::thread other) noexcept
  {
    if (joinable ())
      join ();
    _t = std::move (other);
    return *this;
  }
  ~joining_thread () noexcept
  {
    if (joinable ())
      join ();
  }
  void
  swap (joining_thread &other) noexcept
  {
    _t.swap (other._t);
  }
  std::thread::id
  get_id () const noexcept
  {
    return _t.get_id ();
  }
  bool
  joinable () const noexcept
  {
    return _t.joinable ();
  }
  void
  join ()
  {
    _t.join ();
  }
  void
  detach ()
  {
    _t.detach ();
  }
  std::thread &
  as_thread () noexcept
  {
    return _t;
  }
  const std::thread &
  as_thread () const noexcept
  {
    return _t;
  }

private:
  std::thread _t;
};

#endif /* LIB_THD */
