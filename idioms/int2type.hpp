//
#ifndef BITDEWY_INT2TYPE_H_
#define BITDEWY_INT2TYPE_H_

template <int I>
struct Int2Type
{
  enum { value = I };
};

#endif

