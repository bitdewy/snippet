#ifndef BITDEWY_MEMBER_DETECTOR_H_
#define BITDEWY_MEMBER_DETECTOR_H_

template<typename T>
class DetectX
{
  struct Fallback { int X; };  // add member name "X"
  struct Derived : T, Fallback { };

  template<typename U, U> struct Check;

  typedef char ArrayOfOne[1];  // typedef for an array of size one.
  typedef char ArrayOfTwo[2];  // typedef for an array of size two.

  template<typename U>
  static ArrayOfOne& func(Check<int Fallback::*, &U::X>*);

  template<typename U>
  static ArrayOfTwo& func(...);

public:
  typedef DetectX type;
  enum { value = sizeof(func<Derived>(0)) == 2 };
};

#endif

