#ifndef BITDEWY_PIMPL_IMPL_H_
#define BITDEWY_PIMPL_IMPL_H_

#include <utility>

namespace bitdewy
{

template <typename T>
pimpl<T>::pimpl() : m(new T)
{
}

template <typename T>
template <typename Arg>
pimpl<T>::pimpl(Arg&& arg) : m(new T(std::forward<Arg>(arg)))
{
}
template <typename T>
template <typename Arg1, typename Arg2> 
pimpl<T>::pimpl(Arg1&& arg1, Arg2&& arg2)
  : m(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)))
{
}

template <typename T>
pimpl<T>::~pimpl()
{
}

template <typename T>
T* pimpl<T>::operator->()
{
  return m.operator->();
}

template <typename T>
T& pimpl<T>::operator*()
{
  return m.operator*();
}

}  // namespace bitdewy

#endif
