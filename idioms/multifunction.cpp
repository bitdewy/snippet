
#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/builtin.hpp>
#include <boost/type_erasure/callable.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/variant.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/range/algorithm.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::type_erasure;
namespace phoenix = boost::phoenix;

template<class... Sig>
using multifunction =
  any<
    mpl::vector<
      copy_constructible<>,
      typeid_<>,
      relaxed,
      callable<Sig>...
    >
  >;

typedef boost::make_recursive_variant<
  int,
  double,
  std::string,
  std::vector<boost::recursive_variant_>
>::type variant_type;

typedef std::vector<variant_type> vector_type;

typedef multifunction<void(int), void(double), void(std::string)> function_type;

class variant_handler {
 public:
  void handle(const variant_type& arg) {
    boost::apply_visitor(impl, arg);
  }

  void set_handler(function_type f) {
    impl.f = f;
  }
  
 private:
  // A class that works with boost::apply_visitor
  struct dispatcher : boost::static_visitor<void> {
    // used for the leaves
    template<class T>
    void operator()(const T& t) { f(t); }
    // For a vector, we recursively operate on the elements
    void operator()(const vector_type& v) {
      boost::for_each(v, boost::apply_visitor(*this));
    }

    function_type f;
  };

  dispatcher impl;
};

int main() {
  variant_handler x;
  x.set_handler(std::cout << phoenix::val("Value: ") << phoenix::placeholders::_1 << std::endl);

  x.handle(1);
  x.handle(2.718);
  x.handle("The quick brown fox jumps over the lazy dog.");
  x.handle(vector_type{ 1.618, "Gallia est omnis divisa in partes tres", 42 });
  return 0;
}
