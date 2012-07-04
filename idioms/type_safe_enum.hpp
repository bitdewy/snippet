//
#ifndef BITDEWY_TYPE_SAFE_ENUM_H_
#define BITDEWY_TYPE_SAFE_ENUM_H_

template<typename def, typename inner = typename def::type>
class safe_enum : public def
{
  typedef typename def::type type;
  inner val;

public:
  safe_enum(type v) : val(v) {}

  bool operator == (const safe_enum& s) const { return this->val == s.val; }
  bool operator != (const safe_enum& s) const { return this->val != s.val; }
};

#endif

// usage:
//struct color_def {
//  enum type { red, green, blue };
//};
//typedef safe_enum<color_def> color;
//
//struct shape_def {
//  enum type { circle, square, triangle };
//};
//typedef safe_enum<shape_def> shape;
//
//int main(void)
//{
//  color c = color::red;
//  bool flag = (c != shape::triangle);  // Compiler error.
//  return 0;
//}

