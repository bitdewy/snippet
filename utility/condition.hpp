#ifndef BITDEWY_CONDITION_H_
#define BITDEWY_CONDITION_H_

#include <boost/noncopyable.hpp>
#include <Windows.h>

namespace bitdewy {

namespace detail {

template <typename lock_type>
class relocker : boost::noncopyable {
 public:
  explicit relocker(lock_type& lk) : lock_(lk), unlocked_(false) {}
  ~relocker() {
    if (unlocked_)
      lock_.lock();
  }

  void unlock() { 
    lock_.unlock();
    unlocked_ = true;
  }

 private:
  lock_type& lock_;
  bool unlocked_;
};

}

class condition : boost::noncopyable {
 public:
  condition()
    : hsemaphore_(CreateSemaphore(NULL, 0, MAXLONG, NULL)), 
      count_(0) {
    if (!hsemaphore_) {
      // create semaphore failed
    }
  }

  ~condition() {
    CloseHandle(hsemaphore_);
  }

  void notify_one() {
    if (!count_)
      return;
    wake_waiters(1);
  }

  void notify_all() {
    if (!count_)
      return;
    wake_waiters(count_);
  }

  template<typename lock_type> void wait(lock_type& lk) {
    detail::relocker<lock_type> lock(lk);
    ++count_;
    lock.unlock();
    WaitForSingleObject(hsemaphore_, INFINITE);
  }

 private:
  void wake_waiters(unsigned long count) {
    ReleaseSemaphore(hsemaphore_, count, NULL);
    count_ -= count;
  }

  typedef HANDLE handle;
  handle hsemaphore_;
  unsigned long count_;
};

}  // namespace bitdewy

#endif