#ifndef BITDEWY_THREAD_H_
#define BITDEWY_THREAD_H_

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/thread/condition.hpp>
#include <Windows.h>

namespace bitdewy
{

class thread : boost::noncopyable,
               boost::equality_comparable<thread>
{

public:
  typedef DWORD id;
  typedef boost::function<void ()> thread_func;
  explicit thread(const thread_func& f)
    : hthread_(0), tid_(0), func_(f)
  {}
  ~thread() {
    // FIXME: Closing a thread handle does not terminate the associated thread
    // or remove the thread object.
    CloseHandle(hthread_);
  }

  void start() {
    hthread_ = CreateThread(NULL, 0, start_thread, this, 0, &tid_);
    if (!hthread_) {
      //create thread failed
    }
  }
  void join() {
    WaitForSingleObject(hthread_, INFINITE);
  }

  id tid() const { return tid_; }

private:
  static unsigned long WINAPI start_thread(void* o) {
    thread* t = static_cast<thread*>(o);
    t->run();
    return 0;
  }
  void run() { func_(); }
  typedef HANDLE handle;
  handle hthread_;
  id tid_;
  thread_func func_;

};

bool operator==(const thread& lhs, const thread& rhs)
{
  return lhs.tid() == rhs.tid();
}

}  // namespace bitdewy

#endif
