#ifndef BITDEWY_CALLBACK_H_
#define BITDEWY_CALLBACK_H_

#include <cassert>

namespace bitdewy {

class Any {
public:
  virtual ~Any() {}
};

template<typename A>
class CallbackT : public Any
{
public:
    virtual ~CallbackT() {}
    virtual void exec(A) = 0;
};

template<typename T, typename A>
class Bind : public CallbackT<A>
{
public:
  typedef void (T::*F)(A);

  Bind(T *target, F function)
    : target_(target), function_(function)
  {
  }

  void exec(A arg)
  {
      assert(target_);
      (target_->*function_)(arg);
  }

private:
  T *target_;
  F function_;
};

template<typename T, typename C, typename A>
class BindWithContext : public CallbackT<A>
{
public:
  typedef void (T::*F)(C, A);

  BindWithContext(T *target, F function, C context)
    : target_(target), function_(function), context_(context)
  {
  }

  void exec(A arg)
  {
      assert(target_);
      (target_->*function_)(context_, arg);
  }

private:
  T* target_;
  F function_;
  C context_;
};

class Callback
{
public:
  template<typename T, typename C, typename A>
  Callback(T *target, void (T::*function)(C, A), C context)
    : base_(new BindWithContext<T, C, A>(target, function, context))
  {
  }

  template<typename T, typename A>
  Callback(T *target, void (T::*function)(A))
    : base_(new Bind<T, A>(target, function))
  {
  }

  ~Callback()
  {
      delete base_;
  }

  template<typename A>
  void exec(A arg)
  {
      CallbackT<A>* cbp = (CallbackT<A>*) base_;
      cbp->exec(arg);
  }

private:
  Any* base_;
};

}  // namespace bitdewy

#endif // BITDEWY_CALLBACK_H_

