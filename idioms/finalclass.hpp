// Note that error occurs only when the test class is instantiated.
// As long as the test class is not instantiated and it accesses only the static
// members of the sealed class, compiler does not complain.

#ifndef BITDEWY_FINALCLASS_H_
#define BItDEWY_FINALCLASS_H_

template <typename T>
class MakeFinal {
  MakeFinal() { }  // private by default.
  friend T;
};

#endif

// usage:
// sealed is final class
// virtual inherit, ensure MakeFinal's constructor called in derived-most class
//class sealed : virtual MakeFinal<sealed>
//{ };
//
//class test : public sealed
//{ };
//
//int main()
//{
//  test t;  // Compilation error here.
//  return 0;
//}

