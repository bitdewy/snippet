// null pointer idioms resolve confusion in overload resolution problem between
// pointer type and digital type
// NOTE: In C++0x, the nullptr name itself is a keyword and requires no headers.

const  // It is a const object
class nullptr_t
{
public:
  // convertible to any type of null non-member pointer
  template <class T>
  inline operator T*() const
  { return 0; }

  template<class C, class T>
  inline operator T C::*() const  // or any type of null member pointer
  { return 0; }

private:
  void operator&() const;  // Can't take address of nullptr

} null_ptr = {};
