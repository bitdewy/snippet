class MakeFinal
{
  ~MakeFinal() {}  // private by default.
  friend class sealed;
};

class sealed : virtual MakeFinal
{ };

class test : public sealed
{ };

int main (void)
{
  test t;  // Compilation error here.
}
