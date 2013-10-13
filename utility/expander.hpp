#ifndef BITDEWY_EXPANDER_HPP_
#define BITDEWY_EXPANDER_HPP_

namespace bitdewy {

template <unsigned K, class R, class F, class Tup> struct Expander {
  template <class... Us>
  static R expand(F f, Tup&& t, Us... args) {
    return Expander<K - 1, R, F, Tup>::expand(f,
                                              std::forward<Tup>(t),
                                              std::get<K - 1>(std::forward<Tup>(t)),
                                              std::forward<Us>(args)...);
  }
};

template <class F, class R, class Tup> struct Expander<0, R, F, Tup> {
  template <class... Us> static R expand(F f, Tup&&, Us... args) {
    return f(std::forward<Us>(args)...);
  }
};

template <class F, class... Ts>
auto explode(F&& f, const std::tuple<Ts...>& t)
  -> typename std::result_of<F(Ts...)>::type {
  return Expander<sizeof...(Ts),
                  typename std::result_of<F(Ts...)>::type,
                  F,
                  const std::tuple<Ts...>&>::expand(f, t);
}
  
template <class F, class... Ts>
auto explode(F&& f, std::tuple<Ts...>& t)
  -> typename std::result_of<F(Ts...)>::type {
  return Expander<sizeof...(Ts),
                  typename std::result_of<F(Ts...)>::type,
                  F,
                  std::tuple<Ts...>&>::expand(f, t);
}
  
template <class F, class... Ts>
auto explode(F&& f, std::tuple<Ts...>&& t)
  -> typename std::result_of<F(Ts...)>::type {
  return Expander<sizeof...(Ts),
                  typename std::result_of<F(Ts...)>::type,
                  F,
                  std::tuple<Ts...>&&>::expand(f, std::forward<std::tuple<Ts...>>(t));
}
  
}  // namespace bitdewy


#endif  // BITDEWY_EXPANDER_HPP_
