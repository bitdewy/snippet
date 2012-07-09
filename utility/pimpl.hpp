#ifndef BITDEWY_PIMPL_H_
#define BITDEWY_PIMPL_H_

#include <memory>

namespace bitdewy
{

template <typename T>
class pimpl
{

public:
  pimpl();
  template <typename Arg> pimpl(Arg&& arg);
  template <typename Arg1, typename Arg2> pimpl(Arg1&& arg1, Arg2&& arg2);
  ~pimpl();
  T* operator->();
  T& operator*();

private:
  std::unique_ptr<T> m;

};

}  // namespace bitdewy

#endif
