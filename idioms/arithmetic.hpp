#ifndef BITDEWY_ARITHMETIC_H_
#define BITDEWY_ARITHMETIC_H_

#include <iostream>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

namespace bitdewy {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct arithmetic : qi::grammar<Iterator, double(), ascii::space_type> {
  arithmetic() : arithmetic::base_type(expr) {
    using qi::double_;
    using namespace qi::labels;

    // EBNF
    // expr -> term [ ('+' | '-') term ]*
    // term -> factor [ ('*' | '/') factor ]*
    // factor -> number | '(' expr ')' | (('+' | '-') factor)
    // number -> real number

    expr =
      term                [_val = _1]
      >> *( ('+' >> term  [_val += _1])
          | ('-' >> term  [_val -= _1])
          )
      ;

    term =
      factor                [_val = _1]
      >> *( ('*' >> factor  [_val *= _1])
          | ('/' >> factor  [_val /= _1])
          )
      ;

    factor =
      double_           [_val = _1]
      | '(' >> expr     [_val = _1] >> ')'
      | ('+' >> factor  [_val = _1])
      | ('-' >> factor  [_val = -_1])
      ;
  }
  qi::rule<Iterator, double(), ascii::space_type> expr;
  qi::rule<Iterator, double(), ascii::space_type> term;
  qi::rule<Iterator, double(), ascii::space_type> factor;
};

}  // namespace bitdewy

#endif  // BITDEWY_ARITHMETIC_H_

// usage...
// int main()
// {
//   using boost::spirit::qi::eps;
//   using boost::spirit::qi::int_;
//   using boost::spirit::qi::_1;
//   using boost::spirit::ascii::space;
//   using boost::spirit::qi::phrase_parse;
//   namespace phx = boost::phoenix;
//   double result;
//   std::string str ="-123 + (1 + 24 / 6) * 5 - 2";
//   std::string::const_iterator iter = str.begin();
//   std::string::const_iterator end = str.end();
//   bitdewy::arithmetic<std::string::const_iterator> arithmetic;
//   bool r = phrase_parse(iter, end, arithmetic, space, result);
//   std::cout << result << std::endl;
//   return 0;
// }
