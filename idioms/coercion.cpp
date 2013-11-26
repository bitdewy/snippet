#include <iostream>

class B {};
class D : public B {};

template <class T>
class Ptr {
 public:
  Ptr() {}

  Ptr(const Ptr& p)
    : ptr(p.ptr) {
    std::cout << "Copy constructor\n";
  }

  // Supporting coercion using member template constructor.
  // This is not a copy constructor, but behaves similarly.
  template <class U>
  Ptr(const Ptr<U>& p)
    : ptr(p.ptr) {  // Implicit conversion from U to T required
    std::cout << "Coercing member template constructor\n";
  }

  // Copy assignment operator.
  Ptr& operator=(const Ptr& p) {
    ptr = p.ptr;
    std::cout << "Copy assignment operator\n";
    return *this;
  }

  // Supporting coercion using member template assignment operator.
  // This is not the copy assignment operator, but works similarly.
  template <class U>
  Ptr& operator=(const Ptr<U>& p) {
    ptr = p.ptr; // Implicit conversion from U to T required
    std::cout << "Coercing member template assignment operator\n";
    return *this;
  }

  T* ptr;
};

int main(void) {
  Ptr<D> d_ptr;
  Ptr<B> b_ptr(d_ptr);  // Now supported
  b_ptr = d_ptr;        // Now supported
  return 0;
}
