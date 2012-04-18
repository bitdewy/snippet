// The C++ Standard allows, in 5.3.5/5, pointers to incomplete class types to be
// deleted with a delete-expression. When the class has a non-trivial
// destructor, or a class-specific operator delete, the behavior is undefined.

// checked delete idioms verify that types are complete for increased safety
// implement in boost
// http://svn.boost.org/svn/boost/trunk/boost/checked_delete.hpp

template<class T> inline void checked_delete(T* x)
{
  // intentionally complex - simplification causes regressions
  typedef char type_must_be_complete[sizeof(T)? 1: -1];
  (void) sizeof(type_must_be_complete);
  delete x;
}

template<class T> inline void checked_array_delete(T* x)
{
  typedef char type_must_be_complete[sizeof(T)? 1: -1];
  (void) sizeof(type_must_be_complete);
  delete[] x;
}
