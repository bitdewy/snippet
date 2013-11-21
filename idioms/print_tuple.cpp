#include <tuple>
#include <iostream>

template<std::size_t> struct int_{};

// Forward declaration
template <typename... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t);

// Deal with pair, too
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p) {
  return out << '(' << p.first << ", " << p.second << ')';
}

template <typename Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> ) {
  out << std::get< std::tuple_size<Tuple>::value-Pos>(t) << ", ";
  return print_tuple(out, t, int_<Pos-1>());
}

template <typename Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> ) {
  return out << std::get<std::tuple_size<Tuple>::value-1>(t);
}

template <typename... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
  out << '(';
  print_tuple(out, t, int_<sizeof...(Args)>());
  return out << ')';
}

int main() {
  std::tuple<int, std::string, float> t1{10, "Test", 3.14};
  std::cout << "t1:" << t1 << std::endl;
  std::tuple<int, std::tuple<std::string, float>> t2{10, std::make_tuple("Test", 3.14 )};
  std::cout << "t2:" << t2 << std::endl;
  auto t3 = std::make_tuple(t1, std::make_pair("Foo", std::make_tuple("Nest", 23, 2.71, "bar")), t1);
  std::cout << "t3:" << t3 << std::endl;
  return 0;
}