#include <iostream>

template<typename A> struct monad {
public:
  template<typename B> monad<B>& operator >>=(monad<B>& (*f)(A)) {
    return *new monad_bind<A,B>(*this,f);
  }
  static monad<A>& return_value(A a) {
    return *new monad_return<A>(a);
  }
  virtual A execute() = 0;    // this should be protected, but that causes a c++ problem
private:
  template<typename A1,typename B> struct monad_bind : public monad<B> {
    monad_bind(monad<A1>& ma, monad<B>& (*f)(A1)) : ma_(ma), f_(f) {}
    monad<A1>& ma_;
    monad<B>& (*f_)(A1);
    virtual B execute() {
      A1 a = ma_.execute();
      monad<B>& mb = f_(a);
      return mb.execute();
    }
  };
  template<typename A1> struct monad_return : public monad<A> {
    monad_return(A1 a) : a_(a) {}
    A1 a_;
    virtual A1 execute() {
      return a_;
    }
  };
};

struct unit {};

monad<unit>& write_character(char c) {
  std::cout << c;
  return monad<unit>::return_value(unit());
}

monad<char>& read_character(unit) {
  char c;
  std::cin >> c;
  return monad<char>::return_value(c);
}

monad<char>& is_it_capitalized(char c) {
  return isupper(c) ?
    monad<char>::return_value('y') :
    monad<char>::return_value('n');
}
monad<unit>& program(monad<unit>& start)
{
  return (((start >>= read_character) >>= is_it_capitalized) >>= write_character);
}

int main(void)
{
  monad<unit>& result = program(monad<unit>::return_value(unit()));
  unit end = result.execute();
  (void)(end);
  return 0;
}