//

#ifndef BITDEWY_ENABLE_IF_H_
#define BITDEWY_ENABLE_IF_H_

template <bool, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T>
{
  typedef T type;
};

#endif

