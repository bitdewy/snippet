#ifndef BITDEWY_FIXEDPOINT_HPP_
#define BITDEWY_FIXEDPOINT_HPP_

namespace bitdewy {
    
template<typename R, typename V>
struct fixpoint {
  typedef std::function<R(V)> func_t;
  typedef std::function<func_t(func_t)> tfunc_t;
  typedef std::function<func_t(tfunc_t)> yfunc_t;
  
  class loopfunc_t {
   public:
    func_t operator()(loopfunc_t v) const {
      return func(v);
    }
    
    template<typename L> loopfunc_t(const L &l):func(l) {}
  
   private:
    std::function<func_t(loopfunc_t)> func;
  };
  
  static yfunc_t fix;
};

template<typename R, typename V>
typename fixpoint<R, V>::yfunc_t fixpoint<R, V>::fix =
  [](fixpoint<R, V>::tfunc_t f) -> fixpoint<R, V>::func_t {
    fixpoint<R, V>::loopfunc_t l = [f](fixpoint<R, V>::loopfunc_t x)
    ->fixpoint<R, V>::func_t {
      return [f, x](V v) {
        return f(x(x))(v);
      };
    };
    return l(l);
  };
}  // namespace bitdewy

#endif  // BITDEWY_FIXEDPOINT_HPP_
