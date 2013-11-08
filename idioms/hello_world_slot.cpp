#include <iostream>
#include <boost/signals2/signal.hpp>

struct HelloWorld {
  void operator()() const {
    std::cout << "Hello, World!" << std::endl;
  }
};

int main() {
  boost::signals2::signal<void ()> sig;

  HelloWorld hello;
  sig.connect(hello);

  sig();

  return 0;
};
