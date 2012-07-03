#ifndef BITDEWY_MUTEX_H_
#define BITDEWY_MUTEX_H_

#include <boost/noncopyable.hpp>
#include <Windows.h>

namespace bitdewy
{

class mutex : boost::noncopyable
{

public:
  mutex() { InitializeCriticalSection(&mutex_); }
  ~mutex() { DeleteCriticalSection(&mutex_); }
  void lock() { EnterCriticalSection(&mutex_); }
  void unlock() { LeaveCriticalSection(&mutex_); }

private:
  typedef CRITICAL_SECTION mutex_type;
  mutex_type mutex_;

};

class lock_guard : boost::noncopyable
{

public:
  explicit lock_guard(mutex& m) : mutex_(m) {
    mutex_.lock();
  }
  ~lock_guard() { mutex_.unlock(); }

private:
  mutex& mutex_;

};

}  // namespace bitdewy

#endif
