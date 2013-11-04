#include <iostream>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/typeof/std/ostream.hpp>
#include <boost/proto/proto.hpp>

namespace mpl = boost::mpl;
namespace proto = boost::proto;
namespace fusion = boost::fusion;
using proto::_;

namespace mini_lambda {
struct at : proto::callable {
  template<class Sig>
  struct result;

  template<class This, class Vector, class N>
  struct result<This(Vector, N)>
    : fusion::result_of::at<
      typename boost::remove_reference<Vector>::type,
      typename boost::remove_reference<N>::type
    >
  {};

  template<class Vector, class N>
  typename fusion::result_of::at<Vector const, N>::type
    operator()(Vector const &vector, N) const {
    return fusion::at<N>(vector);
  }
};

template<class N>
struct placeholder {
  typedef N type;
  typedef typename N::tag tag;
  typedef typename N::next next;
  typedef typename N::prior prior;
  typedef typename N::value_type value_type;
  static const value_type value = N::value;
};

namespace keyword {
  struct if_ {};
  struct else_ {};
  struct do_ {};
  struct while_ {};
  struct try_ {};
  struct catch_ {};
}

struct eval_if_else;

template<class E>
struct expression;

struct grammar
  : proto::or_<
      proto::when<
        proto::terminal<placeholder<_> >, at(proto::_data, proto::_value)
      >,
      proto::when<
        proto::subscript<
          proto::member<
            proto::subscript<
              proto::function<
                proto::terminal<keyword::if_>, grammar
              >,
              grammar
            >,
            proto::terminal<keyword::else_>
          >,
          grammar
        >,
        eval_if_else(proto::_right(proto::_left(proto::_left(proto::_left))),
        proto::_right(proto::_left(proto::_left)),
        proto::_right,
        proto::_data)
      >,
      proto::otherwise<proto::_default<grammar> >
    >{};

struct eval_if_else : proto::callable {
  typedef void result_type;

  template<typename If, typename Then, typename Else, typename Args>
  void operator()(
    If const &if_,
    Then const &then_,
    Else const &else_,
    Args const &args) const {
    if(grammar()(if_, 0, args)) {
      grammar()(then_, 0, args);
    } else {
      grammar()(else_, 0, args);
    }
  }
};

struct domain
  : proto::domain<proto::pod_generator<expression> > {};

struct arity_of
  : proto::or_<
      proto::when<
        proto::terminal< placeholder<_> >,
        mpl::next<proto::_value>()
      >,
      proto::when<
        proto::terminal<_>,
        mpl::int_<0>()
      >,
      proto::otherwise<
        proto::fold<_,
          mpl::int_<0>(),
          mpl::max<arity_of, proto::_state>()
        >
      >
    >{};

template<class E>
struct expression {
  BOOST_PROTO_BASIC_EXTENDS(E, expression<E>, domain)
  BOOST_PROTO_EXTENDS_ASSIGN()
  BOOST_PROTO_EXTENDS_SUBSCRIPT()

  BOOST_PROTO_EXTENDS_MEMBERS(
    ((keyword::else_,   else_))
    ((keyword::while_,  while_))
    ((keyword::catch_,  catch_))
  )

  static int const arity = boost::result_of<arity_of(E)>::type::value;

  typename mpl::eval_if_c<
    0 != arity,
    mpl::identity<void>,
    boost::result_of<grammar(E const &, int const &, fusion::vector<> &)>
  >::type

  operator()() const {
    BOOST_MPL_ASSERT_RELATION(arity, ==, 0);
    fusion::vector<> args;
    return grammar()(proto_base(), 0, args);
  }

#define BOOST_PROTO_LOCAL_MACRO(                  \
  N, typename_A, A_const_ref, A_const_ref_a, a)   \
  template<typename_A(N)>                         \
  typename boost::result_of<grammar(              \
    E const &,                                    \
    int const &,                                  \
    fusion::vector<A_const_ref(N)> &)             \
  >::type                                         \
  operator()(A_const_ref_a(N)) const {            \
    BOOST_MPL_ASSERT_RELATION(arity, <=, N);      \
    fusion::vector<A_const_ref(N)> args(a(N));    \
    return grammar()(proto_base(), 0, args);      \
  }

#define BOOST_PROTO_LOCAL_a       BOOST_PROTO_a
#define BOOST_PROTO_LOCAL_LIMITS  (1, 3)
#include BOOST_PROTO_LOCAL_ITERATE()
};

namespace placeholders {
  typedef placeholder<mpl::int_<0> > _1_t;
  typedef placeholder<mpl::int_<1> > _2_t;
  typedef placeholder<mpl::int_<2> > _3_t;

  expression<proto::terminal<_1_t>::type> const _1 = {{{}}};
  expression<proto::terminal<_2_t>::type> const _2 = {{{}}};
  expression<proto::terminal<_3_t>::type> const _3 = {{{}}};

  template<typename E>
  typename proto::result_of::make_expr<proto::tag::function, domain,
    keyword::if_,
    E const &
  >::type const
  if_(E const &e) {
    return proto::make_expr<proto::tag::function, domain>(
      keyword::if_(),
      boost::ref(e));
  }
}

using placeholders::if_;
}

int main()
{
  using namespace mini_lambda::placeholders;

  if_(_1 > 0)[
    std::cout << _2 << '\n'
  ].else_[
    std::cout << _3 << '\n'
  ] 
  (-42, "positive", "non-positive");

  BOOST_MPL_ASSERT_RELATION(sizeof(_1), ==, 2);

  return 0;
}
