#ifndef BITDEWY_UNIQUE_HANDLE_HPP_
#define BITDEWY_UNIQUE_HANDLE_HPP_
#include <windows.h>

namespace bitdewy {

template <typename T, typename Traits>
class unique_handle {
public:
  explicit unique_handle(T value = Traits::invalid())
    : value_(value) {}
  unique_handle(unique_handle&& other)
    : value_(other.release()) {}
  unique_handle& operator=(unique_handle&& other) {
    reset(other.release());
    return *this;
  }
  ~unique_handle() { close(); }
  T get() { return value_; }
  bool reset(T value = Traits::invalid()) {
    if (value_ != value) {
      close();
      value_ = value;
    }
    return *this;
  }
  T release() {
    auto value = value_;
    value_ = Traits::invalid();
    return value;
  }
private:
  unique_handle(const unique_handle&);
  unique_handle& operator=(const unique_handle&);
  bool operator==(const unique_handle&);
  bool operator!=(const unique_handle&);
  struct bool_struct { int member; };
  using bool_type = int bool_struct::*;
  operator bool_type() {
    return Traits::invalid() != value_ ? &bool_struct::member : nullptr;
  }
  void close() {
    if (*this) {
      Traits::close(value_);
    }
  }
  T value_;
};

struct handle_traits {
  static HANDLE invalid() {
    return nullptr;
  }
  static void close(HANDLE handle) {
    CloseHandle(handle);
  }
};

typedef unique_handle<HANDLE, handle_traits> handle;

// more traits here...

}  // namespace bitdewy

#endif  // BITDEWY_UNIQUE_HANDLE_HPP_
