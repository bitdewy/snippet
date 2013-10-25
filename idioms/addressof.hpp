#ifndef BITDEWY_ADDRESSOF_H_
#define BITDEWY_ADDRESSOF_H_

class nonaddressable {
 public:
  typedef double useless_type;
 private:
  useless_type operator&() const;
};

// implement in boost
// http://svn.boost.org/svn/boost/trunk/boost/utility/addressof.hpp
template <typename T> T* addressof(T& v) {
  return reinterpret_cast<T*>(
    &const_cast<char&>(reinterpret_cast<const volatile char&>(v)));
}

#endif

// usage:
//int main(void) {
//  nonaddressable na;
//  nonaddressable* naptr = addressof(na);
//  return 0;
//}

