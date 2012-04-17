// type selection idioms is mentioned in <Morden C++ Design> section 2.6
// implement in Loki
// http://loki-lib.svn.sourceforge.net/viewvc/loki-lib/trunk/include/loki/TypeManip.h

template <bool, class L, class R>
struct IF  // primary template
{
  typedef R type;
};

template <class L, class R>
struct IF<true, L, R>  // partial specialization
{
  typedef L type;
};

IF<false, int, long>::type i;  // is equivalent to long i;
IF<true, int, long>::type i;  // is equivalent to int i;

template <class T, unsigned int CAPACITY>
class Queue
{
  T array[CAPACITY];
  IF<(CAPACITY <= 256),
      unsigned char,
      typename IF<(CAPACITY <= 65536),
                  unsigned short,
                  unsigned int
                 >::type
    >::type size;
  // ...
};
